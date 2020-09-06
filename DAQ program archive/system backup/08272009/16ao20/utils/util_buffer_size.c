// $URL: http://subversion:8080/svn/gsc/trunk/drivers/LINUX/16AO20/16AO20_Linux_2.x.x.x_GSC_DN/utils/util_buffer_size.c $
// $Rev: 2014 $
// $Date: 2009-05-19 12:39:09 -0500 (Tue, 19 May 2009) $

#include <stdio.h>
#include <string.h>

#include "16ao20_dsl.h"
#include "16ao20_utils.h"
#include "gsc_utils.h"



/******************************************************************************
*
*	Function:	ao20_buffer_size
*
*	Purpose:
*
*		Set and/or get the Buffer Size setting.
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

int	ao20_buffer_size(int fd, int index, __s32 set, __s32* get)
{
	char	buf[128];
	int		errs;

	gsc_label_index("Buffer Size", index);
	errs	= ao20_dsl_ioctl(fd, AO20_IOCTL_BUFFER_SIZE, &set);

	switch (set)
	{
		default:

			sprintf(buf, "INVALID: %ld", (long) set);
			break;

		case AO20_BUFFER_SIZE_8:	strcpy(buf, "8 Samples");		break;
		case AO20_BUFFER_SIZE_16:	strcpy(buf, "16 Samples");		break;
		case AO20_BUFFER_SIZE_32:	strcpy(buf, "32 Samples");		break;
		case AO20_BUFFER_SIZE_64:	strcpy(buf, "64 Samples");		break;
		case AO20_BUFFER_SIZE_128:	strcpy(buf, "128 Samples");		break;
		case AO20_BUFFER_SIZE_256:	strcpy(buf, "256 Samples");		break;
		case AO20_BUFFER_SIZE_512:	strcpy(buf, "512 Samples");		break;
		case AO20_BUFFER_SIZE_1K:	strcpy(buf, "1K Samples");		break;
		case AO20_BUFFER_SIZE_2K:	strcpy(buf, "2K Samples");		break;
		case AO20_BUFFER_SIZE_4K:	strcpy(buf, "4K Samples");		break;
		case AO20_BUFFER_SIZE_8K:	strcpy(buf, "8K Samples");		break;
		case AO20_BUFFER_SIZE_16K:	strcpy(buf, "16K Samples");		break;
		case AO20_BUFFER_SIZE_32K:	strcpy(buf, "32K Samples");		break;
		case AO20_BUFFER_SIZE_64K:	strcpy(buf, "64K Samples");		break;
		case AO20_BUFFER_SIZE_128K:	strcpy(buf, "128K Samples");	break;
		case AO20_BUFFER_SIZE_256K:	strcpy(buf, "256K Samples");	break;
	}

	printf("%s  (%s)\n", errs ? "FAIL <---" : "PASS", buf);

	if (get)
		get[0]	= set;

	return(errs);
}


