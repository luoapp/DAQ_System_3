// $URL: http://subversion:8080/svn/gsc/trunk/drivers/LINUX/ADADIO/ADADIO_Linux_3.x.x.x_GSC_DN/sbtest/ain_buf_clear.c $
// $Rev: 1620 $
// $Date: 2009-04-10 11:41:41 -0500 (Fri, 10 Apr 2009) $

#include <errno.h>
#include <stdio.h>
#include <unistd.h>

#include "main.h"



//*****************************************************************************
static int _service_test(int fd)
{
	int errs	= 0;

	// There are no persistent bits to test with this service.
	return(errs);
}



//*****************************************************************************
static int _function_test(int fd)
{
	static const service_data_t	list[]	=
	{
		{				// Enable Bursting
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	ADADIO_IOCTL_AIN_MODE,
			/* arg		*/	ADADIO_AIN_MODE_DIFF_BURST,
			/* reg		*/	-1,
			/* mask		*/	0,
			/* value	*/	0
		},
		{					// Set the buffer size.
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	ADADIO_IOCTL_AIN_BUF_SIZE,
			/* arg		*/	ADADIO_AIN_BUF_SIZE_8,
			/* reg		*/	-1,
			/* mask		*/	0,
			/* value	*/	0
		},
		{				// Verify that the buffer is empty
			/* service	*/	SERVICE_REG_TEST,
			/* cmd		*/	0,
			/* arg		*/	0,
			/* reg		*/	ADADIO_GSC_BCR,
			/* mask		*/	0x100000,
			/* value	*/	0x100000
		},
		{				// Get a burst of data.
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	ADADIO_IOCTL_AIN_TRIGGER,
			/* arg		*/	0,
			/* reg		*/	-1,
			/* mask		*/	0,
			/* value	*/	0
		},
		{				// Wait a moment
			/* service	*/	SERVICE_SLEEP,
			/* cmd		*/	0,
			/* arg		*/	1,
			/* reg		*/	-1,
			/* mask		*/	0,
			/* value	*/	0
		},
		{				// Verify that the buffer is full
			/* service	*/	SERVICE_REG_TEST,
			/* cmd		*/	0,
			/* arg		*/	0,
			/* reg		*/	ADADIO_GSC_BCR,
			/* mask		*/	0x400000,
			/* value	*/	0x400000
		},
		{				// Clear the buffer
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	ADADIO_IOCTL_AIN_BUF_CLEAR,
			/* arg		*/	0,
			/* reg		*/	-1,
			/* mask		*/	0,
			/* value	*/	0
		},
		{				// Verify that the buffer is empty
			/* service	*/	SERVICE_REG_TEST,
			/* cmd		*/	0,
			/* arg		*/	0,
			/* reg		*/	ADADIO_GSC_BCR,
			/* mask		*/	0x100000,
			/* value	*/	0x100000
		},

		{ SERVICE_END_LIST }
	};

	int errs	= 0;

	errs	+= adadio_initialize_quiet(fd);

	errs	+= service_ioctl_set_reg_list(fd, list);

	errs	+= adadio_initialize_quiet(fd);
	return(errs);
}




/******************************************************************************
*
*	Function:	ain_buf_clear_test
*
*	Purpose:
*
*		Perform a test of the IOCTL service ADADIO_IOCTL_AIN_BUF_CLEAR.
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

int ain_buf_clear_test(int fd)
{
	int	errs	= 0;

	gsc_label("ADADIO_IOCTL_AIN_BUF_CLEAR");
	errs	+= _service_test(fd);
	errs	+= _function_test(fd);

	if (errs == 0)
		printf("PASS\n");

	return(errs);
}


