// $URL: http://subversion:8080/svn/gsc/trunk/drivers/LINUX/16AO20/16AO20_Linux_2.x.x.x_GSC_DN/sbtest/load_request.c $
// $Rev: 2014 $
// $Date: 2009-05-19 12:39:09 -0500 (Tue, 19 May 2009) $

#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/ioctl.h>

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
		{					// Enable only a single channel.
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	AO20_IOCTL_CHANNEL_SEL,
			/* arg		*/	0x1,
			/* reg		*/	-1,
			/* mask		*/	0,
			/* value	*/	0
		},
		{					// Output data with the EOF flag set.
			/* service	*/	SERVICE_REG_MOD,
			/* cmd		*/	0,
			/* arg		*/	0,
			/* reg		*/	AO20_GSC_ODBR,
			/* mask		*/	0x1FFFF,
			/* value	*/	0x10000
		},

		{ SERVICE_END_LIST }
	};

	static const service_data_t	list_2[]	=
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

	static const service_data_t	list_3[]	=
	{
		{					// Enable the clock.
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	AO20_IOCTL_CLOCK_ENABLE,
			/* arg		*/	AO20_CLOCK_ENABLE_YES,
			/* reg		*/	-1,
			/* mask		*/	0,
			/* value	*/	0
		},
		{					// Issue a load request.
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	AO20_IOCTL_LOAD_REQUEST,
			/* arg		*/	0,
			/* reg		*/	-1,
			/* mask		*/	0,
			/* value	*/	0
		},

		{ SERVICE_END_LIST }
	};

	__s32	_1_yes;
	__s32	_2_no;
	__s32	_3_m1;
	__s32	_3_to;
	__s32	_4_no;
	int		errs	= 0;

	errs	+= ao20_initialize_quiet(fd);

	errs	+= service_ioctl_set_reg_list(fd, list_1);
	errs	+= ao20_dsl_ioctl(fd, AO20_IOCTL_LOAD_READY,&_1_yes);

	errs	+= service_ioctl_set_reg_list(fd, list_2);
	errs	+= ao20_dsl_ioctl(fd, AO20_IOCTL_LOAD_READY,&_2_no);

	_3_m1	= ioctl(fd, AO20_IOCTL_LOAD_REQUEST, NULL);
	_3_to	= errno;

	// The buffer should empty almost immediately and return to circular mode.
	errs	+= service_ioctl_set_reg_list(fd, list_3);
	errs	+= ao20_dsl_ioctl(fd, AO20_IOCTL_LOAD_READY, &_4_no);

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
	else if (_3_m1 != -1)
	{
		errs++;
		printf("FAIL <--- (Test 3 did not fail.)\n");
	}
	else if (_3_to != ETIMEDOUT)
	{
		errs++;
		printf("FAIL <--- (Test 3 results are not ETIMEDOUT.)\n");
	}
	else if (_4_no != AO20_LOAD_READY_NO)
	{
		errs++;
		printf("FAIL <--- (Test 4 results are not NO.)\n");
	}

	errs	+= ao20_initialize_quiet(fd);
	return(errs);
}




/******************************************************************************
*
*	Function:	load_request_test
*
*	Purpose:
*
*		Perform a test of the IOCTL service AO20_IOCTL_LOAD_REQUEST.
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

int load_request_test(int fd)
{
	int	errs	= 0;

	gsc_label("AO20_IOCTL_LOAD_REQUEST");
	errs	+= _service_test(fd);
	errs	+= _function_test(fd);

	if (errs == 0)
		printf("PASS\n");

	return(errs);
}


