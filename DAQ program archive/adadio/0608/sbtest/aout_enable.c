// $URL: http://subversion:8080/svn/gsc/trunk/drivers/LINUX/ADADIO/ADADIO_Linux_3.x.x.x_GSC_DN/sbtest/aout_enable.c $
// $Rev: 1620 $
// $Date: 2009-04-10 11:41:41 -0500 (Fri, 10 Apr 2009) $

#include <errno.h>
#include <stdio.h>
#include <unistd.h>

#include "main.h"



//*****************************************************************************
static int _service_test(int fd)
{
	#define	MASK	(1 << SHIFT)
	#define	SHIFT	18

	static const service_data_t	list[]	=
	{
		{
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	ADADIO_IOCTL_AOUT_ENABLE,
			/* arg		*/	ADADIO_AOUT_ENABLE_NO,
			/* reg		*/	ADADIO_GSC_BCR,
			/* mask		*/	MASK,
			/* value	*/	0 << SHIFT
		},
		{
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	ADADIO_IOCTL_AOUT_ENABLE,
			/* arg		*/	ADADIO_AOUT_ENABLE_YES,
			/* reg		*/	ADADIO_GSC_BCR,
			/* mask		*/	MASK,
			/* value	*/	1 << SHIFT
		},

		{ SERVICE_END_LIST }
	};

	int errs	= 0;

	errs	+= adadio_initialize_quiet(fd);

	errs	+= service_ioctl_set_reg_list(fd, list);
	errs	+= service_ioctl_reg_get_list(fd, list);

	errs	+= service_ioctl_set_reg_list(fd, list);
	errs	+= service_ioctl_reg_get_list(fd, list);

	errs	+= adadio_initialize_quiet(fd);
	return(errs);
}




//*****************************************************************************
static int _function_test(int fd)
{
	// Additional equipment is required to test this service.
	return(0);
}




/******************************************************************************
*
*	Function:	aout_enable_test
*
*	Purpose:
*
*		Perform a test of the IOCTL service ADADIO_IOCTL_AOUT_ENABLE.
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

int aout_enable_test(int fd)
{
	int	errs	= 0;

	gsc_label("ADADIO_IOCTL_AOUT_ENABLE");
	errs	+= _service_test(fd);
	errs	+= _function_test(fd);

	if (errs == 0)
		printf("PASS\n");

	return(errs);
}


