#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/ioctl.h>

#include "adadio_dsl.h"

int adadio_dsl_ioctl(int fd, int request, void *arg)
{
	int	status;

	status	= ioctl(fd, request, arg);

	if (status == -1)
		printf("ioctl() failure, errno = %d\n", errno);

	return(status);
}
