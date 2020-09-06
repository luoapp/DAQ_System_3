// $URL: http://subversion:8080/svn/gsc/trunk/drivers/LINUX/ADADIO/ADADIO_Linux_3.x.x.x_GSC_DN/sbtest/dio_port_write.c $
// $Rev: 1620 $
// $Date: 2009-04-10 11:41:41 -0500 (Fri, 10 Apr 2009) $

#include <stdio.h>

#include "main.h"



//*****************************************************************************
static int _service_test(int fd)
{
	static const service_data_t	list[]	=
	{
		{
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	ADADIO_IOCTL_DIO_PORT_DIR,
			/* arg		*/	ADADIO_DIO_PORT_DIR_OUTPUT,
			/* reg		*/	-1,
			/* mask		*/	0,
			/* value	*/	0
		},
		{
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	ADADIO_IOCTL_DIO_PORT_WRITE,
			/* arg		*/	0xFF,
			/* reg		*/	ADADIO_GSC_DIOPR,
			/* mask		*/	0xFF,
			/* value	*/	0xFF
		},
		{
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	ADADIO_IOCTL_DIO_PORT_WRITE,
			/* arg		*/	0x00,
			/* reg		*/	ADADIO_GSC_DIOPR,
			/* mask		*/	0xFF,
			/* value	*/	0x00
		},
		{
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	ADADIO_IOCTL_DIO_PORT_WRITE,
			/* arg		*/	0xAA,
			/* reg		*/	ADADIO_GSC_DIOPR,
			/* mask		*/	0xFF,
			/* value	*/	0xAA
		},
		{
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	ADADIO_IOCTL_DIO_PORT_WRITE,
			/* arg		*/	0x55,
			/* reg		*/	ADADIO_GSC_DIOPR,
			/* mask		*/	0xFF,
			/* value	*/	0x55
		},
		{
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	ADADIO_IOCTL_DIO_PORT_WRITE,
			/* arg		*/	0x0F,
			/* reg		*/	ADADIO_GSC_DIOPR,
			/* mask		*/	0xFF,
			/* value	*/	0x0F
		},
		{
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	ADADIO_IOCTL_DIO_PORT_WRITE,
			/* arg		*/	0xF0,
			/* reg		*/	ADADIO_GSC_DIOPR,
			/* mask		*/	0xFF,
			/* value	*/	0xF0
		},
		{
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	ADADIO_IOCTL_DIO_PORT_WRITE,
			/* arg		*/	0x00,
			/* reg		*/	ADADIO_GSC_DIOPR,
			/* mask		*/	0xFF,
			/* value	*/	0x00
		},

		{ SERVICE_END_LIST }
	};

	int errs	= 0;

	errs	+= adadio_initialize_quiet(fd);

	errs	+= service_ioctl_set_reg_list(fd, list);
	errs	+= service_ioctl_reg_get_list(fd, list);

	errs	+= service_ioctl_set_reg_list(fd, list);
	errs	+= service_ioctl_reg_get_list(fd, list);

	errs	+= adadio_initialize_quiet(fd);
	return(errs);
}




//*****************************************************************************
static int _function_test(int fd)
{
	// Additional equipment is required to test this service.
	return(0);
}




/******************************************************************************
*
*	Function:	dio_port_write_test
*
*	Purpose:
*
*		Perform a test of the IOCTL service ADADIO_IOCTL_DIO_PORT_WRITE.
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

int dio_port_write_test(int fd)
{
	int	errs	= 0;

	gsc_label("ADADIO_IOCTL_DIO_PORT_WRITE");
	errs	+= _service_test(fd);
	errs	+= _function_test(fd);

	if (errs == 0)
		printf("PASS\n");

	return(errs);
}


