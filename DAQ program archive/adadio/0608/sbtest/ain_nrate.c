// $URL: http://subversion:8080/svn/gsc/trunk/drivers/LINUX/ADADIO/ADADIO_Linux_3.x.x.x_GSC_DN/sbtest/ain_nrate.c $
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
			/* cmd		*/	ADADIO_IOCTL_AIN_NRATE,
			/* arg		*/	0xFFFF,
			/* reg		*/	ADADIO_GSC_SRR,
			/* mask		*/	0xFFFF,
			/* value	*/	0xFFFF
		},
		{
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	ADADIO_IOCTL_AIN_NRATE,
			/* arg		*/	0xAAAA,
			/* reg		*/	ADADIO_GSC_SRR,
			/* mask		*/	0xFFFF,
			/* value	*/	0xAAAA
		},
		{
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	ADADIO_IOCTL_AIN_NRATE,
			/* arg		*/	0x5555,
			/* reg		*/	ADADIO_GSC_SRR,
			/* mask		*/	0xFFFF,
			/* value	*/	0x5555
		},
		{
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	ADADIO_IOCTL_AIN_NRATE,
			/* arg		*/	0xF000,
			/* reg		*/	ADADIO_GSC_SRR,
			/* mask		*/	0xFFFF,
			/* value	*/	0xF000
		},
		{
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	ADADIO_IOCTL_AIN_NRATE,
			/* arg		*/	0x0F00,
			/* reg		*/	ADADIO_GSC_SRR,
			/* mask		*/	0xFFFF,
			/* value	*/	0x0F00
		},
		{
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	ADADIO_IOCTL_AIN_NRATE,
			/* arg		*/	0x00F0,
			/* reg		*/	ADADIO_GSC_SRR,
			/* mask		*/	0xFFFF,
			/* value	*/	0x00F0
		},
		{
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	ADADIO_IOCTL_AIN_NRATE,
			/* arg		*/	0x0064,
			/* reg		*/	ADADIO_GSC_SRR,
			/* mask		*/	0xFFFF,
			/* value	*/	0x0064
		},

		{ SERVICE_END_LIST }
	};

	int errs	= 0;

	errs	+= adadio_initialize_quiet(fd);

	errs	+= service_ioctl_reg_get_list(fd, list);
	errs	+= service_ioctl_set_reg_list(fd, list);

	errs	+= service_ioctl_reg_get_list(fd, list);
	errs	+= service_ioctl_set_reg_list(fd, list);

	errs	+= adadio_initialize_quiet(fd);
	return(errs);
}




//*****************************************************************************
static int _function_test(int fd)
{
	int errs	= 0;

	// This requires external equipment to test.
	return(errs);
}




/******************************************************************************
*
*	Function:	ain_nrate_test
*
*	Purpose:
*
*		Perform a test of the IOCTL service ADADIO_IOCTL_AIN_NRATE.
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

int ain_nrate_test(int fd)
{
	int	errs	= 0;

	gsc_label("ADADIO_IOCTL_AIN_NRATE");
	errs	+= _service_test(fd);
if (errs == 999)
	errs	+= _function_test(fd);

	if (errs == 0)
		printf("PASS\n");

	return(errs);
}


