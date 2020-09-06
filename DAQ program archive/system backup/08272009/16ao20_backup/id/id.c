// $URL: http://subversion:8080/svn/gsc/trunk/drivers/LINUX/16AO20/16AO20_Linux_2.x.x.x_GSC_DN/id/id.c $
// $Rev: 2014 $
// $Date: 2009-05-19 12:39:09 -0500 (Tue, 19 May 2009) $

#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "main.h"



//*****************************************************************************
static void _local_label_string(const char* str)
{
	int	len;

	printf("%s", str);
	len	= 7 - (int) strlen(str);

	for (; len > 0; len--)
		printf(" ");
}



//*****************************************************************************
static void _local_label_long(long l)
{
	char	buf[32];

	sprintf(buf, "%ld", l);
	_local_label_string(buf);
}



//*****************************************************************************
static int _voltage_range(int fd)
{
	int		errs	= 0;
	__s32	range;

	gsc_label("Voltage Range");
	errs	+= ao20_query(fd, AO20_QUERY_RANGE, &range);

	if (errs == 0)
	{
		switch (range)
		{
			default:

				errs	= 1;
				printf("ERROR: unrecognized value: %ld\n", (long) range);
				break;

			case AO20_RANGE_2_5:	printf("+-2.5 V\n");	break;
			case AO20_RANGE_5:		printf("+-5 V\n");		break;
			case AO20_RANGE_10:		printf("+-10 V\n");		break;
		}
	}

	return(errs);
}



//*****************************************************************************
static int _output_filter(int fd)
{
	int		errs	= 0;
	__s32	filter;

	gsc_label("Output Filter");
	errs	+= ao20_query(fd, AO20_QUERY_FILTER, &filter);

	if (errs == 0)
	{
		switch (filter)
		{
			default:

				errs	= 1;
				printf("ERROR: unrecognized value: %ld\n", (long) filter);
				break;

			case AO20_FILTER_NONE:		printf("No Filter\n");	break;
			case AO20_FILTER_10KHZ:		printf("10K Hz\n");		break;
			case AO20_FILTER_100KHZ:	printf("100K Hz\n");	break;
		}
	}

	return(errs);
}



//*****************************************************************************
static int _clocking_sources(int fd)
{
	gsc_label("Clocking Sources");
	printf("Master (30MHz), Alternate (16MHz-32MHz), External, Software\n");
	return(0);
}



//*****************************************************************************
static int _channel_qty(int fd)
{
	__s32	channel_qty;
	int		errs	= 0;

	gsc_label("D/A Channels");
	errs	+= ao20_query(fd, AO20_QUERY_CHANNEL_QTY, &channel_qty);

	if (errs)
	{
	}
	else if (channel_qty <= 0)
	{
		errs	= 1;
		printf(	"FAIL <---  (%d. qty response error: %ld)\n",
				__LINE__,
				(long) channel_qty);
	}
	else
	{
		_local_label_long(channel_qty);
		printf("(16-bit resolution)\n");
	}

	return(errs);
}



//*****************************************************************************
static int _output_modes(int fd)
{
	gsc_label("Output Modes");
	printf("Simultaneous, Sequential\n");
	return(0);
}



//*****************************************************************************
static int _clocking_modes(int fd)
{
	gsc_label("Clocking Modes");
	printf("Continuous, Triggered Burst\n");
	return(0);
}



//*****************************************************************************
static int _fifo_size(int fd)
{
	int		errs	= 0;
	__s32	size;			// FIFO Size in samples

	gsc_label("FIFO Size");

	errs	+= ao20_query(fd, AO20_QUERY_FIFO_SIZE, &size);

	if (errs)
	{
	}
	else if (size <= 0)
	{
		errs	= 1;
		printf(	"FAIL <---  (%d. size response error: %ld)\n",
				__LINE__,
				(long) size);
	}
	else
	{
		gsc_label_long_comma(size);
		printf(" Samples Deep");

		if ((size % 1024) == 0)
			printf("  (%ldK)", (long) size / 1024);

		printf(", Circular or Open operation\n");
	}

	return(errs);
}



//*****************************************************************************
static int _buffer_size(int fd)
{
	int		errs	= 0;
	__s32	size;			// FIFO Size in samples

	gsc_label("FIFO Size");

	errs	+= ao20_query(fd, AO20_QUERY_FIFO_SIZE, &size);

	if (errs)
	{
	}
	else if (size <= 0)
	{
		errs	= 1;
		printf(	"FAIL <---  (%d. size response error: %ld)\n",
				__LINE__,
				(long) size);
	}
	else
	{
		printf("8 - ");
		gsc_label_long_comma(size);
		printf(" Samples Deep (by power of 2)\n");
	}

	return(errs);
}



