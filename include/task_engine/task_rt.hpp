#ifndef TASK_RT_HPP
#define TASK_RT_HPP

#include <cstdint>

typedef std::uint16_t input_id;
typedef std::uint16_t output_id;

class task_rt_t {
public:
	void* alloc(std::size_t) const;
	void* get_input(input_id input_id_) const;
	void set_output(output_id input_id_, void* val) const;
};

#endif
