// $URL: http://subversion:8080/svn/gsc/trunk/drivers/LINUX/ADADIO/ADADIO_Linux_3.x.x.x_GSC_DN/sbtest/query.c $
// $Rev: 1620 $
// $Date: 2009-04-10 11:41:41 -0500 (Fri, 10 Apr 2009) $

#include <stdio.h>

#include "main.h"



/******************************************************************************
*
*	Function:	query_test
*
*	Purpose:
*
*		Perform a test of the IOCTL service ADADIO_IOCTL_QUERY. We test only the
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

	gsc_label("ADADIO_IOCTL_QUERY");
	errs	= adadio_query_quiet(fd, ADADIO_QUERY_COUNT, &count);

	if (count != (ADADIO_IOCTL_QUERY_LAST + 1))
	{
		errs	= 1;
		printf(	"FAIL <---  (expected %ld, got %ld, rebuild application)\n",
				(long) ADADIO_IOCTL_QUERY_LAST + 1,
				(long) count);
	}
	else
	{
		for (i = 0; (errs == 0) && (i <= ADADIO_IOCTL_QUERY_LAST); i++)
			errs	= adadio_query_quiet(fd, i, &data);

		if (errs == 0)
			printf("PASS\n");
	}

	return(errs);
}


