// $URL: http://subversion:8080/svn/gsc/trunk/drivers/LINUX/16AO20/16AO20_Linux_2.x.x.x_GSC_DN/sbtest/irq_sel.c $
// $Rev: 2014 $
// $Date: 2009-05-19 12:39:09 -0500 (Tue, 19 May 2009) $

#include <errno.h>
#include <stdio.h>
#include <unistd.h>

#include "main.h"



//*****************************************************************************
static int _function_sub_test(int fd, const service_data_t* list, const char* name)
{
	int errs	= 0;

	gsc_label(name);

	errs	+= ao20_initialize_quiet(fd);

	errs	+= service_ioctl_set_reg_list(fd, list);

	errs	+= ao20_initialize_quiet(fd);

	if (errs == 0)
		printf("PASS\n");

	return(errs);
}



//*****************************************************************************
static int _service_test(int fd)
{
	static const service_data_t	list[]	=
	{
		{
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	AO20_IOCTL_IRQ_SEL,
			/* arg		*/	AO20_IRQ_SEL_INIT_DONE,
			/* reg		*/	AO20_GSC_BCR,
			/* mask		*/	0x700,
			/* value	*/	0x000
		},
		{
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	AO20_IOCTL_IRQ_SEL,
			/* arg		*/	AO20_IRQ_SEL_AUTOCAL_DONE,
			/* reg		*/	AO20_GSC_BCR,
			/* mask		*/	0x700,
			/* value	*/	0x100
		},
		{
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	AO20_IOCTL_IRQ_SEL,
			/* arg		*/	AO20_IRQ_SEL_BUF_EMPTY,
			/* reg		*/	AO20_GSC_BCR,
			/* mask		*/	0x700,
			/* value	*/	0x200
		},
		{
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	AO20_IOCTL_IRQ_SEL,
			/* arg		*/	AO20_IRQ_SEL_BUF_1Q_FULL,
			/* reg		*/	AO20_GSC_BCR,
			/* mask		*/	0x700,
			/* value	*/	0x300
		},
		{
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	AO20_IOCTL_IRQ_SEL,
			/* arg		*/	AO20_IRQ_SEL_BUF_3Q_FULL,
			/* reg		*/	AO20_GSC_BCR,
			/* mask		*/	0x700,
			/* value	*/	0x400
		},
		{
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	AO20_IOCTL_IRQ_SEL,
			/* arg		*/	AO20_IRQ_SEL_BURST_TRIG_READY,
			/* reg		*/	AO20_GSC_BCR,
			/* mask		*/	0x700,
			/* value	*/	0x500
		},
		{
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	AO20_IOCTL_IRQ_SEL,
			/* arg		*/	AO20_IRQ_SEL_LOAD_READY,
			/* reg		*/	AO20_GSC_BCR,
			/* mask		*/	0x700,
			/* value	*/	0x600
		},
		{
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	AO20_IOCTL_IRQ_SEL,
			/* arg		*/	AO20_IRQ_SEL_LOAD_READY_END,
			/* reg		*/	AO20_GSC_BCR,
			/* mask		*/	0x700,
			/* value	*/	0x700
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
	static const service_data_t	list_0[]	=
	{
		{					// IRQ: Initialize Done
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	AO20_IOCTL_IRQ_SEL,
			/* arg		*/	AO20_IRQ_SEL_INIT_DONE,
			/* reg		*/	-1,
			/* mask		*/	0,
			/* value	*/	0
		},
		{					// Clear IRQ Status
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	AO20_IOCTL_IRQ_STATE,
			/* arg		*/	AO20_IRQ_STATE_CLEAR,
			/* reg		*/	-1,
			/* mask		*/	0,
			/* value	*/	0
		},
		{					// Initiate an initialization.
			/* service	*/	SERVICE_REG_MOD,
			/* cmd		*/	0,
			/* arg		*/	0,
			/* reg		*/	AO20_GSC_BCR,
			/* mask		*/	0x8000,
			/* value	*/	0x8000
		},
		{					// Wait for completion.
			/* service	*/	SERVICE_SLEEP,
			/* cmd		*/	0,
			/* arg		*/	1,
			/* reg		*/	-1,
			/* mask		*/	0,
			/* value	*/	0
		},
		{					// Verify that the status flag is set.
			/* service	*/	SERVICE_REG_TEST,
			/* cmd		*/	0,
			/* arg		*/	0,
			/* reg		*/	AO20_GSC_BCR,
			/* mask		*/	0x800,
			/* value	*/	0x800
		},

		{ SERVICE_END_LIST }
	};

	static const service_data_t	list_1[]	=
	{
		{					// IRQ: Auto-Calibration Done
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	AO20_IOCTL_IRQ_SEL,
			/* arg		*/	AO20_IRQ_SEL_AUTOCAL_DONE,
			/* reg		*/	-1,
			/* mask		*/	0,
			/* value	*/	0
		},
		{					// Clear IRQ Status
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	AO20_IOCTL_IRQ_STATE,
			/* arg		*/	AO20_IRQ_STATE_CLEAR,
			/* reg		*/	-1,
			/* mask		*/	0,
			/* value	*/	0
		},
		{					// Initiate an Auto-Calibration.
			/* service	*/	SERVICE_REG_MOD,
			/* cmd		*/	0,
			/* arg		*/	0,
			/* reg		*/	AO20_GSC_BCR,
			/* mask		*/	0x2000,
			/* value	*/	0x2000
		},
		{					// Wait for completion.
			/* service	*/	SERVICE_SLEEP,
			/* cmd		*/	0,
			/* arg		*/	6,
			/* reg		*/	-1,
			/* mask		*/	0,
			/* value	*/	0
		},
		{					// Verify that the status flag is set.
			/* service	*/	SERVICE_REG_TEST,
			/* cmd		*/	0,
			/* arg		*/	0,
			/* reg		*/	AO20_GSC_BCR,
			/* mask		*/	0x800,
			/* value	*/	0x800
		},

		{ SERVICE_END_LIST }
	};

	static const service_data_t	list_2[]	=
	{
		{					// IRQ: Buffer Empty
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	AO20_IOCTL_IRQ_SEL,
			/* arg		*/	AO20_IRQ_SEL_BUF_EMPTY,
			/* reg		*/	-1,
			/* mask		*/	0,
			/* value	*/	0
		},
		{					// Clear IRQ Status
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	AO20_IOCTL_IRQ_STATE,
			/* arg		*/	AO20_IRQ_STATE_CLEAR,
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
		{					// Put data in the buffer.
			/* service	*/	SERVICE_REG_MOD,
			/* cmd		*/	0,
			/* arg		*/	0,
			/* reg		*/	AO20_GSC_ODBR,
			/* mask		*/	0xFFFF,
			/* value	*/	0x0000
		},
		{					// Enable the clock.
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	AO20_IOCTL_CLOCK_ENABLE,
			/* arg		*/	AO20_CLOCK_ENABLE_YES,
			/* reg		*/	-1,
			/* mask		*/	0,
			/* value	*/	0
		},
		{					// Wait for completion.
			/* service	*/	SERVICE_SLEEP,
			/* cmd		*/	0,
			/* arg		*/	1,
			/* reg		*/	-1,
			/* mask		*/	0,
			/* value	*/	0
		},
		{					// Verify that the status flag is set.
			/* service	*/	SERVICE_REG_TEST,
			/* cmd		*/	0,
			/* arg		*/	0,
			/* reg		*/	AO20_GSC_BCR,
			/* mask		*/	0x800,
			/* value	*/	0x800
		},

		{ SERVICE_END_LIST }
	};

	static const service_data_t	list_3[]	=
	{
		{					// IRQ: Buffer 1/4 Full
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	AO20_IOCTL_IRQ_SEL,
			/* arg		*/	AO20_IRQ_SEL_BUF_1Q_FULL,
			/* reg		*/	-1,
			/* mask		*/	0,
			/* value	*/	0
		},
		{					// Clear IRQ Status
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	AO20_IOCTL_IRQ_STATE,
			/* arg		*/	AO20_IRQ_STATE_CLEAR,
			/* reg		*/	-1,
			/* mask		*/	0,
			/* value	*/	0
		},
		{					// Enable one channel only.
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	AO20_IOCTL_CHANNEL_SEL,
			/* arg		*/	0x1,
			/* reg		*/	-1,
			/* mask		*/	0,
			/* value	*/	0
		},
		{					// Simultaneous Sampling
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	AO20_IOCTL_OUTPUT_MODE,
			/* arg		*/	AO20_OUTPUT_MODE_SIM,
			/* reg		*/	AO20_GSC_BCR,
			/* mask		*/	0x80,
			/* value	*/	0x80
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
		{					// Make the buffer very small
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	AO20_IOCTL_BUFFER_SIZE,
			/* arg		*/	AO20_BUFFER_SIZE_8,
			/* reg		*/	AO20_GSC_BOR,
			/* mask		*/	0xF,
			/* value	*/	0x0
		},
		{					// Select burst operation.
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	AO20_IOCTL_SAMPLE_MODE,
			/* arg		*/	AO20_SAMPLE_MODE_BURST,
			/* reg		*/	-1,
			/* mask		*/	0,
			/* value	*/	0
		},
		{					// Put data in the buffer (out).
			/* service	*/	SERVICE_REG_MOD,
			/* cmd		*/	0,
			/* arg		*/	0,
			/* reg		*/	AO20_GSC_ODBR,
			/* mask		*/	0x1FFFF,
			/* value	*/	0x10000
		},
		{					// Put data in the buffer (1 of 8).
			/* service	*/	SERVICE_REG_MOD,
			/* cmd		*/	0,
			/* arg		*/	0,
			/* reg		*/	AO20_GSC_ODBR,
			/* mask		*/	0x1FFFF,
			/* value	*/	0x10000
		},
		{					// Put data in the buffer (2 of 8).
			/* service	*/	SERVICE_REG_MOD,
			/* cmd		*/	0,
			/* arg		*/	0,
			/* reg		*/	AO20_GSC_ODBR,
			/* mask		*/	0x1FFFF,
			/* value	*/	0x10000
		},
		{					// Wait for completion.
			/* service	*/	SERVICE_SLEEP,
			/* cmd		*/	0,
			/* arg		*/	1,
			/* reg		*/	-1,
			/* mask		*/	0,
			/* value	*/	0
		},
		{					// Initiate a burst
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	AO20_IOCTL_BURST_TRIGGER,
			/* arg		*/	0,
			/* reg		*/	-1,
			/* mask		*/	0,
			/* value	*/	0
		},
		{					// Verify that the status flag is set.
			/* service	*/	SERVICE_REG_TEST,
			/* cmd		*/	0,
			/* arg		*/	0,
			/* reg		*/	AO20_GSC_BCR,
			/* mask		*/	0x800,
			/* value	*/	0x800
		},

		{ SERVICE_END_LIST }
	};

	static const service_data_t	list_4[]	=
	{
		{					// IRQ: Buffer 3/4 Full
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	AO20_IOCTL_IRQ_SEL,
			/* arg		*/	AO20_IRQ_SEL_BUF_3Q_FULL,
			/* reg		*/	-1,
			/* mask		*/	0,
			/* value	*/	0
		},
		{					// Clear IRQ Status
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	AO20_IOCTL_IRQ_STATE,
			/* arg		*/	AO20_IRQ_STATE_CLEAR,
			/* reg		*/	-1,
			/* mask		*/	0,
			/* value	*/	0
		},
		{					// Enable one channel only.
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	AO20_IOCTL_CHANNEL_SEL,
			/* arg		*/	0x1,
			/* reg		*/	-1,
			/* mask		*/	0,
			/* value	*/	0
		},
		{					// Simultaneous Sampling
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	AO20_IOCTL_OUTPUT_MODE,
			/* arg		*/	AO20_OUTPUT_MODE_SIM,
			/* reg		*/	AO20_GSC_BCR,
			/* mask		*/	0x80,
			/* value	*/	0x80
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
		{					// Make the buffer very small
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	AO20_IOCTL_BUFFER_SIZE,
			/* arg		*/	AO20_BUFFER_SIZE_8,
			/* reg		*/	AO20_GSC_BOR,
			/* mask		*/	0xF,
			/* value	*/	0x0
		},
		{					// Select burst operation.
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	AO20_IOCTL_SAMPLE_MODE,
			/* arg		*/	AO20_SAMPLE_MODE_BURST,
			/* reg		*/	-1,
			/* mask		*/	0,
			/* value	*/	0
		},
		{					// Put data in the buffer (out).
			/* service	*/	SERVICE_REG_MOD,
			/* cmd		*/	0,
			/* arg		*/	0,
			/* reg		*/	AO20_GSC_ODBR,
			/* mask		*/	0x1FFFF,
			/* value	*/	0x10000
		},
		{					// Put data in the buffer (1 of 8).
			/* service	*/	SERVICE_REG_MOD,
			/* cmd		*/	0,
			/* arg		*/	0,
			/* reg		*/	AO20_GSC_ODBR,
			/* mask		*/	0x1FFFF,
			/* value	*/	0x10000
		},
		{					// Put data in the buffer (2 of 8).
			/* service	*/	SERVICE_REG_MOD,
			/* cmd		*/	0,
			/* arg		*/	0,
			/* reg		*/	AO20_GSC_ODBR,
			/* mask		*/	0x1FFFF,
			/* value	*/	0x10000
		},
		{					// Put data in the buffer (3 of 8).
			/* service	*/	SERVICE_REG_MOD,
			/* cmd		*/	0,
			/* arg		*/	0,
			/* reg		*/	AO20_GSC_ODBR,
			/* mask		*/	0x1FFFF,
			/* value	*/	0x10000
		},
		{					// Put data in the buffer (4 of 8).
			/* service	*/	SERVICE_REG_MOD,
			/* cmd		*/	0,
			/* arg		*/	0,
			/* reg		*/	AO20_GSC_ODBR,
			/* mask		*/	0x1FFFF,
			/* value	*/	0x10000
		},
		{					// Put data in the buffer (5 of 8).
			/* service	*/	SERVICE_REG_MOD,
			/* cmd		*/	0,
			/* arg		*/	0,
			/* reg		*/	AO20_GSC_ODBR,
			/* mask		*/	0x1FFFF,
			/* value	*/	0x10000
		},
		{					// Put data in the buffer (6 of 8).
			/* service	*/	SERVICE_REG_MOD,
			/* cmd		*/	0,
			/* arg		*/	0,
			/* reg		*/	AO20_GSC_ODBR,
			/* mask		*/	0x1FFFF,
			/* value	*/	0x10000
		},
		{					// Wait for completion.
			/* service	*/	SERVICE_SLEEP,
			/* cmd		*/	0,
			/* arg		*/	1,
			/* reg		*/	-1,
			/* mask		*/	0,
			/* value	*/	0
		},
		{					// Verify that the status flag is set.
			/* service	*/	SERVICE_REG_TEST,
			/* cmd		*/	0,
			/* arg		*/	0,
			/* reg		*/	AO20_GSC_BCR,
			/* mask		*/	0x800,
			/* value	*/	0x800
		},

		{ SERVICE_END_LIST }
	};

	static const service_data_t	list_5[]	=
	{
		{					// IRQ: Burst Trigger Ready
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	AO20_IOCTL_IRQ_SEL,
			/* arg		*/	AO20_IRQ_SEL_BURST_TRIG_READY,
			/* reg		*/	-1,
			/* mask		*/	0,
			/* value	*/	0
		},
		{					// Clear IRQ Status
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	AO20_IOCTL_IRQ_STATE,
			/* arg		*/	AO20_IRQ_STATE_CLEAR,
			/* reg		*/	-1,
			/* mask		*/	0,
			/* value	*/	0
		},
		{					// Enable one channel only.
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	AO20_IOCTL_CHANNEL_SEL,
			/* arg		*/	0x1,
			/* reg		*/	-1,
			/* mask		*/	0,
			/* value	*/	0
		},
		{					// Simultaneous Sampling
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	AO20_IOCTL_OUTPUT_MODE,
			/* arg		*/	AO20_OUTPUT_MODE_SIM,
			/* reg		*/	AO20_GSC_BCR,
			/* mask		*/	0x80,
			/* value	*/	0x80
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
		{					// Put data in the buffer (out).
			/* service	*/	SERVICE_REG_MOD,
			/* cmd		*/	0,
			/* arg		*/	0,
			/* reg		*/	AO20_GSC_ODBR,
			/* mask		*/	0x1FFFF,
			/* value	*/	0x10000
		},
		{					// Put data in the buffer (1).
			/* service	*/	SERVICE_REG_MOD,
			/* cmd		*/	0,
			/* arg		*/	0,
			/* reg		*/	AO20_GSC_ODBR,
			/* mask		*/	0x1FFFF,
			/* value	*/	0x10000
		},
		{					// Wait for completion.
			/* service	*/	SERVICE_SLEEP,
			/* cmd		*/	0,
			/* arg		*/	1,
			/* reg		*/	-1,
			/* mask		*/	0,
			/* value	*/	0
		},
		{					// Verify that the status flag is set.
			/* service	*/	SERVICE_REG_TEST,
			/* cmd		*/	0,
			/* arg		*/	0,
			/* reg		*/	AO20_GSC_BCR,
			/* mask		*/	0x800,
			/* value	*/	0x800
		},

		{ SERVICE_END_LIST }
	};

	static const service_data_t	list_6[]	=
	{
		{					// IRQ: Load Ready
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	AO20_IOCTL_IRQ_SEL,
			/* arg		*/	AO20_IRQ_SEL_LOAD_READY,
			/* reg		*/	-1,
			/* mask		*/	0,
			/* value	*/	0
		},
		{					// Clear IRQ Status
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	AO20_IOCTL_IRQ_STATE,
			/* arg		*/	AO20_IRQ_STATE_CLEAR,
			/* reg		*/	-1,
			/* mask		*/	0,
			/* value	*/	0
		},
		{					// Enable one channel only.
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	AO20_IOCTL_CHANNEL_SEL,
			/* arg		*/	0x1,
			/* reg		*/	-1,
			/* mask		*/	0,
			/* value	*/	0
		},
		{					// Simultaneous Sampling
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	AO20_IOCTL_OUTPUT_MODE,
			/* arg		*/	AO20_OUTPUT_MODE_SIM,
			/* reg		*/	AO20_GSC_BCR,
			/* mask		*/	0x80,
			/* value	*/	0x80
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
		{					// Put data in the buffer (out).
			/* service	*/	SERVICE_REG_MOD,
			/* cmd		*/	0,
			/* arg		*/	0,
			/* reg		*/	AO20_GSC_ODBR,
			/* mask		*/	0x1FFFF,
			/* value	*/	0x10000
		},
		{					// Put data in the buffer (1).
			/* service	*/	SERVICE_REG_MOD,
			/* cmd		*/	0,
			/* arg		*/	0,
			/* reg		*/	AO20_GSC_ODBR,
			/* mask		*/	0x1FFFF,
			/* value	*/	0x10000
		},
		{					// Put the buffer in circular mode.
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	AO20_IOCTL_BUFFER_MODE,
			/* arg		*/	AO20_BUFFER_MODE_CIRC,
			/* reg		*/	-1,
			/* mask		*/	0,
			/* value	*/	0
		},
		{					// Put the buffer in open mode.
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	AO20_IOCTL_BUFFER_MODE,
			/* arg		*/	AO20_BUFFER_MODE_OPEN,
			/* reg		*/	-1,
			/* mask		*/	0,
			/* value	*/	0
		},
		{					// Verify that the status flag is set.
			/* service	*/	SERVICE_REG_TEST,
			/* cmd		*/	0,
			/* arg		*/	0,
			/* reg		*/	AO20_GSC_BCR,
			/* mask		*/	0x800,
			/* value	*/	0x800
		},

		{ SERVICE_END_LIST }
	};

	static const service_data_t	list_7[]	=
	{
		{					// IRQ: Load Ready End
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	AO20_IOCTL_IRQ_SEL,
			/* arg		*/	AO20_IRQ_SEL_LOAD_READY_END,
			/* reg		*/	-1,
			/* mask		*/	0,
			/* value	*/	0
		},
		{					// Clear IRQ Status
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	AO20_IOCTL_IRQ_STATE,
			/* arg		*/	AO20_IRQ_STATE_CLEAR,
			/* reg		*/	-1,
			/* mask		*/	0,
			/* value	*/	0
		},
		{					// Enable one channel only.
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	AO20_IOCTL_CHANNEL_SEL,
			/* arg		*/	0x1,
			/* reg		*/	-1,
			/* mask		*/	0,
			/* value	*/	0
		},
		{					// Simultaneous Sampling
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	AO20_IOCTL_OUTPUT_MODE,
			/* arg		*/	AO20_OUTPUT_MODE_SIM,
			/* reg		*/	AO20_GSC_BCR,
			/* mask		*/	0x80,
			/* value	*/	0x80
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
		{					// Put data in the buffer (out).
			/* service	*/	SERVICE_REG_MOD,
			/* cmd		*/	0,
			/* arg		*/	0,
			/* reg		*/	AO20_GSC_ODBR,
			/* mask		*/	0x1FFFF,
			/* value	*/	0x10000
		},
		{					// Put data in the buffer (1).
			/* service	*/	SERVICE_REG_MOD,
			/* cmd		*/	0,
			/* arg		*/	0,
			/* reg		*/	AO20_GSC_ODBR,
			/* mask		*/	0x1FFFF,
			/* value	*/	0x10000
		},
		{					// Put the buffer in circular mode.
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	AO20_IOCTL_BUFFER_MODE,
			/* arg		*/	AO20_BUFFER_MODE_CIRC,
			/* reg		*/	-1,
			/* mask		*/	0,
			/* value	*/	0
		},
		{					// Verify that the status flag is set.
			/* service	*/	SERVICE_REG_TEST,
			/* cmd		*/	0,
			/* arg		*/	0,
			/* reg		*/	AO20_GSC_BCR,
			/* mask		*/	0x800,
			/* value	*/	0x800
		},

		{ SERVICE_END_LIST }
	};

	int errs	= 0;

	errs	+= _function_sub_test(fd, list_0, "Initialization Done");
	errs	+= _function_sub_test(fd, list_1, "Auto-Calibration Done");
	errs	+= _function_sub_test(fd, list_2, "Buffer Empty");
	errs	+= _function_sub_test(fd, list_3, "Buffer Drops to 1/4 Full");
	errs	+= _function_sub_test(fd, list_4, "Buffer Becomes 3/4 Full");
	errs	+= _function_sub_test(fd, list_5, "Burst Trigger Ready");
	errs	+= _function_sub_test(fd, list_6, "Load Ready");
	errs	+= _function_sub_test(fd, list_7, "Load Ready End");
	return(errs);
}




/******************************************************************************
*
*	Function:	irq_sel_test
*
*	Purpose:
*
*		Perform a test of the IOCTL service AO20_IOCTL_IRQ_SEL.
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

int irq_sel_test(int fd)
{
	int	errs	= 0;

	gsc_label("AO20_IOCTL_IRQ_SEL");
	errs	+= _service_test(fd);

	if (errs == 0)
		printf("PASS\n");

	gsc_label_level_inc();
	errs	+= _function_test(fd);
	gsc_label_level_dec();

	return(errs);
}


