// $URL: http://subversion:8080/svn/gsc/trunk/drivers/LINUX/ADADIO/ADADIO_Linux_3.x.x.x_GSC_DN/sbtest/dio_port_read.c $
// $Rev: 1620 $
// $Date: 2009-04-10 11:41:41 -0500 (Fri, 10 Apr 2009) $

#include <stdio.h>

#include "main.h"



//*****************************************************************************
static int _service_test(int fd)
{
	// There are no persistent bits to test.
	return(0);
}




//*****************************************************************************
static int _function_test(int fd)
{
	// Additional equipment is required to test this service.
	return(0);
}




/******************************************************************************
*
*	Function:	dio_port_read_test
*
*	Purpose:
*
*		Perform a test of the IOCTL service ADADIO_IOCTL_DIO_PORT_READ.
*
*	Arguments:
*
*		fd		The handle for the board to access.
*
*	Returned:
*
*		>= 0	The number of errors encounterred.
*
******************************************************************************/

int dio_port_read_test(int fd)
{
	int	errs	= 0;

	gsc_label("ADADIO_IOCTL_DIO_PORT_READ");
	errs	+= _service_test(fd);
	errs	+= _function_test(fd);

	if (errs == 0)
		printf("PASS\n");

	return(errs);
}


