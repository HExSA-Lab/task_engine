#include <thread>
#include <chrono>
#include "debug/unittest.h"
#include "task_engine/task_server.hpp"
#include "task_engine/task.hpp"
#include "task_engine/task_rt.hpp"
#include "task_engine/queue.hpp"

// The inputs are mapped to unique integers here
// so a task can take essentially "named" inputs.
// This is needed instead of one void pointers (as done in pthreads),
// because it allows some of the tasks input to come from task A
// and other of it to come from task B.
// It could even keep executing until it tries to get_input an input that has not yet been set.
const input_id pythag_input_a = 0;
const input_id pythag_input_b = 1;

// For similar reasons, we have "named" outputs
const output_id pythag_output_hypot = 0;
const output_id pythag_output_sum = 1;

// pythag will be wrapped in task
void pythag(const task_rt_t& task_rt) {

	// task_rt is the runtime the task_fn sees
	// The task_fn can ask it for input, set output, etc.

	int* a = (int*) task_rt.get_input(pythag_input_a);
	int* b = (int*) task_rt.get_input(pythag_input_b);

	int* sum = (int*) task_rt.alloc(sizeof(int));
	*sum = (*a) + (*b);
	task_rt.set_output(pythag_output_sum, sum);

	int* hypot = (int*) task_rt.alloc(sizeof(int));
	*hypot = (*a)*(*a) + (*b)*(*b);
	task_rt.set_output(pythag_output_hypot, hypot);
}

int test_task_engine() {
	task_server_t<queue_t<task_t>> task_server;

	// create the task
	int a = 3, b = 4;
	task_t task (pythag);
	task.set_input(pythag_input_a, &a);
	task.set_input(pythag_input_b, &b);

	task_id taskid = task_server.submit(task);

	for(int i = 0; i < 100 or task_server.check(taskid) == DONE; ++i) {
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}

	int* sum = (int*) task.get_output(pythag_output_sum);
	int* hypot = (int*) task.get_output(pythag_output_hypot);

	unittest_assert_eq(*hypot, 25, NULL);
	unittest_assert_eq(*sum, 7, NULL);

	// It is the caller's responsibility to delete input and output.
	// Since it was allocated by task_rt, task_server should know how to free it.
	// (It might not be a regular malloc/free)
	task_server.free(sum);
	task_server.free(hypot);

	return 0;
}
