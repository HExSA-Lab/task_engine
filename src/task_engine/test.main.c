#include <stdio.h>
#include "task_engine/task.h"
#include "task_engine/task_server.h"
#include "task_engine/dag.h"
#include "debug/unittest.h"

int main() {
	test_task();
	test_task_server();
	test_dag();
	return 0;
}
