// $URL: http://subversion:8080/svn/gsc/trunk/drivers/LINUX/16AO20/16AO20_Linux_2.x.x.x_GSC_DN/sbtest/output_mode.c $
// $Rev: 2034 $
// $Date: 2009-05-26 14:45:21 -0500 (Tue, 26 May 2009) $

#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "main.h"


#include <sys/ioctl.h>



//*****************************************************************************
static int _service_test(int fd)
{
	static const service_data_t	list[]	=
	{
		{
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	AO20_IOCTL_OUTPUT_MODE,
			/* arg		*/	AO20_OUTPUT_MODE_SEQ,
			/* reg		*/	AO20_GSC_BCR,
			/* mask		*/	0x80,
			/* value	*/	0x00
		},
		{
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	AO20_IOCTL_OUTPUT_MODE,
			/* arg		*/	AO20_OUTPUT_MODE_SIM,
			/* reg		*/	AO20_GSC_BCR,
			/* mask		*/	0x80,
			/* value	*/	0x80
		},

		{ SERVICE_END_LIST }
	};

	int errs	= 0;

	errs	+= ao20_initialize_quiet(fd);

	errs	+= service_ioctl_set_reg_list(fd, list);
	errs	+= service_ioctl_reg_get_list(fd, list);

	errs	+= service_ioctl_set_reg_list(fd, list);
	errs	+= service_ioctl_reg_get_list(fd, list);

	errs	+= ao20_initialize_quiet(fd);
	return(errs);
}




