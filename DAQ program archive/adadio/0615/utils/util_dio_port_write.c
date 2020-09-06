// $URL: http://subversion:8080/svn/gsc/trunk/drivers/LINUX/ADADIO/ADADIO_Linux_3.x.x.x_GSC_DN/utils/util_dio_port_write.c $
// $Rev: 1620 $
// $Date: 2009-04-10 11:41:41 -0500 (Fri, 10 Apr 2009) $

#include <stdio.h>
#include <string.h>

#include "adadio_dsl.h"
#include "adadio_utils.h"
#include "gsc_utils.h"



/******************************************************************************
*
*	Function:	adadio_dio_port_write
*
*	Purpose:
*
*		Provide a visual wrapper for the ADADIO_IOCTL_DIO_PORT_WRITE service.
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

int	adadio_dio_port_write(int fd, int index, __s32 set, __s32* get)
{
	int	errs;

	gsc_label_index("DIO Port Write", index);
	errs	= adadio_dsl_ioctl(fd, ADADIO_IOCTL_DIO_PORT_WRITE, &set);
	printf("%s  (0x%02lX)\n", errs ? "FAIL <---" : "PASS", (long) set);

	if (get)
		get[0]	= set;

	return(errs);
}


