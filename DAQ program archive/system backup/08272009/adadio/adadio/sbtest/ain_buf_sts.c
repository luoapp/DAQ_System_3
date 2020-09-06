// $URL: http://subversion:8080/svn/gsc/trunk/drivers/LINUX/ADADIO/ADADIO_Linux_3.x.x.x_GSC_DN/sbtest/ain_buf_sts.c $
// $Rev: 1620 $
// $Date: 2009-04-10 11:41:41 -0500 (Fri, 10 Apr 2009) $

#include <errno.h>
#include <stdio.h>
#include <unistd.h>

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
		{				// Verify that the buffer is empty
			/* service	*/	SERVICE_REG_TEST,
			/* cmd		*/	0,
			/* arg		*/	0,
			/* reg		*/	ADADIO_GSC_BCR,
			/* mask		*/	0x700000,
			/* value	*/	0x100000
		},

		{ SERVICE_END_LIST }
	};

	static const service_data_t	list_2[]	=
	{
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
		{				// Verify that the buffer is full
			/* service	*/	SERVICE_REG_TEST,
			/* cmd		*/	0,
			/* arg		*/	0,
			/* reg		*/	ADADIO_GSC_BCR,
			/* mask		*/	0x700000,
			/* value	*/	0x600000
		},

		{ SERVICE_END_LIST }
	};

	static const service_data_t	list_3[]	=
	{
		{				// Read one data value.
			/* service	*/	SERVICE_REG_READ,
			/* cmd		*/	0,
			/* arg		*/	0,
			/* reg		*/	ADADIO_GSC_AIDR,
			/* mask		*/	0,
			/* value	*/	0
		},
		{				// Verify that the buffer is Half Full
			/* service	*/	SERVICE_REG_TEST,
			/* cmd		*/	0,
			/* arg		*/	0,
			/* reg		*/	ADADIO_GSC_BCR,
			/* mask		*/	0x700000,
			/* value	*/	0x200000
		},

		{ SERVICE_END_LIST }
	};

	static const service_data_t	list_4[]	=
	{
		{				// Read one more data value.
			/* service	*/	SERVICE_REG_READ,
			/* cmd		*/	0,
			/* arg		*/	0,
			/* reg		*/	ADADIO_GSC_AIDR,
			/* mask		*/	0,
			/* value	*/	0
		},
		{				// Read one more data value.
			/* service	*/	SERVICE_REG_READ,
			/* cmd		*/	0,
			/* arg		*/	0,
			/* reg		*/	ADADIO_GSC_AIDR,
			/* mask		*/	0,
			/* value	*/	0
		},
		{				// Read one more data value.
			/* service	*/	SERVICE_REG_READ,
			/* cmd		*/	0,
			/* arg		*/	0,
			/* reg		*/	ADADIO_GSC_AIDR,
			/* mask		*/	0,
			/* value	*/	0
		},
		{				// Verify that the buffer is Half Full
			/* service	*/	SERVICE_REG_TEST,
			/* cmd		*/	0,
			/* arg		*/	0,
			/* reg		*/	ADADIO_GSC_BCR,
			/* mask		*/	0x700000,
			/* value	*/	0x200000
		},

		{ SERVICE_END_LIST }
	};

	static const service_data_t	list_5[]	=
	{
		{				// Read one more data value.
			/* service	*/	SERVICE_REG_READ,
			/* cmd		*/	0,
			/* arg		*/	0,
			/* reg		*/	ADADIO_GSC_AIDR,
			/* mask		*/	0,
			/* value	*/	0
		},
		{				// Verify that the buffer is Almost Empty
			/* service	*/	SERVICE_REG_TEST,
			/* cmd		*/	0,
			/* arg		*/	0,
			/* reg		*/	ADADIO_GSC_BCR,
			/* mask		*/	0x700000,
			/* value	*/	0x000000
		},

		{ SERVICE_END_LIST }
	};

	static const service_data_t	list_6[]	=
	{
		{				// Read one more data value.
			/* service	*/	SERVICE_REG_READ,
			/* cmd		*/	0,
			/* arg		*/	0,
			/* reg		*/	ADADIO_GSC_AIDR,
			/* mask		*/	0,
			/* value	*/	0
		},
		{				// Read one more data value.
			/* service	*/	SERVICE_REG_READ,
			/* cmd		*/	0,
			/* arg		*/	0,
			/* reg		*/	ADADIO_GSC_AIDR,
			/* mask		*/	0,
			/* value	*/	0
		},
		{				// Verify that the buffer is Almost Empty
			/* service	*/	SERVICE_REG_TEST,
			/* cmd		*/	0,
			/* arg		*/	0,
			/* reg		*/	ADADIO_GSC_BCR,
			/* mask		*/	0x700000,
			/* value	*/	0x000000
		},

		{ SERVICE_END_LIST }
	};

	static const service_data_t	list_7[]	=
	{
		{				// Read one more data value.
			/* service	*/	SERVICE_REG_READ,
			/* cmd		*/	0,
			/* arg		*/	0,
			/* reg		*/	ADADIO_GSC_AIDR,
			/* mask		*/	0,
			/* value	*/	0
		},
		{				// Verify that the buffer is Empty
			/* service	*/	SERVICE_REG_TEST,
			/* cmd		*/	0,
			/* arg		*/	0,
			/* reg		*/	ADADIO_GSC_BCR,
			/* mask		*/	0x700000,
			/* value	*/	0x100000
		},

		{ SERVICE_END_LIST }
	};

	int		errs	= 0;
	__s32	sts;

	errs	+= adadio_initialize_quiet(fd);

	// Empty
	errs	+= service_ioctl_set_reg_list(fd, list_1);
	errs	+= adadio_dsl_ioctl(fd, ADADIO_IOCTL_AIN_BUF_STS, &sts);

	if ((errs == 0) && (sts != ADADIO_AIN_BUF_STS_EMPTY))
	{
		errs++;
		printf(	"FAIL <---  (%d. Expected EMPTY status, got %ld)\n",
				__LINE__,
				(long) sts);
	}

	// Full
	errs	+= service_ioctl_set_reg_list(fd, list_2);
	errs	+= adadio_dsl_ioctl(fd, ADADIO_IOCTL_AIN_BUF_STS, &sts);

	if ((errs == 0) && (sts != ADADIO_AIN_BUF_STS_FULL))
	{
		errs++;
		printf(	"FAIL <---  (%d. Expected FULL status, got %ld)\n",
				__LINE__,
				(long) sts);
	}

	// Half Full
	errs	+= service_ioctl_set_reg_list(fd, list_3);
	errs	+= adadio_dsl_ioctl(fd, ADADIO_IOCTL_AIN_BUF_STS, &sts);

	if ((errs == 0) && (sts != ADADIO_AIN_BUF_STS_HALF_FULL))
	{
		errs++;
		printf(	"FAIL <---  (%d. Expected HALF FULL status, got %ld)\n",
				__LINE__,
				(long) sts);
	}

	// Half Full
	errs	+= service_ioctl_set_reg_list(fd, list_4);
	errs	+= adadio_dsl_ioctl(fd, ADADIO_IOCTL_AIN_BUF_STS, &sts);

	if ((errs == 0) && (sts != ADADIO_AIN_BUF_STS_HALF_FULL))
	{
		errs++;
		printf(	"FAIL <---  (%d. Expected HALF FULL status, got %ld)\n",
				__LINE__,
				(long) sts);
	}

	// Almost Empty
	errs	+= service_ioctl_set_reg_list(fd, list_5);
	errs	+= adadio_dsl_ioctl(fd, ADADIO_IOCTL_AIN_BUF_STS, &sts);

	if ((errs == 0) && (sts != ADADIO_AIN_BUF_STS_ALMOST_EMPTY))
	{
		errs++;
		printf(	"FAIL <---  (%d. Expected ALMOST EMPTY status, got %ld)\n",
				__LINE__,
				(long) sts);
	}

	// Almost Empty
	errs	+= service_ioctl_set_reg_list(fd, list_6);
	errs	+= adadio_dsl_ioctl(fd, ADADIO_IOCTL_AIN_BUF_STS, &sts);

	if ((errs == 0) && (sts != ADADIO_AIN_BUF_STS_ALMOST_EMPTY))
	{
		errs++;
		printf(	"FAIL <---  (%d. Expected ALMOST EMPTY status, got %ld)\n",
				__LINE__,
				(long) sts);
	}

	// Empty
	errs	+= service_ioctl_set_reg_list(fd, list_7);
	errs	+= adadio_dsl_ioctl(fd, ADADIO_IOCTL_AIN_BUF_STS, &sts);

	if ((errs == 0) && (sts != ADADIO_AIN_BUF_STS_EMPTY))
	{
		errs++;
		printf(	"FAIL <---  (%d. Expected EMPTY status, got %ld)\n",
				__LINE__,
				(long) sts);
	}

	errs	+= adadio_initialize_quiet(fd);
	return(errs);
}




/******************************************************************************
*
*	Function:	ain_buf_sts_test
*
*	Purpose:
*
*		Perform a test of the IOCTL service ADADIO_IOCTL_AIN_BUF_STS.
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

int ain_buf_sts_test(int fd)
{

	int	errs	= 0;

	gsc_label("ADADIO_IOCTL_AIN_BUF_STS");
	errs	+= _service_test(fd);
	errs	+= _function_test(fd);

	if (errs == 0)
		printf("PASS\n");

	return(errs);
}


