// $URL: http://subversion:8080/svn/gsc/trunk/drivers/LINUX/16AO20/16AO20_Linux_2.x.x.x_GSC_DN/sbtest/irq_enable.c $
// $Rev: 2014 $
// $Date: 2009-05-19 12:39:09 -0500 (Tue, 19 May 2009) $

#include <errno.h>
#include <stdio.h>
#include <unistd.h>

#include "main.h"



//*****************************************************************************
static int _service_test(int fd)
{
	static const service_data_t	list[]	=
	{
		{
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	AO20_IOCTL_IRQ_ENABLE,
			/* arg		*/	AO20_IRQ_ENABLE_NO,
			/* reg		*/	GSC_PLX_9080_INTCSR,
			/* mask		*/	0x800,
			/* value	*/	0x000
		},
		{
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	AO20_IOCTL_IRQ_ENABLE,
			/* arg		*/	AO20_IRQ_ENABLE_YES,
			/* reg		*/	GSC_PLX_9080_INTCSR,
			/* mask		*/	0x800,
			/* value	*/	0x800
		},

		{ SERVICE_END_LIST }
	};

	int errs	= 0;

	errs	+= ao20_initialize_quiet(fd);

	errs	+= service_ioctl_set_reg_list(fd, list);

	errs	+= service_ioctl_set_reg_list(fd, list);

	errs	+= ao20_initialize_quiet(fd);
	return(errs);
}




//*****************************************************************************
static int _function_test(int fd)
{
	static const service_data_t	list[]	=
	{
		{					// IRQ: output Buffer Empty
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
		{					// Verify that IRQ status flag is clear.
			/* service	*/	SERVICE_REG_TEST,
			/* cmd		*/	0,
			/* arg		*/	0,
			/* reg		*/	AO20_GSC_BCR,
			/* mask		*/	0x800,
			/* value	*/	0x000
		},

		// Verify that the interrupt gets cleared.

		{					// Enable local interrupt.
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	AO20_IOCTL_IRQ_ENABLE,
			/* arg		*/	AO20_IRQ_ENABLE_YES,
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
		{					// Wait a bit.
			/* service	*/	SERVICE_SLEEP,
			/* cmd		*/	0,
			/* arg		*/	1,
			/* reg		*/	-1,
			/* mask		*/	0,
			/* value	*/	0
		},
		{					// Verify that the interrupt bit is clear.
			/* service	*/	SERVICE_REG_TEST,
			/* cmd		*/	0,
			/* arg		*/	0,
			/* reg		*/	GSC_PLX_9080_INTCSR,
			/* mask		*/	0x800,
			/* value	*/	0x000
		},

		// Verify that the interrupt stays cleared.

		{					// Disable local interrupt.
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	AO20_IOCTL_IRQ_ENABLE,
			/* arg		*/	AO20_IRQ_ENABLE_NO,
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
		{					// Wait a bit.
			/* service	*/	SERVICE_SLEEP,
			/* cmd		*/	0,
			/* arg		*/	1,
			/* reg		*/	-1,
			/* mask		*/	0,
			/* value	*/	0
		},
		{					// Verify that the interrupt bit is clear.
			/* service	*/	SERVICE_REG_TEST,
			/* cmd		*/	0,
			/* arg		*/	0,
			/* reg		*/	GSC_PLX_9080_INTCSR,
			/* mask		*/	0x800,
			/* value	*/	0x000
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
*	Function:	irq_enable_test
*
*	Purpose:
*
*		Perform a test of the IOCTL service AO20_IOCTL_IRQ_ENABLE.
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

int irq_enable_test(int fd)
{
	int	errs	= 0;

	gsc_label("AO20_IOCTL_IRQ_ENABLE");
	errs	+= _service_test(fd);
	errs	+= _function_test(fd);

	if (errs == 0)
		printf("PASS\n");

	return(errs);
}


