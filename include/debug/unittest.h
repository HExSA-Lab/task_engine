#ifndef UNITTEST_H
#define UNITTEST_H

#include <stdlib.h>
#include <stdbool.h>

/*
@summary this function family is like `assert`, but does not halt.
 */

#define unittest_assert(cond, message)							\
	unittest_assert_(cond  , message, __FILE__, __LINE__, #cond, NULL);

#define unittest_assert_eq(a, b, message)								\
	unittest_assert_(a == b, message, __FILE__, __LINE__, #a " == " #b, "fasle: %s == %s", #a, #b);

int unittest_assert_(bool cond, char const* message, char const* file, size_t line, char const* cond_str, char const* fmt, ...);
/*
@summary used like `assert` backend

@param message: format string for the var_args

@returns negative if unable to unittest or print the debug
information. `cond` being `false` doesn't count as a failure. This fn
could _successfully_ report that `cond` is `false`.
 */

#endif
