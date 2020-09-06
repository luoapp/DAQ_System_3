// $URL: http://subversion:8080/svn/gsc/trunk/drivers/LINUX/ADADIO/ADADIO_Linux_3.x.x.x_GSC_DN/dout/dio.c $
// $Rev: 1620 $
// $Date: 2009-04-10 11:41:41 -0500 (Fri, 10 Apr 2009) $

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <asm/types.h>
#include <sys/ioctl.h>

#include "adadio.h"
#include "main.h"
#include "gsc_utils.h"



/******************************************************************************
*
*	Function:	_bin_show
*
*	Purpose:
*
*		Display the given data in binary.
*
*	Arguments:
*
*		data	The data to show.
*
*	Returned:
*
*		None.
*
******************************************************************************/

static void _bin_show(__u8 data)
{
	__u8	bit;

	for (bit = 0x01; bit; bit *= 2)
	{
		if (bit & data)
			printf("1");
		else
			printf("0");
	}
}



/******************************************************************************
*
*	Function:	_dev_init
*
*	Purpose:
*
*		Initialize the board.
*
*	Arguments:
*
*		fd		The file descriptor for the board to access.
*
*	Returned:
*
*		>= 0	The number of errors seen.
*
******************************************************************************/

static int _dev_init(int fd)
{
	int	errs;

	errs	= ioctl(fd, ADADIO_IOCTL_INITIALIZE);
	errs	= (errs == -1) ? 1 : 0;
	return(errs);
}



/******************************************************************************
*
*	Function:	_dev_dio_port_dir_set_out
*
*	Purpose:
*
*		Set GPIO 0 to an output.
*
*	Arguments:
*
*		fd		The file descriptor for the board to access.
*
*	Returned:
*
*		>= 0	The number of errors seen.
*
******************************************************************************/

static int _dev_dio_port_dir_set_out(int fd)
{
	int		errs;
	__u32	val		= ADADIO_DIO_PORT_DIR_OUTPUT;

	errs	= ioctl(fd, ADADIO_IOCTL_DIO_PORT_DIR, &val);
	errs	= (errs == -1) ? 1 : 0;
	return(errs);
}



/******************************************************************************
*
*	Function:	_dev_dio_port_out
*
*	Purpose:
*
*		Write to the Digital I/O Port output.
*
*	Arguments:
*
*		fd		The file descriptor for the board to access.
*
*		data	The data to write.
*
*	Returned:
*
*		>= 0	The number of errors seen.
*
******************************************************************************/

static int _dev_dio_port_out(int fd, __u8 data)
{
	int		errs;
	__u32	val		= data;

	_bin_show(data);
	errs	= ioctl(fd, ADADIO_IOCTL_DIO_PORT_WRITE, &val);
	errs	= (errs == -1) ? 1 : 0;
	return(errs);
}



/******************************************************************************
*
*	Function:	_dev_dio_pin_out
*
*	Purpose:
*
*		Write to the Digital Output Pin output.
*
*	Arguments:
*
*		fd		The file descriptor for the board to access.
*
*		data	The data to write.
*
*	Returned:
*
*		>= 0	The number of errors seen.
*
******************************************************************************/

static int _dev_dio_pin_out(int fd, __u8 data)
{
	int		errs;
	__u32	val		= data ? ADADIO_DIO_PIN_SET : ADADIO_DIO_PIN_CLEAR;

	if (data)
		printf("1");
	else
		printf("0");

	errs	= ioctl(fd, ADADIO_IOCTL_DIO_PIN_WRITE, &val);
	errs	= (errs == -1) ? 1 : 0;
	return(errs);
}



/******************************************************************************
*
*	Function:	_dev_dio_output
*
*	Purpose:
*
*		Write to the Digital I/O outputs.
*
*	Arguments:
*
*		fd		The file descriptor for the board to access.
*
*		data	The data to write.
*
*	Returned:
*
*		>= 0	The number of errors seen.
*
******************************************************************************/

static int _dev_dio_output(int fd, __u16 data)
{
	int		errs	= 0;

	printf("    ");
	errs	+= _dev_dio_port_out(fd, data & 0xFF);
	printf("  ");
	errs	+= _dev_dio_pin_out(fd, data >> 8);
	printf("\n");
	usleep(250000L);
	return(errs);
}



/******************************************************************************
*
*	Function:	dio_out
*
*	Purpose:
*
*		Perform a GPIO output test.
*
*	Arguments:
*
*		fd		The file descriptor for the board to access.
*
*	Returned:
*
*		>= 0	The number of errors seen.
*
******************************************************************************/

int dio_out(int fd)
{
	int	errs	= 0;
	int	i;

	for (;;)	// A convenience loop
	{
		gsc_label("GPIO Output");
		errs	+= _dev_init(fd);
		errs	+= _dev_dio_port_dir_set_out(fd);

		if (errs)
		{
			printf("FAIL <---\n");
			break;
		}

		printf("\n");
		printf("    DIO Port  DIO Pin\n");
		printf("    01234567  0\n");
		printf("    ========  =\n");

		errs	+= _dev_dio_output(fd, 0x000);
		errs	+= _dev_dio_output(fd, 0x1FF);
		errs	+= _dev_dio_output(fd, 0x000);
		errs	+= _dev_dio_output(fd, 0x1FF);
		errs	+= _dev_dio_output(fd, 0x000);

		for (i = 0; i < 9; i++)
			errs	+= _dev_dio_output(fd, 0x0001 << i);

		errs	+= _dev_dio_output(fd, 0x000);

		for (i = 8; i >= 0; i--)
			errs	+= _dev_dio_output(fd, 0x0001 << i);

		errs	+= _dev_dio_output(fd, 0x000);
		errs	+= _dev_dio_output(fd, 0x1FF);
		errs	+= _dev_dio_output(fd, 0x000);
		errs	+= _dev_dio_output(fd, 0x1FF);
		errs	+= _dev_dio_output(fd, 0x000);

		gsc_label_level_inc();
		errs	+= _dev_init(fd);
		gsc_label("Status");
		printf("%s\n", errs ? "FAIL <---" : "PASS");
		gsc_label_level_dec();
		break;
	}

	return(errs);
}



