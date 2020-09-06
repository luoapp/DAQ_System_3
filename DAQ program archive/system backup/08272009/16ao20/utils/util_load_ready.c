// $URL: http://subversion:8080/svn/gsc/trunk/drivers/LINUX/16AO20/16AO20_Linux_2.x.x.x_GSC_DN/utils/util_load_ready.c $
// $Rev: 2014 $
// $Date: 2009-05-19 12:39:09 -0500 (Tue, 19 May 2009) $

#include <stdio.h>
#include <string.h>

#include "16ao20_dsl.h"
#include "16ao20_utils.h"
#include "gsc_utils.h"



/******************************************************************************
*
*	Function:	ao20_load_ready
*
*	Purpose:
*
*		Get the Load Ready state.
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

int	ao20_load_ready(int fd, int index, __s32* get)
{
	char	buf[128];
	int		errs	= 0;
	__s32	set;

	gsc_label_index("Load Ready", index);
	errs	+= ao20_dsl_ioctl(fd, AO20_IOCTL_LOAD_READY, &set);

	switch (set)
	{
		default:

			sprintf(buf, "INVALID: %ld", (long) set);
			break;

		case AO20_LOAD_READY_NO:

			strcpy(buf, "No, Not Ready");
			break;

		case AO20_LOAD_READY_YES:

			strcpy(buf, "Yes, Ready");
			break;
	}

	printf("%s  (%s)\n", errs ? "FAIL <---" : "PASS", buf);

	if (get)
		get[0]	= set;

	return(errs);
}


