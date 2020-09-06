// $URL: http://subversion:8080/svn/gsc/trunk/drivers/LINUX/ADADIO/ADADIO_Linux_3.x.x.x_GSC_DN/rxrate/rx.c $
// $Rev: 1620 $
// $Date: 2009-04-10 11:41:41 -0500 (Fri, 10 Apr 2009) $

#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/timeb.h>

#include "main.h"



// #defines	*******************************************************************

#define	_1M	(1024L * 1024L)



// variables	***************************************************************

static __u32	_rx[_1M];



/******************************************************************************
*
*	Function:	_rate_test
*
*	Purpose:
*
*		Perform for the read rate test.
*
*	Arguments:
*
*		fd		The handle to the board.
*
*		seconds	The minimum number of seconds to operate.
*
*		mb		The niminum number of mega-bytes to read.
*
*		get		The number of bytes to request with each read call.
*
*	Returned:
*
*		>= 0	The number of errors encounterred.
*
******************************************************************************/

static int _rate_test(int fd, int seconds, long mb, long get)
{
	struct timeb	begin;
	int				errs	= 0;
	long			got;
	long			got_acc	= 0;
	long			got_mb	= 0;
	struct timeb	minimum;
	float			ms;
	struct timeb	now;
	float			total;

	gsc_label("Reading");

	ftime(&begin);
	minimum.time	= begin.time + seconds;
	minimum.millitm	= begin.millitm;

	for (;;)
	{
		got	= read(fd, _rx, get);

		if (got < 0)
		{
			errs++;
			printf("FAIL <--- (read, errno %d)\n", errno);
			break;
		}

		ftime(&now);
		got_acc	+= got;

		if (got_acc >= _1M)
		{
			for (; got_acc >= _1M;)
			{
				got_acc	-= _1M;
				got_mb++;
			}

			if (((now.time > minimum.time) ||
				((now.time == minimum.time) && (now.millitm >= minimum.millitm))) &&
				(got_mb >= mb))
			{
				break;
			}
		}
	}

	if (errs == 0)
	{
		total	= (float) got_mb * _1M + got_acc;
		ms		= ((1.0 * now.time - begin.time) * 1000)
				+ now.millitm - begin.millitm;
		printf(	"PASS  (");
		gsc_label_long_comma((long) total);
		printf(" Bytes, %.3f Seconds, ", ms / 1000);
		gsc_label_long_comma((long) (total / ms * 1000));
		printf(" B/S, ");
		gsc_label_long_comma((long) (total / ms * 1000) / 4);
		printf(" S/S)\n");
	}

	return(errs);
}



/******************************************************************************
*
*	Function:	rx_rate_test
*
*	Purpose:
*
*		Perform an Rx Rate test - measure the read throughput.
*
*	Arguments:
*
*		fd		The handle to the board.
*
*		mb		The niminum number of mega-bytes to read.
*
*	Returned:
*
*		>= 0	The number of errors encounterred.
*
******************************************************************************/

int rx_rate_test(int fd, long mb)
{
	int		errs	= 0;
	long	get		= sizeof(_rx);
	int		seconds	= 5;

	gsc_label ("Read Rate");
	printf("(%d second minimum, %ld MB minimum)\n", seconds, mb);
	gsc_label_level_inc();

	errs	+= _rate_test(fd, seconds, mb, get);

	gsc_label_level_dec();
	return(errs);
}



