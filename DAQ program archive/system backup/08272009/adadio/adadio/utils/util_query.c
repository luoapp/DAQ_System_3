// $URL: http://subversion:8080/svn/gsc/trunk/drivers/LINUX/ADADIO/ADADIO_Linux_3.x.x.x_GSC_DN/utils/util_query.c $
// $Rev: 1620 $
// $Date: 2009-04-10 11:41:41 -0500 (Fri, 10 Apr 2009) $

#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>

#include "adadio_dsl.h"
#include "adadio_utils.h"
#include "gsc_utils.h"



/******************************************************************************
*
*	Function:	adadio_query_quiet
*
*	Purpose:
*
*		Provide a quiet wrapper for the ADADIO_IOCTL_QUERY service.
*
*	Arguments:
*
*		fd		The handle to use to access the driver.
*
*		set		Apply this setting.
*
*		get		Return the resulting setting here, if non-NULL.
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

int	adadio_query_quiet(int fd, __s32 query, __s32* answer)
{
	int	errs;
	int	i;

	if (answer)
	{
		answer[0]	= query;
		i			= ioctl(fd, ADADIO_IOCTL_QUERY, answer);

		if (i == -1)
		{
			errs	= 1;
			printf("ERROR: ioctl() failure, errno = %d\n", errno);
		}
		else
		{
			errs	= 0;
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
*	Function:		adadio_query_model
*
*	Purpose:
*
*		Provide a visual wrapper for the ADADIO_IOCTL_QUERY service.
*
*	Arguments:
*
*		fd		The handle for the board to access.
*
*		index	The index of the board to access. Ignore if < 0.
*
*		quiet	Operate quietly?
*
*		model	The model is reported here.
*
*	Returned:
*
*		>= 0	The number of errors encounterred.
*
******************************************************************************/

int	adadio_query_model(int fd, int index, int quiet, __s32* model)
{
	int			errs;
	const char*	name;

	if (quiet == 0)
		gsc_label_index("Model", index);

	errs	= adadio_query_quiet(fd, ADADIO_QUERY_DEVICE_TYPE, model);

	if (errs == 0)
	{
		switch (model[0])
		{
			default:

				errs	= 1;
				name	= NULL;
				printf(	"FAIL <---  (unrecognized model: %ld)\n",
						(long) model[0]);
				break;

			case GSC_DEV_TYPE_ADADIO:	name	= "ADADIO";		break;
		}

		if ((errs == 0) && (quiet == 0) && (name))
			printf("%s\n", name);
	}

	return(errs);
}


