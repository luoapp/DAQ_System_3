// $URL: http://subversion:8080/svn/gsc/trunk/drivers/LINUX/ADADIO/ADADIO_Linux_3.x.x.x_GSC_DN/sbtest/ain_chan_last.c $
// $Rev: 1620 $
// $Date: 2009-04-10 11:41:41 -0500 (Fri, 10 Apr 2009) $

#include <stdio.h>

#include "main.h"
#include "adadio_dsl.h"



//*****************************************************************************
static int _service_test(int fd)
{
	#define	MASK	(7 << SHIFT)
	#define	SHIFT	15

	static const service_data_t	list[]	=
	{
		{
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	ADADIO_IOCTL_AIN_CHAN_LAST,
			/* arg		*/	0,
			/* reg		*/	ADADIO_GSC_BCR,
			/* mask		*/	MASK,
			/* value	*/	0 << SHIFT
		},
		{
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	ADADIO_IOCTL_AIN_CHAN_LAST,
			/* arg		*/	1,
			/* reg		*/	ADADIO_GSC_BCR,
			/* mask		*/	MASK,
			/* value	*/	1 << SHIFT
		},
		{
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	ADADIO_IOCTL_AIN_CHAN_LAST,
			/* arg		*/	2,
			/* reg		*/	ADADIO_GSC_BCR,
			/* mask		*/	MASK,
			/* value	*/	2 << SHIFT
		},
		{
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	ADADIO_IOCTL_AIN_CHAN_LAST,
			/* arg		*/	3,
			/* reg		*/	ADADIO_GSC_BCR,
			/* mask		*/	MASK,
			/* value	*/	3 << SHIFT
		},
		{
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	ADADIO_IOCTL_AIN_CHAN_LAST,
			/* arg		*/	4,
			/* reg		*/	ADADIO_GSC_BCR,
			/* mask		*/	MASK,
			/* value	*/	4 << SHIFT
		},
		{
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	ADADIO_IOCTL_AIN_CHAN_LAST,
			/* arg		*/	5,
			/* reg		*/	ADADIO_GSC_BCR,
			/* mask		*/	MASK,
			/* value	*/	5 << SHIFT
		},
		{
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	ADADIO_IOCTL_AIN_CHAN_LAST,
			/* arg		*/	6,
			/* reg		*/	ADADIO_GSC_BCR,
			/* mask		*/	MASK,
			/* value	*/	6 << SHIFT
		},
		{
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	ADADIO_IOCTL_AIN_CHAN_LAST,
			/* arg		*/	7,
			/* reg		*/	ADADIO_GSC_BCR,
			/* mask		*/	MASK,
			/* value	*/	7 << SHIFT
		},

		{ SERVICE_END_LIST }
	};

	int	errs	= 0;

	errs	+= adadio_initialize_quiet(fd);

	errs	+= service_ioctl_set_reg_list(fd, list);
	errs	+= service_ioctl_reg_get_list(fd, list);

	errs	+= service_ioctl_set_reg_list(fd, list);
	errs	+= service_ioctl_reg_get_list(fd, list);

	errs	+= adadio_initialize_quiet(fd);
	return(errs);
}




