#include <stdarg.h>
#include <stdio.h>
#include <stdbool.h>
#include "debug/error.h"
#include "debug/unittest.h"

int unittest_assert_(bool cond, char const* file, size_t line, char const* cond_str, char const* message, ...);
/*
@summary used like `assert` backend

@param message: format string for the var_args

@returns negative if unable to unittest or print the debug
information. `cond` being `false` doesn't count as a failure. This fn
could _successfully_ report that `cond` is `false`.
 */

int unittest_assert_(bool cond, char const* file, size_t line, char const* cond_str, char const* message, ...) {
	if(!cond) {
		try_nneg(printf("Unittest failed: %s:%ld: %s\n", file, line, cond_str));
		if(message) {
			va_list vargs;
			va_start(vargs, message);
			try_nneg(printf(message, vargs));
			va_end(vargs);
		}
	}
	return 0;
}
