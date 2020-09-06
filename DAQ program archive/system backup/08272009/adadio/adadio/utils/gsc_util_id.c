// $URL: http://subversion:8080/svn/gsc/trunk/drivers/gsc_common/linux/utils/gsc_util_id.c $
// $Rev: 2618 $
// $Date: 2009-06-23 17:10:49 -0500 (Tue, 23 Jun 2009) $

#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <asm/types.h>
#include <sys/stat.h>
#include <sys/utsname.h>

#include "gsc_utils.h"



// #defines	*******************************************************************

#define	ISEOL(_c)	((((_c) == 0)		|| \
					  ((_c) == '\r')	|| \
					  ((_c) == '\n')) ? 1 : 0)



/******************************************************************************
*
*	Function:	_get_total_mb
*
*	Purpose:
*
*		Report the amount of total RAM in megabytes.
*
*	Arguments:
*
*		None.
*
*	Returned:
*
*		None.
*
******************************************************************************/

static long _get_total_mb(void)
{
	char	buf[1024];
	int		end;
	char	factor	= 0;
	FILE*	file;
	int		i;
	long	total	= 0;

	file	= fopen("/proc/meminfo", "r");

	if (file)
	{
		for (;;)
		{
			end	= feof(file);

			if (end)
				break;

			fgets(buf, sizeof(buf), file);
			i	= sscanf(buf, "MemTotal: %ld %c", &total, &factor);

			if (i == 2)
				break;
		}

		fclose(file);
	}

	if (factor == 0)
	{
		total	= (total + 1023) / 1024;
		factor	= 'k';
	}

	if ((factor == 'k') || (factor == 'K'))
	{
		total	= (total + 1023) / 1024;
		factor	= 'm';
	}

	if ((factor == 't') || (factor == 'T'))
	{
		total	*= 1024;
		factor	= 'm';
	}
	if ((factor == 'g') || (factor == 'G'))
	{
		total	*= 1024;
		factor	= 'm';
	}

	return(total);
}



/******************************************************************************
*
*	Function:	_skipws
*
*	Purpose:
*
*		Skip the leading white space in the given string.
*
*	Arguments:
*
*		psz		The string to process.
*
*	Returned:
*
*		The resulting string, if non-NULL.
*
******************************************************************************/

static char* _skipws(char* psz)
{
	for (; (psz) && (isspace(psz[0]));)
		psz++;

	return(psz);
}



/******************************************************************************
*
*	Function:	_id_host_memory_total
*
*	Purpose:
*
*		Identify total host memory.
*
*	Arguments:
*
*		None.
*
*	Returned:
*
*		None.
*
******************************************************************************/

static void _id_host_memory_total(void)
{
	long	total;

	gsc_label("Total Memory");
	total	= _get_total_mb();

	if (total == 0)
		printf("Unknown\n");
	else
		printf("%ld MB\n", total);
}



/******************************************************************************
*
*	Function:	_id_host_memory_physical
*
*	Purpose:
*
*		Identify total physical memory. We could get the exact amount and
*		nature of physical memory, but that is an indepth process. See the
*		source code for the dmidecode utility for details. Here I'll just
*		guesstimate physical memory by rounding total memory up a bit.
*
*	Arguments:
*
*		None.
*
*	Returned:
*
*		None.
*
******************************************************************************/

static void _id_host_memory_physical(void)
{
	long	total;

	gsc_label("Physical Memory");
	total	= _get_total_mb();

	if (total == 0)
	{
		printf("Unknown\n");
	}
	else
	{
		total	= (((total + 63) / 64) * 64);
		printf("%ld MB  (\?\?\?)\n", total);
	}
}



/******************************************************************************
*
*	Function:	_id_host_os
*
*	Purpose:
*
*		Identify the host os.
*
*	Arguments:
*
*		None.
*
*	Returned:
*
*		None.
*
******************************************************************************/

