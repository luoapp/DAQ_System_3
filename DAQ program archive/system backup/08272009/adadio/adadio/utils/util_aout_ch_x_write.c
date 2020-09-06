// $URL: http://subversion:8080/svn/gsc/trunk/drivers/LINUX/ADADIO/ADADIO_Linux_3.x.x.x_GSC_DN/utils/util_aout_ch_x_write.c $
// $Rev: 1620 $
// $Date: 2009-04-10 11:41:41 -0500 (Fri, 10 Apr 2009) $

#include <stdio.h>
#include <string.h>

#include "adadio_dsl.h"
#include "adadio_utils.h"
#include "gsc_utils.h"



/******************************************************************************
*
*	Function:	adadio_aout_ch_0_write
*
*	Purpose:
*
*		Provide a visual wrapper for the ADADIO_IOCTL_AOUT_CH_0_WRITE service.
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

int adadio_aout_ch_0_write(int fd, int index, __s32 set, __s32* get)
{
	int	errs;

	gsc_label_index("Channel 0 Output", index);
	errs	= adadio_dsl_ioctl(fd, ADADIO_IOCTL_AOUT_CH_0_WRITE, &set);
	printf("%s  (0x%04lX)\n", errs ? "FAIL <---" : "PASS", (long) set);

	if (get)
		get[0]	= set;

	return(errs);
}



/******************************************************************************
*
*	Function:	adadio_aout_ch_1_write
*
*	Purpose:
*
*		Provide a visual wrapper for the ADADIO_IOCTL_AOUT_CH_1_WRITE service.
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

int adadio_aout_ch_1_write(int fd, int index, __s32 set, __s32* get)
{
	int	errs;

	gsc_label_index("Channel 1 Output", index);
	errs	= adadio_dsl_ioctl(fd, ADADIO_IOCTL_AOUT_CH_1_WRITE, &set);
	printf("%s  (0x%04lX)\n", errs ? "FAIL <---" : "PASS", (long) set);

	if (get)
		get[0]	= set;

	return(errs);
}



/******************************************************************************
*
*	Function:	adadio_aout_ch_2_write
*
*	Purpose:
*
*		Provide a visual wrapper for the ADADIO_IOCTL_AOUT_CH_2_WRITE service.
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

int adadio_aout_ch_2_write(int fd, int index, __s32 set, __s32* get)
{
	int	errs;

	gsc_label_index("Channel 2 Output", index);
	errs	= adadio_dsl_ioctl(fd, ADADIO_IOCTL_AOUT_CH_2_WRITE, &set);
	printf("%s  (0x%04lX)\n", errs ? "FAIL <---" : "PASS", (long) set);

	if (get)
		get[0]	= set;

	return(errs);
}



/******************************************************************************
*
*	Function:	adadio_aout_ch_3_write
*
*	Purpose:
*
*		Provide a visual wrapper for the ADADIO_IOCTL_AOUT_CH_3_WRITE service.
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

int adadio_aout_ch_3_write(int fd, int index, __s32 set, __s32* get)
{
	int	errs;

	gsc_label_index("Channel 3 Output", index);
	errs	= adadio_dsl_ioctl(fd, ADADIO_IOCTL_AOUT_CH_3_WRITE, &set);
	printf("%s  (0x%04lX)\n", errs ? "FAIL <---" : "PASS", (long) set);

	if (get)
		get[0]	= set;

	return(errs);
}


