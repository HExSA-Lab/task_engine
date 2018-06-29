#ifndef PROPAGATE_H
#define PROPAGATE_H

#include <stdio.h>
#include <errno.h>

// call should return true on success
#define try(call)									\
	int ret = (call);								\
	/* if ret is not zero (success) (true) */		\
	if(!ret) {										\
		if (errno) {								\
			perror("");								\
		}											\
		printf("%s returned %d\n", #call, ret);		\
		return -1;									\
	}
/*
@summary expects call to be zero (success) (true)

Otherwise, this will print an error message arnd return -1 from the
caller's function.
*/

#define try_nneg(call)							\
	try((call) > 0)								\
/*
@summary expects call to be non-negative
*/

#define try_nnull(call)							\
	try((call) != NULL)							\
/*
@summary expects call to be non-null
*/

#endif
