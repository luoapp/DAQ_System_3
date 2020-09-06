// $URL: http://subversion:8080/svn/gsc/trunk/drivers/gsc_common/linux/utils/gsc_util_open.c $
// $Rev: 1593 $
// $Date: 2009-03-29 12:49:08 -0500 (Sun, 29 Mar 2009) $

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>

#include "gsc_utils.h"



/******************************************************************************
*
*	Function:	gsc_dev_open
*
*	Purpose:
*
*		Perform an open on the device with the specified index.
*
*	Arguments:
*
*		index		The index of the board to accessed.
*
*		base_name	The base name for the /proc file entry.
*
*	Returned:
*
*		>= 0		The handle to the board to access.
*		-1			There was a problem. Consult errno.
*
******************************************************************************/

int gsc_dev_open(unsigned int index, const char* base_name)
{
	char	buf[80];
	int		fd;
	char	name[128];

	sprintf(buf, "Opening #%u", index);
	gsc_label(buf);
	sprintf(name, "/dev/%s%u", base_name, index);
	fd	= open(name, O_RDWR);

	if (fd == -1)
		printf("FAIL <--- (errno %d)\n", errno);
	else
		printf("PASS\n");

	return(fd);
}


