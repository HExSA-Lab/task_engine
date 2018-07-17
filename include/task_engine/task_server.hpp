#ifndef TASK_SERVER_HPP
#define TASK_SERVER_HPP

#include "task_engine/task.hpp"

typedef enum {
	WAITING,
	RUNNING,
	DONE,
	NOT_FOUND,
	ERROR,
} task_status_t;

typedef std::uint16_t task_id;

template<typename task_queue_t>
class task_server_t {
public:
	task_server_t();
	task_id submit(const task_t& task);
	task_status_t check(task_id task) const;
	void free(void*) const;
private:
	task_queue_t queue;
};

// PRIVATE

template<typename task_queue_t>
task_server_t<task_queue_t>::task_server_t() : queue() {}

template<typename task_queue_t>
task_id task_server_t<task_queue_t>::submit(const task_t& task) {
	return 0;
}

template<typename task_queue_t>
task_status_t task_server_t<task_queue_t>::check(task_id task) const {
	return ERROR;
}

template<typename task_queue_t>
void task_server_t<task_queue_t>::free(void* ptr) const {}

#endif
