#include <errno.h>
#include <stdio.h>

#include "16ao20_dsl.h"

int ao20_dsl_close(int fd)
{
	int	err;
	int	status;

	status	= close(fd);

	if (status == -1)
		printf("ERROR: close() failure, errno = %d\n", errno);

	err	= (status == -1) ? 1 : 0;
	return(err);
}
