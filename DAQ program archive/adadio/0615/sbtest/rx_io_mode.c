// $URL: http://subversion:8080/svn/gsc/trunk/drivers/LINUX/ADADIO/ADADIO_Linux_3.x.x.x_GSC_DN/sbtest/rx_io_mode.c $
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
			/* cmd		*/	ADADIO_IOCTL_RX_IO_MODE,
			/* arg		*/	GSC_IO_MODE_DMDMA,
			/* reg		*/	-1,
			/* mask		*/	0,
			/* value	*/	0
		},
		{
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	ADADIO_IOCTL_RX_IO_MODE,
			/* arg		*/	GSC_IO_MODE_DMA,
			/* reg		*/	-1,
			/* mask		*/	0,
			/* value	*/	0
		},
		{
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	ADADIO_IOCTL_RX_IO_MODE,
			/* arg		*/	GSC_IO_MODE_PIO,
			/* reg		*/	-1,
			/* mask		*/	0,
			/* value	*/	0
		},

		{ SERVICE_END_LIST }
	};

	__s32	dmdma;
	int		errs	= 0;

	errs	+= adadio_query_quiet(fd, ADADIO_QUERY_DMDMA, &dmdma);

	if (errs == 0)
	{
		dmdma	= dmdma ? 0 : 1;
		errs	+= adadio_initialize_quiet(fd);

		errs	+= service_ioctl_set_get_list(fd, list + dmdma);

		errs	+= service_ioctl_set_get_list(fd, list + dmdma);

		errs	+= adadio_initialize_quiet(fd);
	}

	return(errs);
}




//*****************************************************************************
static int _function_test(int fd)
{
	int errs	= 0;

	// There aren't simple functional tests we can perform to verify this.
	return(errs);
}




/******************************************************************************
*
*	Function:	rx_io_mode_test
*
*	Purpose:
*
*		Perform a test of the IOCTL service ADADIO_IOCTL_RX_IO_MODE.
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

int rx_io_mode_test(int fd)
{
	int	errs	= 0;

	gsc_label("ADADIO_IOCTL_RX_IO_MODE");
	errs	+= _service_test(fd);
	errs	+= _function_test(fd);

	if (errs == 0)
		printf("PASS\n");

	return(errs);
}


