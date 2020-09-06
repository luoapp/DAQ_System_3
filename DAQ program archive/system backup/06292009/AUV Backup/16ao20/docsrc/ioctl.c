#include <errno.h>
#include <stdio.h>
#include <sys/ioctl.h>

#include "16ao20_dsl.h"

int ao20_dsl_ioctl(int fd, int request, void *arg)
{
	int	err;
	int	status;

	status	= ioctl(fd, request, arg);

	if (status == -1)
		printf("ERROR: ioctl() failure, errno = %d\n", errno);

	err	= (status == -1) ? 1 : 0;
	return(err);
}
