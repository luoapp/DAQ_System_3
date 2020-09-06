// $URL: http://subversion:8080/svn/gsc/trunk/drivers/gsc_common/linux/utils/gsc_util_count.c $
// $Rev: 1593 $
// $Date: 2009-03-29 12:49:08 -0500 (Sun, 29 Mar 2009) $

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

#include "gsc_utils.h"



/******************************************************************************
*
*	Function:	gsc_count_boards
*
*	Purpose:
*
*		Count the number of installed SIO4 boards.
*
*	Arguments:
*
*		base_name	The base name for the /proc file entry.
*
*	Returned:
*
*		> 0			The number of boards found.
*		== 0		No boards were found.
*		< 0			The number of errors encounterred here.
*
******************************************************************************/

int gsc_count_boards(const char* base_name)
{
	char		buf[1024];
	int			fd;
	const char*	key	= "boards: ";
	char*		ptr;
	int			qty	= 0;

	for (;;)	// A convenience loop.
	{
		gsc_label("Board Count");
		sprintf(buf, "/proc/%s", base_name);
		fd	= open(buf, S_IRUSR);

		if (fd == -1)
		{
			qty	= 0;
			printf("0      (no boards found)\n");
			break;
		}

		memset(buf, 0, sizeof(buf));
		read(fd, buf, sizeof(buf));
		buf[sizeof(buf) - 1]	= 0;
		close(fd);
		ptr	= strstr(buf, key);

		if (ptr)
		{
			ptr	+= strlen(key);
			qty	= atoi(ptr);
		}

		if (qty <= 0)
		{
			qty	= 0;
			printf("0      (no boards found)\n");
		}
		else
		{
			printf("%d\n", qty);
		}

		break;
	}

	return(qty);
}



