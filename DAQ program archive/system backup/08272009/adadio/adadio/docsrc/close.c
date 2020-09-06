#include <errno.h>
#include <stdio.h>
#include <unistd.h>

#include "adadio_dsl.h"

int adadio_dsl_close(int fd)
{
	int	status;

	status	= close(fd);

	if (status == -1)
		printf("close() failure, errno = %d\n", errno);

	return(status);
}
