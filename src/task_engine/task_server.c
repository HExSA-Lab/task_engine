#include "task_engine/task_server.h"

task_server_t* task_server_new() {
	return NULL;
}

/* int __task_server_start_worker(task_server_t* task_server, int cpuid); */

/* int __task_server_do_work(task_server_t* task_server); */

int task_server_submit(task_server_t* task_server, task_t* task) {
	return -1;
}

int task_server_submit_group(task_server_t* task_server, task_t** tasks, uint16_t n_tasks) {
	return -1;
}

int task_server_is_done(task_server_t* task_server, task_t* task) {
	return -1;
}

void task_server_delete(task_server_t* task_server) { }
