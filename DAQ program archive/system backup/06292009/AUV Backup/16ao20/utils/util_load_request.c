// $URL: http://subversion:8080/svn/gsc/trunk/drivers/LINUX/16AO20/16AO20_Linux_2.x.x.x_GSC_DN/utils/util_load_request.c $
// $Rev: 2014 $
// $Date: 2009-05-19 12:39:09 -0500 (Tue, 19 May 2009) $

#include <stdio.h>
#include <string.h>

#include "16ao20_dsl.h"
#include "16ao20_utils.h"
#include "gsc_utils.h"



/******************************************************************************
*
*	Function:	ao20_load_request
*
*	Purpose:
*
*		Set and/or get the Load Request setting.
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

int	ao20_load_request(int fd, int index)
{
	int	errs;

	gsc_label_index("Clock Enable", index);
	errs	= ao20_dsl_ioctl(fd, AO20_IOCTL_LOAD_REQUEST, NULL);
	printf("%s\n", errs ? "FAIL <---" : "PASS");

	return(errs);
}


