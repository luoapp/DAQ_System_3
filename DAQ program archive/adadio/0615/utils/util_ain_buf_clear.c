// $URL: http://subversion:8080/svn/gsc/trunk/drivers/LINUX/ADADIO/ADADIO_Linux_3.x.x.x_GSC_DN/utils/util_ain_buf_clear.c $
// $Rev: 1620 $
// $Date: 2009-04-10 11:41:41 -0500 (Fri, 10 Apr 2009) $

#include <stdio.h>
#include <string.h>

#include "adadio_dsl.h"
#include "adadio_utils.h"
#include "gsc_utils.h"



/******************************************************************************
*
*	Function:	adadio_ain_buf_clear
*
*	Purpose:
*
*		Provide a visual wrapper for the ADADIO_IOCTL_AIN_BUF_CLEAR service.
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

int	adadio_ain_buf_clear(int fd, int index)
{
	int	errs;

	gsc_label_index("Input Buffer Clear", index);
	errs	= adadio_dsl_ioctl(fd, ADADIO_IOCTL_AIN_BUF_CLEAR, NULL);
	printf("%s\n", errs ? "FAIL <---" : "PASS");
	return(errs);
}


