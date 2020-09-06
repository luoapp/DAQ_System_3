// $URL: http://subversion:8080/svn/gsc/trunk/drivers/LINUX/16AO20/16AO20_Linux_2.x.x.x_GSC_DN/sbtest/buffer_over_data.c $
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
		// Fill the buffer.

		{					// Make the buffer as small as possible.
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	AO20_IOCTL_BUFFER_SIZE,
			/* arg		*/	AO20_BUFFER_SIZE_8,
			/* reg		*/	-1,
			/* mask		*/	0,
			/* value	*/	0
		},
		{					// Put data in the buffer (1 sample).
			/* service	*/	SERVICE_REG_MOD,
			/* cmd		*/	0,
			/* arg		*/	0,
			/* reg		*/	AO20_GSC_ODBR,
			/* mask		*/	0x0000,
			/* value	*/	0x0000
		},
		{					// Put data in the buffer (2 samples).
			/* service	*/	SERVICE_REG_MOD,
			/* cmd		*/	0,
			/* arg		*/	0,
			/* reg		*/	AO20_GSC_ODBR,
			/* mask		*/	0x0000,
			/* value	*/	0x0000
		},
		{					// Put data in the buffer (3 samples).
			/* service	*/	SERVICE_REG_MOD,
			/* cmd		*/	0,
			/* arg		*/	0,
			/* reg		*/	AO20_GSC_ODBR,
			/* mask		*/	0x0000,
			/* value	*/	0x0000
		},
		{					// Put data in the buffer (4 samples).
			/* service	*/	SERVICE_REG_MOD,
			/* cmd		*/	0,
			/* arg		*/	0,
			/* reg		*/	AO20_GSC_ODBR,
			/* mask		*/	0x0000,
			/* value	*/	0x0000
		},
		{					// Put data in the buffer (5 samples).
			/* service	*/	SERVICE_REG_MOD,
			/* cmd		*/	0,
			/* arg		*/	0,
			/* reg		*/	AO20_GSC_ODBR,
			/* mask		*/	0x0000,
			/* value	*/	0x0000
		},
		{					// Put data in the buffer (6 samples).
			/* service	*/	SERVICE_REG_MOD,
			/* cmd		*/	0,
			/* arg		*/	0,
			/* reg		*/	AO20_GSC_ODBR,
			/* mask		*/	0x0000,
			/* value	*/	0x0000
		},
		{					// Put data in the buffer (7 samples).
			/* service	*/	SERVICE_REG_MOD,
			/* cmd		*/	0,
			/* arg		*/	0,
			/* reg		*/	AO20_GSC_ODBR,
			/* mask		*/	0x0000,
			/* value	*/	0x0000
		},
		{					// Put data in the buffer (8 samples).
			/* service	*/	SERVICE_REG_MOD,
			/* cmd		*/	0,
			/* arg		*/	0,
			/* reg		*/	AO20_GSC_ODBR,
			/* mask		*/	0x0000,
			/* value	*/	0x0000
		},
		{					// Verify that there is NOT a data overflow.
			/* service	*/	SERVICE_REG_TEST,
			/* cmd		*/	0,
			/* arg		*/	0,
			/* reg		*/	AO20_GSC_BOR,
			/* mask		*/	0x10000,
			/* value	*/	0x00000
		},

		{ SERVICE_END_LIST }
	};

	static const service_data_t	list_2[]	=
	{
		// Over fill the buffer.

		{					// Put data in the buffer (9 samples).
			/* service	*/	SERVICE_REG_MOD,
			/* cmd		*/	0,
			/* arg		*/	0,
			/* reg		*/	AO20_GSC_ODBR,
			/* mask		*/	0x0000,
			/* value	*/	0x0000
		},

		{ SERVICE_END_LIST }
	};

	static const service_data_t	list_3[]	=
	{
		// Clear the status.

		{					// Clear the status.
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	AO20_IOCTL_BUFFER_OVER_DATA,
			/* arg		*/	AO20_BUFFER_OVER_DATA_CLR,
			/* reg		*/	-1,
			/* mask		*/	0,
			/* value	*/	0
		},

		{ SERVICE_END_LIST }
	};

	__s32	_1_no;
	__s32	_2_yes;
	__s32	_3_no;
	int		errs	= 0;

	errs	+= ao20_initialize_quiet(fd);

	errs	+= service_ioctl_set_reg_list(fd, list_1);
	_1_no	= AO20_BUFFER_OVER_DATA_CHK;
	errs	+= ao20_dsl_ioctl(fd, AO20_IOCTL_BUFFER_OVER_DATA,&_1_no);

	errs	+= service_ioctl_set_reg_list(fd, list_2);
	_2_yes	= AO20_BUFFER_OVER_DATA_CHK;
	errs	+= ao20_dsl_ioctl(fd, AO20_IOCTL_BUFFER_OVER_DATA,&_2_yes);

	errs	+= service_ioctl_set_reg_list(fd, list_3);
	_3_no	= AO20_BUFFER_OVER_DATA_CHK;
	errs	+= ao20_dsl_ioctl(fd, AO20_IOCTL_BUFFER_OVER_DATA,&_3_no);

	if (errs)
	{
	}
	else if (_1_no != AO20_BUFFER_OVER_DATA_NO)
	{
		errs++;
		printf("FAIL <--- (List 1 results are not NO.)\n");
	}
	else if (_2_yes != AO20_BUFFER_OVER_DATA_YES)
	{
		errs++;
		printf("FAIL <--- (List 2 results are not YES.)\n");
	}
	else if (_3_no != AO20_BUFFER_OVER_DATA_NO)
	{
		errs++;
		printf("FAIL <--- (List 3 results are not NO.)\n");
	}

	errs	+= ao20_initialize_quiet(fd);
	return(errs);
}




/******************************************************************************
*
*	Function:	buffer_over_data_test
*
*	Purpose:
*
*		Perform a test of the IOCTL service AO20_IOCTL_BUFFER_OVER_DATA.
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

int buffer_over_data_test(int fd)
{
	int	errs	= 0;

	gsc_label("AO20_IOCTL_BUFFER_OVER_DATA");
	errs	+= _service_test(fd);
	errs	+= _function_test(fd);

	if (errs == 0)
		printf("PASS\n");

	return(errs);
}