//*****************************************************************************
static int _function_sub_test(int fd, int last, __s32 sts_1, __s32 sts_2)
{
	service_data_t	list_1[]	=
	{
		{				// Enable Bursting
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	ADADIO_IOCTL_AIN_MODE,
			/* arg		*/	ADADIO_AIN_MODE_DIFF_BURST,
			/* reg		*/	-1,
			/* mask		*/	0,
			/* value	*/	0
		},
		{					// Adjust the buffer size.
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	ADADIO_IOCTL_AIN_BUF_SIZE,
			/* arg		*/	ADADIO_AIN_BUF_SIZE_8,
			/* reg		*/	-1,
			/* mask		*/	0,
			/* value	*/	0
		},
		{
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	ADADIO_IOCTL_AIN_CHAN_LAST,
			/* arg		*/	last,
			/* reg		*/	-1,
			/* mask		*/	0,
			/* value	*/	0
		},
		{				// Get a burst of data.
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	ADADIO_IOCTL_AIN_TRIGGER,
			/* arg		*/	0,
			/* reg		*/	-1,
			/* mask		*/	0,
			/* value	*/	0
		},
		{				// Wait a moment
			/* service	*/	SERVICE_SLEEP,
			/* cmd		*/	0,
			/* arg		*/	1,
			/* reg		*/	-1,
			/* mask		*/	0,
			/* value	*/	0
		},

		{ SERVICE_END_LIST }
	};

	service_data_t	list_2[]	=
	{
		{				// Read one more data value.
			/* service	*/	SERVICE_REG_READ,
			/* cmd		*/	0,
			/* arg		*/	0,
			/* reg		*/	ADADIO_GSC_AIDR,
			/* mask		*/	0,
			/* value	*/	0
		},

		{ SERVICE_END_LIST }
	};

	int		errs	= 0;
	__s32	sts;

	errs	+= adadio_initialize_quiet(fd);

	errs	+= service_ioctl_set_reg_list(fd, list_1);
	errs	+= adadio_dsl_ioctl(fd, ADADIO_IOCTL_AIN_BUF_STS, &sts);

	if ((errs == 0) && (sts != sts_1))
	{
		errs++;
		printf(	"FAIL <---  (%d. Expected %ld status, got %ld)\n",
				__LINE__,
				(long) sts_1,
				(long) sts);
	}

	errs	+= service_ioctl_set_reg_list(fd, list_2);
	errs	+= adadio_dsl_ioctl(fd, ADADIO_IOCTL_AIN_BUF_STS, &sts);

	if ((errs == 0) && (sts != sts_2))
	{
		errs++;
		printf(	"FAIL <---  (%d. Expected %ld status, got %ld)\n",
				__LINE__,
				(long) sts_2,
				(long) sts);
	}

	errs	+= adadio_initialize_quiet(fd);
	return(errs);
}



//*****************************************************************************
static int _function_test(int fd)
{
	int	errs	= 0;

	errs	+= _function_sub_test(fd, 0, ADADIO_AIN_BUF_STS_ALMOST_EMPTY,	ADADIO_AIN_BUF_STS_EMPTY);
	errs	+= _function_sub_test(fd, 1, ADADIO_AIN_BUF_STS_ALMOST_EMPTY,	ADADIO_AIN_BUF_STS_ALMOST_EMPTY);
	errs	+= _function_sub_test(fd, 2, ADADIO_AIN_BUF_STS_ALMOST_EMPTY,	ADADIO_AIN_BUF_STS_ALMOST_EMPTY);
	errs	+= _function_sub_test(fd, 3, ADADIO_AIN_BUF_STS_HALF_FULL,		ADADIO_AIN_BUF_STS_ALMOST_EMPTY);
	errs	+= _function_sub_test(fd, 4, ADADIO_AIN_BUF_STS_HALF_FULL,		ADADIO_AIN_BUF_STS_HALF_FULL);
	errs	+= _function_sub_test(fd, 5, ADADIO_AIN_BUF_STS_HALF_FULL,		ADADIO_AIN_BUF_STS_HALF_FULL);
	errs	+= _function_sub_test(fd, 6, ADADIO_AIN_BUF_STS_HALF_FULL,		ADADIO_AIN_BUF_STS_HALF_FULL);
	errs	+= _function_sub_test(fd, 7, ADADIO_AIN_BUF_STS_FULL,			ADADIO_AIN_BUF_STS_HALF_FULL);

	return(errs);
}




/******************************************************************************
*
*	Function:	ain_chan_last_test
*
*	Purpose:
*
*		Perform a test of the IOCTL service ADADIO_IOCTL_AIN_CHAN_LAST.
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

int ain_chan_last_test(int fd)
{
	int		errs	= 0;

	gsc_label("ADADIO_IOCTL_AIN_CHAN_LAST");
	errs	+= _service_test(fd);
	errs	+= _function_test(fd);

	if (errs == 0)
		printf("PASS\n");

	return(errs);
}


