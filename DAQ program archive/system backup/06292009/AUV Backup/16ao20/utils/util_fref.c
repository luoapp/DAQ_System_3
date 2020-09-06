// $URL: http://subversion:8080/svn/gsc/trunk/drivers/LINUX/16AO20/16AO20_Linux_2.x.x.x_GSC_DN/utils/util_fref.c $
// $Rev: 2014 $
// $Date: 2009-05-19 12:39:09 -0500 (Tue, 19 May 2009) $

#include <stdio.h>
#include <string.h>

#include "16ao20_dsl.h"
#include "16ao20_utils.h"
#include "gsc_utils.h"



//*****************************************************************************
static int _fref_compute(int fd, int index, int quiet, __s32* get)
{
	int		errs	= 0;
	__s32	nclk;
	__s32	nclk_max;
	__s32	nclk_min;
	__s32	osc_src;
	__s32	set;

	if (quiet == 0)
		gsc_label_index("Fref", index);

	errs	+= ao20_query(fd, AO20_QUERY_NCLK_MAX, &nclk_max);
	errs	+= ao20_query(fd, AO20_QUERY_NCLK_MIN, &nclk_min);
	errs	+= ao20_clock_osc_src_quiet(fd, -1, &osc_src);
	errs	+= ao20_nclk_quiet(fd, -1, &nclk);

	switch (osc_src)
	{
		default:

			errs++;
			set	= 0;

			if (quiet == 0)
			{
				printf(	"FAIL <---  (Oscillator Source error: %ld)\n",
						(long) osc_src);
			}

			break;

		case AO20_CLOCK_OSC_SRC_PRI:

			set	= 30000000L;

			if (quiet == 0)
			{
				gsc_label_long_comma(set);
				printf("  (Source = Primary)\n");
			}

			break;

		case AO20_CLOCK_OSC_SRC_ALT:

			set	= (__s32) (16000000.0 * (511.0 + nclk) / 511);

			if (quiet == 0)
			{
				gsc_label_long_comma(set);
				printf("  (Source = Alternate, Nclk = %ld)\n", (long) nclk);
			}

			break;
	}

	if (get)
		get[0]	= set;

	return(errs);
}



/******************************************************************************
*
*	Function:	ao20_fref_compute_quiet
*
*	Purpose:
*
*		Configure the board, then capture data.
*
*	Arguments:
*
*		fd		The handle for the board to access.
*
*		get		The computed Fref value is put here.
*
*	Returned:
*
*		>= 0	The number of errors encounterred.
*
******************************************************************************/

int ao20_fref_compute_quiet(int fd, __s32* get)
{
	int	errs;

	errs	= _fref_compute(fd, -1, 1, get);
	return(errs);
}



/******************************************************************************
*
*	Function:	ao20_fref_compute
*
*	Purpose:
*
*		Configure the board, then capture data.
*
*	Arguments:
*
*		fd		The handle for the board to access.
*
*		index	The index of the board being accessed or -1 to ignore.
*
*		get		The computed Fref value is put here.
*
*	Returned:
*
*		>= 0	The number of errors encounterred.
*
******************************************************************************/

int ao20_fref_compute(int fd, int index, __s32* get)
{
	int	errs;

	errs	= _fref_compute(fd, index, 0, get);
	return(errs);
}


