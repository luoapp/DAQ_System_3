// $URL: http://subversion:8080/svn/gsc/trunk/drivers/LINUX/ADADIO/ADADIO_Linux_3.x.x.x_GSC_DN/utils/util_initialize.c $
// $Rev: 1620 $
// $Date: 2009-04-10 11:41:41 -0500 (Fri, 10 Apr 2009) $

#include <stdio.h>

#include "adadio_dsl.h"
#include "adadio_utils.h"
#include "gsc_utils.h"



/******************************************************************************
*
*	Function:	adadio_initialize_quiet
*
*	Purpose:
*
*		Provide a quiet wrapper for the ADADIO_IOCTL_INITIALIZE service.
*
*	Arguments:
*
*		fd		The handle to use to access the driver.
*
*	Returned:
*
*		>= 0	The number of errors encountered here.
*
******************************************************************************/

int	adadio_initialize_quiet(int fd)
{
	int	errs;

	errs	= adadio_dsl_ioctl(fd, ADADIO_IOCTL_INITIALIZE, NULL);
	errs	= (errs == 0) ? 0 : 1;
	return(errs);
}



/******************************************************************************
*
*	Function:	adadio_initialize
*
*	Purpose:
*
*		Provide a visual wrapper for the ADADIO_IOCTL_INITIALIZE service.
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

int	adadio_initialize(int fd, int index)
{
	int	errs;

	gsc_label_index("Initialize", index);
	errs	= adadio_initialize_quiet(fd);
	printf("%s\n", errs ? "FAIL <---" : "PASS");
	return(errs);
}


