// $URL: http://subversion:8080/svn/gsc/trunk/drivers/LINUX/ADADIO/ADADIO_Linux_3.x.x.x_GSC_DN/sbtest/auto_calibrate.c $
// $Rev: 1620 $
// $Date: 2009-04-10 11:41:41 -0500 (Fri, 10 Apr 2009) $

#include <stdio.h>

#include "main.h"



//*****************************************************************************
static int _service_test(int fd)
{
	static const service_data_t	list[]	=
	{
		{
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	ADADIO_IOCTL_AUTO_CALIBRATE,
			/* arg		*/	0,
			/* reg		*/	ADADIO_GSC_BCR,
			/* mask		*/	0x18000020,
			/* value	*/	0x00000000
		},

		{ SERVICE_END_LIST }
	};

	int errs	= 0;

	errs	+= adadio_initialize_quiet(fd);

	errs	+= service_ioctl_set_reg_list(fd, list);

	errs	+= service_ioctl_set_reg_list(fd, list);

	errs	+= adadio_initialize_quiet(fd);
	return(errs);
}




//*****************************************************************************
static int _function_test(int fd)
{
	int errs	= 0;

	// This would require additional equipment.
	return(errs);
}




/******************************************************************************
*
*	Function:	auto_calibrate_test
*
*	Purpose:
*
*		Perform a test of the IOCTL service ADADIO_IOCTL_AUTO_CALIBRATE. We can't
*		verify that an auto-calibration was performed, so we simply check that
*		the respective bits are correct afterwards.
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

int auto_calibrate_test(int fd)
{
	int	errs	= 0;

	gsc_label("ADADIO_IOCTL_AUTO_CALIBRATE");
	errs	+= _service_test(fd);
	errs	+= _function_test(fd);

	if (errs == 0)
		printf("PASS\n");

	return(errs);
}


