#ifndef TASK_HPP
#define TASK_HPP

#include "task_engine/task_rt.hpp"

class task_t {
public:
	task_t(void (*fn_)(const task_rt_t& task_rt));
	// TODO: add priority and core no
	void set_input(input_id input_id_, void* input_);
	void* get_output(output_id output_id_);
	// TODO: set input of one task to be the output of another
private:
	void (*fn)(const task_rt_t& task_rt);
};

task_t::task_t(void (*fn_)(const task_rt_t& task_rt)) {
	fn = fn_;
}

void task_t::set_input(input_id input_id_, void* input_) {
}

void* task_t::get_output(output_id output_id_) {
	return nullptr;
}

#endif
