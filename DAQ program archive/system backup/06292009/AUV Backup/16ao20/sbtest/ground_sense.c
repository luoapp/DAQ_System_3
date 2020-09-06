// $URL: http://subversion:8080/svn/gsc/trunk/drivers/LINUX/16AO20/16AO20_Linux_2.x.x.x_GSC_DN/sbtest/ground_sense.c $
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
			/* cmd		*/	AO20_IOCTL_GROUND_SENSE,
			/* arg		*/	AO20_GROUND_SENSE_DISABLE,
			/* reg		*/	AO20_GSC_BCR,
			/* mask		*/	0x8,
			/* value	*/	0x0
		},
		{
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	AO20_IOCTL_GROUND_SENSE,
			/* arg		*/	AO20_GROUND_SENSE_REMOTE,
			/* reg		*/	AO20_GSC_BCR,
			/* mask		*/	0x8,
			/* value	*/	0x8
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
*	Function:	ground_sense_test
*
*	Purpose:
*
*		Perform a test of the IOCTL service AO20_IOCTL_GROUND_SENSE.
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

int ground_sense_test(int fd)
{
	int	errs	= 0;

	gsc_label("AO20_IOCTL_GROUND_SENSE");
	errs	+= _service_test(fd);
	errs	+= _function_test(fd);

	if (errs == 0)
		printf("PASS\n");

	return(errs);
}


