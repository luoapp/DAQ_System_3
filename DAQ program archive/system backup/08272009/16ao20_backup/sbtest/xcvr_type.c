// $URL: http://subversion:8080/svn/gsc/trunk/drivers/LINUX/16AO20/16AO20_Linux_2.x.x.x_GSC_DN/sbtest/xcvr_type.c $
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
			/* cmd		*/	AO20_IOCTL_XCVR_TYPE,
			/* arg		*/	AO20_XCVR_TYPE_TTL,
			/* reg		*/	AO20_GSC_BCR,
			/* mask		*/	0x20,
			/* value	*/	0x00
		},
		{
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	AO20_IOCTL_XCVR_TYPE,
			/* arg		*/	AO20_XCVR_TYPE_LVDS,
			/* reg		*/	AO20_GSC_BCR,
			/* mask		*/	0x20,
			/* value	*/	0x20
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
	// This requires external equipment to test.
	return(0);
}




/******************************************************************************
*
*	Function:	xcvr_type_test
*
*	Purpose:
*
*		Perform a test of the IOCTL service AO20_IOCTL_XCVR_TYPE.
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

int xcvr_type_test(int fd)
{
	int	errs	= 0;

	gsc_label("AO20_IOCTL_XCVR_TYPE");
	errs	+= _service_test(fd);
	errs	+= _function_test(fd);

	if (errs == 0)
		printf("PASS\n");

	return(errs);
}


