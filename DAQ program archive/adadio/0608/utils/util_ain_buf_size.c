// $URL: http://subversion:8080/svn/gsc/trunk/drivers/LINUX/ADADIO/ADADIO_Linux_3.x.x.x_GSC_DN/utils/util_ain_buf_size.c $
// $Rev: 1620 $
// $Date: 2009-04-10 11:41:41 -0500 (Fri, 10 Apr 2009) $

#include <stdio.h>
#include <string.h>

#include "adadio_dsl.h"
#include "adadio_utils.h"
#include "gsc_utils.h"



/******************************************************************************
*
*	Function:	adadio_ain_buf_size
*
*	Purpose:
*
*		Provide a visual wrapper for the ADADIO_IOCTL_AIN_BUF_SIZE service.
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

int	adadio_ain_buf_size(int fd, int index, __s32 set, __s32* get)
{
	char	buf[128];
	int		errs;

	gsc_label_index("Input Buffer Size", index);
	errs	= adadio_dsl_ioctl(fd, ADADIO_IOCTL_AIN_BUF_SIZE, &set);

	switch (set)
	{
		default:

			sprintf(buf, "INVALID: %ld", (long) set);
			break;

		case ADADIO_AIN_BUF_SIZE_1:

			strcpy(buf, "1");
			break;

		case ADADIO_AIN_BUF_SIZE_2:

			strcpy(buf, "2");
			break;

		case ADADIO_AIN_BUF_SIZE_4:

			strcpy(buf, "4");
			break;

		case ADADIO_AIN_BUF_SIZE_8:

			strcpy(buf, "8");
			break;

		case ADADIO_AIN_BUF_SIZE_16:

			strcpy(buf, "16");
			break;

		case ADADIO_AIN_BUF_SIZE_32:

			strcpy(buf, "32");
			break;

		case ADADIO_AIN_BUF_SIZE_64:

			strcpy(buf, "64");
			break;

		case ADADIO_AIN_BUF_SIZE_128:

			strcpy(buf, "128");
			break;

		case ADADIO_AIN_BUF_SIZE_256:

			strcpy(buf, "256");
			break;

		case ADADIO_AIN_BUF_SIZE_512:

			strcpy(buf, "512");
			break;

		case ADADIO_AIN_BUF_SIZE_1024:

			strcpy(buf, "1,024");
			break;

		case ADADIO_AIN_BUF_SIZE_2048:

			strcpy(buf, "2,048");
			break;

		case ADADIO_AIN_BUF_SIZE_4096:

			strcpy(buf, "4,096");
			break;

		case ADADIO_AIN_BUF_SIZE_8192:

			strcpy(buf, "8,192");
			break;

		case ADADIO_AIN_BUF_SIZE_16384:

			strcpy(buf, "16,384");
			break;

		case ADADIO_AIN_BUF_SIZE_32768:

			strcpy(buf, "32,768");
			break;
	}

	printf("%s  (%s samples deep)\n", errs ? "FAIL <---" : "PASS", buf);

	if (get)
		get[0]	= set;

	return(errs);
}


