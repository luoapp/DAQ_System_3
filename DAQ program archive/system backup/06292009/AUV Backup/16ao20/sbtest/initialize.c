// $URL: http://subversion:8080/svn/gsc/trunk/drivers/LINUX/16AO20/16AO20_Linux_2.x.x.x_GSC_DN/sbtest/initialize.c $
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
		{					// Select a non-zero value interrupt/
			/* service	*/	SERVICE_REG_MOD,
			/* cmd		*/	0,
			/* arg		*/	0,
			/* reg		*/	AO20_GSC_BCR,
			/* mask		*/	0x700,
			/* value	*/	0x100
		},

		{					// Perform initialization.
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	AO20_IOCTL_INITIALIZE,
			/* arg		*/	0,
			/* reg		*/	-1,
			/* mask		*/	0,
			/* value	*/	0
		},

		{					// Verify that init is done.
			/* service	*/	SERVICE_REG_TEST,
			/* cmd		*/	0,
			/* arg		*/	0,
			/* reg		*/	AO20_GSC_BCR,
			/* mask		*/	0x8000,
			/* value	*/	0x0000
		},
		{					// Verify that the irq was reset.
			/* service	*/	SERVICE_REG_TEST,
			/* cmd		*/	0,
			/* arg		*/	0,
			/* reg		*/	AO20_GSC_BCR,
			/* mask		*/	0x700,
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
*	Function:	initialize_test
*
*	Purpose:
*
*		Perform a test of the IOCTL service AO20_IOCTL_INITIALIZE.
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

int initialize_test(int fd)
{
	int	errs	= 0;

	gsc_label("AO20_IOCTL_INITIALIZE");
	errs	+= _service_test(fd);
	errs	+= _function_test(fd);

	if (errs == 0)
		printf("PASS\n");

	return(errs);
}


