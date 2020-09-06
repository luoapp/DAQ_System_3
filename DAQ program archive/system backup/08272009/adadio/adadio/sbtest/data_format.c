// $URL: http://subversion:8080/svn/gsc/trunk/drivers/LINUX/ADADIO/ADADIO_Linux_3.x.x.x_GSC_DN/sbtest/data_format.c $
// $Rev: 1620 $
// $Date: 2009-04-10 11:41:41 -0500 (Fri, 10 Apr 2009) $

#include <stdio.h>

#include "main.h"



//*****************************************************************************
static int _service_test(int fd)
{
	#define	MASK	(1 << SHIFT)
	#define	SHIFT	6

	static const service_data_t	list[]	=
	{
		{
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	ADADIO_IOCTL_DATA_FORMAT,
			/* arg		*/	ADADIO_DATA_FORMAT_2S_COMP,
			/* reg		*/	ADADIO_GSC_BCR,
			/* mask		*/	MASK,
			/* value	*/	0 << SHIFT
		},
		{
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	ADADIO_IOCTL_DATA_FORMAT,
			/* arg		*/	ADADIO_DATA_FORMAT_OFF_BIN,
			/* reg		*/	ADADIO_GSC_BCR,
			/* mask		*/	MASK,
			/* value	*/	1 << SHIFT
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
	static const service_data_t	list[]	=
	{
		{
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	ADADIO_IOCTL_AIN_MODE,
			/* arg		*/	ADADIO_AIN_MODE_VREF_TEST,
			/* reg		*/	-1,
			/* mask		*/	0,
			/* value	*/	0
		},

		{
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	ADADIO_IOCTL_DATA_FORMAT,
			/* arg		*/	ADADIO_DATA_FORMAT_2S_COMP,
			/* reg		*/	-1,
			/* mask		*/	0,
			/* value	*/	0
		},
		{				// Clear the buffer
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	ADADIO_IOCTL_AIN_BUF_CLEAR,
			/* arg		*/	0,
			/* reg		*/	-1,
			/* mask		*/	0,
			/* value	*/	0
		},
		{				// Get a burst of data.
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	ADADIO_IOCTL_AIN_TRIGGER,
			/* arg		*/	0,
			/* reg		*/	-1,
			/* mask		*/	0,
			/* value	*/	0
		},
		{				// Wait for data.
			/* service	*/	SERVICE_SLEEP,
			/* cmd		*/	0,
			/* arg		*/	1,
			/* reg		*/	-1,
			/* mask		*/	0,
			/* value	*/	0
		},
		{
			/* service	*/	SERVICE_REG_TEST,
			/* cmd		*/	0,
			/* arg		*/	0,
			/* reg		*/	ADADIO_GSC_AIDR,
			/* mask		*/	0xF000,
			/* value	*/	0x7000
		},

		{
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	ADADIO_IOCTL_DATA_FORMAT,
			/* arg		*/	ADADIO_DATA_FORMAT_OFF_BIN,
			/* reg		*/	-1,
			/* mask		*/	0,
			/* value	*/	0
		},
		{				// Clear the buffer
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	ADADIO_IOCTL_AIN_BUF_CLEAR,
			/* arg		*/	0,
			/* reg		*/	-1,
			/* mask		*/	0,
			/* value	*/	0
		},
		{				// Get a burst of data.
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	ADADIO_IOCTL_AIN_TRIGGER,
			/* arg		*/	0,
			/* reg		*/	-1,
			/* mask		*/	0,
			/* value	*/	0
		},
		{				// Wait for data.
			/* service	*/	SERVICE_SLEEP,
			/* cmd		*/	0,
			/* arg		*/	1,
			/* reg		*/	-1,
			/* mask		*/	0,
			/* value	*/	0
		},
		{
			/* service	*/	SERVICE_REG_TEST,
			/* cmd		*/	0,
			/* arg		*/	0,
			/* reg		*/	ADADIO_GSC_AIDR,
			/* mask		*/	0xF000,
			/* value	*/	0xF000
		},

		{ SERVICE_END_LIST }
	};

	int	errs	= 0;

	errs	+= adadio_initialize_quiet(fd);

	errs	= service_ioctl_set_reg_list(fd, list);

	errs	+= adadio_initialize_quiet(fd);
	return(errs);
}




/******************************************************************************
*
*	Function:	data_format_test
*
*	Purpose:
*
*		Perform a test of the IOCTL service ADADIO_IOCTL_DATA_FORMAT.
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

int data_format_test(int fd)
{
	int	errs	= 0;

	gsc_label("ADADIO_IOCTL_DATA_FORMAT");
	errs	+= _service_test(fd);
	errs	+= _function_test(fd);

	if (errs == 0)
		printf("PASS\n");

	return(errs);
}


