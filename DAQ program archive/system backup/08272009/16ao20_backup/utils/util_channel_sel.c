// $URL: http://subversion:8080/svn/gsc/trunk/drivers/LINUX/16AO20/16AO20_Linux_2.x.x.x_GSC_DN/utils/util_channel_sel.c $
// $Rev: 2014 $
// $Date: 2009-05-19 12:39:09 -0500 (Tue, 19 May 2009) $

#include <stdio.h>
#include <string.h>

#include "16ao20_dsl.h"
#include "16ao20_utils.h"
#include "gsc_utils.h"



/******************************************************************************
*
*	Function:	ao20_channel_sel_quiet
*
*	Purpose:
*
*		Set and/or get the Channel Select setting.
*
*	Arguments:
*
*		fd		The handle to use to access the driver.
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

int ao20_channel_sel_quiet(int fd, __s32 set, __s32* get)
{
	int		errs	= 0;

	errs	= ao20_dsl_ioctl(fd, AO20_IOCTL_CHANNEL_SEL, &set);

	if (get)
		get[0]	= set;

	return(errs);
}


/******************************************************************************
*
*	Function:	ao20_channel_sel
*
*	Purpose:
*
*		Set and/or get the Channel Select setting.
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

int ao20_channel_sel(int fd, int index, __s32 set, __s32* get)
{
	int		errs	= 0;

	gsc_label_index("Channel Selections", index);
	errs	= ao20_dsl_ioctl(fd, AO20_IOCTL_CHANNEL_SEL, &set);
	printf("%s  (Channels 0x%lX)\n", errs ? "FAIL <---" : "PASS", (long) set);

	if (get)
		get[0]	= set;

	return(errs);
}


