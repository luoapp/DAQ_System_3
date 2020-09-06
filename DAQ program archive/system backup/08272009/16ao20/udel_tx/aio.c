// $URL: http://subversion:8080/svn/gsc/trunk/drivers/LINUX/16AO20/16AO20_Linux_2.x.x.x_GSC_DN/aout/aio.c $
// $Rev: 2014 $
// $Date: 2009-05-19 12:39:09 -0500 (Tue, 19 May 2009) $

#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <time.h>


#include "udel_output.h"



/* variables	**************************************************************/

static	__u32	_data[128 * 1024];
static	long	_loops;	// Number of times to send a block of data.
static	long	_qty;	// Number of samples to send per block.



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
*		chans	The number of channels we're using.
*
*		rate	The data output clock rate.
*
*		seconds	Generate data for this period of time.
*
*	Returned:
*
*		>= 0	The number of errors seen.
*
******************************************************************************/

static void _init_data(int chans, long rate, int seconds)
{
	#define	PIE		(3.1415962)

	__u32*		dest;
	int			i;
	long		period_len;	// The length of the pattern in samples.
	long		period_tot;	// Pattern samples total for all channels.
	long		period;		// Pattern length in x units.
	int			samp;
	float		samp_dat;	// Total sample size of the data buffer.
	float		samp_sec;	// Samples Per Second for all active channels
	float		samp_tot;	// Samples Total for all active channels
	const char*	units;

	gsc_label("Initializing Data");
	memset(_data, 0, sizeof(_data));
	samp_sec	= ((float) rate) * chans;
	samp_tot	= ((float) rate) * chans * seconds;
	samp_dat	= sizeof(_data) / 4;

	period_len	= (rate <= 100) ? rate				//      10-      100 ->    10-   100
				: (rate <= 1000) ? (rate / 2)		//     101-    1,000 ->    50-   500
				: (rate <= 10000) ? (rate / 5)		//   1,001-   10,000 ->   200- 2,000
				: (rate <= 100000) ? (rate / 10)	//  10,001-  100,000 -> 1,000-10,000
				: (rate / 100);						// 100,001-1,000,000 -> 1,000-10,000
	period_tot	= period_len * chans;
	period		= (long) (1000000000. / rate * period_len);
	units		= "ns";

	if ((period % 1000) == 0)
	{
		period	/= 1000;
		units	= "us";
	}

	if ((period % 1000) == 0)
	{
		period	/= 1000;
		units	= "ms";
	}

	if (samp_tot <= ARRAY_ELEMENTS(_data))
	{
		// We can get the entire image in the buffer.
		_loops	= 1;
		_qty	= (long) samp_tot;
	}
	else if (samp_sec <= ARRAY_ELEMENTS(_data))
	{
		// We can get one second of the image in the buffer.
		_loops	= seconds;
		_qty	= (long) samp_sec;
	}
	else if (period_tot <= ARRAY_ELEMENTS(_data))
	{
		// We can get one period of the image in the buffer.
		_loops	= seconds * (samp_sec / period_tot);
		_qty	= period_tot;
	}
	else
	{
		// We can get only a fraction of a period of the image in the buffer.
		_qty	= (samp_dat / chans) * chans;
		_loops	= (samp_tot + _qty - 1) / _qty;
	}

	// Initialize the data buffer.
	// The data is encoded in OFFSET BINARY format.
	dest	= _data;;

	for (i = 0, samp = 0; i < _qty; i += chans, samp++)
	{
		samp	= (samp < period_len) ? samp : 0;

		// 1st channel: sawtooth wave
		*dest++	= (__u16) (0xFFFF - (0xFFFF * samp / (period_len - 1)));

		// 2nd channel: ramp wave
		if (chans >= 2)
			*dest++	= (__u16) (0xFFFF * samp / (period_len - 1));

		// 3rd channel: square wave
		if (chans >= 3)
			*dest++	= (samp < (period_len / 2)) ? 0xFFFF : 0;

		// 4th channel: sine wave
		if (chans >= 4)
			*dest++	= ((long) 0x7FFF) * (1 + sin((2 * PIE / period_len) * samp));
		if (chans >= 5)
			*dest++	= ((long) 0x7FFF) * (1 + sin((2 * PIE / period_len) * samp));
		if (chans >= 6)
			*dest++	= ((long) 0x7FFF) * (1 + sin((2 * PIE / period_len) * samp));
		if (chans >= 7)
			*dest++	= ((long) 0x7FFF) * (1 + sin((2 * PIE / period_len) * samp));
		if (chans >= 8)
			*dest++	= ((long) 0x7FFF) * (1 + sin((2 * PIE / period_len) * samp));
		if (chans >= 9)
			*dest++	= ((long) 0x7FFF) * (1 + sin((2 * PIE / period_len) * samp));
		if (chans >= 10)
			*dest++	= ((long) 0x7FFF) * (1 + sin((2 * PIE / period_len) * samp));
	}

	printf("DONE   (pattern length: %ld samples, %ld %s)\n", period_len, period, units);
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
*		chans	The number of channels being used.
*
*		errs	This is the number of errors seen so far. We don't do the
*				work if errors have been see.
*
*	Returned:
*
*		>= 0	The number of errors seen.
*
******************************************************************************/

static int _io_write(int fd, int chans, int errs)
{
	time_t	begin;
	time_t	end;
	long	loop;
	char*	ptr;
	int		secs;
	int		send;
	int		sent;
	__s32	status;
	float	total	= 0;

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
		begin	= time(NULL);

		// Write the data to the device.

		for (loop = 0; loop < _loops; loop++)
		{
			send	= _qty * 4;
			ptr		= (char*) &_data;
			//printf("send = %d\n", send);
			for (;;)
			{
				sent	= write(fd, ptr, send);
				//printf("sent = %d\n",sent);
				if (sent <= 0)
					break;

				total	+= sent;

				if (sent == send)
					break;

				ptr		+= sent;
				send	-= sent;
			}

			if (sent <= 0)
				break;
		}

		// Wait for the output buffer to empty.

		for (;;)
		{
			errs	+= ao20_dsl_ioctl(fd, AO20_IOCTL_BUFFER_STATUS, &status);

			if ((errs) || (status == AO20_BUFFER_STATUS_EMPTY))
				break;
		}

		// Compute the results.

		end		= time(NULL);

		if (sent == -1)
		{
			errs	= 1;
			printf("FAIL <---  (write error)\n");
		}
		else if (sent == 0)
		{
			secs	= end - begin;
			printf("FAIL <---  (I/O timeout, ");
			gsc_label_long_comma(secs);
			printf(" seconds, %.0f bytes, %.0f samples)\n", total, total / 4);
		}
		else
		{
			float	bps;
			float	sps;

			secs	= end - begin;
			bps		= total / secs;
			sps		= bps / 4;

			printf("PASS  (");
			gsc_label_long_comma(secs);
			printf(" seconds, ");

			if (total < LONG_MAX)
				gsc_label_long_comma((long) total);
			else
				printf("%.0f", total);

			printf(" bytes, ");
			gsc_label_long_comma(bps);
			printf(" B/S, ");
			gsc_label_long_comma(sps);
			printf(" S/S)\n");
		}

		break;
	}

	return(errs);
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
*		seconds	Generate data for this period of time.
*
*	Returned:
*
*		>= 0	The number of errors seen.
*
******************************************************************************/

int aio_out(int fd, int seconds, UDELctl udelctl)
{
	int		errs	= 0;
	__s32	rate;
	int nchans = 10;
	gsc_label("Analog Output");
	printf("\n");
	gsc_label_level_inc();

	errs	+= ao20_fsamp_get(fd, 1, &rate);
	_init_data(nchans, rate, seconds);
	errs	+= ao20_buffer_over_frame(fd, -1, AO20_BUFFER_OVER_FRAME_CLR, NULL);
	errs	+= ao20_buffer_over_data(fd, -1, AO20_BUFFER_OVER_DATA_CLR, NULL);
	errs	+= _io_write(fd, nchans, errs);

	gsc_label_level_dec();
	return(errs);
}


