// $URL: http://subversion:8080/svn/gsc/trunk/drivers/LINUX/16AO20/16AO20_Linux_2.x.x.x_GSC_DN/sbtest/burst_trigger.c $
// $Rev: 2014 $
// $Date: 2009-05-19 12:39:09 -0500 (Tue, 19 May 2009) $

#include <errno.h>
#include <stdio.h>
#include <unistd.h>

#include "main.h"



//*****************************************************************************
static int _service_test(int fd)
{
	// There are no persistent bits to test with this service.
	return(0);
}




//*****************************************************************************
static int _function_test(int fd)
{
	static const service_data_t	list[]	=
	{
		{					// Enable one channel only.
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	AO20_IOCTL_CHANNEL_SEL,
			/* arg		*/	0x1,
			/* reg		*/	-1,
			/* mask		*/	0,
			/* value	*/	0
		},
		{					// Select simultaneous outputs.
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	AO20_IOCTL_OUTPUT_MODE,
			/* arg		*/	AO20_OUTPUT_MODE_SIM,
			/* reg		*/	-1,
			/* mask		*/	0,
			/* value	*/	0
		},
		{					// Enable the clock.
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	AO20_IOCTL_CLOCK_ENABLE,
			/* arg		*/	AO20_CLOCK_ENABLE_YES,
			/* reg		*/	-1,
			/* mask		*/	0,
			/* value	*/	0
		},
		{					// Select software burst triggering.
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	AO20_IOCTL_BURST_TRIG_SRC,
			/* arg		*/	AO20_BURST_TRIG_SRC_SW,
			/* reg		*/	-1,
			/* mask		*/	0,
			/* value	*/	0
		},
		{					// Select burst operation.
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	AO20_IOCTL_SAMPLE_MODE,
			/* arg		*/	AO20_SAMPLE_MODE_BURST,
			/* reg		*/	-1,
			/* mask		*/	0,
			/* value	*/	0
		},
		{					// Put data in the buffer.
			/* service	*/	SERVICE_REG_MOD,
			/* cmd		*/	0,
			/* arg		*/	0,
			/* reg		*/	AO20_GSC_ODBR,
			/* mask		*/	0x1FFFF,
			/* value	*/	0x10000
		},
		{					// Put data in the buffer.
			/* service	*/	SERVICE_REG_MOD,
			/* cmd		*/	0,
			/* arg		*/	0,
			/* reg		*/	AO20_GSC_ODBR,
			/* mask		*/	0x1FFFF,
			/* value	*/	0x00000
		},
		{					// Wait a bit.
			/* service	*/	SERVICE_SLEEP,
			/* cmd		*/	0,
			/* arg		*/	1,
			/* reg		*/	-1,
			/* mask		*/	0,
			/* value	*/	0
		},
		{					// Verify that the buffer is NOT empty.
			/* service	*/	SERVICE_REG_TEST,
			/* cmd		*/	0,
			/* arg		*/	0,
			/* reg		*/	AO20_GSC_BOR,
			/* mask		*/	0xF000,
			/* value	*/	0x2000
		},

		// Verify that the software burst operates as expected.

		{					// Initiate a burst
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	AO20_IOCTL_BURST_TRIGGER,
			/* arg		*/	0,
			/* reg		*/	-1,
			/* mask		*/	0,
			/* value	*/	0
		},
		{					// Wait a bit.
			/* service	*/	SERVICE_SLEEP,
			/* cmd		*/	0,
			/* arg		*/	1,
			/* reg		*/	-1,
			/* mask		*/	0,
			/* value	*/	0
		},
		{					// Verify that the buffer IS empty.
			/* service	*/	SERVICE_REG_TEST,
			/* cmd		*/	0,
			/* arg		*/	0,
			/* reg		*/	AO20_GSC_BOR,
			/* mask		*/	0xF000,
			/* value	*/	0x3000
		},

		{ SERVICE_END_LIST }
	};

	int errs	= 0;

	errs	+= ao20_initialize_quiet(fd);

	errs	+= service_ioctl_set_reg_list(fd, list);

	errs	+= ao20_initialize_quiet(fd);
	return(errs);
}




/******************************************************************************
*
*	Function:	burst_trigger_test
*
*	Purpose:
*
*		Perform a test of the IOCTL service AO20_IOCTL_BURST_TRIGGER.
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

int burst_trigger_test(int fd)
{
	int	errs	= 0;

	gsc_label("AO20_IOCTL_BURST_TRIGGER");
	errs	+= _service_test(fd);
	errs	+= _function_test(fd);

	if (errs == 0)
		printf("PASS\n");

	return(errs);
}


