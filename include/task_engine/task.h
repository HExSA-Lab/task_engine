#ifndef TASK_H
#define TASK_H

#include <stdint.h>

typedef struct task_t_ task_t;
struct task_t_ {
	void (*__fn)(void*);
	int priority;
	int cpu;

	void** __inputs;
	uint16_t __n_inputs;

	void** __outputs;
	uint16_t __n_outputs;

	task_t** __depends_on;
	uint16_t __n_depends_on;
};

task_t* task_new(void (*fn)(void*), uint16_t n_inputs, uint16_t n_outputs);
void task_delete(task_t* task);

int test_task();

#endif
