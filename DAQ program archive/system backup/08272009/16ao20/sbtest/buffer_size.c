// $URL: http://subversion:8080/svn/gsc/trunk/drivers/LINUX/16AO20/16AO20_Linux_2.x.x.x_GSC_DN/sbtest/buffer_size.c $
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
			/* cmd		*/	AO20_IOCTL_BUFFER_SIZE,
			/* arg		*/	AO20_BUFFER_SIZE_8,
			/* reg		*/	AO20_GSC_BOR,
			/* mask		*/	0xF,
			/* value	*/	0x0
		},
		{
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	AO20_IOCTL_BUFFER_SIZE,
			/* arg		*/	AO20_BUFFER_SIZE_16,
			/* reg		*/	AO20_GSC_BOR,
			/* mask		*/	0xF,
			/* value	*/	0x1
		},
		{
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	AO20_IOCTL_BUFFER_SIZE,
			/* arg		*/	AO20_BUFFER_SIZE_32,
			/* reg		*/	AO20_GSC_BOR,
			/* mask		*/	0xF,
			/* value	*/	0x2
		},
		{
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	AO20_IOCTL_BUFFER_SIZE,
			/* arg		*/	AO20_BUFFER_SIZE_64,
			/* reg		*/	AO20_GSC_BOR,
			/* mask		*/	0xF,
			/* value	*/	0x3
		},
		{
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	AO20_IOCTL_BUFFER_SIZE,
			/* arg		*/	AO20_BUFFER_SIZE_128,
			/* reg		*/	AO20_GSC_BOR,
			/* mask		*/	0xF,
			/* value	*/	0x4
		},
		{
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	AO20_IOCTL_BUFFER_SIZE,
			/* arg		*/	AO20_BUFFER_SIZE_256,
			/* reg		*/	AO20_GSC_BOR,
			/* mask		*/	0xF,
			/* value	*/	0x5
		},
		{
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	AO20_IOCTL_BUFFER_SIZE,
			/* arg		*/	AO20_BUFFER_SIZE_512,
			/* reg		*/	AO20_GSC_BOR,
			/* mask		*/	0xF,
			/* value	*/	0x6
		},
		{
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	AO20_IOCTL_BUFFER_SIZE,
			/* arg		*/	AO20_BUFFER_SIZE_1K,
			/* reg		*/	AO20_GSC_BOR,
			/* mask		*/	0xF,
			/* value	*/	0x7
		},
		{
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	AO20_IOCTL_BUFFER_SIZE,
			/* arg		*/	AO20_BUFFER_SIZE_2K,
			/* reg		*/	AO20_GSC_BOR,
			/* mask		*/	0xF,
			/* value	*/	0x8
		},
		{
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	AO20_IOCTL_BUFFER_SIZE,
			/* arg		*/	AO20_BUFFER_SIZE_4K,
			/* reg		*/	AO20_GSC_BOR,
			/* mask		*/	0xF,
			/* value	*/	0x9
		},
		{
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	AO20_IOCTL_BUFFER_SIZE,
			/* arg		*/	AO20_BUFFER_SIZE_8K,
			/* reg		*/	AO20_GSC_BOR,
			/* mask		*/	0xF,
			/* value	*/	0xA
		},
		{
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	AO20_IOCTL_BUFFER_SIZE,
			/* arg		*/	AO20_BUFFER_SIZE_16K,
			/* reg		*/	AO20_GSC_BOR,
			/* mask		*/	0xF,
			/* value	*/	0xB
		},
		{
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	AO20_IOCTL_BUFFER_SIZE,
			/* arg		*/	AO20_BUFFER_SIZE_32K,
			/* reg		*/	AO20_GSC_BOR,
			/* mask		*/	0xF,
			/* value	*/	0xC
		},
		{
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	AO20_IOCTL_BUFFER_SIZE,
			/* arg		*/	AO20_BUFFER_SIZE_64K,
			/* reg		*/	AO20_GSC_BOR,
			/* mask		*/	0xF,
			/* value	*/	0xD
		},
		{
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	AO20_IOCTL_BUFFER_SIZE,
			/* arg		*/	AO20_BUFFER_SIZE_128K,
			/* reg		*/	AO20_GSC_BOR,
			/* mask		*/	0xF,
			/* value	*/	0xE
		},
		{
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	AO20_IOCTL_BUFFER_SIZE,
			/* arg		*/	AO20_BUFFER_SIZE_256K,
			/* reg		*/	AO20_GSC_BOR,
			/* mask		*/	0xF,
			/* value	*/	0xF
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
	static const service_data_t	list[]	=
	{
		{					// Set the buffer size.
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	AO20_IOCTL_BUFFER_SIZE,
			/* arg		*/	AO20_BUFFER_SIZE_8,
			/* reg		*/	-1,
			/* mask		*/	0,
			/* value	*/	0
		},

		// 0 of 8 data values

		{					// Verify the buffer status.
			/* service	*/	SERVICE_REG_TEST,
			/* cmd		*/	0,
			/* arg		*/	0,
			/* reg		*/	AO20_GSC_BOR,
			/* mask		*/	0xF000,
			/* value	*/	0x3000
		},

		// 1 of 8 data values

		{					// Put data in the buffer.
			/* service	*/	SERVICE_REG_MOD,
			/* cmd		*/	0,
			/* arg		*/	0,
			/* reg		*/	AO20_GSC_ODBR,
			/* mask		*/	0x0000,
			/* value	*/	0x0000
		},
		{					// Verify the buffer status.
			/* service	*/	SERVICE_REG_TEST,
			/* cmd		*/	0,
			/* arg		*/	0,
			/* reg		*/	AO20_GSC_BOR,
			/* mask		*/	0xF000,
			/* value	*/	0x2000
		},

		// 2 of 8 data values

		{					// Put data in the buffer.
			/* service	*/	SERVICE_REG_MOD,
			/* cmd		*/	0,
			/* arg		*/	0,
			/* reg		*/	AO20_GSC_ODBR,
			/* mask		*/	0x0000,
			/* value	*/	0x0000
		},
		{					// Verify the buffer status.
			/* service	*/	SERVICE_REG_TEST,
			/* cmd		*/	0,
			/* arg		*/	0,
			/* reg		*/	AO20_GSC_BOR,
			/* mask		*/	0xF000,
			/* value	*/	0x0000
		},

		// 3 of 8 data values

		{					// Put data in the buffer.
			/* service	*/	SERVICE_REG_MOD,
			/* cmd		*/	0,
			/* arg		*/	0,
			/* reg		*/	AO20_GSC_ODBR,
			/* mask		*/	0x0000,
			/* value	*/	0x0000
		},
		{					// Verify the buffer status.
			/* service	*/	SERVICE_REG_TEST,
			/* cmd		*/	0,
			/* arg		*/	0,
			/* reg		*/	AO20_GSC_BOR,
			/* mask		*/	0xF000,
			/* value	*/	0x0000
		},

		// 4 of 8 data values

		{					// Put data in the buffer.
			/* service	*/	SERVICE_REG_MOD,
			/* cmd		*/	0,
			/* arg		*/	0,
			/* reg		*/	AO20_GSC_ODBR,
			/* mask		*/	0x0000,
			/* value	*/	0x0000
		},
		{					// Verify the buffer status.
			/* service	*/	SERVICE_REG_TEST,
			/* cmd		*/	0,
			/* arg		*/	0,
			/* reg		*/	AO20_GSC_BOR,
			/* mask		*/	0xF000,
			/* value	*/	0x0000
		},

		// 5 of 8 data values

		{					// Put data in the buffer.
			/* service	*/	SERVICE_REG_MOD,
			/* cmd		*/	0,
			/* arg		*/	0,
			/* reg		*/	AO20_GSC_ODBR,
			/* mask		*/	0x0000,
			/* value	*/	0x0000
		},
		{					// Verify the buffer status.
			/* service	*/	SERVICE_REG_TEST,
			/* cmd		*/	0,
			/* arg		*/	0,
			/* reg		*/	AO20_GSC_BOR,
			/* mask		*/	0xF000,
			/* value	*/	0x0000
		},

		// 6 of 8 data values

		{					// Put data in the buffer.
			/* service	*/	SERVICE_REG_MOD,
			/* cmd		*/	0,
			/* arg		*/	0,
			/* reg		*/	AO20_GSC_ODBR,
			/* mask		*/	0x0000,
			/* value	*/	0x0000
		},
		{					// Verify the buffer status.
			/* service	*/	SERVICE_REG_TEST,
			/* cmd		*/	0,
			/* arg		*/	0,
			/* reg		*/	AO20_GSC_BOR,
			/* mask		*/	0xF000,
			/* value	*/	0x4000
		},

		// 7 of 8 data values

		{					// Put data in the buffer.
			/* service	*/	SERVICE_REG_MOD,
			/* cmd		*/	0,
			/* arg		*/	0,
			/* reg		*/	AO20_GSC_ODBR,
			/* mask		*/	0x0000,
			/* value	*/	0x0000
		},
		{					// Verify the buffer status.
			/* service	*/	SERVICE_REG_TEST,
			/* cmd		*/	0,
			/* arg		*/	0,
			/* reg		*/	AO20_GSC_BOR,
			/* mask		*/	0xF000,
			/* value	*/	0x4000
		},

		// 8 of 8 data values

		{					// Put data in the buffer.
			/* service	*/	SERVICE_REG_MOD,
			/* cmd		*/	0,
			/* arg		*/	0,
			/* reg		*/	AO20_GSC_ODBR,
			/* mask		*/	0x0000,
			/* value	*/	0x0000
		},
		{					// Verify the buffer status.
			/* service	*/	SERVICE_REG_TEST,
			/* cmd		*/	0,
			/* arg		*/	0,
			/* reg		*/	AO20_GSC_BOR,
			/* mask		*/	0xF000,
			/* value	*/	0xC000
		},

		// Change the buffer size.

		{					// Set the buffer size.
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	AO20_IOCTL_BUFFER_SIZE,
			/* arg		*/	AO20_BUFFER_SIZE_16,
			/* reg		*/	-1,
			/* mask		*/	0,
			/* value	*/	0
		},

		// 8 of 16 data values

		{					// Verify the buffer status.
			/* service	*/	SERVICE_REG_TEST,
			/* cmd		*/	0,
			/* arg		*/	0,
			/* reg		*/	AO20_GSC_BOR,
			/* mask		*/	0xF000,
			/* value	*/	0x0000
		},

		// 9 of 16 data values

		{					// Put data in the buffer.
			/* service	*/	SERVICE_REG_MOD,
			/* cmd		*/	0,
			/* arg		*/	0,
			/* reg		*/	AO20_GSC_ODBR,
			/* mask		*/	0x0000,
			/* value	*/	0x0000
		},
		{					// Verify the buffer status.
			/* service	*/	SERVICE_REG_TEST,
			/* cmd		*/	0,
			/* arg		*/	0,
			/* reg		*/	AO20_GSC_BOR,
			/* mask		*/	0xF000,
			/* value	*/	0x0000
		},

		// 10 of 16 data values

		{					// Put data in the buffer.
			/* service	*/	SERVICE_REG_MOD,
			/* cmd		*/	0,
			/* arg		*/	0,
			/* reg		*/	AO20_GSC_ODBR,
			/* mask		*/	0x0000,
			/* value	*/	0x0000
		},
		{					// Verify the buffer status.
			/* service	*/	SERVICE_REG_TEST,
			/* cmd		*/	0,
			/* arg		*/	0,
			/* reg		*/	AO20_GSC_BOR,
			/* mask		*/	0xF000,
			/* value	*/	0x0000
		},

		// 11 of 16 data values

		{					// Put data in the buffer.
			/* service	*/	SERVICE_REG_MOD,
			/* cmd		*/	0,
			/* arg		*/	0,
			/* reg		*/	AO20_GSC_ODBR,
			/* mask		*/	0x0000,
			/* value	*/	0x0000
		},
		{					// Verify the buffer status.
			/* service	*/	SERVICE_REG_TEST,
			/* cmd		*/	0,
			/* arg		*/	0,
			/* reg		*/	AO20_GSC_BOR,
			/* mask		*/	0xF000,
			/* value	*/	0x0000
		},

		// 12 of 16 data values

		{					// Put data in the buffer.
			/* service	*/	SERVICE_REG_MOD,
			/* cmd		*/	0,
			/* arg		*/	0,
			/* reg		*/	AO20_GSC_ODBR,
			/* mask		*/	0x0000,
			/* value	*/	0x0000
		},
		{					// Verify the buffer status.
			/* service	*/	SERVICE_REG_TEST,
			/* cmd		*/	0,
			/* arg		*/	0,
			/* reg		*/	AO20_GSC_BOR,
			/* mask		*/	0xF000,
			/* value	*/	0x4000
		},

		// 13 of 16 data values

		{					// Put data in the buffer.
			/* service	*/	SERVICE_REG_MOD,
			/* cmd		*/	0,
			/* arg		*/	0,
			/* reg		*/	AO20_GSC_ODBR,
			/* mask		*/	0x0000,
			/* value	*/	0x0000
		},
		{					// Verify the buffer status.
			/* service	*/	SERVICE_REG_TEST,
			/* cmd		*/	0,
			/* arg		*/	0,
			/* reg		*/	AO20_GSC_BOR,
			/* mask		*/	0xF000,
			/* value	*/	0x4000
		},

		// 14 of 16 data values

		{					// Put data in the buffer.
			/* service	*/	SERVICE_REG_MOD,
			/* cmd		*/	0,
			/* arg		*/	0,
			/* reg		*/	AO20_GSC_ODBR,
			/* mask		*/	0x0000,
			/* value	*/	0x0000
		},
		{					// Verify the buffer status.
			/* service	*/	SERVICE_REG_TEST,
			/* cmd		*/	0,
			/* arg		*/	0,
			/* reg		*/	AO20_GSC_BOR,
			/* mask		*/	0xF000,
			/* value	*/	0x4000
		},

		// 15 of 16 data values

		{					// Put data in the buffer.
			/* service	*/	SERVICE_REG_MOD,
			/* cmd		*/	0,
			/* arg		*/	0,
			/* reg		*/	AO20_GSC_ODBR,
			/* mask		*/	0x0000,
			/* value	*/	0x0000
		},
		{					// Verify the buffer status.
			/* service	*/	SERVICE_REG_TEST,
			/* cmd		*/	0,
			/* arg		*/	0,
			/* reg		*/	AO20_GSC_BOR,
			/* mask		*/	0xF000,
			/* value	*/	0x4000
		},

		// 16 of 16 data values

		{					// Put data in the buffer.
			/* service	*/	SERVICE_REG_MOD,
			/* cmd		*/	0,
			/* arg		*/	0,
			/* reg		*/	AO20_GSC_ODBR,
			/* mask		*/	0x0000,
			/* value	*/	0x0000
		},
		{					// Verify the buffer status.
			/* service	*/	SERVICE_REG_TEST,
			/* cmd		*/	0,
			/* arg		*/	0,
			/* reg		*/	AO20_GSC_BOR,
			/* mask		*/	0xF000,
			/* value	*/	0xC000
		},

		{ SERVICE_END_LIST }
	};

	int errs	= 0;

	errs	+= ao20_initialize_quiet(fd);

	errs	+= service_ioctl_set_reg_list(fd, list);

	errs	+= ao20_initialize_quiet(fd);
	return(errs);
}




/******************************************************************************
*
*	Function:	buffer_size_test
*
*	Purpose:
*
*		Perform a test of the IOCTL service AO20_IOCTL_BUFFER_SIZE.
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

int buffer_size_test(int fd)
{
	int	errs	= 0;

	gsc_label("AO20_IOCTL_BUFFER_SIZE");
	errs	+= _service_test(fd);
	errs	+= _function_test(fd);

	if (errs == 0)
		printf("PASS\n");

	return(errs);
}


