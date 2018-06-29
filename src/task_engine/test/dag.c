#include "task_engine/dag.h"
#include "debug/unittest.h"

int a = 0;
int b = 0;

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
void task_fn1(void* _) {
	a = 1;
}

void task_fn2(void* _) {
	b = 2;
}

void task_fn3(void* _) {
	unittest_assert(a == 1 && b == 2, "respect prerequisite tasks");
}
#pragma GCC diagnostic pop

int test_dag() {
	dag_t* dag = dag_new();
	unittest_assert(dag != NULL, "can create dag");

	task_t* task1 = task_new(task_fn1, 0, 0);
	task_t* task2 = task_new(task_fn2, 0, 0);
	task_t* task3 = task_new(task_fn3, 0, 0);

	#define n_task3_deps 2
	task_t* task3_deps[n_task3_deps] = {task1, task2};

	dag_add(dag, task3, task3_deps, n_task3_deps);
	dag_add(dag, task1, NULL, 0);
	dag_add(dag, task2, NULL, 0);

	task_server_t* task_server = task_server_new();

	unittest_assert(dag_run(dag, task_server), "can run dag");

	dag_delete(dag);
	task_delete(task1);
	task_delete(task2);
	task_delete(task3);

	return 0;
}
