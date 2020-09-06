// $URL: http://subversion:8080/svn/gsc/trunk/drivers/LINUX/16AO20/16AO20_Linux_2.x.x.x_GSC_DN/utils/util_query.c $
// $Rev: 2014 $
// $Date: 2009-05-19 12:39:09 -0500 (Tue, 19 May 2009) $

#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>

#include "16ao20_dsl.h"
#include "16ao20_utils.h"
#include "gsc_utils.h"



/******************************************************************************
*
*	Function:	ao20_query
*
*	Purpose:
*
*		Implement a wrapper around the sio4_mp_config() function.
*
*	Arguments:
*
*		fd	The handle to use to access the driver.
*
*		set	Apply this setting.
*
*		get	Return the resulting setting here, if non-NULL.
*
*		errs	The number of errors seen so far.
*
*		loud	Work verbosely?
*
*	Returned:
*
*		>= 0	The number of errors encountered here.
*
******************************************************************************/

int	ao20_query(int fd, __s32 query, __s32* answer)
{
	int	errs	= 0;
	int	i;

	if (answer)
	{
		answer[0]	= query;
		i			= ioctl(fd, AO20_IOCTL_QUERY, answer);

		if (i == -1)
		{
			errs	= 1;
			printf("ERROR: ioctl() failure, errno = %d\n", errno);
		}
	}
	else
	{
		errs	= 1;
		printf("FAIL: internal error\n");
	}

	return(errs);
}



/******************************************************************************
*
*	Function:		ao20_query_channel_mask
*
*	Purpose:
*
*		Read and report the board's channel mask value.
*
*	Arguments:
*
*		fd		The handle for the board to access.
*
*		index	The index of the board to access. Ignore if < 0.
*
*		quiet	Operate quietly?
*
*		min		The minimum value is reported here.
*
*		max		The maximum value is reported here.
*
*	Returned:
*
*		>= 0	The number of errors encounterred.
*
******************************************************************************/

int ao20_query_channel_mask(int fd, int index, int quiet, __s32* get)
{
	int		errs	= 0;
	__s32	set;

	if (quiet == 0)
		gsc_label_index("Channel Mask", index);

	errs	+= ao20_query(fd, AO20_QUERY_CHANNEL_MASK, &set);

	if ((errs == 0) && (quiet == 0))
		printf("0x%lX\n", (long) set);

	if (get)
		get[0]	= set;

	return(errs);
}



/******************************************************************************
*
*	Function:		ao20_query_range
*
*	Purpose:
*
*		Read and report the board's Fgen range.
*
*	Arguments:
*
*		fd		The handle for the board to access.
*
*		index	The index of the board to access. Ignore if < 0.
*
*		quiet	Operate quietly?
*
*		min		The minimum value is reported here.
*
*		max		The maximum value is reported here.
*
*	Returned:
*
*		>= 0	The number of errors encounterred.
*
******************************************************************************/

int ao20_query_range(int fd, int index, int quiet, __s32* get)
{
	char	buf[64];
	int		errs	= 0;
	__s32	set;

	if (quiet == 0)
		gsc_label_index("Range", index);

	errs	+= ao20_query(fd, AO20_QUERY_RANGE, &set);

	if ((errs == 0) && (quiet == 0))
	{
		switch (set)
		{
			default:

				sprintf(buf, "INVALID: %ld", (long) set);
				break;

			case AO20_RANGE_2_5:

				strcpy(buf, "+-2.5v");
				break;

			case AO20_RANGE_5:

				strcpy(buf, "+-5v");
				break;

			case AO20_RANGE_10:

				strcpy(buf, "+-10v");
				break;
		}

		printf("%s  (%s)\n", errs ? "FAIL <---" : "PASS", buf);
	}

	if (get)
		get[0]	= set;

	return(errs);
}


