// $URL: http://subversion:8080/svn/gsc/trunk/drivers/LINUX/ADADIO/ADADIO_Linux_3.x.x.x_GSC_DN/sbtest/irq_sel.c $
// $Rev: 1620 $
// $Date: 2009-04-10 11:41:41 -0500 (Fri, 10 Apr 2009) $

#include <stdio.h>

#include "main.h"



//*****************************************************************************
static int _service_test(int fd)
{
	#define	MASK	(7 << SHIFT)
	#define	SHIFT	23

	static const service_data_t	list[]	=
	{
		{
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	ADADIO_IOCTL_IRQ_SEL,
			/* arg		*/	ADADIO_IRQ_SEL_INIT_DONE,
			/* reg		*/	ADADIO_GSC_BCR,
			/* mask		*/	MASK,
			/* value	*/	0 << SHIFT
		},
		{
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	ADADIO_IOCTL_IRQ_SEL,
			/* arg		*/	ADADIO_IRQ_SEL_AUTO_CAL_DONE,
			/* reg		*/	ADADIO_GSC_BCR,
			/* mask		*/	MASK,
			/* value	*/	1 << SHIFT
		},
		{
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	ADADIO_IOCTL_IRQ_SEL,
			/* arg		*/	ADADIO_IRQ_SEL_AIN_BUF_EMPTY,
			/* reg		*/	ADADIO_GSC_BCR,
			/* mask		*/	MASK,
			/* value	*/	2 << SHIFT
		},
		{
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	ADADIO_IOCTL_IRQ_SEL,
			/* arg		*/	ADADIO_IRQ_SEL_AIN_BUF_HALF_FULL,
			/* reg		*/	ADADIO_GSC_BCR,
			/* mask		*/	MASK,
			/* value	*/	3 << SHIFT
		},
		{
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	ADADIO_IOCTL_IRQ_SEL,
			/* arg		*/	ADADIO_IRQ_SEL_AIN_BUF_FULL,
			/* reg		*/	ADADIO_GSC_BCR,
			/* mask		*/	MASK,
			/* value	*/	4 << SHIFT
		},
		{
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	ADADIO_IOCTL_IRQ_SEL,
			/* arg		*/	ADADIO_IRQ_SEL_AIN_BURST_DONE,
			/* reg		*/	ADADIO_GSC_BCR,
			/* mask		*/	MASK,
			/* value	*/	5 << SHIFT
		},
		{
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	ADADIO_IOCTL_IRQ_SEL,
			/* arg		*/	ADADIO_IRQ_SEL_AOUT_STROBE_DONE,
			/* reg		*/	ADADIO_GSC_BCR,
			/* mask		*/	MASK,
			/* value	*/	6 << SHIFT
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
static int _function_sub_test(int fd, const service_data_t* list, const char* name)
{
	int errs	= 0;

	gsc_label(name);

	errs	+= adadio_initialize_quiet(fd);

	errs	+= service_ioctl_set_reg_list(fd, list);

	errs	+= adadio_initialize_quiet(fd);

	if (errs == 0)
		printf("PASS\n");

	return(errs);
}



//*****************************************************************************
static int _function_test(int fd)
{
	static const service_data_t	list_0[]	=
	{
		{					// IRQ: Initialize Done
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	ADADIO_IOCTL_IRQ_SEL,
			/* arg		*/	ADADIO_IRQ_SEL_INIT_DONE,
			/* reg		*/	-1,
			/* mask		*/	0,
			/* value	*/	0
		},
		{					// Clear IRQ Status
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	ADADIO_IOCTL_IRQ_STATUS,
			/* arg		*/	ADADIO_IRQ_STATUS_CLEAR,
			/* reg		*/	-1,
			/* mask		*/	0,
			/* value	*/	0
		},
		{					// Initiate an initialization.
			/* service	*/	SERVICE_REG_MOD,
			/* cmd		*/	0,
			/* arg		*/	0,
			/* reg		*/	ADADIO_GSC_BCR,
			/* mask		*/	0x80000000,
			/* value	*/	0x80000000
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
			/* reg		*/	ADADIO_GSC_BCR,
			/* mask		*/	0x4000000,
			/* value	*/	0x4000000
		},

		{ SERVICE_END_LIST }
	};

	static const service_data_t	list_1[]	=
	{
		{					// IRQ: Auto-Calibration Done
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	ADADIO_IOCTL_IRQ_SEL,
			/* arg		*/	ADADIO_IRQ_SEL_AUTO_CAL_DONE,
			/* reg		*/	-1,
			/* mask		*/	0,
			/* value	*/	0
		},
		{					// Clear IRQ Status
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	ADADIO_IOCTL_IRQ_STATUS,
			/* arg		*/	ADADIO_IRQ_STATUS_CLEAR,
			/* reg		*/	-1,
			/* mask		*/	0,
			/* value	*/	0
		},
		{					// Initiate an auto-calibration.
			/* service	*/	SERVICE_REG_MOD,
			/* cmd		*/	0,
			/* arg		*/	0,
			/* reg		*/	ADADIO_GSC_BCR,
			/* mask		*/	0x18000000,
			/* value	*/	0x10000000
		},
		{					// Wait for completion.
			/* service	*/	SERVICE_SLEEP,
			/* cmd		*/	0,
			/* arg		*/	15,
			/* reg		*/	-1,
			/* mask		*/	0,
			/* value	*/	0
		},
		{					// Verify that the status flag is set.
			/* service	*/	SERVICE_REG_TEST,
			/* cmd		*/	0,
			/* arg		*/	0,
			/* reg		*/	ADADIO_GSC_BCR,
			/* mask		*/	0x4000000,
			/* value	*/	0x4000000
		},

		{ SERVICE_END_LIST }
	};

	static const service_data_t	list_2[]	=
	{
		{
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	ADADIO_IOCTL_AIN_MODE,
			/* arg		*/	ADADIO_AIN_MODE_DIFF_BURST,
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
		{					// IRQ: Input Buffer Empty
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	ADADIO_IOCTL_IRQ_SEL,
			/* arg		*/	ADADIO_IRQ_SEL_AIN_BUF_EMPTY,
			/* reg		*/	-1,
			/* mask		*/	0,
			/* value	*/	0
		},
		{					// Clear IRQ Status
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	ADADIO_IOCTL_IRQ_STATUS,
			/* arg		*/	ADADIO_IRQ_STATUS_CLEAR,
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
		{					// Verify that the status flag is set.
			/* service	*/	SERVICE_REG_TEST,
			/* cmd		*/	0,
			/* arg		*/	0,
			/* reg		*/	ADADIO_GSC_BCR,
			/* mask		*/	0x4000000,
			/* value	*/	0x4000000
		},

		{ SERVICE_END_LIST }
	};

	static const service_data_t	list_3[]	=
	{
		{
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	ADADIO_IOCTL_AIN_MODE,
			/* arg		*/	ADADIO_AIN_MODE_DIFF_BURST,
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
		{
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	ADADIO_IOCTL_AIN_BUF_SIZE,
			/* arg		*/	ADADIO_AIN_BUF_SIZE_16,
			/* reg		*/	-1,
			/* mask		*/	0,
			/* value	*/	0
		},
		{					// IRQ: Input Buffer Half Full
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	ADADIO_IOCTL_IRQ_SEL,
			/* arg		*/	ADADIO_IRQ_SEL_AIN_BUF_HALF_FULL,
			/* reg		*/	-1,
			/* mask		*/	0,
			/* value	*/	0
		},
		{					// Clear IRQ Status
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	ADADIO_IOCTL_IRQ_STATUS,
			/* arg		*/	ADADIO_IRQ_STATUS_CLEAR,
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
		{					// Verify that the status flag is set.
			/* service	*/	SERVICE_REG_TEST,
			/* cmd		*/	0,
			/* arg		*/	0,
			/* reg		*/	ADADIO_GSC_BCR,
			/* mask		*/	0x4000000,
			/* value	*/	0x4000000
		},

		{ SERVICE_END_LIST }
	};

	static const service_data_t	list_4[]	=
	{
		{
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	ADADIO_IOCTL_AIN_MODE,
			/* arg		*/	ADADIO_AIN_MODE_DIFF_BURST,
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
		{
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	ADADIO_IOCTL_AIN_BUF_SIZE,
			/* arg		*/	ADADIO_AIN_BUF_SIZE_8,
			/* reg		*/	-1,
			/* mask		*/	0,
			/* value	*/	0
		},
		{					// IRQ: Input Buffer Full
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	ADADIO_IOCTL_IRQ_SEL,
			/* arg		*/	ADADIO_IRQ_SEL_AIN_BUF_FULL,
			/* reg		*/	-1,
			/* mask		*/	0,
			/* value	*/	0
		},
		{					// Clear IRQ Status
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	ADADIO_IOCTL_IRQ_STATUS,
			/* arg		*/	ADADIO_IRQ_STATUS_CLEAR,
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
		{					// Verify that the status flag is set.
			/* service	*/	SERVICE_REG_TEST,
			/* cmd		*/	0,
			/* arg		*/	0,
			/* reg		*/	ADADIO_GSC_BCR,
			/* mask		*/	0x4000000,
			/* value	*/	0x4000000
		},

		{ SERVICE_END_LIST }
	};

	static const service_data_t	list_5[]	=
	{
		{
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	ADADIO_IOCTL_AIN_MODE,
			/* arg		*/	ADADIO_AIN_MODE_DIFF_BURST,
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
		{					// IRQ: Input Burst Completed
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	ADADIO_IOCTL_IRQ_SEL,
			/* arg		*/	ADADIO_IRQ_SEL_AIN_BURST_DONE,
			/* reg		*/	-1,
			/* mask		*/	0,
			/* value	*/	0
		},
		{					// Clear IRQ Status
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	ADADIO_IOCTL_IRQ_STATUS,
			/* arg		*/	ADADIO_IRQ_STATUS_CLEAR,
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
		{					// Verify that the status flag is set.
			/* service	*/	SERVICE_REG_TEST,
			/* cmd		*/	0,
			/* arg		*/	0,
			/* reg		*/	ADADIO_GSC_BCR,
			/* mask		*/	0x4000000,
			/* value	*/	0x4000000
		},

		{ SERVICE_END_LIST }
	};

	static const service_data_t	list_6[]	=
	{
		{
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	ADADIO_IOCTL_AOUT_STROBE_ENABLE,
			/* arg		*/	ADADIO_AOUT_STROBE_ENABLE_YES,
			/* reg		*/	-1,
			/* mask		*/	0,
			/* value	*/	0
		},
		{					// IRQ: Output Strobe Completed
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	ADADIO_IOCTL_IRQ_SEL,
			/* arg		*/	ADADIO_IRQ_SEL_AOUT_STROBE_DONE,
			/* reg		*/	-1,
			/* mask		*/	0,
			/* value	*/	0
		},
		{					// Clear IRQ Status
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	ADADIO_IOCTL_IRQ_STATUS,
			/* arg		*/	ADADIO_IRQ_STATUS_CLEAR,
			/* reg		*/	-1,
			/* mask		*/	0,
			/* value	*/	0
		},
		{
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	ADADIO_IOCTL_AOUT_STROBE,
			/* arg		*/	0,
			/* reg		*/	-1,
			/* mask		*/	0,
			/* value	*/	0
		},
		{					// Verify that the status flag is set.
			/* service	*/	SERVICE_REG_TEST,
			/* cmd		*/	0,
			/* arg		*/	0,
			/* reg		*/	ADADIO_GSC_BCR,
			/* mask		*/	0x4000000,
			/* value	*/	0x4000000
		},

		{ SERVICE_END_LIST }
	};

	int errs	= 0;

	errs	+= _function_sub_test(fd, list_0, "Initialization Done");
	errs	+= _function_sub_test(fd, list_1, "Auto-Calibration Done");
	errs	+= _function_sub_test(fd, list_2, "Input Buffer Empty");
	errs	+= _function_sub_test(fd, list_3, "Input Buffer Half Full");
	errs	+= _function_sub_test(fd, list_4, "Input Buffer Full");
	errs	+= _function_sub_test(fd, list_5, "Input Burst Completed");
	errs	+= _function_sub_test(fd, list_6, "Output Strobe Completed");
	return(errs);
}



/******************************************************************************
*
*	Function:	irq_sel_test
*
*	Purpose:
*
*		Perform a test of the IOCTL service ADADIO_IOCTL_IRQ_SEL.
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

	gsc_label("ADADIO_IOCTL_IRQ_SEL");
	errs	+= _service_test(fd);

	if (errs == 0)
		printf("PASS\n");

	gsc_label_level_inc();
	errs	+= _function_test(fd);
	gsc_label_level_dec();

	return(errs);
}


