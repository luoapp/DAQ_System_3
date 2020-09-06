// $URL: http://subversion:8080/svn/gsc/trunk/drivers/LINUX/ADADIO/ADADIO_Linux_3.x.x.x_GSC_DN/utils/util_ain_buf_sts.c $
// $Rev: 1620 $
// $Date: 2009-04-10 11:41:41 -0500 (Fri, 10 Apr 2009) $

#include <stdio.h>
#include <string.h>

#include "adadio_dsl.h"
#include "adadio_utils.h"
#include "gsc_utils.h"



/******************************************************************************
*
*	Function:	adadio_ain_buf_sts
*
*	Purpose:
*
*		Provide a visual wrapper for the ADADIO_IOCTL_AIN_BUF_STS service.
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

int adadio_ain_buf_sts(int fd, int index, __s32* get)
{
	char	buf[128];
	int		errs;
	__s32	set		= -1;

	gsc_label_index("Input Buffer Status", index);
	errs	= adadio_dsl_ioctl(fd, ADADIO_IOCTL_AIN_BUF_STS, &set);

	switch (get[0])
	{
		default:

			sprintf(buf, "INVALID: %ld", (long) get[0]);
			break;

		case ADADIO_AIN_BUF_STS_EMPTY:

			strcpy(buf, "Empty");
			break;

		case ADADIO_AIN_BUF_STS_ALMOST_EMPTY:

			strcpy(buf, "Almost Empty");
			break;

		case ADADIO_AIN_BUF_STS_HALF_FULL:

			strcpy(buf, "Half Full");
			break;

		case ADADIO_AIN_BUF_STS_FULL:

			strcpy(buf, "Full");
			break;
	}

	printf("%s  (%s)\n", errs ? "FAIL <---" : "PASS", buf);

	if (get)
		get[0]	= set;

	return(errs);
}


