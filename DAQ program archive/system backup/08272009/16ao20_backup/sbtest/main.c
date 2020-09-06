// $URL: http://subversion:8080/svn/gsc/trunk/drivers/LINUX/16AO20/16AO20_Linux_2.x.x.x_GSC_DN/sbtest/main.c $
// $Rev: 2014 $
// $Date: 2009-05-19 12:39:09 -0500 (Tue, 19 May 2009) $

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "main.h"



// variables	***************************************************************

static	int		_continuous		= 0;
static	int		_ignore_errors	= 0;
static	int		_index			= 0;
static	long	_minute_limit	= 0;
static	int		_test_limit		= -1;



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

	printf("USAGE: sbtest <-c> <-C> <-m#> <-n#> <index>\n");
	printf("   -c     Continue testing until an error occurs.\n");
	printf("   -C     Continue testing even if errors occur.\n");
	printf("   -m#    Run for at most # minutes (a decimal number).\n");
	printf("   -n#    Repeat test at most # times (a decimal number).\n");
	printf("   index  The index of the board to access.\n");
	printf(" NOTE: Hit Ctrl-C to abort continuous testing.\n");

	for (i = 1; i < argc; i++)
	{
		if (strcmp(argv[i], "-c") == 0)
		{
			_continuous		= 1;
			_ignore_errors	= 0;
			continue;
		}

		if (strcmp(argv[i], "-C") == 0)
		{
			_continuous		= 1;
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

		j	= sscanf(argv[i], "%d%c", &k, &c);

		if ((j == 1) && (k >= 0))
		{
			_index	= k;
			continue;
		}
		else
		{
			errs	= 1;
			printf("ERROR: invalid board selection: %s\n", argv[i]);
			break;
		}
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

	errs	+= reg_read_test(fd);			// AO20_IOCTL_REG_READ
	errs	+= reg_write_test(fd);			// AO20_IOCTL_REG_WRITE
	errs	+= reg_mod_test(fd);			// AO20_IOCTL_REG_MOD
	errs	+= query_test(fd);				// AO20_IOCTL_QUERY
	errs	+= initialize_test(fd);			// AO20_IOCTL_INITIALIZE
	errs	+= auto_calibrate_test(fd);		// AO20_IOCTL_AUTO_CALIBRATE
	errs	+= buffer_clear_test(fd);		// AO20_IOCTL_BUFFER_CLEAR
	errs	+= buffer_mode_test(fd);		// AO20_IOCTL_BUFFER_MODE
	errs	+= buffer_over_data_test(fd);	// AO20_IOCTL_BUFFER_OVER_DATA
	errs	+= buffer_over_frame_test(fd);	// AO20_IOCTL_BUFFER_OVER_FRAME
	errs	+= buffer_size_test(fd);		// AO20_IOCTL_BUFFER_SIZE
	errs	+= buffer_status_test(fd);		// AO20_IOCTL_BUFFER_STATUS
	errs	+= burst_ready_test(fd);		// AO20_IOCTL_BURST_READY
	errs	+= burst_trg_src_test(fd);		// AO20_IOCTL_BURST_TRIG_SRC
	errs	+= burst_trigger_test(fd);		// AO20_IOCTL_BURST_TRIGGER
	errs	+= channel_sel_test(fd);		// AO20_IOCTL_CHANNEL_SEL
	errs	+= clock_enable_test(fd);		// AO20_IOCTL_CLOCK_ENABLE
	errs	+= clock_osc_src_test(fd);		// AO20_IOCTL_CLOCK_OSC_SRC
	errs	+= clock_ready_test(fd);		// AO20_IOCTL_CLOCK_READY
	errs	+= clock_src_test(fd);			// AO20_IOCTL_CLOCK_SRC
	errs	+= clock_sw_test(fd);			// AO20_IOCTL_CLOCK_SW
	errs	+= data_format_test(fd);		// AO20_IOCTL_DATA_FORMAT
	errs	+= ground_sense_test(fd);		// AO20_IOCTL_GROUND_SENSE
	errs	+= irq_enable_test(fd);			// AO20_IOCTL_IRQ_ENABLE
	errs	+= irq_sel_test(fd);			// AO20_IOCTL_IRQ_SEL
	errs	+= irq_state_test(fd);			// AO20_IOCTL_IRQ_STATE
	errs	+= load_ready_test(fd);			// AO20_IOCTL_LOAD_READY
	errs	+= load_request_test(fd);		// AO20_IOCTL_LOAD_REQUEST
	errs	+= nclk_test(fd);				// AO20_IOCTL_NCLK
	errs	+= nrate_test(fd);				// AO20_IOCTL_NRATE
	errs	+= output_mode_test(fd);		// AO20_IOCTL_OUTPUT_MODE
	errs	+= sample_mode_test(fd);		// AO20_IOCTL_SAMPLE_MODE
	errs	+= tx_io_mode_test(fd);			// AO20_IOCTL_TX_IO_MODE
	errs	+= tx_io_over_data_test(fd);	// AO20_IOCTL_TX_IO_OVER_DATA
	errs	+= tx_io_over_frame_test(fd);	// AO20_IOCTL_TX_IO_OVER_FRAME
	errs	+= tx_io_timeout_test(fd);		// AO20_IOCTL_TX_IO_TIMEOUT
	errs	+= xcvr_type_test(fd);			// AO20_IOCTL_XCVR_TYPE

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

int main(int argc, char** argv)
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
	time_t	t_limit;
	time_t	test;
	long	tests		= 0;

	gsc_label_init(28);

	for (;;)
	{
		test	= time(NULL);
		printf("sbtest - Single Board Test Application (Version %s)\n", VERSION);
		errs	= _parse_args(argc, argv);

		if (errs)
			break;

		gsc_id_host();
		t_limit	= exec + (_minute_limit * 60);
		qty		= gsc_count_boards(AO20_BASE_NAME);
		errs	= gsc_select_1_board(qty, &_index);

		if ((qty <= 0) || (errs))
			break;

		gsc_label("Testing Board Index");
		printf("%d\n", _index);
		fd	= gsc_dev_open(_index, AO20_BASE_NAME);

		if (fd == -1)
		{
			errs	= 1;
			printf(	"ERROR: Unable to access device %d.", _index);
		}

		if (errs == 0)
		{
			ret		= EXIT_SUCCESS;
			errs	= _perform_tests(fd);
		}

		gsc_dev_close(_index, fd);

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



