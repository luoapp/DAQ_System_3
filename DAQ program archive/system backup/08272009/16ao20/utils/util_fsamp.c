// $URL: http://subversion:8080/svn/gsc/trunk/drivers/LINUX/16AO20/16AO20_Linux_2.x.x.x_GSC_DN/utils/util_fsamp.c $
// $Rev: 2014 $
// $Date: 2009-05-19 12:39:09 -0500 (Tue, 19 May 2009) $

#include <limits.h>
#include <stdio.h>
#include <string.h>

#include "16ao20_dsl.h"
#include "16ao20_utils.h"
#include "gsc_utils.h"



// #defines	*******************************************************************

#define	ABS(v)		(((v) < 0) ? (-(v)) : (v))



/******************************************************************************
*
*	Function:	ao20_fsamp_compute
*
*	Purpose:
*
*		Determine the best configuration for the specified sample rate.
*
*	Arguments:
*
*		fd		The handle to use to access the driver.
*
*		fsamp	The desired sample rate.
*
*		osc_src	The oscillator source is put here. MUST NOT BE NULL!
*
*		nclk	The Nclk value is put here. MUST NOT BE NULL!
*
*		nrate	The Nrate value is put here. MUST NOT BE NULL!
*
*	Returned:
*
*		>= 0	The number of errors encountered here.
*
******************************************************************************/

int ao20_fsamp_compute(int fd, __s32 fsamp, __s32* osc_src, __s32* nclk, __s32* nrate)
{
	#define	REF_ALT		16000000.0
	#define	REF_PRI		30000000.0

	int		errs		= 0;
	float	delta;
	float	delta_best	= REF_PRI;
	float	fref;
	__s32	fsamp_max;	// Queried value.
	__s32	fsamp_min;	// Queried value.
	float	rate;
	__s32	nc;
	__s32	nclk_max;	// Queried value.
	__s32	nclk_min;	// Queried value.
	__s32	nr;
	__s32	nr_max;
	__s32	nr_min;
	__s32	nrate_max;	// Queried value.
	__s32	nrate_min;	// Queried value.

	gsc_label("Fsamp Computation");
	gsc_label_long_comma(fsamp);
	printf(" S/S  ");

	errs	+= ao20_query(fd, AO20_QUERY_FSAMP_MAX, &fsamp_max);
	errs	+= ao20_query(fd, AO20_QUERY_FSAMP_MIN, &fsamp_min);
	errs	+= ao20_query(fd, AO20_QUERY_NCLK_MAX, &nclk_max);
	errs	+= ao20_query(fd, AO20_QUERY_NCLK_MIN, &nclk_min);
	errs	+= ao20_query(fd, AO20_QUERY_NRATE_MAX, &nrate_max);
	errs	+= ao20_query(fd, AO20_QUERY_NRATE_MIN, &nrate_min);

	fsamp	= (fsamp < fsamp_min) ? fsamp_min
			: (fsamp > fsamp_max) ? fsamp_max : fsamp;

	// Apply defaults.
	osc_src[0]	= AO20_CLOCK_OSC_SRC_PRI;
	nclk[0]		= 0x1FF;
	nrate[0]	= 0xFFFF;

	// First try the alternate reference source.

	for (nc = nclk_min; nc <= nclk_max; nc++)
	{
		fref	= REF_ALT * (1.0 + (((float) nc) / 511));
		nr		= (__s32) (fref / fsamp);
		nr_min	= nr - 1;
		nr_max	= nr + 1;
		nr_min	= (nr_min < nrate_min) ? nrate_min : nr_min;
		nr_max	= (nr_max > nrate_max) ? nrate_max : nr_max;

		for (nr = nr_min; nr <= nr_max; nr++)
		{
			rate	= fref / nr;
			delta	= rate - fsamp;
			delta	= ABS(delta);

			if (delta < delta_best)
			{
				delta_best	= delta;
				osc_src[0]	= AO20_CLOCK_OSC_SRC_ALT;
				nclk[0]		= nc;
				nrate[0]	= nr;
			}
		}

	}

	// Now try the primary reference source.
	nr		= (long) (REF_PRI / fsamp);
	nr_min	= nr - 1;
	nr_max	= nr + 1;
	nr_min	= (nr_min < nrate_min) ? nrate_min : nr_min;
	nr_max	= (nr_max > nrate_max) ? nrate_max : nr_max;

	for (nr = nr_min; nr <= nr_max; nr++)
	{
		rate	= REF_PRI / nr;
		delta	= rate - fsamp;
		delta	= ABS(delta);

		if (delta < delta_best)
		{
			delta_best	= delta;
			osc_src[0]	= AO20_CLOCK_OSC_SRC_PRI;
			nrate[0]	= nr;
		}
	}

	// Report the results.

	if (errs)
	{
		printf("FAIL <---\n");
	}
	else
	{
		if (osc_src[0] == AO20_CLOCK_OSC_SRC_PRI)
		{
			printf("(Pri Src ");
			gsc_label_long_comma((long) REF_PRI);

			printf(", Nrate ");
			gsc_label_long_comma((long) nrate[0]);

			fsamp	= (long) ((REF_PRI / nrate[0]) + 0.5);
			printf(", Fsamp ");
			gsc_label_long_comma((long) fsamp);

			printf(", Delta %.3f)\n", delta_best);
		}
		else
		{
			printf("(Alt Src ");
			gsc_label_long_comma((long) REF_ALT);

			printf(", Nclk ");
			gsc_label_long_comma((long) nclk[0]);

			printf(", Nrate ");
			gsc_label_long_comma((long) nrate[0]);

			fref	= REF_ALT * (1.0 + (((float) nclk[0]) / 511));
			fsamp	= (long) ((fref / nrate[0]) + 0.5);
			printf(", Fsamp ");
			gsc_label_long_comma((long) fsamp);

			printf(", Delta %.3f)\n", delta_best);
		}
	}

	return(errs);
}



