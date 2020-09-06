// $URL: http://subversion:8080/svn/gsc/trunk/drivers/gsc_common/linux/utils/gsc_util_close.c $
// $Rev: 1593 $
// $Date: 2009-03-29 12:49:08 -0500 (Sun, 29 Mar 2009) $

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#include "gsc_utils.h"



/******************************************************************************
*
*	Function:	gsc_dev_close
*
*	Purpose:
*
*		Perform a close on the device with the specified access handle.
*
*	Arguments:
*
*		index	The index of the board to accessed.
*
*		fd		The file descriptor used to access the device.
*
*	Returned:
*
*		None.
*
******************************************************************************/

void gsc_dev_close(unsigned int index, int fd)
{
	char	buf[80];
	int		i;

	sprintf(buf, "Closing #%u", index);
	gsc_label(buf);
	i	= close(fd);

	if (i == -1)
		printf("FAIL <--- (errno %d)\n", errno);
	else
		printf("PASS\n");
}



