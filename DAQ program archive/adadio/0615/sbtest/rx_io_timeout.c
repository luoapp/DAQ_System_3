// $URL: http://subversion:8080/svn/gsc/trunk/drivers/LINUX/ADADIO/ADADIO_Linux_3.x.x.x_GSC_DN/sbtest/rx_io_timeout.c $
// $Rev: 1620 $
// $Date: 2009-04-10 11:41:41 -0500 (Fri, 10 Apr 2009) $

#include <errno.h>
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
			/* cmd		*/	ADADIO_IOCTL_RX_IO_TIMEOUT,
			/* arg		*/	ADADIO_IO_TIMEOUT_MAX,
			/* reg		*/	-1,
			/* mask		*/	0,
			/* value	*/	0
		},
		{
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	ADADIO_IOCTL_RX_IO_TIMEOUT,
			/* arg		*/	(ADADIO_IO_TIMEOUT_MIN + ADADIO_IO_TIMEOUT_MAX) / 2,
			/* reg		*/	-1,
			/* mask		*/	0,
			/* value	*/	0
		},
		{
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	ADADIO_IOCTL_RX_IO_TIMEOUT,
			/* arg		*/	ADADIO_IO_TIMEOUT_MIN,
			/* reg		*/	-1,
			/* mask		*/	0,
			/* value	*/	0
		},
		{
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	ADADIO_IOCTL_RX_IO_TIMEOUT,
			/* arg		*/	ADADIO_IO_TIMEOUT_NO_SLEEP,
			/* reg		*/	-1,
			/* mask		*/	0,
			/* value	*/	0
		},
		{
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	ADADIO_IOCTL_RX_IO_TIMEOUT,
			/* arg		*/	ADADIO_IO_TIMEOUT_DEFAULT,
			/* reg		*/	-1,
			/* mask		*/	0,
			/* value	*/	0
		},
		{ SERVICE_END_LIST }
	};

	int errs	= 0;

	errs	+= adadio_initialize_quiet(fd);

	errs	+= service_ioctl_set_get_list(fd, list);

	errs	+= service_ioctl_set_get_list(fd, list);

	errs	+= adadio_initialize_quiet(fd);
	return(errs);
}




//*****************************************************************************
static int _function_test(int fd)
{
	#define	TIMEOUT_1	2
	#define	TIMEOUT_2	6

	static const service_data_t	list_1[]	=
	{
		{
			/* service	*/	SERVICE_NORMAL,
			/* cmd		*/	ADADIO_IOCTL_RX_IO_TIMEOUT,
			/* arg		*/	TIMEOUT_1,
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
			/* cmd		*/	ADADIO_IOCTL_RX_IO_TIMEOUT,
			/* arg		*/	TIMEOUT_2,
			/* reg		*/	-1,
			/* mask		*/	0,
			/* value	*/	0
		},

		{ SERVICE_END_LIST }
	};

	__u32	data[1];
	long	dt1;
	long	dt2;
	int		errs	= 0;
	int		i;
	time_t	t1;
	time_t	t2;
	time_t	t3;

	errs	+= adadio_initialize_quiet(fd);
	errs	+= service_ioctl_set_get_list(fd, list_1);
	t1		= time(NULL);

	if (errs == 0)
	{
		i	= read(fd, &data, 4);

		if (i != 0)
		{
			errs++;
			printf(	"FAIL <---  (%d. read(): returned %d, expected 0)\n",
					__LINE__,
					i);
		}
	}

	errs	+= service_ioctl_set_get_list(fd, list_2);
	t2		= time(NULL);

	if (errs == 0)
	{
		i	= read(fd, &data, 4);

		if (i != 0)
		{
			errs++;
			printf(	"FAIL <---  (%d. read(): returned %d, expected 0)\n",
					__LINE__,
					i);
		}
	}

	t3	= time(NULL);
	dt1	= t2 - t1;
	dt2	= t3 - t2;

	if (errs)
	{
	}
	else if ((dt1 < (TIMEOUT_1 - 1)) || (dt1 > (TIMEOUT_1 + 1)))
	{
		errs++;
		printf(	"FAIL <---  (%d. timeout was %ld, expected %ld to %ld)\n",
				__LINE__,
				dt1,
				(long) TIMEOUT_1 - 1,
				(long) TIMEOUT_1 + 1);
	}
	else if ((dt2 < (TIMEOUT_2 - 1)) || (dt2 > (TIMEOUT_2 + 1)))
	{
		errs++;
		printf(	"FAIL <---  (%d. timeout was %ld, expected %ld to %ld)\n",
				__LINE__,
				dt2,
				(long) TIMEOUT_2 - 1,
				(long) TIMEOUT_2 + 1);
	}

	errs	+= adadio_initialize_quiet(fd);
	return(errs);
}




/******************************************************************************
*
*	Function:	rx_io_timeout_test
*
*	Purpose:
*
*		Perform a test of the IOCTL service ADADIO_IOCTL_RX_IO_TIMEOUT.
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

int rx_io_timeout_test(int fd)
{
	int	errs	= 0;

	gsc_label("ADADIO_IOCTL_RX_IO_TIMEOUT");
	errs	+= _service_test(fd);
	errs	+= _function_test(fd);

	if (errs == 0)
		printf("PASS\n");

	return(errs);
}


