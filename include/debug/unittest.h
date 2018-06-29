#ifndef UNITTEST_H
#define UNITTEST_H

/*
@summary this function family is like `assert`, but does not halt.
 */

#define unittest_assert(cond) \
	unittest_bool_(cond  , __FILE__, __LINE__, #cond, NULL);

#define unittest_assert_eq(a, b) \
	unittest_bool_(a == b, __FILE__, __LINE__, #a " == " #b, "%s != %s", #a, #b);

#endif