static void _id_host_os(void)
{
	struct utsname	uts;

	memset(&uts, 0, sizeof(uts));
	uname(&uts);

	gsc_label("Operating System");
	printf("%s\n", uts.sysname);
	gsc_label("Kernel");
	printf("%s\n", uts.release);
}



/******************************************************************************
*
*	Function:	_id_host_processor
*
*	Purpose:
*
*		Identify the host processor.
*
*	Arguments:
*
*		None.
*
*	Returned:
*
*		None.
*
******************************************************************************/

static void _id_host_processor(void)
{
	char			buf[1024];
	int				end;
	FILE*			file;
	int				i;
	int				index;
	char*			psz;
	char			tmp[1024];
	struct utsname	uts;

	memset(&uts, 0, sizeof(uts));
	uname(&uts);

	gsc_label("Processor");
	printf("%s\n", uts.machine);
	gsc_label_level_inc();

	file	= fopen("/proc/cpuinfo", "r");

	if (file)
	{
		for (;;)
		{
			end	= feof(file);

			if (end)
				break;

			fgets(buf, sizeof(buf), file);
			i	= sscanf(buf, "processor : %d", &index);

			if (i == 1)
			{
				gsc_label_level_dec();
				sprintf(buf, "Processor #%d", index);
				gsc_label(buf);
				printf("\n");
				gsc_label_level_inc();
				continue;
			}

			i	= sscanf(buf, "model name : %s", tmp);

			if (i == 1)
			{
				gsc_label("CPU Model");
				psz	= strchr(buf, ':') + 2;
				psz	= _skipws(psz);
				printf("%s", psz);
				continue;
			}

			i	= sscanf(buf, "cpu MHz : %s", tmp);

			if (i == 1)
			{
				gsc_label("CPU Speed");
				printf("%s MHz\n", tmp);
				continue;
			}
		}

		fclose(file);
	}

	gsc_label_level_dec();
}



/******************************************************************************
*
*	Function:	gsc_id_driver
*
*	Purpose:
*
*		Identify the driver.
*
*	Arguments:
*
*		fd			The handle to use to access the driver.
*
*		base_name	The base name of the device.
*
*	Returned:
*
*		>= 0		The number of errors encountered here.
*
******************************************************************************/

int gsc_id_driver(int fd, const char* base_name)
{
	char	buf[1024];
	int		errs	= 0;
	char*	ptr;

	for (;;)	// A convenience loop.
	{
		gsc_label("Driver");
		sprintf(buf, "/proc/%s", base_name);
		fd	= open(buf, S_IRUSR);

		if (fd == -1)
		{
			printf("UNKNOWN\n");
			break;
		}

		memset(buf, 0, sizeof(buf));
		read(fd, buf, sizeof(buf));
		buf[sizeof(buf) - 1]	= 0;
		close(fd);

		// Version
		printf("Version ");
		ptr	= strstr(buf, "version");

		if (ptr == NULL)
		{
			printf("UNKNOWN\n");
		}
		else
		{
			for (ptr += 9; !ISEOL(ptr[0]); ptr++)
				printf("%c", ptr[0]);
		}

		printf(", Built ");
		ptr	= strstr(buf, "built");

		if (ptr == NULL)
		{
			printf("UNKNOWN\n");
		}
		else
		{
			for (ptr += 7; !ISEOL(ptr[0]); ptr++)
				printf("%c", ptr[0]);
		}

		printf("\n");
		break;
	}

	return(errs);
}



/******************************************************************************
*
*	Function:	gsc_id_host
*
*	Purpose:
*
*		Identify the host os and machine.
*
*	Arguments:
*
*		None.
*
*	Returned:
*
*		None.
*
******************************************************************************/

void gsc_id_host(void)
{
	gsc_label("Host");
	printf("\n");
	gsc_label_level_inc();

	_id_host_os();
	_id_host_processor();
	_id_host_memory_total();
	_id_host_memory_physical();

	gsc_label_level_dec();
}