//*****************************************************************************
static int _nrate_range(int fd)
{
	int		errs	= 0;
	__s32	mask;
	__s32	max;
	__s32	min;

	gsc_label("Nrate Range");

	errs	+= ao20_query(fd, AO20_QUERY_NRATE_MASK, &mask);
	errs	+= ao20_query(fd, AO20_QUERY_NRATE_MAX, &max);
	errs	+= ao20_query(fd, AO20_QUERY_NRATE_MIN, &min);

	if (errs)
	{
	}
	else if (max < 0)
	{
		errs	= 1;
		printf(	"FAIL <---  (%d. max response error: %ld)\n",
				__LINE__,
				(long) max);
	}
	else if (min < 0)
	{
		errs	= 1;
		printf(	"FAIL <---  (%d. min response error: %ld)\n",
				__LINE__,
				(long) min);
	}
	else if (mask < 0)
	{
		errs	= 1;
		printf(	"FAIL <---  (%d. mask response error: %ld)\n",
				__LINE__,
				(long) mask);
	}
	else if (min >= max)
	{
		errs	= 1;
		printf(	"FAIL <---  (%d. range error: %ld-%ld)\n",
				__LINE__,
				(long) min,
				(long) max);
	}
	else if (max > mask)
	{
		errs	= 1;
		printf(	"FAIL <---  (%d. mask range error: mask 0x%lX, max %ld)\n",
				__LINE__,
				(long) mask,
				(long) max);
	}
	else
	{
		gsc_label_long_comma(min);
		printf(" to ");
		gsc_label_long_comma(max);
		printf("  (mask 0x%lX)\n", (long) mask);
	}

	return(errs);
}



//*****************************************************************************
static int _fsamp_range(int fd)
{
	__s32	chans;
	int		errs	= 0;
	__s32	max;			// Sample Rate Maximum
	__s32	min;			// Sample Rate Minimum

	gsc_label("Sample Rates");

	errs	+= ao20_query(fd, AO20_QUERY_CHANNEL_QTY, &chans);
	errs	+= ao20_query(fd, AO20_QUERY_FSAMP_MAX, &max);
	errs	+= ao20_query(fd, AO20_QUERY_FSAMP_MIN, &min);

	if (errs)
	{
	}
	else if ((chans < 1) || (chans > 20))
	{
		errs	= 1;
		printf(	"FAIL <---  (%d. channel response error: %ld)\n",
				__LINE__,
				(long) max);
	}
	else if (max < 0)
	{
		errs	= 1;
		printf(	"FAIL <---  (%d. max response error: %ld)\n",
				__LINE__,
				(long) max);
	}
	else if (min < 0)
	{
		errs	= 1;
		printf(	"FAIL <---  (%d. min response error: %ld)\n",
				__LINE__,
				(long) min);
	}
	else if (min >= max)
	{
		errs	= 1;
		printf(	"FAIL <---  (%d. range error: %ld-%ld)\n",
				__LINE__,
				(long) min,
				(long) max);
	}
	else
	{
		gsc_label_long_comma(min);
		printf(" to ");
		gsc_label_long_comma(max);
		printf(" S/S/C, ");
		gsc_label_long_comma(max * chans);
		printf(" S/S/B\n");
	}

	return(errs);
}



//*****************************************************************************
static int _transceivers(int fd)
{
	gsc_label("Control Transceivers");
	printf("LVDS, TTL\n");
	return(0);
}



//*****************************************************************************
static int _firmware_version(int fd)
{
	__u32	bor;		// Board Options Register
	int		errs	= 0;
	__u32	ver;

	gsc_label("Firmware Version");

	errs	+= gsc_dev_reg_read(fd, AO20_GSC_BOR, &bor);

	if (errs == 0)
	{
		ver	= GSC_FIELD_DECODE(bor, 11, 0);
		printf("%03lX\n", (long) ver);
	}

	return(errs);
}



//*****************************************************************************
static int _initialize(int fd)
{
	int		errs	= 0;
	__s32	ms;

	gsc_label("Initialize Period");

	errs	+= ao20_query(fd, AO20_QUERY_INIT_MS, &ms);

	if (errs)
	{
	}
	else if (ms <= 0)
	{
		errs	= 1;
		printf(	"FAIL <---  (%d. ms response error: %ld)\n",
				__LINE__,
				(long) ms);
	}
	else
	{
		gsc_label_long_comma(ms);
		printf(" ms maximum\n");
	}

	return(errs);
}



//*****************************************************************************
static int _autocalibrate(int fd)
{
	int		errs	= 0;
	__s32	ms;

	gsc_label("Auto-Calibrate Period");

	errs	+= ao20_query(fd, AO20_QUERY_AUTO_CAL_MS, &ms);

	if (errs)
	{
	}
	else if (ms < 0)
	{
		errs	= 1;
		printf(	"FAIL <---  (%d. ms response error: %ld)\n",
				__LINE__,
				(long) ms);
	}
	else if (ms == 0)
	{
		printf("Auto-Calibration not supported\n");
	}
	else
	{
		gsc_label_long_comma(ms);
		printf(" ms maximum\n");
	}

	return(errs);
}



/******************************************************************************
*
*	Function:	id_device
*
*		Identify the device and its features.
*
*	Arguments:
*
*		fd		The handle to the board to access.
*
*	Returned:
*
*		>= 0	The number of errors encounterred.
*
******************************************************************************/

int id_device(int fd)
{
	int	errs	= 0;

	gsc_label("Board Features");
	printf("\n");

	gsc_label_level_inc();

	errs	+= _voltage_range(fd);
	errs	+= _channel_qty(fd);
	errs	+= _output_modes(fd);
	errs	+= _output_filter(fd);
	errs	+= _clocking_sources(fd);
	errs	+= _clocking_modes(fd);
	errs	+= _fifo_size(fd);
	errs	+= _buffer_size(fd);
	errs	+= _nrate_range(fd);
	errs	+= _fsamp_range(fd);
	errs	+= _transceivers(fd);
	errs	+= _firmware_version(fd);
	errs	+= _initialize(fd);
	errs	+= _autocalibrate(fd);

	gsc_label_level_dec();

	return(errs);
}


