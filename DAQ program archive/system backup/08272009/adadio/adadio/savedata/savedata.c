// $URL: http://subversion:8080/svn/gsc/trunk/drivers/LINUX/ADADIO/ADADIO_Linux_3.x.x.x_GSC_DN/savedata/savedata.c $
// $Rev: 1620 $
// $Date: 2009-04-10 11:41:41 -0500 (Fri, 10 Apr 2009) $

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "main.h"



// #defines	*******************************************************************

#define	_1M		(1024L * 1024L)



// variables	***************************************************************

static	__u32	_buffer[_1M];



/******************************************************************************
*
*	Function:	_channels
*
*	Purpose:
*
*		Check to see how many channels the board has.
*
*	Arguments:
*
*		fd		The handle for the board to access.
*
*		chan	Report the number of channels here.
*
*	Returned:
*
*		>= 0	The number of errors encounterred.
*
******************************************************************************/

static int _channels(int fd, __s32* chans)
{
	char	buf[64];
	int		errs	= 0;
	__s32	last	= 4;

	gsc_label("Input Channels");

	errs	+= adadio_dsl_ioctl(fd, ADADIO_IOCTL_AIN_CHAN_LAST,	&last	);

	if (errs == 0)
	{
		chans[0]	= last + 1;

		if (last == 0)
			sprintf(buf, "# %ld", (long) last);
		else
			sprintf(buf, "#s 0-%ld", (long) last);

		printf(	"%ld Channel%s  (%s)\n",
				(long) chans[0],
				(chans[0] == 1) ? "" : "s",
				buf);
	}

	return(errs);
}



/******************************************************************************
*
*	Function:	_read_data
*
*	Purpose:
*
*		Read data into the buffer.
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

static int _read_data(int fd)
{
	int		errs;
	long	get		= sizeof(_buffer) / 4;
	int		got;

	gsc_label("Reading");
	got	= adadio_dsl_read(fd, _buffer, get);

	if (got < 0)
	{
		errs	= 1;
	}
	else if (got != get)
	{
		errs	= 1;
		printf(	"FAIL <---  (got %ld samples, requested %ld)\n",
				(long) got,
				(long) get);
	}
	else
	{
		errs	= 0;
		printf(	"PASS  (%ld samples)\n",
				(long) get);
	}

	return(errs);
}



/******************************************************************************
*
*	Function:	_save_data
*
*	Purpose:
*
*		Save the read data to a text file.
*
*	Arguments:
*
*		fd		The handle for the board to access.
*
*		chans	The number of channels.
*
*		errs	have there been any errors so far?
*
*	Returned:
*
*		>= 0	The number of errors encounterred.
*
******************************************************************************/

static int _save_data(int fd, int chans, int errs)
{
	FILE*		file;
	int			i;
	long		l;
	const char*	name	= "data.txt";
	long		samples	= sizeof(_buffer) / 4;

	gsc_label("Saving");

	for (;;)
	{
		if (errs)
		{
			printf("SKIPPED  (errors)\n");
			errs	= 0;
			break;
		}

		file	= fopen(name, "w+b");

		if (file == NULL)
		{
			printf("FAIL <---  (unable to create %s)\n", name);
			errs	= 1;
			break;
		}

		for (l = 0; l < samples; l++)
		{
			if ((l) && ((l % chans) == 0))
			{
				i	= fprintf(file, "\r\n");

				if (i != 2)
				{
					printf("FAIL <---  (fprintf() failure to %s)\n", name);;
					errs	= 1;
					break;
				}
			}

			i	= fprintf(file, "  %04lX", (unsigned long) (0xFFFFUL & _buffer[l]));

			if (i != 6)
			{
				printf("FAIL <---  (fprintf() failure to %s)\n", name);
				errs	= 1;
				break;
			}
		}

		fclose(file);

		if (errs == 0)
			printf("PASS  (%s)\n", name);

		break;
	}

	return(errs);
}



/******************************************************************************
*
*	Function:	save_data
*
*	Purpose:
*
*		Configure the board, then capture data to a file.
*
*	Arguments:
*
*		fd		The handle for the board to access.
*
*		io_mode	Use the I/O mode for data transfer.
*
*	Returned:
*
*		>= 0	The number of errors encounterred.
*
******************************************************************************/

int save_data(int fd, __s32 io_mode)
{
	__s32	chans	= 32;
	int		errs	= 0;

	gsc_label("Capture & Save");
	printf("\n");
	gsc_label_level_inc();

	errs	+= adadio_config(fd, -1);
	errs	+= adadio_rx_io_mode(fd, -1, io_mode, NULL);
	errs	+= adadio_ain_nrate(fd, -1, 100, NULL);
	errs	+= _channels(fd, &chans);
	errs	+= _read_data(fd);
	errs	+= _save_data(fd, chans, errs);

	gsc_label_level_dec();
	return(errs);
}



