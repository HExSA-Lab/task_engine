#include <check.h>
#include "task_engine/task_ctl.h"

START_TEST (test_name)
{
  /* unit test code */
}
END_TEST


int main(void) {
	const struct CMUnitTest tests[] = {
		cmocka_unit_test(null_test_success),
	};

	return cmocka_run_group_tests(tests, NULL, NULL);
}
