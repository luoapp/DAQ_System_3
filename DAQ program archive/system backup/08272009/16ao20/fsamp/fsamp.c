// $URL: http://subversion:8080/svn/gsc/trunk/drivers/LINUX/16AO20/16AO20_Linux_2.x.x.x_GSC_DN/fsamp/fsamp.c $
// $Rev: 2014 $
// $Date: 2009-05-19 12:39:09 -0500 (Tue, 19 May 2009) $

#include <stdio.h>
#include <string.h>

#include "main.h"



/******************************************************************************
*
*	Function:	fsamp_compute
*
*	Purpose:
*
*		Configure the board, then capture data.
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

int fsamp_compute(int fd, __s32 fsamp)
{
	int		errs	= 0;
	__s32	nclk;
	__s32	nrate;
	__s32	osc_src;

	errs	+= ao20_fsamp_compute(fd, fsamp, &osc_src, &nclk, &nrate);
	return(errs);
}


