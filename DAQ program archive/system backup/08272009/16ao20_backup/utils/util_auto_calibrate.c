// $URL: http://subversion:8080/svn/gsc/trunk/drivers/LINUX/16AO20/16AO20_Linux_2.x.x.x_GSC_DN/utils/util_auto_calibrate.c $
// $Rev: 2014 $
// $Date: 2009-05-19 12:39:09 -0500 (Tue, 19 May 2009) $

#include <stdio.h>

#include "16ao20_dsl.h"
#include "16ao20_utils.h"
#include "gsc_utils.h"



/******************************************************************************
*
*	Function:	ao20_auto_calibrate
*
*	Purpose:
*
*		Perform an Auto-Calibration cycle.
*
*	Arguments:
*
*		fd		The handle to use to access the driver.
*
*		index	The index of the board to access. Ignore if < 0.
*
*	Returned:
*
*		>= 0	The number of errors encountered here.
*
******************************************************************************/

int	ao20_auto_calibrate(int fd, int index)
{
	int		errs	= 0;
	__s32	query;

	gsc_label_index("Auto-Calibrate", index);
	errs	+= ao20_query(fd,AO20_QUERY_AUTO_CAL_MS, &query);

	if (errs)
	{
	}
	else if (query)
	{
		errs	= ao20_dsl_ioctl(fd, AO20_IOCTL_AUTO_CALIBRATE, NULL);
		printf("%s\n", errs ? "FAIL <---" : "PASS");
	}
	else
	{
		printf("SKIPPED  (Not supported on this board.)\n");
	}

	return(errs);
}