//*****************************************************************************
static int _function_test(int fd)
{
	static const service_data_t	list_1[]	=
	{
		{					// Enable two channels only.
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	AO20_IOCTL_CHANNEL_SEL,
			/* arg		*/	0x3,
			/* reg		*/	-1,
			/* mask		*/	0,
			/* value	*/	0
		},
		{					// Select DMA mode.
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	AO20_IOCTL_TX_IO_MODE,
			/* arg		*/	GSC_IO_MODE_DMA,
			/* reg		*/	-1,
			/* mask		*/	0,
			/* value	*/	0
		},
		{					// Select the primary clock source.
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	AO20_IOCTL_CLOCK_OSC_SRC,
			/* arg		*/	AO20_CLOCK_OSC_SRC_PRI,
			/* reg		*/	-1,
			/* mask		*/	0,
			/* value	*/	0
		},
		{					// Set Nrate high for the lowest possible Fsamp.
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	AO20_IOCTL_NRATE,
			/* arg		*/	0xFFFF,
			/* reg		*/	-1,
			/* mask		*/	0,
			/* value	*/	0
		},

		{ SERVICE_END_LIST }
	};

	static const service_data_t	list_2[]	=
	{
		{					// Select simultaneous outputs for a higher rate.
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	AO20_IOCTL_OUTPUT_MODE,
			/* arg		*/	AO20_OUTPUT_MODE_SIM,
			/* reg		*/	-1,
			/* mask		*/	0,
			/* value	*/	0
		},

		{ SERVICE_END_LIST }
	};

	static const service_data_t	list_3[]	=
	{
		{					// Select sequential outputs for a lower rate.
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	AO20_IOCTL_OUTPUT_MODE,
			/* arg		*/	AO20_OUTPUT_MODE_SEQ,
			/* reg		*/	-1,
			/* mask		*/	0,
			/* value	*/	0
		},

		{ SERVICE_END_LIST }
	};

	static const service_data_t	clock_enable[]	=
	{
		{					// Enable the clock.
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	AO20_IOCTL_CLOCK_ENABLE,
			/* arg		*/	AO20_CLOCK_ENABLE_YES,
			/* reg		*/	-1,
			/* mask		*/	0,
			/* value	*/	0
		},

		{ SERVICE_END_LIST }
	};

	static const service_data_t	clock_disable[]	=
	{
		{					// Clear the buffer and flags.
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	AO20_IOCTL_BUFFER_CLEAR,
			/* arg		*/	0,
			/* reg		*/	-1,
			/* mask		*/	0,
			/* value	*/	0
		},
		{					// Disable the clock.
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	AO20_IOCTL_CLOCK_ENABLE,
			/* arg		*/	AO20_CLOCK_ENABLE_NO,
			/* reg		*/	-1,
			/* mask		*/	0,
			/* value	*/	0
		},

		{ SERVICE_END_LIST }
	};

	#define	SAMPLES	(801 * 2)

	__s32	_1_ne;
	__s32	_2_e;
	__s32	_3_ne;
	__s32	_4_e;
	__u32	buf[SAMPLES];
	int		errs	= 0;
	int		sent;

	// The procedure is to select a sample rate and duration so we can look at
	// the time it takes for the buffer to empty.

	memset(buf, 0, sizeof(buf));
	errs	+= ao20_initialize_quiet(fd);

	errs	+= service_ioctl_set_reg_list(fd, list_1);

	// Here, it should take about 1.75 seconds for the buffer to empty.
	errs	+= service_ioctl_set_reg_list(fd, list_2);
	errs	+= service_ioctl_set_reg_list(fd, clock_disable);
	sent	= ao20_dsl_write(fd, buf, SAMPLES);

	if ((sent >= 0) && (sent != SAMPLES))
	{
		errs++;
		printf(	"ERROR: write: send %ld, expected %ld)\n",
				(long) sent,
				(long) SAMPLES);
	}

	errs	+= service_ioctl_set_reg_list(fd, clock_enable);
	sleep(1);
	errs	+= ao20_dsl_ioctl(fd, AO20_IOCTL_BUFFER_STATUS,&_1_ne);
	sleep(1);
	errs	+= ao20_dsl_ioctl(fd, AO20_IOCTL_BUFFER_STATUS,&_2_e);
	errs	+= service_ioctl_set_reg_list(fd, clock_disable);

	// Here, it should take about 3.5 seconds for the buffer to empty.
	errs	+= service_ioctl_set_reg_list(fd, list_3);
	errs	+= service_ioctl_set_reg_list(fd, clock_disable);
	sent	= ao20_dsl_write(fd, buf, SAMPLES);

	if ((sent >= 0) && (sent != SAMPLES))
	{
		errs++;
		printf(	"ERROR: write: send %ld, expected %ld)\n",
				(long) sent,
				(long) SAMPLES);
	}

	errs	+= service_ioctl_set_reg_list(fd, clock_enable);
	sleep(3);
	errs	+= ao20_dsl_ioctl(fd, AO20_IOCTL_BUFFER_STATUS,&_3_ne);

	sleep(1);

	errs	+= ao20_dsl_ioctl(fd, AO20_IOCTL_BUFFER_STATUS,&_4_e);
	errs	+= service_ioctl_set_reg_list(fd, clock_disable);

	// Now verify all of the results.

	if (errs)
	{
	}
	else if (_1_ne == AO20_BUFFER_STATUS_EMPTY)
	{
		errs++;
		printf("FAIL <--- (Test 1 results are EMPTY.)\n");
	}
	else if (_2_e != AO20_BUFFER_STATUS_EMPTY)
	{
		errs++;
		printf("FAIL <--- (Test 2 results are not EMPTY.)\n");
	}
	else if (_3_ne == AO20_BUFFER_STATUS_EMPTY)
	{
		errs++;
		printf("FAIL <--- (Test 3 results are EMPTY.)\n");
	}
	else if (_4_e != AO20_BUFFER_STATUS_EMPTY)
	{
		errs++;
		printf("FAIL <--- (Test 4 results are not EMPTY.)\n");
	}

	errs	+= ao20_initialize_quiet(fd);
	return(errs);
}




/******************************************************************************
*
*	Function:	output_mode_test
*
*	Purpose:
*
*		Perform a test of the IOCTL service AO20_IOCTL_OUTPUT_MODE.
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

int output_mode_test(int fd)
{
	int	errs	= 0;

	gsc_label("AO20_IOCTL_OUTPUT_MODE");
	errs	+= _service_test(fd);
	errs	+= _function_test(fd);

	if (errs == 0)
		printf("PASS\n");

	return(errs);
}


