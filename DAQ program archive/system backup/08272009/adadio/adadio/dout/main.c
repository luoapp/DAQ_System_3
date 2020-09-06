// $URL: http://subversion:8080/svn/gsc/trunk/drivers/LINUX/ADADIO/ADADIO_Linux_3.x.x.x_GSC_DN/dout/main.c $
// $Rev: 1620 $
// $Date: 2009-04-10 11:41:41 -0500 (Fri, 10 Apr 2009) $

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <asm/types.h>

#include "adadio.h"
#include "main.h"
#include "gsc_utils.h"



/* variables	**************************************************************/

static	int		_continuous		= 0;
static	int		_def_board		= -1;
static	int		_ignore_errors	= 0;
static	long	_minute_limit	= 0;
static	int		_test_limit		= -1;



/*****************************************************************************
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
*****************************************************************************/

static int _parse_args(int argc, char** argv)
{
	char	c;
	int		errs	= 0;
	int		i;
	int		j;
	int		k;

	printf("USAGE: dout <-c> <-C> <-m#> <-n#> <#>\n");
	printf("   -c   Continue testing until an error occurs.\n");
	printf("   -C   Continue testing even if errors occur.\n");
	printf("   -m#  Run for at most # minutes (a decimal number).\n");
	printf("   -n#  Repeat test at most # times (a decimal number).\n");
	printf("   #    The default board index to test.\n");
	printf(" NOTE: Hit Ctrl-C to abort continuous testing.\n");

	for (i = 1; i < argc; i++)
	{
		if (strcmp(argv[i], "-c") == 0)
		{
			_continuous	= 1;
			_ignore_errors	= 0;
			continue;
		}

		if (strcmp(argv[i], "-C") == 0)
		{
			_continuous	= 1;
			_ignore_errors	= 1;
			continue;
		}

		if ((argv[i][0] == '-') && (argv[i][1] == 'm') && (argv[i][2]))
		{
			j	= sscanf(&argv[i][2], "%d%c", &k, &c);

			if ((j == 1) && (k > 0))
			{
				_minute_limit	= k;
				continue;
			}

			errs	= 1;
			printf("ERROR: invalid argument: %s\n", argv[i]);
			break;
		}

		if ((argv[i][0] == '-') && (argv[i][1] == 'n') && (argv[i][2]))
		{
			j	= sscanf(&argv[i][2], "%d%c", &k, &c);

			if ((j == 1) && (k > 0))
			{
				_test_limit	= k;
				continue;
			}

			errs	= 1;
			printf("ERROR: invalid argument: %s\n", argv[i]);
			break;
		}

		if (isdigit(argv[i][0]) == 0)
		{
			errs	= 1;
			printf("ERROR: invalid argument: %s\n", argv[i]);
			break;
		}

		j	= sscanf(argv[i], "%d%c", &k, &c);

		if ((j == 1) && (k >= 0))
		{
			_def_board	= k;
			continue;
		}

		errs	= 1;
		printf("ERROR: invalid argument: %s\n", argv[i]);
		break;
	}

	return(errs);
}



/*****************************************************************************
*
*	Function:	_perform_tests
*
*	Purpose:
*
*		Perform the appropriate testing.
*
*	Arguments:
*
*		fd		The handle for the device to test.
*
*	Returned:
*
*		>= 0	The number of errors encounterred.
*
*****************************************************************************/

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

	errs	+= gsc_id_driver(fd, ADADIO_BASE_NAME);
	errs	+= dio_out(fd);

	return(errs);
}



/******************************************************************************
*
*	Function:	main
*
*	Purpose:
*
*		Control the overall operation of the program.
*
*	Arguments:
*
*		argc			The number of arguments passed to the program.
*
*		argv			The list of arguments passed to the program.
*
*	Returned:
*
*		EXIT_SUCCESS	All went well.
*
******************************************************************************/

int main(int argc, char** argv)
{
	int		errs;
	time_t	exec		= time(NULL);
	long	failures	= 0;
	int		fd			= -1;
	long	hours;
	long	mins;
	time_t	now;
	long	passes		= 0;
	int		qty;
	int		ret			= EXIT_FAILURE;
	long	secs;
	time_t	t_limit;
	time_t	test;
	long	tests		= 0;

	gsc_label_init(26);

	for (;;)	// This is a convenience loop.
	{
		test	= time(NULL);
		printf("ADADIO Digital Output Sample (Version %s)\n", VERSION);
		errs	= _parse_args(argc, argv);

		if (errs)
			break;

		t_limit	= exec + (_minute_limit * 60);
		gsc_id_host();
		qty		= gsc_count_boards(ADADIO_BASE_NAME);
		errs	= gsc_select_1_board(qty, &_def_board);

		if ((qty <= 0) || (errs))
			break;

		gsc_label("Testing Board Index");
		printf("%d\n", _def_board);
		fd	= gsc_dev_open(_def_board, ADADIO_BASE_NAME);

		if (fd == -1)
		{
			errs	= 1;
			printf("ERROR: Unable to access device %d\n", _def_board);
		}
		else
		{
			ret		= EXIT_SUCCESS;
			errs	= _perform_tests(fd);
		}

		gsc_dev_close(_def_board, fd);

		now	= time(NULL);
		tests++;

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
		printf(	"SUMMARY: tests %ld, pass %ld, fail %ld"
				" (duration %ld:%ld:%02ld)\n\n",
				tests,
				passes,
				failures,
				hours,
				mins,
				secs);

		if ((_test_limit > 0) && (_test_limit <= tests))
			break;

		if (_continuous == 0)
			break;

		if ((_ignore_errors == 0) && (errs))
			break;

		if ((_minute_limit) && (now >= t_limit))
			break;
	}

	return(ret);
}



