// $URL: http://subversion:8080/svn/gsc/trunk/drivers/LINUX/16AO20/16AO20_Linux_2.x.x.x_GSC_DN/sbtest/tx_io_timeout.c $
// $Rev: 2014 $
// $Date: 2009-05-19 12:39:09 -0500 (Tue, 19 May 2009) $

#include <stdio.h>
#include <time.h>
#include <unistd.h>

#include "main.h"



//*****************************************************************************
static int _service_test(int fd)
{
	static const service_data_t	list[]	=
	{
		{
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	AO20_IOCTL_TX_IO_TIMEOUT,
			/* arg		*/	AO20_IO_TIMEOUT_MAX,
			/* reg		*/	-1,
			/* mask		*/	0,
			/* value	*/	0
		},
		{
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	AO20_IOCTL_TX_IO_TIMEOUT,
			/* arg		*/	(AO20_IO_TIMEOUT_MIN + AO20_IO_TIMEOUT_MAX) / 2,
			/* reg		*/	-1,
			/* mask		*/	0,
			/* value	*/	0
		},
		{
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	AO20_IOCTL_TX_IO_TIMEOUT,
			/* arg		*/	AO20_IO_TIMEOUT_MIN,
			/* reg		*/	-1,
			/* mask		*/	0,
			/* value	*/	0
		},
		{
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	AO20_IOCTL_TX_IO_TIMEOUT,
			/* arg		*/	AO20_IO_TIMEOUT_NO_SLEEP,
			/* reg		*/	-1,
			/* mask		*/	0,
			/* value	*/	0
		},
		{
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	AO20_IOCTL_TX_IO_TIMEOUT,
			/* arg		*/	AO20_IO_TIMEOUT_DEFAULT,
			/* reg		*/	-1,
			/* mask		*/	0,
			/* value	*/	0
		},

		{ SERVICE_END_LIST }
	};

	int errs	= 0;

	errs	+= ao20_initialize_quiet(fd);

	errs	+= service_ioctl_set_get_list(fd, list);

	errs	+= service_ioctl_set_get_list(fd, list);

	errs	+= ao20_initialize_quiet(fd);
	return(errs);
}




