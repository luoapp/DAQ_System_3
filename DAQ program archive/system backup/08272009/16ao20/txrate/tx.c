// $URL: http://subversion:8080/svn/gsc/trunk/drivers/LINUX/16AO20/16AO20_Linux_2.x.x.x_GSC_DN/txrate/tx.c $
// $Rev: 2014 $
// $Date: 2009-05-19 12:39:09 -0500 (Tue, 19 May 2009) $

#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/timeb.h>

#include "main.h"



// #defines	*******************************************************************

#define	_1M	(1024L * 1024L)



// variables	***************************************************************

static __u32	_tx[_1M];



/******************************************************************************
*
*	Function:	_rate_test
*
*	Purpose:
*
*		Perform for the write rate test.
*
*	Arguments:
*
*		fd		The handle to the board.
*
*		seconds	The minimum number of seconds to operate.
*
*		mb		The niminum number of mega-bytes to write.
*
*		send	The number of bytes to request with each write call.
*
*	Returned:
*
*		>= 0	The number of errors encounterred.
*
******************************************************************************/

static int _rate_test(int fd, int seconds, long mb, long send)
{
	struct timeb	begin;
	int				errs	= 0;
	struct timeb	minimum;
	float			ms;
	struct timeb	now;
	long			sent;
	long			sent_acc	= 0;
	long			sent_mb	= 0;
	float			total;

	gsc_label("Writing");

	ftime(&begin);
	minimum.time	= begin.time + seconds;
	minimum.millitm	= begin.millitm;

	memset(_tx, 0x01, sizeof(_tx));

	for (;;)
	{
		sent	= write(fd, _tx, send);

		if (sent < 0)
		{
			errs++;
			printf("FAIL <--- (write, errno %d)\n", errno);
			break;
		}

		ftime(&now);
		sent_acc	+= sent;

		if (sent_acc >= _1M)
		{
			for (; sent_acc >= _1M;)
			{
				sent_acc	-= _1M;
				sent_mb++;
			}

			if (((now.time > minimum.time) ||
				((now.time == minimum.time) && (now.millitm >= minimum.millitm))) &&
				(sent_mb >= mb))
			{
				break;
			}
		}
	}

	if (errs == 0)
	{
		total	= (float) sent_mb * _1M + sent_acc;
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
*	Function:	tx_rate_test
*
*	Purpose:
*
*		Perform an Tx Rate test - measure the write throughput.
*
*	Arguments:
*
*		fd		The handle to the board.
*
*		mb		The niminum number of mega-bytes to write.
*
*	Returned:
*
*		>= 0	The number of errors encounterred.
*
******************************************************************************/

int tx_rate_test(int fd, long mb)
{
	int		errs	= 0;
	int		seconds	= 5;
	long	send	= sizeof(_tx);

	gsc_label ("Write Rate");
	printf("(%d second minimum, %ld MB minimum)\n", seconds, mb);
	gsc_label_level_inc();

	errs	+= _rate_test(fd, seconds, mb, send);

	gsc_label_level_dec();
	return(errs);
}



