// $URL: http://subversion:8080/svn/gsc/trunk/drivers/LINUX/ADADIO/ADADIO_Linux_3.x.x.x_GSC_DN/aout/aio.c $
// $Rev: 1620 $
// $Date: 2009-04-10 11:41:41 -0500 (Fri, 10 Apr 2009) $

#include <ctype.h>
#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <asm/types.h>
#include <sys/ioctl.h>
#include <sys/time.h>

#include "adadio.h"
#include "main.h"
#include "adadio_utils.h"
#include "gsc_utils.h"



/* #defines	******************************************************************/

#define	PIE					(3.1415962)
#define	CYCLES_PER_SECOND	10
#define	SAMPLES_PER_SECOND	1000	// try to output samples at this rate.
#define	PERIOD_SAMPLES		(SAMPLES_PER_SECOND / CYCLES_PER_SECOND)	// in samples



/* variables	**************************************************************/

static	__u32	_chan_0[SAMPLES_PER_SECOND];
static	__u32	_chan_1[SAMPLES_PER_SECOND];
static	__u32	_chan_2[SAMPLES_PER_SECOND];
static	__u32	_chan_3[SAMPLES_PER_SECOND];



/******************************************************************************
*
*	Function:	_output_timed_sample
*
*	Purpose:
*
*		Output a sample for each output channel and time it to a millesecond
*		boundary.
*
*	Arguments:
*
*		fd		This is the handle used to access the device.
*
*		index	The sample index to output.
*
*	Returned:
*
*		>= 0	The number of errors seen.
*
******************************************************************************/

static int _output_timed_sample(int fd, int index)
{
	long			ms_begin;
	long			ms_end;
	int				errs	= 0;
	int				i;
	struct timeval	tv;
	struct timezone	tz;

	i			= gettimeofday(&tv, &tz);
	ms_begin	=  tv.tv_usec / 1000;

	if (i != -1)
		i	= ioctl(fd, ADADIO_IOCTL_AOUT_CH_0_WRITE, &_chan_0[index]);

	if (i != -1)
		i	= ioctl(fd, ADADIO_IOCTL_AOUT_CH_1_WRITE, &_chan_1[index]);

	if (i != -1)
		i	= ioctl(fd, ADADIO_IOCTL_AOUT_CH_2_WRITE, &_chan_2[index]);

	if (i != -1)
		i	= ioctl(fd, ADADIO_IOCTL_AOUT_CH_3_WRITE, &_chan_3[index]);

	for (; i == 0;)
	{
		i		= gettimeofday(&tv, &tz);
		ms_end	=  tv.tv_usec / 1000;

		if (ms_end != ms_begin)
			break;	// We've rolled over to a new ms interval;
	}

	if (i != -1)
		i	= ioctl(fd, ADADIO_IOCTL_AOUT_STROBE);

	if (i == -1)
	{
		errs	= 1;
		printf("FAIL <---  (ioctl() failure, errno = %d)\n", errno);
	}

	return(errs);
}



/******************************************************************************
*
*	Function:	_io_write
*
*	Purpose:
*
*		Write the data to the device.
*
*	Arguments:
*
*		fd		This is the handle used to access the device.
*
*		seconds	Output data for this many seconds.
*
*		errs	This is the number of errors seen so far. We don't do the
*				work if errors have been see.
*
*	Returned:
*
*		>= 0	The number of errors seen.
*
******************************************************************************/

static int _io_write(int fd, int seconds, int errs)
{
	int	i;
	int	secs;

	gsc_label("Writing Data");

	for (;;)	// A convenience loop.
	{
		if (errs)
		{
			errs	= 0;
			printf("SKIPPED   (due to errors)\n");
			break;
		}

		errs	= 0;

		for (secs = 0; secs < seconds; secs++)
		{
			for (i = 0; (errs == 0) && (i < SAMPLES_PER_SECOND); i++)
				errs	+= _output_timed_sample(fd, i);
		}

		if (errs == 0)
			printf("PASS  (~%ld seconds @ ~1ms/sample)\n", (long) seconds);

		break;
	}

	return(errs);
}



/******************************************************************************
*
*	Function:	_init_data
*
*	Purpose:
*
*		initialize our transmit data buffer.
*
*	Arguments:
*
*		None.
*
*	Returned:
*
*		>= 0	The number of errors seen.
*
******************************************************************************/

static void _init_data(void)
{
	__u32*		dest;
	int			i;
	int			samp;

	// The data is encoded in OFFSET BINARY format.
	gsc_label("Initializing Data");

	// Channel 0: sawtooth wave
	memset(_chan_0, 0, sizeof(_chan_0));
	dest	= _chan_0;

	for (i = 0, samp = 0; i < SAMPLES_PER_SECOND; i++)
	{
		*dest++	= (__u16) (0xFFFF - (0xFFFF * samp / (PERIOD_SAMPLES - 1)));
		samp	= (samp + 1) % PERIOD_SAMPLES;
	}

	// Channel 1: ramp wave
	memset(_chan_1, 0, sizeof(_chan_1));
	dest	= _chan_1;

	for (i = 0, samp = 0; i < SAMPLES_PER_SECOND; i++)
	{
		*dest++	= (__u16) (0xFFFF * samp / (PERIOD_SAMPLES - 1));
		samp	= (samp + 1) % PERIOD_SAMPLES;
	}

	// Channel 2: square wave
	memset(_chan_2, 0, sizeof(_chan_2));
	dest	= _chan_2;

	for (i = 0, samp = 0; i < SAMPLES_PER_SECOND; i++)
	{
		*dest++	= (samp < (PERIOD_SAMPLES / 2)) ? 0xFFFF : 0;
		samp	= (samp + 1) % PERIOD_SAMPLES;
	}

	// Channel 3: square wave
	memset(_chan_3, 0, sizeof(_chan_3));
	dest	= _chan_3;

	for (i = 0, samp = 0; i < SAMPLES_PER_SECOND; i++)
	{
		*dest++	= ((long) 0x7FFF) * (1 + sin((2 * PIE / PERIOD_SAMPLES) * samp));
		samp	= (samp + 1) % PERIOD_SAMPLES;
	}

	printf("DONE  (pattern length: %ld samples)\n", (long) PERIOD_SAMPLES);
}



/******************************************************************************
*
*	Function:	aio_out
*
*	Purpose:
*
*		Ganerate Analog Output.
*
*	Arguments:
*
*		fd		The file descriptor for the board to access.
*
*		seconds	Output data for this period of time.
*
*	Returned:
*
*		>= 0	The number of errors seen.
*
******************************************************************************/

int aio_out(int fd, int seconds)
{
	int	errs	= 0;

	gsc_label("Analog Output");
	printf("\n");
	gsc_label_level_inc();

	gsc_label("Channels");
	printf("#0, #1, #2, #3\n");

	errs	+= adadio_initialize(fd, -1);
	errs	+= adadio_auto_calibrate(fd, -1);
	errs	+= adadio_aout_strobe_enable(fd, -1, ADADIO_AOUT_STROBE_ENABLE_YES, NULL);
	errs	+= adadio_data_format(fd, -1, ADADIO_DATA_FORMAT_OFF_BIN, NULL);
	errs	+= adadio_aout_enable(fd, -1, ADADIO_AOUT_ENABLE_YES, NULL);
	_init_data();
	errs	+= _io_write(fd, seconds, errs);
	gsc_label_level_dec();
	return(errs);
}


