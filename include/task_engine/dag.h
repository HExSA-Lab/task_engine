#ifndef DAG_H
#define DAG_H

#include "task_engine/task.h"
#include "task_engine/task_server.h"

typedef struct __node_t_ __node_t;
struct __node_t_ {
	uint16_t n_successors;
	__node_t* successors;
	uint16_t n_predecessors;
	__node_t* predecessors;
};

typedef struct {
	__node_t *base;
	__node_t *__frontier;
} dag_t;

dag_t* dag_new();
int dag_add(dag_t* dag, task_t* task, task_t** dependencies, uint16_t n_dependencies);
int dag_run(dag_t* dag, task_server_t* task_server);
void dag_delete(dag_t* dat);

int test_dag();

#endif
