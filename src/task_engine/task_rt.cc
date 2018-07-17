#include "task_engine/task_rt.hpp"

void* task_rt_t::alloc(std::size_t size) const {
	return new char[size];
}

void* task_rt_t::get_input(input_id input_id) const {
	return nullptr;
}

void task_rt_t::set_output(output_id output_id, void* val) const {
}
