// $URL: http://subversion:8080/svn/gsc/trunk/drivers/LINUX/ADADIO/ADADIO_Linux_3.x.x.x_GSC_DN/sbtest/irq_status.c $
// $Rev: 1620 $
// $Date: 2009-04-10 11:41:41 -0500 (Fri, 10 Apr 2009) $

#include <stdio.h>

#include "main.h"
#include "adadio_dsl.h"



//*****************************************************************************
static int _service_test(int fd)
{
	int errs	= 0;

	// There are no persistent bits to test with this service.
	return(errs);
}




//*****************************************************************************
static int _function_test(int fd)
{
	static const service_data_t	list_1[]	=
	{
		{
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	ADADIO_IOCTL_AOUT_STROBE_ENABLE,
			/* arg		*/	ADADIO_AOUT_STROBE_ENABLE_YES,
			/* reg		*/	-1,
			/* mask		*/	0,
			/* value	*/	0
		},
		{					// IRQ: Output Strobe Completed
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	ADADIO_IOCTL_IRQ_SEL,
			/* arg		*/	ADADIO_IRQ_SEL_AOUT_STROBE_DONE,
			/* reg		*/	-1,
			/* mask		*/	0,
			/* value	*/	0
		},
		{					// Clear IRQ Status
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	ADADIO_IOCTL_IRQ_STATUS,
			/* arg		*/	ADADIO_IRQ_STATUS_CLEAR,
			/* reg		*/	-1,
			/* mask		*/	0,
			/* value	*/	0
		},

		{ SERVICE_END_LIST }
	};

	static const service_data_t	list_2[]	=
	{
		{
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	ADADIO_IOCTL_AOUT_STROBE,
			/* arg		*/	0,
			/* reg		*/	-1,
			/* mask		*/	0,
			/* value	*/	0
		},

		{ SERVICE_END_LIST }
	};

	int		errs	= 0;
	__s32	sts;

	errs	+= adadio_initialize_quiet(fd);

	errs	+= service_ioctl_set_reg_list(fd, list_1);
	sts		= -1;
	errs	+= adadio_dsl_ioctl(fd, ADADIO_IOCTL_IRQ_STATUS, &sts);

	if ((errs == 0) && (sts != ADADIO_IRQ_STATUS_IDLE))
	{
		errs++;
		printf(	"FAIL <---  (%d. Expected IDLE status, got %ld)\n",
				__LINE__,
				(long) sts);
	}

	errs	+= service_ioctl_set_reg_list(fd, list_2);
	sts		= ADADIO_IRQ_STATUS_IGNORE;
	errs	+= adadio_dsl_ioctl(fd, ADADIO_IOCTL_IRQ_STATUS, &sts);

	if ((errs == 0) && (sts != ADADIO_IRQ_STATUS_ACTIVE))
	{
		errs++;
		printf(	"FAIL <---  (%d. Expected ACTIVE status, got %ld)\n",
				__LINE__,
				(long) sts);
	}

	sts		= ADADIO_IRQ_STATUS_CLEAR;
	errs	+= adadio_dsl_ioctl(fd, ADADIO_IOCTL_IRQ_STATUS, &sts);

	if ((errs == 0) && (sts != ADADIO_IRQ_STATUS_IDLE))
	{
		errs++;
		printf(	"FAIL <---  (%d. Expected ACTIVE status, got %ld)\n",
				__LINE__,
				(long) sts);
	}

	errs	+= adadio_initialize_quiet(fd);
	return(errs);
}



/******************************************************************************
*
*	Function:	irq_status_test
*
*	Purpose:
*
*		Perform a test of the IOCTL service ADADIO_IOCTL_IRQ_STATUS.
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

int irq_status_test(int fd)
{
	int	errs	= 0;

	gsc_label("ADADIO_IOCTL_IRQ_STATUS");
	errs	+= _service_test(fd);
	errs	+= _function_test(fd);

	if (errs == 0)
		printf("PASS\n");

	return(errs);
}


