#include <stdio.h>
#include "task_engine/task_ctl.h"

int main() {
	printf("see how fast I go\n");
	for (unsigned int i = 0; i < 20; ++i) {
		do_stuff();
	}
	return 0;
}