/******************************************************************************
*
*	Function:	ao20_fsamp_get
*
*	Purpose:
*
*		Determine the sample rate.
*
*	Arguments:
*
*		fd		The handle to use to access the driver.
*
*		title	Show a title?
*
*		get		Store the sample rate here, if non-NULL.
*
*	Returned:
*
*		>= 0	The number of errors encountered here.
*
******************************************************************************/

int ao20_fsamp_get(int fd, int title, __s32* get)
{
	__s32	clk_src;
	int		errs		= 0;
	__s32	fref;
	__s32	nclk;
	__s32	nrate;
	__s32	osc_src;
	__s32	set			= 0;

	if (title)
		gsc_label("Sample Rate");

	errs	+= ao20_clock_osc_src_quiet(fd, -1, &osc_src);
	errs	+= ao20_fref_compute_quiet(fd, &fref);
	errs	+= ao20_clock_src_quiet(fd, -1, &clk_src);
	errs	+= ao20_nclk_quiet(fd, -1, &nclk);
	errs	+= ao20_nrate_quiet(fd, -1, &nrate);

	if (clk_src == AO20_CLOCK_SRC_EXT_SW)
	{
		set	= 0;
		printf("Unknown  (Source = External/Software)\n");
	}
	else if (osc_src == AO20_CLOCK_OSC_SRC_PRI)
	{
		set	= fref / nrate;
		gsc_label_long_comma(set);
		printf(" S/S  (Source = Internal, Pri Ref, Nrate = ");
		gsc_label_long_comma(nrate);
		printf(")\n");
	}
	else
	{
		set	= fref / nrate;
		gsc_label_long_comma(set);
		printf(" S/S  (Source = Internal, Alt Ref, Nclk = ");
		gsc_label_long_comma(nclk);
		printf(", Nrate = ");
		gsc_label_long_comma(nrate);
		printf(")\n");
	}

	if (get)
		get[0]	= set;

	return(errs);
}



/******************************************************************************
*
*	Function:	ao20_fsamp_report
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
*		get		Store the sample rate here, if non-NULL.
*
*	Returned:
*
*		>= 0	The number of errors encountered here.
*
******************************************************************************/

int ao20_fsamp_report(int fd, int index, int chan, __s32* get)
{
	__s32	bit			= 0x1L << chan;
	char	buf[64];
	int		errs		= 0;
	__s32	select;
	__s32	set			= 0;

	sprintf(buf, "Channel %d", chan);
	gsc_label_index(buf, index);
	errs	+= ao20_channel_sel_quiet(fd, -1, &select);

	printf("\nchan select = %x \n", select);
	if (select & bit)
	{
		// The channel is enabled.
		errs	+= ao20_fsamp_get(fd, 0, &set);
	}
	else
	{
		// The channel is disabled.
		set	= 0;
		printf("0 S/S  (Channel Disabled)\n");
	}

	if (get)
		get[0]	= set;

	return(errs);
}



/******************************************************************************
*
*	Function:	ao20_fsamp_report_all
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
*	Returned:
*
*		>= 0	The number of errors encountered here.
*
******************************************************************************/

int ao20_fsamp_report_all(int fd, int index)
{
	__s32	chans;
	int		chan;
	int		errs	= 0;
	__s32	sps;
	__s32	total	= 0;

	gsc_label_index("Sample Rates", index);
	errs	+= ao20_query(fd, AO20_QUERY_CHANNEL_QTY, &chans);

	if (errs == 0)
	{
		printf("\n");
		gsc_label_level_inc();

		for (chan = 0; chan < chans; chan++)
		{
			sps		= 0;
			errs	+= ao20_fsamp_report(fd, -1, chan, &sps);
			total	+= sps;
		}

		gsc_label("Overall Rate");
		gsc_label_long_comma(total);
		printf(" S/S\n");

		gsc_label_level_dec();
	}

	return(errs);
}