//*****************************************************************************
static int _function_test(int fd)
{
	static const service_data_t	list_1[]	=
	{
		// Fill the buffer.

		{					// Make the buffer as small as possible.
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	AO20_IOCTL_BUFFER_SIZE,
			/* arg		*/	AO20_BUFFER_SIZE_8,
			/* reg		*/	-1,
			/* mask		*/	0,
			/* value	*/	0
		},
		{					// Put data in the buffer (1 sample).
			/* service	*/	SERVICE_REG_MOD,
			/* cmd		*/	0,
			/* arg		*/	0,
			/* reg		*/	AO20_GSC_ODBR,
			/* mask		*/	0x0000,
			/* value	*/	0x0000
		},
		{					// Put data in the buffer (2 samples).
			/* service	*/	SERVICE_REG_MOD,
			/* cmd		*/	0,
			/* arg		*/	0,
			/* reg		*/	AO20_GSC_ODBR,
			/* mask		*/	0x0000,
			/* value	*/	0x0000
		},
		{					// Put data in the buffer (3 samples).
			/* service	*/	SERVICE_REG_MOD,
			/* cmd		*/	0,
			/* arg		*/	0,
			/* reg		*/	AO20_GSC_ODBR,
			/* mask		*/	0x0000,
			/* value	*/	0x0000
		},
		{					// Put data in the buffer (4 samples).
			/* service	*/	SERVICE_REG_MOD,
			/* cmd		*/	0,
			/* arg		*/	0,
			/* reg		*/	AO20_GSC_ODBR,
			/* mask		*/	0x0000,
			/* value	*/	0x0000
		},
		{					// Put data in the buffer (5 samples).
			/* service	*/	SERVICE_REG_MOD,
			/* cmd		*/	0,
			/* arg		*/	0,
			/* reg		*/	AO20_GSC_ODBR,
			/* mask		*/	0x0000,
			/* value	*/	0x0000
		},
		{					// Put data in the buffer (6 samples).
			/* service	*/	SERVICE_REG_MOD,
			/* cmd		*/	0,
			/* arg		*/	0,
			/* reg		*/	AO20_GSC_ODBR,
			/* mask		*/	0x0000,
			/* value	*/	0x0000
		},
		{					// Put data in the buffer (7 samples).
			/* service	*/	SERVICE_REG_MOD,
			/* cmd		*/	0,
			/* arg		*/	0,
			/* reg		*/	AO20_GSC_ODBR,
			/* mask		*/	0x0000,
			/* value	*/	0x0000
		},
		{					// Put data in the buffer (8 samples).
			/* service	*/	SERVICE_REG_MOD,
			/* cmd		*/	0,
			/* arg		*/	0,
			/* reg		*/	AO20_GSC_ODBR,
			/* mask		*/	0x0000,
			/* value	*/	0x0000
		},
		{					// Ignore the buffer overflow.
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	AO20_IOCTL_TX_IO_OVER_DATA,
			/* arg		*/	AO20_TX_IO_OVER_DATA_IGNORE,
			/* reg		*/	-1,
			/* mask		*/	0,
			/* value	*/	0
		},
		{					// Set a short second timeout.
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	AO20_IOCTL_TX_IO_TIMEOUT,
			/* arg		*/	2,
			/* reg		*/	-1,
			/* mask		*/	0,
			/* value	*/	0
		},

		{ SERVICE_END_LIST }
	};

	static const service_data_t	list_2[]	=
	{
		{					// Set a longer second timeout.
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	AO20_IOCTL_TX_IO_TIMEOUT,
			/* arg		*/	5,
			/* reg		*/	-1,
			/* mask		*/	0,
			/* value	*/	0
		},

		{ SERVICE_END_LIST }
	};

	__s32	_1_0;
	__s32	_2_0;
	__u32	buf[1024];
	int		errs	= 0;
	time_t	t1;
	time_t	t2;
	time_t	t3;
	time_t	t4;

	errs	+= ao20_initialize_quiet(fd);

	// Work with a shorter timeout.
	errs	+= service_ioctl_set_reg_list(fd, list_1);

	t1		= time(NULL);
	_1_0	= write(fd, buf, sizeof(buf));
	t2		= time(NULL);

	// Work with a longer timeout.
	errs	+= service_ioctl_set_reg_list(fd, list_2);

	t3		= time(NULL);
	_2_0	= write(fd, buf, sizeof(buf));
	t4		= time(NULL);

	if (errs)
	{
	}
	else if (_1_0 != 0)
	{
		errs++;
		printf("FAIL <--- (Test 1 results are not zero.)\n");
	}
	else if ((t2 - t1) < 1)
	{
		errs++;
		printf(	"FAIL <--- (The 1st write took less than 1 second.)\n");
	}
	else if ((t2 - t1) > 3)
	{
		errs++;
		printf(	"FAIL <--- (The 1st write took more than 3 seconds.)\n");
	}
	else if (_2_0 != 0)
	{
		errs++;
		printf("FAIL <--- (Test 2 results are not zero.)\n");
	}
	else if ((t4 - t3) < 4)
	{
		errs++;
		printf("FAIL <--- (The 2nd write took less than 4 seconds.)\n");
	}
	else if ((t4 - t3) > 6)
	{
		errs++;
		printf("FAIL <--- (The 2nd write took more than 6 seconds.)\n");
	}

	errs	+= ao20_initialize_quiet(fd);
	return(errs);
}




/******************************************************************************
*
*	Function:	tx_io_timeout_test
*
*	Purpose:
*
*		Perform a test of the IOCTL service AO20_IOCTL_TX_IO_TIMEOUT.
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

int tx_io_timeout_test(int fd)
{
	int	errs	= 0;

	gsc_label("AO20_IOCTL_TX_IO_TIMEOUT");
	errs	+= _service_test(fd);
	errs	+= _function_test(fd);

	if (errs == 0)
		printf("PASS\n");

	return(errs);
}


