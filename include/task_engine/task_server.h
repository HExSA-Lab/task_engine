#ifndef TASK_CTL_H
#define TASK_CTL_H

#include <stdlib.h>
#include "task_engine/task.h"

typedef struct task_queue_node_t_ task_queue_node_t;
struct task_queue_node_t_ {
	task_t task;
	task_queue_node_t* next;
};

typedef struct {
	task_queue_node_t head;
	size_t size;
} task_queue_t;

typedef struct {
	task_queue_t __queue;
	int16_t __cores;
} task_server_t;

task_server_t* task_server_new();
int task_server_submit(task_server_t* task_server, task_t* task);
int task_server_submit_group(task_server_t* task_server, task_t** tasks, uint16_t n_tasks);
int task_server_is_done(task_server_t* task_server, task_t* task);
void task_server_delete(task_server_t* task_server);

int test_task_server();

#endif
