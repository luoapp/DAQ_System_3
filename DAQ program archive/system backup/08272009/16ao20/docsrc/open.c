#include <errno.h>
#include <fcntl.h>
#include <stdio.h>

#include "16ao20_dsl.h"

int ao20_dsl_open(unsigned int board)
{
	int		fd;
	char	name[80];

	sprintf(name, AO20_DEV_BASE_NAME "%u", board);
	fd	= open(name, O_RDWR);

	if (fd == -1)
	{
		printf(	"ERROR: open() failure on %s, errno = %d\n",
				name,
				errno);
	}

	return(fd);
}
