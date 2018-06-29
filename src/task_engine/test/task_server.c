#include <unistd.h>
#include "task_engine/task_server.h"
#include "debug/unittest.h"

int a;

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
void set_a(void* _) {
#pragma GCC diagnostic pop
	a = 5;
}

int test_task_server() {
	a = 2;

	task_t* task = task_new(set_a, 0, 0);

	task_server_t* task_server = task_server_new();
	unittest_assert(task_server != NULL, "create server");

	unittest_assert(
		task_server_submit(task_server, task),
		"can submit task to server"
	);

	while(!task_server_is_done(task_server, task)) {
		sleep(50);
	}

	unittest_assert(a == 5, "server does task");

	task_server_delete(task_server);
	task_delete(task);

	return 0;
}
