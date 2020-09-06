// $URL: http://subversion:8080/svn/gsc/trunk/drivers/LINUX/ADADIO/ADADIO_Linux_3.x.x.x_GSC_DN/utils/util_fsamp.c $
// $Rev: 1620 $
// $Date: 2009-04-10 11:41:41 -0500 (Fri, 10 Apr 2009) $

#include <limits.h>
#include <stdio.h>
#include <string.h>

#include "adadio_dsl.h"
#include "adadio_utils.h"
#include "gsc_utils.h"



// #defines	*******************************************************************

#define	F_REF		20000000L	// 20MHz



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
*		first	This is the index of the first channel.
*
*		last	This is the index of the last channel.
*
*	Returned:
*
*		>= 0	The number of errors encounterred.
*
******************************************************************************/

static int _channels(int fd, __s32* first, __s32* last)
{
	int	errs	= 0;

	first[0]	= 0;
	last[0]		= -1;

	errs	+= adadio_dsl_ioctl(fd, ADADIO_IOCTL_AIN_CHAN_LAST, last);
	return(errs);
}



/******************************************************************************
*
*	Function:	adadio_fsamp_report
*
*	Purpose:
*
*		Determine and report the sample rate for the specified channel.
*
*	Arguments:
*
*		fd		The handle to use to access the driver.
*
*		index	The index of the board to access. Ignore if < 0.
*
*		chan	The index of the channel of interest.
*
*		quiet	Operate quietly?
*
*		sps		Store the sample rate here, if non-NULL.
*
*	Returned:
*
*		>= 0	The number of errors encountered here.
*
******************************************************************************/

int adadio_fsamp_report(int fd, int index, int chan, int quiet, __s32* sps)
{
	__s32	aim			= -1;
	char	buf[1024];
	int		errs		= 0;
	__s32	first;
	__s32	fsamp		= 0;
	__s32	last;
	__s32	nrate		= -1;

	if (quiet == 0)
	{
		sprintf(buf, "Channel %d", chan);
		gsc_label_index(buf, index);
	}

	for (;;)
	{
		if ((chan < 0) || (chan > 7))
		{
			errs++;
			printf("FAIL <---  (invalid channel index: %d)\n", chan);
			break;
		}

		errs	+= _channels(fd, &first, &last);

		if (errs)
			break;

		if ((chan < first) || (chan > last))
		{
			sps[0]	= 0;

			if (quiet == 0)
				printf("SKIPPED  (disabled)\n");

			break;
		}

		errs	+= adadio_dsl_ioctl(fd, ADADIO_IOCTL_AIN_MODE, &aim);
		errs	+= adadio_dsl_ioctl(fd, ADADIO_IOCTL_AIN_NRATE, &nrate);

		if (errs)
			break;

		if (nrate < 1)
		{
			errs++;
			sprintf(buf, "%d. INTERNAL ERROR: Nrate %ld", __LINE__, (long) nrate);
			break;
		}

		switch (aim)
		{
			default:

				errs++;
				sprintf(buf, "%d. INTERNAL ERROR: %ld", __LINE__, (long) aim);
				break;

			case ADADIO_AIN_MODE_SE_CONT:

				fsamp	= F_REF / nrate;
				strcpy(buf, "Single Ended, Continuous");
				break;

			case ADADIO_AIN_MODE_SE_BURST:

				fsamp	= 0;
				strcpy(buf, "Single Ended, Burst");
				break;

			case ADADIO_AIN_MODE_DIFF_CONT:

				fsamp	= F_REF / nrate;
				strcpy(buf, "Differential, Continuous");
				break;

			case ADADIO_AIN_MODE_DIFF_BURST:

				fsamp	= 0;
				strcpy(buf, "Differential, Burst");
				break;

			case ADADIO_AIN_MODE_LB_TEST:

				fsamp	= 0;
				strcpy(buf, "Loopback");
				break;

			case ADADIO_AIN_MODE_VREF_TEST:

				fsamp	= 0;
				strcpy(buf, "Vref Test");
				break;

			case ADADIO_AIN_MODE_ZERO_TEST:

				fsamp	= 0;
				strcpy(buf, "Zero Test");
				break;
		}

		if ((errs == 0) && (quiet == 0))
		{
			gsc_label_long_comma((long) fsamp);
			printf(" S/S  (%s)\n", buf);
		}

		break;
	}

	if (sps)
		sps[0]	= fsamp;

	return(errs);
}



/******************************************************************************
*
*	Function:	adadio_fsamp_report_all
*
*	Purpose:
*
*		Determine and report the sample rate for all channels.
*
*	Arguments:
*
*		fd		The handle to use to access the driver.
*
*		index	The index of the board to access. Ignore if < 0.
*
*		safe	Apply safe limits to the process?
*
*	Returned:
*
*		>= 0	The number of errors encountered here.
*
******************************************************************************/

int adadio_fsamp_report_all(int fd, int index, int safe)
{
	int		chan;
	int		errs	= 0;
	__s32	first;
	__s32	last;
	__s32	sps;
	__s32	total	= 0;

	gsc_label_index("Sample Rates", index);
	errs	+= _channels(fd, &first, &last);

	if (errs == 0)
	{
		printf("\n");
		gsc_label_level_inc();

		for (chan = first; chan <= last; chan++)
		{
			errs	+= adadio_fsamp_report(fd, -1, chan, 0, &sps);
			total	+= sps;
		}

		gsc_label("Overall Rate");
		gsc_label_long_comma(total);
		printf(" S/S\n");

		gsc_label_level_dec();
	}

	return(errs);
}


