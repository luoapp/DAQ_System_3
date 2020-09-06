// $URL: http://subversion:8080/svn/gsc/trunk/drivers/LINUX/16AO20/16AO20_Linux_2.x.x.x_GSC_DN/sbtest/irq_state.c $
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
		{					// Clear IRQ Status
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	AO20_IOCTL_IRQ_STATE,
			/* arg		*/	AO20_IRQ_STATE_CLEAR,
			/* reg		*/	-1,
			/* mask		*/	0,
			/* value	*/	0
		},

		{ SERVICE_END_LIST }
	};

	static const service_data_t	list_2[]	=
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

	__s32	_1_idle;
	__s32	_2_act;
	int		errs	= 0;

	errs	+= ao20_initialize_quiet(fd);

	errs	+= service_ioctl_set_reg_list(fd, list_1);
	_1_idle	= -1;
	errs	+= ao20_dsl_ioctl(fd, AO20_IOCTL_IRQ_STATE,&_1_idle);

	_2_act	= -1;
	errs	+= service_ioctl_set_reg_list(fd, list_2);
	errs	+= ao20_dsl_ioctl(fd, AO20_IOCTL_IRQ_STATE,&_2_act);

	if (errs)
	{
	}
	else if (_1_idle != AO20_IRQ_STATE_IDLE)
	{
		errs++;
		printf("FAIL <--- (List 1 results are not IDLE.)\n");
	}
	else if (_2_act != AO20_IRQ_STATE_ACTIVE)
	{
		errs++;
		printf("FAIL <--- (List 2 results are not ACTIVE.)\n");
	}

	errs	+= ao20_initialize_quiet(fd);
	return(errs);
}




/******************************************************************************
*
*	Function:	irq_state_test
*
*	Purpose:
*
*		Perform a test of the IOCTL service AO20_IOCTL_IRQ_STATE.
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

int irq_state_test(int fd)
{
	int	errs	= 0;

	gsc_label("AO20_IOCTL_IRQ_STATE");
	errs	+= _service_test(fd);
	errs	+= _function_test(fd);

	if (errs == 0)
		printf("PASS\n");

	return(errs);
}


