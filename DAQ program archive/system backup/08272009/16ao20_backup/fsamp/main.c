// $URL: http://subversion:8080/svn/gsc/trunk/drivers/LINUX/16AO20/16AO20_Linux_2.x.x.x_GSC_DN/fsamp/main.c $
// $Rev: 2014 $
// $Date: 2009-05-19 12:39:09 -0500 (Tue, 19 May 2009) $

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "main.h"



// variables	***************************************************************

static	int		_def_board	= -1;
static	__s32	_fsamp		= -1;



/******************************************************************************
*
*	Function:	_parse_args
*
*	Purpose:
*
*		Parse the command line arguments.
*
*	Arguments:
*
*		argc	The number of command line arguments given.
*
*		argv	The list of command line arguments given.
*
*	Returned:
*
*		>= 0	The number of errors encounterred.
*
******************************************************************************/

static int _parse_args(int argc, char** argv)
{
	char	c;
	int		errs	= 0;
	int		i;
	int		j;
	int		k;
	long	l;

	printf("USAGE: fsamp <rate> <index>\n");
	printf("   rate   The desired rate in samples per second (a decimal number).\n");
	printf("   index  The index of the board to access.\n");
	printf(" NOTE: Hit Ctrl-C to abort continuous testing.\n");

	for (i = 1; i < argc; i++)
	{
		if (_fsamp < 0)
		{
			j	= sscanf(argv[i], "%ld%c", &l, &c);

			if ((j == 1) && (l > 0))
			{
				_fsamp	= l;
				continue;
			}

			errs	= 1;
			printf("ERROR: invalid argument: %s\n", argv[i]);
			break;
		}

		if (_def_board < 0)
		{
			j	= sscanf(&argv[i][2], "%d%c", &k, &c);

			if ((j == 1) && (k > 0))
			{
				_def_board	= k;
				continue;
			}

			errs	= 1;
			printf("ERROR: invalid argument: %s\n", argv[i]);
			break;
		}

		errs	= 1;
		printf("ERROR: invalid argument: #%d, %s\n", i, argv[i]);
		break;
	}

	return(errs);
}



/******************************************************************************
*
*	Function:	_perform_tests
*
*	Purpose:
*
*		Perform the appropriate testing.
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

static int _perform_tests(int fd)
{
	int			errs	= 0;
	const char*	psz;
	struct tm*	stm;
	time_t		tt;

	time(&tt);
	stm	= localtime(&tt);
	psz	= asctime(stm);
	gsc_label("Performing Test");
	printf("%s", psz);

	errs	+= gsc_id_driver(fd, AO20_BASE_NAME);
	errs	+= ao20_id_board(fd, -1, NULL);
	errs	+= fsamp_compute(fd, _fsamp);

	return(errs);
}



/******************************************************************************
*
*	Function:	main
*
*	Purpose:
*
*		Control the overall flow of the application.
*
*	Arguments:
*
*		argc			The number of command line arguments.
*
*		argv			The list of command line arguments.
*
*	Returned:
*
*		EXIT_SUCCESS	We tested a device.
*		EXIT_FAILURE	We didn't test a device.
*
******************************************************************************/

int main(int argc, char *argv[])
{
	int		errs;
	time_t	exec		= time(NULL);
	long	failures	= 0;
	int		fd			= 0;
	long	hours;
	long	mins;
	time_t	now;
	long	passes		= 0;
	int		qty;
	int		ret			= EXIT_FAILURE;
	long	secs;
	time_t	test;

	gsc_label_init(26);

	for (;;)
	{
		test	= time(NULL);
		printf("fsamp - compute the oscillator source, Nclk and Nrate for a desired Fsamp (Version %s)\n", VERSION);

		errs	= _parse_args(argc, argv);

		if (errs)
			break;

		gsc_id_host();
		qty		= gsc_count_boards(AO20_BASE_NAME);
		errs	= gsc_select_1_board(qty, &_def_board);

		if ((qty <= 0) || (errs))
			break;

		gsc_label("Testing Board Index");
		printf("%d\n", _def_board);
		fd	= gsc_dev_open(_def_board, AO20_BASE_NAME);

		if (fd == -1)
		{
			errs	= 1;
			printf(	"ERROR: Unable to access device %d,"
					" channel %d.\n",
					_def_board,
					0);
		}

		if (errs == 0)
		{
			ret		= EXIT_SUCCESS;
			errs	= _perform_tests(fd);
		}

		gsc_dev_close(_def_board, fd);

		now	= time(NULL);

		if (errs)
		{
			failures++;
			printf(	"\nRESULTS: FAIL <---  (%d error%s)",
					errs,
					(errs == 1) ? "" : "s");
		}
		else
		{
			passes++;
			printf("\nRESULTS: PASS");
		}

		secs	= now - test;
		hours	= secs / 3600;
		secs	= secs % 3600;
		mins	= secs / 60;
		secs	= secs % 60;
		printf(" (duration %ld:%ld:%02ld)\n", hours, mins, secs);

		secs	= now - exec;
		hours	= secs / 3600;
		secs	= secs % 3600;
		mins	= secs / 60;
		secs	= secs % 60;
		printf(	"SUMMARY: pass %ld, fail %ld"
				" (duration %ld:%ld:%02ld)\n\n",
				passes,
				failures,
				hours,
				mins,
				secs);
		break;
	}

	return(ret);
}


