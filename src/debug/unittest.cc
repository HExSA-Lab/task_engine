#include <stdarg.h>
#include <stdio.h>
#include "debug/error.h"
#include "debug/unittest.h"

int unittest_assert_(bool cond, char const* message, char const* file, size_t line, char const* cond_str, char const* fmt, ...) {
	if(!cond) {
		if(message == NULL) {
			message = "";
		}
		try_nneg(
				 printf("Unittest [%s] failed\n%s:%ld: %s\n", message, file, line, cond_str),
				 -1);
		if(fmt) {
			va_list vargs;
			va_start(vargs, fmt);
			try_nneg(
					 vprintf(fmt, vargs),
					 -1);
			va_end(vargs);
		}
		try_nneg(puts(""), -1);
	}
	return 0;
}
