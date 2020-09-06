// $URL: http://subversion:8080/svn/gsc/trunk/drivers/LINUX/ADADIO/ADADIO_Linux_3.x.x.x_GSC_DN/sbtest/loopback_channel.c $
// $Rev: 1620 $
// $Date: 2009-04-10 11:41:41 -0500 (Fri, 10 Apr 2009) $

#include <stdio.h>

#include "main.h"



//*****************************************************************************
static int _service_test(int fd)
{
	#define	MASK	(3 << SHIFT)
	#define	SHIFT	3

	static const service_data_t	list[]	=
	{
		{
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	ADADIO_IOCTL_LOOPBACK_CHANNEL,
			/* arg		*/	0,
			/* reg		*/	ADADIO_GSC_BCR,
			/* mask		*/	MASK,
			/* value	*/	0 << SHIFT
		},
		{
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	ADADIO_IOCTL_LOOPBACK_CHANNEL,
			/* arg		*/	1,
			/* reg		*/	ADADIO_GSC_BCR,
			/* mask		*/	MASK,
			/* value	*/	1 << SHIFT
		},
		{
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	ADADIO_IOCTL_LOOPBACK_CHANNEL,
			/* arg		*/	2,
			/* reg		*/	ADADIO_GSC_BCR,
			/* mask		*/	MASK,
			/* value	*/	2 << SHIFT
		},
		{
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	ADADIO_IOCTL_LOOPBACK_CHANNEL,
			/* arg		*/	3,
			/* reg		*/	ADADIO_GSC_BCR,
			/* mask		*/	MASK,
			/* value	*/	3 << SHIFT
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
	const service_data_t	list[]	=
	{
		{
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	ADADIO_IOCTL_AOUT_STROBE_ENABLE,
			/* arg		*/	ADADIO_AOUT_STROBE_ENABLE_NO,
			/* reg		*/	-1,
			/* mask		*/	0,
			/* value	*/	0
		},
		{
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	ADADIO_IOCTL_AOUT_CH_0_WRITE,
			/* arg		*/	0x1800,
			/* reg		*/	-1,
			/* mask		*/	0,
			/* value	*/	0
		},
		{
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	ADADIO_IOCTL_AOUT_CH_1_WRITE,
			/* arg		*/	0x2800,
			/* reg		*/	-1,
			/* mask		*/	0,
			/* value	*/	0
		},
		{
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	ADADIO_IOCTL_AOUT_CH_2_WRITE,
			/* arg		*/	0x3800,
			/* reg		*/	-1,
			/* mask		*/	0,
			/* value	*/	0
		},
		{
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	ADADIO_IOCTL_AOUT_CH_3_WRITE,
			/* arg		*/	0x4800,
			/* reg		*/	-1,
			/* mask		*/	0,
			/* value	*/	0
		},


		{
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	ADADIO_IOCTL_AIN_MODE,
			/* arg		*/	ADADIO_AIN_MODE_LB_TEST,
			/* reg		*/	-1,
			/* mask		*/	0,
			/* value	*/	0
		},

		{					// Check the Output Channel 0 option.
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	ADADIO_IOCTL_LOOPBACK_CHANNEL,
			/* arg		*/	0,
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
		{				// Wait a moment
			/* service	*/	SERVICE_SLEEP,
			/* cmd		*/	0,
			/* arg		*/	1,
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
		{				// Wait a moment
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
			/* value	*/	0x1000
		},

		{					// Check the Output Channel 1 option.
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	ADADIO_IOCTL_LOOPBACK_CHANNEL,
			/* arg		*/	1,
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
		{				// Wait a moment
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
			/* value	*/	0x2000
		},

		{					// Check the Output Channel 2 option.
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	ADADIO_IOCTL_LOOPBACK_CHANNEL,
			/* arg		*/	2,
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
		{				// Wait a moment
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
			/* value	*/	0x3000
		},

		{					// Check the Output Channel 3 option.
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	ADADIO_IOCTL_LOOPBACK_CHANNEL,
			/* arg		*/	3,
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
		{				// Wait a moment
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
			/* value	*/	0x4000
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
*	Function:	loopback_channel_test
*
*	Purpose:
*
*		Perform a test of the IOCTL service ADADIO_IOCTL_LOOPBACK_CHANNEL.
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

int loopback_channel_test(int fd)
{
	int	errs	= 0;

	gsc_label("ADADIO_IOCTL_LOOPBACK_CHANNEL");
	errs	+= _service_test(fd);
	errs	+= _function_test(fd);

	if (errs == 0)
		printf("PASS\n");

	return(errs);
}


