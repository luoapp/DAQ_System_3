// $URL: http://subversion:8080/svn/gsc/trunk/drivers/LINUX/16AO20/16AO20_Linux_2.x.x.x_GSC_DN/sbtest/query.c $
// $Rev: 2014 $
// $Date: 2009-05-19 12:39:09 -0500 (Tue, 19 May 2009) $

#include <stdio.h>

#include "main.h"



/******************************************************************************
*
*	Function:	query_test
*
*	Purpose:
*
*		Perform a test of the IOCTL service AO20_IOCTL_QUERY. We test only the
*		overall service, not the values returned.
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

int query_test(int fd)
{
	__s32	data;
	__s32	count;
	int		errs;
	int		i;

	gsc_label("AO20_IOCTL_QUERY");
	errs	= ao20_query(fd, AO20_QUERY_COUNT, &count);

	if (count != AO20_QUERY_LAST)
	{
		errs	= 1;
		printf(	"FAIL <---  (expected %ld, got %ld, rebuild application)\n",
				(long) AO20_QUERY_LAST,
				(long) count);
	}
	else
	{
		for (i = 0; (errs == 0) && (i < AO20_QUERY_LAST); i++)
			errs	= ao20_query(fd, i, &data);

		if (errs == 0)
			printf("PASS\n");
	}

	return(errs);
}


