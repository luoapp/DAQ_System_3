// $URL: http://subversion:8080/svn/gsc/trunk/drivers/LINUX/ADADIO/ADADIO_Linux_3.x.x.x_GSC_DN/din/dio.c $
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
*	Function:	_dev_dio_port_dir_set_in
*
*	Purpose:
*
*		Set the port to an input.
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

static int _dev_dio_port_dir_set_in(int fd)
{
	int		errs;
	__u32	val		= ADADIO_DIO_PORT_DIR_INPUT;

	errs	= ioctl(fd, ADADIO_IOCTL_DIO_PORT_DIR, &val);
	errs	= (errs == -1) ? 1 : 0;
	return(errs);
}



/******************************************************************************
*
*	Function:	_dev_dio_port_in
*
*	Purpose:
*
*		Read from the Digital I/O Port input.
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

static int _dev_dio_port_in(int fd)
{
	__u8	data;
	int		errs;
	__u32	val;

	errs	= ioctl(fd, ADADIO_IOCTL_DIO_PORT_READ, &val);
	errs	= (errs == -1) ? 1 : 0;
	data	= val;
	_bin_show(data);
	return(errs);
}



/******************************************************************************
*
*	Function:	_dev_dio_pin_in
*
*	Purpose:
*
*		Read from the Digital I/O Pin input.
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

static int _dev_dio_pin_in(int fd)
{
	__u8	data;
	int		errs;
	__u32	val;

	errs	= ioctl(fd, ADADIO_IOCTL_DIO_PIN_READ, &val);
	errs	= (errs == -1) ? 1 : 0;
	data	= val;

	if (data == ADADIO_DIO_PIN_SET)
		printf("1");
	else
		printf("0");

	return(errs);
}



/******************************************************************************
*
*	Function:	dio_in
*
*	Purpose:
*
*		Perform a Dogital Input test.
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

int dio_in(int fd)
{
	int	errs	= 0;
	int	i;

	for (;;)	// a CONVENIENCE LOOP.
	{
		gsc_label("Digital Input");
		errs	+= _dev_init(fd);
		errs	+= _dev_dio_port_dir_set_in(fd);

		if (errs)
		{
			printf("FAIL <---\n");
			break;
		}

		printf("\n");
		printf("    DIO PORT  DIO Pin\n");
		printf("    01234567  0\n");
		printf("    ========  =\n");

		for (i = 0; i < 16; i++)
		{
			printf("    ");
			errs	+= _dev_dio_port_in(fd);
			printf("  ");
			errs	+= _dev_dio_pin_in(fd);
			printf("\n");
			usleep(250000);
		}

		gsc_label_level_inc();
		errs	+= _dev_init(fd);
		gsc_label("Status");
		printf("%s\n", errs ? "FAIL <---" : "PASS");
		gsc_label_level_dec();
		break;
	}

	return(errs);
}



