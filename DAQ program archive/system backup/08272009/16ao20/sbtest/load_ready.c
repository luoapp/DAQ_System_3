// $URL: http://subversion:8080/svn/gsc/trunk/drivers/LINUX/16AO20/16AO20_Linux_2.x.x.x_GSC_DN/sbtest/load_ready.c $
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
		{					// Select circular mode.
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	AO20_IOCTL_BUFFER_MODE,
			/* arg		*/	AO20_BUFFER_MODE_CIRC,
			/* reg		*/	-1,
			/* mask		*/	0,
			/* value	*/	0
		},

		{ SERVICE_END_LIST }
	};

	__s32	_1_yes;
	__s32	_2_no;
	int		errs	= 0;

	errs	+= ao20_initialize_quiet(fd);

	errs	+= ao20_dsl_ioctl(fd, AO20_IOCTL_LOAD_READY,&_1_yes);

	errs	+= service_ioctl_set_reg_list(fd, list);

	errs	+= ao20_dsl_ioctl(fd, AO20_IOCTL_LOAD_READY,&_2_no);

	if (errs)
	{
	}
	else if (_1_yes != AO20_LOAD_READY_YES)
	{
		errs++;
		printf("FAIL <--- (Test 1 results are not YES.)\n");
	}
	else if (_2_no != AO20_LOAD_READY_NO)
	{
		errs++;
		printf("FAIL <--- (Test 2 results are not NO.)\n");
	}

	errs	+= ao20_initialize_quiet(fd);
	return(errs);
}




/******************************************************************************
*
*	Function:	load_ready_test
*
*	Purpose:
*
*		Perform a test of the IOCTL service AO20_IOCTL_LOAD_READY.
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

int load_ready_test(int fd)
{
	int	errs	= 0;

	gsc_label("AO20_IOCTL_LOAD_READY");
	errs	+= _service_test(fd);
	errs	+= _function_test(fd);

	if (errs == 0)
		printf("PASS\n");

	return(errs);
}


