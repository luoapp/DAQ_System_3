// $URL: http://subversion:8080/svn/gsc/trunk/drivers/LINUX/16AO20/16AO20_Linux_2.x.x.x_GSC_DN/utils/util_irq_sel.c $
// $Rev: 2014 $
// $Date: 2009-05-19 12:39:09 -0500 (Tue, 19 May 2009) $

#include <stdio.h>
#include <string.h>

#include "16ao20_dsl.h"
#include "16ao20_utils.h"
#include "gsc_utils.h"



/******************************************************************************
*
*	Function:	ao20_irq_sel
*
*	Purpose:
*
*		Set and/or get the IRQ Select setting.
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

int	ao20_irq_sel(int fd, int index, __s32 set, __s32* get)
{
	char	buf[128];
	int		errs;

	gsc_label_index("IRQ Select", index);
	errs	= ao20_dsl_ioctl(fd, AO20_IOCTL_IRQ_SEL, &set);

	switch (set)
	{
		default:

			sprintf(buf, "INVALID: %ld", (long) set);
			break;

		case AO20_IRQ_SEL_INIT_DONE:

			strcpy(buf, "Initialize Done");
			break;

		case AO20_IRQ_SEL_AUTOCAL_DONE:

			strcpy(buf, "Auto-Calibrate Done");
			break;

		case AO20_IRQ_SEL_BUF_EMPTY:

			strcpy(buf, "Buffer Empty");
			break;

		case AO20_IRQ_SEL_BUF_1Q_FULL:

			strcpy(buf, "Buffer < 1/4 Full");
			break;

		case AO20_IRQ_SEL_BUF_3Q_FULL:

			strcpy(buf, "Buffer > 3/4 Full");
			break;

		case AO20_IRQ_SEL_BURST_TRIG_READY:

			strcpy(buf, "Burst Trigger Ready");
			break;

		case AO20_IRQ_SEL_LOAD_READY:

			strcpy(buf, "Load Ready");
			break;

		case AO20_IRQ_SEL_LOAD_READY_END:

			strcpy(buf, "Load Ready End");
			break;
	}

	printf("%s  (%s)\n", errs ? "FAIL <---" : "PASS", buf);

	if (get)
		get[0]	= set;

	return(errs);
}


