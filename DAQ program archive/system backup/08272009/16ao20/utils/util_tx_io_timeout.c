// $URL: http://subversion:8080/svn/gsc/trunk/drivers/LINUX/16AO20/16AO20_Linux_2.x.x.x_GSC_DN/utils/util_tx_io_timeout.c $
// $Rev: 2014 $
// $Date: 2009-05-19 12:39:09 -0500 (Tue, 19 May 2009) $

#include <stdio.h>
#include <string.h>

#include "16ao20_dsl.h"
#include "16ao20_utils.h"
#include "gsc_utils.h"



/******************************************************************************
*
*	Function:	ao20_tx_io_timeout
*
*	Purpose:
*
*		Set and/or get the Tx I/O Timeout.
*
*	Arguments:
*
*		fd		The handle to use to access the driver.
*
*		index	The index of the board to access. Ignore if < 0.
*
*		set		The setting to apply.
*
*		get		The current setting is recorded here, if not NULL.
*
*	Returned:
*
*		>= 0	The number of errors encountered here.
*
******************************************************************************/

int	ao20_tx_io_timeout(int fd, int index, __s32 set, __s32* get)
{
	int	errs;

	gsc_label_index("Tx Timeout", index);
	errs	= ao20_dsl_ioctl(fd, AO20_IOCTL_TX_IO_TIMEOUT, &set);
	printf("%s  (", errs ? "FAIL <---" : "PASS");
	gsc_label_long_comma(set);
	printf(" seconds)\n");

	if (get)
		get[0]	= set;

	return(errs);
}


