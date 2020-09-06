// $URL: http://subversion:8080/svn/gsc/trunk/drivers/LINUX/16AO20/16AO20_Linux_2.x.x.x_GSC_DN/sbtest/burst_ready.c $
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
	static const service_data_t	list_1[]	=
	{
		{					// Verify that the status bit is clear.
			/* service	*/	SERVICE_REG_TEST,
			/* cmd		*/	0,
			/* arg		*/	0,
			/* reg		*/	AO20_GSC_BCR,
			/* mask		*/	0x2,
			/* value	*/	0x0
		},

		{ SERVICE_END_LIST }
	};

	static const service_data_t	list_2[]	=
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

		// Verify burst operation.

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
		{					// Verify that the status bit is set.
			/* service	*/	SERVICE_REG_TEST,
			/* cmd		*/	0,
			/* arg		*/	0,
			/* reg		*/	AO20_GSC_BCR,
			/* mask		*/	0x2,
			/* value	*/	0x2
		},

		{ SERVICE_END_LIST }
	};

	__s32	_1_no;
	__s32	_2_yes;
	int		errs	= 0;

	// There are a multitude of conditions that can result in READY or NOT
	// READY status. We merely generate one condition for each and verify
	// that we get the expected results.

	errs	+= ao20_initialize_quiet(fd);

	errs	+= service_ioctl_set_reg_list(fd, list_1);
	errs	+= ao20_dsl_ioctl(fd, AO20_IOCTL_BURST_READY,&_1_no);

	errs	+= service_ioctl_set_reg_list(fd, list_2);
	errs	+= ao20_dsl_ioctl(fd, AO20_IOCTL_BURST_READY,&_2_yes);

	if (_1_no != AO20_BURST_READY_NO)
	{
		errs++;
		printf("FAIL <--- (List 1 results are not NO.)\n");
	}
	else if (_2_yes != AO20_BURST_READY_YES)
	{
		errs++;
		printf("FAIL <--- (List 2 results are not YES.)\n");
	}

	errs	+= ao20_initialize_quiet(fd);
	return(errs);
}




/******************************************************************************
*
*	Function:	burst_ready_test
*
*	Purpose:
*
*		Perform a test of the IOCTL service AO20_IOCTL_BURST_READY.
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

int burst_ready_test(int fd)
{
	int	errs	= 0;

	gsc_label("AO20_IOCTL_BURST_READY");
	errs	+= _service_test(fd);
	errs	+= _function_test(fd);

	if (errs == 0)
		printf("PASS\n");

	return(errs);
}


