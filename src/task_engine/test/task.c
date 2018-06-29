#include "task_engine/task.h"
#include "debug/unittest.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
void task_fn(void* in) { }
#pragma GCC diagnostic pop

int test_task() {
	task_t* task = task_new(&task_fn, 1, 1);
	unittest_assert(task != NULL, "can create task");
	task_delete(task);
	// valgrind will watch for memory leaks

	return 0;
}
