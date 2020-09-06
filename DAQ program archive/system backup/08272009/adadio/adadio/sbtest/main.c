// $URL: http://subversion:8080/svn/gsc/trunk/drivers/LINUX/ADADIO/ADADIO_Linux_3.x.x.x_GSC_DN/sbtest/main.c $
// $Rev: 1620 $
// $Date: 2009-04-10 11:41:41 -0500 (Fri, 10 Apr 2009) $

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "main.h"



/* #defines	***************************************************************/

#define	VERSION			"1.00"
// 1.00	initial release.



/* variables	*************************************************************/

static	int		_continuous		= 0;
static	int		_ignore_errors	= 0;
static	int		_index			= 0;
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
*		fd		The handle for the board to access.
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
	errs	+= adadio_id_board(fd, -1, NULL);

	errs	+= reg_read_test(fd);				// ADADIO_IOCTL_REG_READ
	errs	+= reg_write_test(fd);				// ADADIO_IOCTL_REG_WRITE
	errs	+= reg_mod_test(fd);				// ADADIO_IOCTL_REG_MOD
	errs	+= query_test(fd);					// ADADIO_IOCTL_QUERY
	errs	+= initialize_test(fd);				// ADADIO_IOCTL_INITIALIZE
	errs	+= auto_calibrate_test(fd);			// ADADIO_IOCTL_AUTO_CALIBRATE
	errs	+= rx_io_mode_test(fd);				// ADADIO_IOCTL_RX_IO_MODE
	errs	+= rx_io_timeout_test(fd);			// ADADIO_IOCTL_RX_IO_TIMEOUT
	errs	+= ain_buf_clear_test(fd);			// ADADIO_IOCTL_AIN_BUF_CLEAR
	errs	+= ain_buf_size_test(fd);			// ADADIO_IOCTL_AIN_BUF_SIZE
	errs	+= ain_buf_sts_test(fd);			// ADADIO_IOCTL_AIN_BUF_STS
	errs	+= ain_chan_last_test(fd);			// ADADIO_IOCTL_AIN_CHAN_LAST
	errs	+= ain_mode_test(fd);				// ADADIO_IOCTL_AIN_MODE
	errs	+= ain_nrate_test(fd);				// ADADIO_IOCTL_AIN_NRATE
	errs	+= ain_trigger_test(fd);			// ADADIO_IOCTL_AIN_TRIGGER
	errs	+= aout_ch_0_write_test(fd);		// ADADIO_IOCTL_AOUT_CH_0_WRITE
	errs	+= aout_ch_1_write_test(fd);		// ADADIO_IOCTL_AOUT_CH_1_WRITE
	errs	+= aout_ch_2_write_test(fd);		// ADADIO_IOCTL_AOUT_CH_2_WRITE
	errs	+= aout_ch_3_write_test(fd);		// ADADIO_IOCTL_AOUT_CH_3_WRITE
	errs	+= aout_enable_test(fd);			// ADADIO_IOCTL_AOUT_ENABLE
	errs	+= aout_strobe_test(fd);			// ADADIO_IOCTL_AOUT_STROBE
	errs	+= aout_strobe_enable_test(fd);		// ADADIO_IOCTL_AOUT_STROBE_ENABLE
	errs	+= data_format_test(fd);			// ADADIO_IOCTL_DATA_FORMAT
	errs	+= dio_pin_read_test(fd);			// ADADIO_IOCTL_DIO_PIN_READ
	errs	+= dio_pin_write_test(fd);			// ADADIO_IOCTL_DIO_PIN_WRITE
	errs	+= dio_port_dir_test(fd);			// ADADIO_IOCTL_DIO_PORT_DIR
	errs	+= dio_port_read_test(fd);			// ADADIO_IOCTL_DIO_PORT_READ
	errs	+= dio_port_write_test(fd);			// ADADIO_IOCTL_DIO_PORT_WRITE
	errs	+= irq_enable_test(fd);				// ADADIO_IOCTL_IRQ_ENABLE
	errs	+= irq_sel_test(fd);				// ADADIO_IOCTL_IRQ_SEL
	errs	+= irq_status_test(fd);				// ADADIO_IOCTL_IRQ_STATUS
	errs	+= loopback_channel_test(fd);		// ADADIO_IOCTL_LOOPBACK_CHANNEL

	return(errs);
}



/*****************************************************************************
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
*****************************************************************************/

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

	gsc_label_init(33);

	for (;;)
	{
		test	= time(NULL);
		printf("sbtest - Single Board Test Application (Version %s)\n", VERSION);
		errs	= _parse_args(argc, argv);

		if (errs)
			break;

		gsc_id_host();
		t_limit	= exec + (_minute_limit * 60);
		qty		= gsc_count_boards(ADADIO_BASE_NAME);
		errs	= gsc_select_1_board(qty, &_index);

		if ((qty <= 0) || (errs))
			break;

		gsc_label("Testing Board Index");
		printf("%d\n", _index);
		fd	= gsc_dev_open(_index, ADADIO_BASE_NAME);

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



