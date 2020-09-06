#include <errno.h>
#include <stddef.h>
#include <stdio.h>
#include <unistd.h>

#include "adadio_dsl.h"

int adadio_dsl_read(int fd, __u32 *buf, size_t samples)
{
	size_t	bytes;
	int 	status;

	bytes	= samples * 4;
	status	= read(fd, buf, bytes);

	if (status >= 0)
		status	/= 4;
	else
		printf("read() failure, errno = %d\n", errno);

	return(status);
}
