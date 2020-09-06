// $URL: http://subversion:8080/svn/gsc/trunk/drivers/LINUX/16AO20/16AO20_Linux_2.x.x.x_GSC_DN/utils/util_buffer_status.c $
// $Rev: 2014 $
// $Date: 2009-05-19 12:39:09 -0500 (Tue, 19 May 2009) $

#include <stdio.h>
#include <string.h>

#include "16ao20_dsl.h"
#include "16ao20_utils.h"
#include "gsc_utils.h"



/******************************************************************************
*
*	Function:	ao20_buffer_status
*
*	Purpose:
*
*		Get the Frame Status.
*
*	Arguments:
*
*		fd		The handle to use to access the driver.
*
*		index	The index of the board to access. Ignore if < 0.
*
*		get		The current setting is recorded here, if not NULL.
*
*	Returned:
*
*		>= 0	The number of errors encountered here.
*
******************************************************************************/

int	ao20_buffer_status(int fd, int index, __s32* get)
{
	char	buf[128];
	int		errs	= 0;
	__s32	set;

	gsc_label_index("Buffer Status", index);
	errs	+= ao20_dsl_ioctl(fd, AO20_IOCTL_BUFFER_STATUS, &set);

	switch (set)
	{
		default:

			sprintf(buf, "INVALID: %ld", (long) set);
			break;

		case AO20_BUFFER_STATUS_EMPTY:

			strcpy(buf, "Empty");
			break;

		case AO20_BUFFER_STATUS_1Q_FULL:

			strcpy(buf, "< 1/4 Full");
			break;

		case AO20_BUFFER_STATUS_MEDIUM:

			strcpy(buf, "Medium");
			break;

		case AO20_BUFFER_STATUS_3Q_FULL:

			strcpy(buf, "> 3/4 Full");
			break;

		case AO20_BUFFER_STATUS_FULL:

			strcpy(buf, "Full");
			break;
	}

	printf("%s  (%s)\n", errs ? "FAIL <---" : "PASS", buf);

	if (get)
		get[0]	= set;

	return(errs);
}


