// $URL: http://subversion:8080/svn/gsc/trunk/drivers/LINUX/ADADIO/ADADIO_Linux_3.x.x.x_GSC_DN/id/id.c $
// $Rev: 1620 $
// $Date: 2009-04-10 11:41:41 -0500 (Fri, 10 Apr 2009) $

#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "main.h"
#include "gsc_pci9080.h"
//#include "adadio_utils.h"



//*****************************************************************************
static int _yes_no_support(int fd, const char* title, __s32 id)
{
	int		errs;
	__s32	supported;

	gsc_label(title);
	errs	= adadio_query_quiet(fd, id, &supported);

	if (errs)
	{
	}
	else if (supported < 0)
	{
		errs	= 1;
		printf("FAIL <---  (query response error: %ld)\n", (long) supported);
	}
	else
	{
		printf("%s\n", supported ? "Yes" : "No");
	}

	return(errs);
}



//*****************************************************************************
static int _input_modes(int fd)
{
	gsc_label("Input Modes");
	printf("Differential, Single Ended, Zero Test, +Vref Test\n");
	return(0);
}



//*****************************************************************************
static int _voltage_ranges(int fd)
{
	gsc_label("Voltage Ranges");
	printf("+-10V, +-5V, +-2.5V (Factory Configured)\n");
	return(0);
}



//*****************************************************************************
static int _channel_qty(int fd)
{
	gsc_label("A/D Channels");
	printf("12 Input (simultaneous), 4 Output, 16-bit resolution\n");
	return(0);
}



//*****************************************************************************
static int _master_clock(int fd)
{
	int		errs	= 0;
	__s32	freq;

	gsc_label("Master Clock");

	errs	+= adadio_query_quiet(fd, ADADIO_QUERY_MASTER_CLOCK, &freq);

	if (errs)
	{
	}
	else if (freq <= 0)
	{
		errs	= 1;
		printf(	"FAIL <---  (%d. frequency response error: %ld)\n",
				__LINE__,
				(long) freq);
	}
	else
	{
		gsc_label_long_comma(freq);
		printf(" Hz\n");
	}

	return(errs);
}



//*****************************************************************************
static int _clocking_sources(int fd)
{
	gsc_label("Clocking Sources");
	printf("Internal (Continuous), Software (Burst)\n");
	return(0);
}



//*****************************************************************************
static int _nrate_range(int fd)
{
	int		errs	= 0;
	__s32	mask;
	__s32	max;
	__s32	min;

	gsc_label("Nrate Range");

	errs	+= adadio_query_quiet(fd, ADADIO_QUERY_NRATE_MASK, &mask);
	errs	+= adadio_query_quiet(fd, ADADIO_QUERY_NRATE_MAX, &max);
	errs	+= adadio_query_quiet(fd, ADADIO_QUERY_NRATE_MIN, &min);

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
	int		errs	= 0;
	__s32	max;			// Sample Rate Maximum
	__s32	min;			// Sample Rate Minimum

	gsc_label("Sample Rates");

	errs	+= adadio_query_quiet(fd, ADADIO_QUERY_FSAMP_MAX, &max);
	errs	+= adadio_query_quiet(fd, ADADIO_QUERY_FSAMP_MIN, &min);

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
		printf(" S/S/C\n");
	}

	return(errs);
}



//*****************************************************************************
static int _fifo_size(int fd)
{
	int		errs	= 0;
	__s32	size;			// FIFO Size in samples

	gsc_label("FIFO Size");

	errs	+= adadio_query_quiet(fd, ADADIO_QUERY_FIFO_SIZE, &size);

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
		printf(" Samples Deep  (%ldK)\n", (long) size / 1024);
	}

	return(errs);
}



//*****************************************************************************
static int _initialize(int fd)
{
	int		errs	= 0;
	__s32	ms;

	gsc_label("Initialize Period");

	errs	+= adadio_query_quiet(fd, ADADIO_QUERY_INIT_MS, &ms);

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

	errs	+= adadio_query_quiet(fd, ADADIO_QUERY_AUTO_CAL_MS, &ms);

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
static int digital_io(int fd)
{
	gsc_label("Digital I/O");
	printf("8-bit Bidirectional, 1-bit In, 1-bit Out\n");
	return(0);
}



/******************************************************************************
*
*	Function:	_id_board_brr
*
*	Purpose:
*
*		Identify the board using the Board Configuration Register.
*
*	Arguments:
*
*		fd		The handle used to access the device.
*
*	Returned:
*
*		>= 0	The number of errors encountered here.
*
******************************************************************************/

static int _id_board_brr(int fd)
{
	__u32	brr;			// Board Revision Register
	int		errs	= 0;
	__u32	field;
	int		width	= 19;

	gsc_label("Board Config. Register");
	errs	+= gsc_dev_reg_read(fd, ADADIO_GSC_BRR, &brr);
	printf("0x%08lX  \n", (long) brr);

	gsc_label_level_inc();

	// D31-D17
	gsc_label("D31-D17");
	field	= (brr & 0xFFFE0000) >> 16;
	printf("0x%04lX----  ", (long) field);
	printf("Reserved\n");

	// D16-D0
	gsc_label("D16-D0");
	field	= (brr & 0x0001FFFF) >> 0;
	printf("0x---%05lX  ", (long) field);
	printf("%-*s", width, "Firmware Revision:");
	printf("%05lX\n", (long) field);

	gsc_label_level_dec();
	return(errs);
}



//*****************************************************************************
static int _register_map_reg(int fd, const gsc_reg_def_t* def)
{
	char	buf[32];
	int		errs	= 0;
	long	offset;
	__u32	val;

	offset	= GSC_REG_OFFSET(def->reg);
	sprintf(buf, "Offset 0x%02lX", offset);
	gsc_label(buf);

	for (;;)
	{
		errs	+= gsc_dev_reg_read(fd, def->reg, &val);

		if (errs)
			break;

		printf("0x%08lX  %-*s  ", (long) val, 9, def->name);
		printf("%s\n", def->desc);
		break;
	}

	return(errs);
}



//*****************************************************************************
static int _register_map(int fd)
{
	const gsc_reg_def_t*	def;
	int						errs	= 0;
	int						i;

	gsc_label("Register Map");
	printf("\n");

	gsc_label_level_inc();

	for (i = 0;; i++)
	{
		def	= adadio_reg_get_def_index(i);

		if (def)
			errs	+= _register_map_reg(fd, def);
		else
			break;
	}

	gsc_label_level_dec();
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

	errs	+= _input_modes(fd);
	errs	+= _voltage_ranges(fd);
	errs	+= _channel_qty(fd);
	errs	+= _master_clock(fd);
	errs	+= _clocking_sources(fd);
	errs	+= _nrate_range(fd);
	errs	+= _fsamp_range(fd);
	errs	+= _fifo_size(fd);
	errs	+= _initialize(fd);
	errs	+= _autocalibrate(fd);
	errs	+= digital_io(fd);

	errs	+= _yes_no_support(fd, "DMDMA", ADADIO_QUERY_DMDMA);

	gsc_label_level_dec();

	errs	+= _id_board_brr(fd);

	errs	+= _register_map(fd);

	return(errs);
}


