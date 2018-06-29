#include "task_engine/dag.h"

dag_t* dag_new() {
	return NULL;
}

int dag_add(dag_t* dag, task_t* task, task_t** dependencies, uint16_t n_dependencies) {
	return -1;
}

int dag_run(dag_t* dag, task_server_t* task_server) {
	return -1;
}

void dag_delete(dag_t* dat) { }
