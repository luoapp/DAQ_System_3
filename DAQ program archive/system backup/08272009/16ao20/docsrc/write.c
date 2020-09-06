#include <errno.h>
#include <stdio.h>

#include "16ao20_dsl.h"

int ao20_dsl_write(int fd, const __u32 *buf, size_t samples)
{
	size_t	bytes;
	int		status;

	bytes	= samples * 4;
	status	= write(fd, buf, bytes);

	if (status == -1)
		printf("ERROR: write() failure, errno = %d\n", errno);
	else
		status	/= 4;

	return(status);
}
