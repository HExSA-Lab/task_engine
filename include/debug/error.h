#ifndef ERROR_H
#define ERROR_H

#include <stdio.h>
#include <errno.h>

#define try_true(call, error_val) {				\
	int ret = (call);							\
	if(!ret) {									\
		if (errno) {							\
			perror("");							\
		}										\
		printf("%s:%d: %s returned %d\n",		\
			   __FILE__, __LINE__, #call, ret);	\
		return error_val;						\
	}											\
}

/*
@summary expects call to be true

Otherwise, this will print an error message arnd return error_val from the
caller's function.
*/

#define try_zero(call, error_val)				\
	try_true(call == 0, error_val)
/*
@summary expects call to be zero. Returns error_val if it is.
 */

#define try_nneg(call, error_val)				\
	try_true((call) > 0, error_val)
/*
@summary expects call to be non-negative. Returns error_val if it is.
*/

#define try_nnull(call, error_val)				\
	try_true((call) != NULL, error_val)
/*
@summary expects call to be non-null. Returns error_val if it is.
*/

#endif
