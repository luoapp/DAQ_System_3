// $URL: http://subversion:8080/svn/gsc/trunk/drivers/LINUX/16AO20/16AO20_Linux_2.x.x.x_GSC_DN/sbtest/buffer_mode.c $
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
			/* cmd		*/	AO20_IOCTL_BUFFER_MODE,
			/* arg		*/	AO20_BUFFER_MODE_OPEN,
			/* reg		*/	AO20_GSC_BOR,
			/* mask		*/	0x100,
			/* value	*/	0x000
		},
		{
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	AO20_IOCTL_BUFFER_MODE,
			/* arg		*/	AO20_BUFFER_MODE_CIRC,
			/* reg		*/	AO20_GSC_BOR,
			/* mask		*/	0x100,
			/* value	*/	0x100
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
	static const service_data_t	list[]	=
	{
		// Verify the CIRCULAR setting.

		{					// Put the buffer in circular mode.
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	AO20_IOCTL_BUFFER_MODE,
			/* arg		*/	AO20_BUFFER_MODE_CIRC,
			/* reg		*/	-1,
			/* mask		*/	0,
			/* value	*/	0
		},
		{					// Verify that there is NOT a frame overflow.
			/* service	*/	SERVICE_REG_TEST,
			/* cmd		*/	0,
			/* arg		*/	0,
			/* reg		*/	AO20_GSC_BOR,
			/* mask		*/	0x20000,
			/* value	*/	0x00000
		},
		{					// Put data in the buffer, or at least try.
			/* service	*/	SERVICE_REG_MOD,
			/* cmd		*/	0,
			/* arg		*/	0,
			/* reg		*/	AO20_GSC_ODBR,
			/* mask		*/	0x0000,
			/* value	*/	0x0000
		},
		{					// Verify that there IS a frame overflow.
			/* service	*/	SERVICE_REG_TEST,
			/* cmd		*/	0,
			/* arg		*/	0,
			/* reg		*/	AO20_GSC_BOR,
			/* mask		*/	0x20000,
			/* value	*/	0x20000
		},

		// Verify the OPEN setting.

		{					// Put the buffer in open mode.
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	AO20_IOCTL_BUFFER_MODE,
			/* arg		*/	AO20_BUFFER_MODE_OPEN,
			/* reg		*/	-1,
			/* mask		*/	0,
			/* value	*/	0
		},
		{					// Verify that the buffer IS empty.
			/* service	*/	SERVICE_REG_TEST,
			/* cmd		*/	0,
			/* arg		*/	0,
			/* reg		*/	AO20_GSC_BOR,
			/* mask		*/	0xF000,
			/* value	*/	0x3000
		},
		{					// Put data in the buffer.
			/* service	*/	SERVICE_REG_MOD,
			/* cmd		*/	0,
			/* arg		*/	0,
			/* reg		*/	AO20_GSC_ODBR,
			/* mask		*/	0x0000,
			/* value	*/	0x0000
		},
		{					// Verify that the buffer is NOT empty.
			/* service	*/	SERVICE_REG_TEST,
			/* cmd		*/	0,
			/* arg		*/	0,
			/* reg		*/	AO20_GSC_BOR,
			/* mask		*/	0xF000,
			/* value	*/	0x2000
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
*	Function:	buffer_mode_test
*
*	Purpose:
*
*		Perform a test of the IOCTL service AO20_IOCTL_BUFFER_MODE.
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

int buffer_mode_test(int fd)
{
	int	errs	= 0;

	gsc_label("AO20_IOCTL_BUFFER_MODE");
	errs	+= _service_test(fd);
	errs	+= _function_test(fd);

	if (errs == 0)
		printf("PASS\n");

	return(errs);
}


