// $URL: http://subversion:8080/svn/gsc/trunk/drivers/LINUX/ADADIO/ADADIO_Linux_3.x.x.x_GSC_DN/utils/util_irq_sel.c $
// $Rev: 1620 $
// $Date: 2009-04-10 11:41:41 -0500 (Fri, 10 Apr 2009) $

#include <stdio.h>
#include <string.h>

#include "adadio_dsl.h"
#include "adadio_utils.h"
#include "gsc_utils.h"



/******************************************************************************
*
*	Function:	adadio_irq_sel
*
*	Purpose:
*
*		Provide a visual wrapper for the ADADIO_IOCTL_IRQ_SEL service.
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

int	adadio_irq_sel(int fd, int index, __s32 set, __s32* get)
{
	char	buf[128];
	int		errs;

	gsc_label_index("IRQ Selection", index);
	errs	= adadio_dsl_ioctl(fd, ADADIO_IOCTL_IRQ_SEL, &set);

	switch (set)
	{
		default:

			sprintf(buf, "INVALID: %ld", (long) set);
			break;

		case ADADIO_IRQ_SEL_INIT_DONE:

			strcpy(buf, "Initialize Done");
			break;

		case ADADIO_IRQ_SEL_AUTO_CAL_DONE:

			strcpy(buf, "Auto-Calibration Done");
			break;

		case ADADIO_IRQ_SEL_AIN_BUF_EMPTY:

			strcpy(buf, "Input Buffer Empty");
			break;

		case ADADIO_IRQ_SEL_AIN_BUF_HALF_FULL:

			strcpy(buf, "Buffer Half Full");
			break;

		case ADADIO_IRQ_SEL_AIN_BUF_FULL:

			strcpy(buf, "Buffer Full");
			break;

		case ADADIO_IRQ_SEL_AIN_BURST_DONE:

			strcpy(buf, "Input Burst Done");
			break;

		case ADADIO_IRQ_SEL_AOUT_STROBE_DONE:

			strcpy(buf, "Output Strobe done");
			break;
	}

	printf("%s  (%s)\n", errs ? "FAIL <---" : "PASS", buf);

	if (get)
		get[0]	= set;

	return(errs);
}


