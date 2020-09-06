// $URL: http://subversion:8080/svn/gsc/trunk/drivers/LINUX/ADADIO/ADADIO_Linux_3.x.x.x_GSC_DN/utils/util_ain_mode.c $
// $Rev: 1620 $
// $Date: 2009-04-10 11:41:41 -0500 (Fri, 10 Apr 2009) $

#include <stdio.h>
#include <string.h>

#include "adadio_dsl.h"
#include "adadio_utils.h"
#include "gsc_utils.h"



/******************************************************************************
*
*	Function:	adadio_ain_mode
*
*	Purpose:
*
*		Provide a visual wrapper for the ADADIO_IOCTL_AIN_MODE service.
*
*	Arguments:
*
*		fd		The handle to use to access the driver.
*
*		index	The index of the board to access. Ignore if < 0.
*
*		set		The setting to apply.
*
*		get		The current setting is recorded here, if not NULL.
*
*	Returned:
*
*		>= 0	The number of errors encountered here.
*
******************************************************************************/

int	adadio_ain_mode(int fd, int index, __s32 set, __s32* get)
{
	char	buf[128];
	int		errs;

	gsc_label_index("Analog Input Mode", index);
	errs	= adadio_dsl_ioctl(fd, ADADIO_IOCTL_AIN_MODE, &set);

	switch (set)
	{
		default:

			sprintf(buf, "INVALID: %ld", (long) set);
			break;

		case ADADIO_AIN_MODE_SE_CONT:

			strcpy(buf, "Single Ended, Continuous");
			break;

		case ADADIO_AIN_MODE_SE_BURST:

			strcpy(buf, "Single Ended, Burst");
			break;

		case ADADIO_AIN_MODE_DIFF_CONT:

			strcpy(buf, "Differential, Continuous");
			break;

		case ADADIO_AIN_MODE_DIFF_BURST:

			strcpy(buf, "Differential, Burst");
			break;

		case ADADIO_AIN_MODE_LB_TEST:

			strcpy(buf, "Loop Back Test");
			break;

		case ADADIO_AIN_MODE_VREF_TEST:

			strcpy(buf, "Vref Test");
			break;

		case ADADIO_AIN_MODE_ZERO_TEST:

			strcpy(buf, "Zero Test");
			break;
	}

	printf("%s  (%s)\n", errs ? "FAIL <---" : "PASS", buf);

	if (get)
		get[0]	= set;

	return(errs);
}


