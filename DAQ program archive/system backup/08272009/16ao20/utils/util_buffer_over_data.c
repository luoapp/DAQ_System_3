// $URL: http://subversion:8080/svn/gsc/trunk/drivers/LINUX/16AO20/16AO20_Linux_2.x.x.x_GSC_DN/utils/util_buffer_over_data.c $
// $Rev: 2014 $
// $Date: 2009-05-19 12:39:09 -0500 (Tue, 19 May 2009) $

#include <stdio.h>
#include <string.h>

#include "16ao20_dsl.h"
#include "16ao20_utils.h"
#include "gsc_utils.h"



/******************************************************************************
*
*	Function:	ao20_buffer_over_data
*
*	Purpose:
*
*		Set and/or get the Buffer Overflow state.
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

int	ao20_buffer_over_data(int fd, int index, __s32 set, __s32* get)
{
	char	buf[128];
	int		errs	= 0;

	gsc_label_index("Buffer Overflow", index);

	if (set == -1)
	{
		errs	+= ao20_dsl_ioctl(fd, AO20_IOCTL_BUFFER_OVER_DATA, &set);
	}
	else
	{
		errs	+= ao20_dsl_ioctl(fd, AO20_IOCTL_BUFFER_OVER_DATA, &set);
		set		= -1;
		errs	+= ao20_dsl_ioctl(fd, AO20_IOCTL_BUFFER_OVER_DATA, &set);
	}

	if (set)
		strcpy(buf, "Yes");
	else
		strcpy(buf, "No");

	printf("%s  (%s)\n", errs ? "FAIL <---" : "PASS", buf);

	if (get)
		get[0]	= set;

	return(errs);
}


