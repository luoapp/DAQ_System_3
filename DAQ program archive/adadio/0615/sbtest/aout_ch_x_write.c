// $URL: http://subversion:8080/svn/gsc/trunk/drivers/LINUX/ADADIO/ADADIO_Linux_3.x.x.x_GSC_DN/sbtest/aout_ch_x_write.c $
// $Rev: 1620 $
// $Date: 2009-04-10 11:41:41 -0500 (Fri, 10 Apr 2009) $

#include <stdio.h>

#include "main.h"



//*****************************************************************************
static int _service_test(int fd, long cmd, __s32 reg)
{
	const service_data_t	list[]	=
	{
		{
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	cmd,
			/* arg		*/	0xFFFF,
			/* reg		*/	reg,
			/* mask		*/	0xFFFF,
			/* value	*/	0xFFFF
		},
		{
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	cmd,
			/* arg		*/	0x0000,
			/* reg		*/	reg,
			/* mask		*/	0xFFFF,
			/* value	*/	0x0000
		},
		{
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	cmd,
			/* arg		*/	0xAAAA,
			/* reg		*/	reg,
			/* mask		*/	0xFFFF,
			/* value	*/	0xAAAA
		},
		{
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	cmd,
			/* arg		*/	0x5555,
			/* reg		*/	reg,
			/* mask		*/	0xFFFF,
			/* value	*/	0x5555
		},
		{
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	cmd,
			/* arg		*/	0x000F,
			/* reg		*/	reg,
			/* mask		*/	0xFFFF,
			/* value	*/	0x000F
		},
		{
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	cmd,
			/* arg		*/	0x00F0,
			/* reg		*/	reg,
			/* mask		*/	0xFFFF,
			/* value	*/	0x00F0
		},
		{
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	cmd,
			/* arg		*/	0x0F00,
			/* reg		*/	reg,
			/* mask		*/	0xFFFF,
			/* value	*/	0x0F00
		},
		{
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	cmd,
			/* arg		*/	0xF000,
			/* reg		*/	reg,
			/* mask		*/	0xFFFF,
			/* value	*/	0xF000
		},
		{
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	cmd,
			/* arg		*/	0x8000,
			/* reg		*/	reg,
			/* mask		*/	0xFFFF,
			/* value	*/	0x8000
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
static int _function_test(int fd, long cmd, long reg)
{
	const service_data_t	list[]	=
	{
		{
			/* service	*/	SERVICE_REG_MOD,
			/* cmd		*/	0,
			/* arg		*/	0,
			/* reg		*/	ADADIO_GSC_AOC0R,
			/* mask		*/	0xFFFF,
			/* value	*/	0x1800
		},
		{
			/* service	*/	SERVICE_REG_MOD,
			/* cmd		*/	0,
			/* arg		*/	0,
			/* reg		*/	ADADIO_GSC_AOC1R,
			/* mask		*/	0xFFFF,
			/* value	*/	0x2800
		},
		{
			/* service	*/	SERVICE_REG_MOD,
			/* cmd		*/	0,
			/* arg		*/	0,
			/* reg		*/	ADADIO_GSC_AOC2R,
			/* mask		*/	0xFFFF,
			/* value	*/	0x3800
		},
		{
			/* service	*/	SERVICE_REG_MOD,
			/* cmd		*/	0,
			/* arg		*/	0,
			/* reg		*/	ADADIO_GSC_AOC3R,
			/* mask		*/	0xFFFF,
			/* value	*/	0x4800
		},
		{
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	cmd,
			/* arg		*/	0xC888,
			/* reg		*/	-1,
			/* mask		*/	0,
			/* value	*/	0
		},
		{
			/* service	*/	SERVICE_REG_TEST,
			/* cmd		*/	0,
			/* arg		*/	0,
			/* reg		*/	reg,
			/* mask		*/	0xFFFF,
			/* value	*/	0xC888
		},

		{ SERVICE_END_LIST }
	};

	int errs	= 0;

	errs	+= adadio_initialize_quiet(fd);

	errs	+= service_ioctl_set_reg_list(fd, list);

	errs	+= adadio_initialize_quiet(fd);
	return(errs);
}




/******************************************************************************
*
*	Function:	aout_ch_0_write_test
*
*	Purpose:
*
*		Perform a test of the IOCTL service ADADIO_IOCTL_AOUT_CH_0_WRITE.
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

int aout_ch_0_write_test(int fd)
{
	int	errs	= 0;

	gsc_label("ADADIO_IOCTL_AOUT_CH_0_WRITE");
	errs	+= _service_test (fd, ADADIO_IOCTL_AOUT_CH_0_WRITE, ADADIO_GSC_AOC0R);
	errs	+= _function_test(fd, ADADIO_IOCTL_AOUT_CH_0_WRITE, ADADIO_GSC_AOC0R);

	if (errs == 0)
		printf("PASS\n");

	return(errs);
}



/******************************************************************************
*
*	Function:	aout_ch_1_write_test
*
*	Purpose:
*
*		Perform a test of the IOCTL service ADADIO_IOCTL_AOUT_CH_1_WRITE.
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

int aout_ch_1_write_test(int fd)
{
	int	errs	= 0;

	gsc_label("ADADIO_IOCTL_AOUT_CH_1_WRITE");
	errs	+= _service_test (fd, ADADIO_IOCTL_AOUT_CH_1_WRITE, ADADIO_GSC_AOC1R);
	errs	+= _function_test(fd, ADADIO_IOCTL_AOUT_CH_1_WRITE, ADADIO_GSC_AOC1R);

	if (errs == 0)
		printf("PASS\n");

	return(errs);
}



/******************************************************************************
*
*	Function:	aout_ch_2_write_test
*
*	Purpose:
*
*		Perform a test of the IOCTL service ADADIO_IOCTL_AOUT_CH_2_WRITE.
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

int aout_ch_2_write_test(int fd)
{
	int	errs	= 0;

	gsc_label("ADADIO_IOCTL_AOUT_CH_2_WRITE");
	errs	+= _service_test (fd, ADADIO_IOCTL_AOUT_CH_2_WRITE, ADADIO_GSC_AOC2R);
	errs	+= _function_test(fd, ADADIO_IOCTL_AOUT_CH_2_WRITE, ADADIO_GSC_AOC2R);

	if (errs == 0)
		printf("PASS\n");

	return(errs);
}



/******************************************************************************
*
*	Function:	aout_ch_3_write_test
*
*	Purpose:
*
*		Perform a test of the IOCTL service ADADIO_IOCTL_AOUT_CH_3_WRITE.
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

int aout_ch_3_write_test(int fd)
{
	int	errs	= 0;

	gsc_label("ADADIO_IOCTL_AOUT_CH_3_WRITE");
	errs	+= _service_test (fd, ADADIO_IOCTL_AOUT_CH_3_WRITE, ADADIO_GSC_AOC3R);
	errs	+= _function_test(fd, ADADIO_IOCTL_AOUT_CH_3_WRITE, ADADIO_GSC_AOC3R);

	if (errs == 0)
		printf("PASS\n");

	return(errs);
}


