// $URL: http://subversion:8080/svn/gsc/trunk/drivers/LINUX/ADADIO/ADADIO_Linux_3.x.x.x_GSC_DN/utils/util_config.c $
// $Rev: 1620 $
// $Date: 2009-04-10 11:41:41 -0500 (Fri, 10 Apr 2009) $

#include <stdio.h>
#include <string.h>

#include "adadio_dsl.h"
#include "adadio_utils.h"
#include "gsc_utils.h"



/******************************************************************************
*
*	Function:	adadio_config
*
*	Purpose:
*
*		Configure the basic services.
*
*	Arguments:
*
*		fd		The handle to use to access the driver.
*
*		index	The index of the board to access. Ignore if < 0.
*
*	Returned:
*
*		>= 0	The number of errors encountered here.
*
******************************************************************************/

int	adadio_config(int fd, int index)
{
	int	errs	= 0;

	errs	+= adadio_rx_io_mode		(fd, index, GSC_IO_MODE_PIO,				NULL);
	errs	+= adadio_rx_io_timeout		(fd, index, ADADIO_IO_TIMEOUT_DEFAULT,		NULL);

	errs	+= adadio_initialize		(fd, index);
	errs	+= adadio_auto_calibrate	(fd, index);

	errs	+= adadio_ain_nrate			(fd, index, 400,							NULL);
	errs	+= adadio_ain_mode			(fd, index, ADADIO_AIN_MODE_DIFF_CONT,		NULL);
	errs	+= adadio_data_format		(fd, index, ADADIO_DATA_FORMAT_OFF_BIN,		NULL);
	errs	+= adadio_ain_chan_last		(fd, index, 7,								NULL);
	errs	+= adadio_ain_buf_size		(fd, index, ADADIO_AIN_BUF_SIZE_32768,		NULL);

	errs	+= adadio_aout_enable		(fd, index, ADADIO_AOUT_ENABLE_NO,			NULL);
	errs	+= adadio_aout_ch_0_write	(fd, index, 0xFC,							NULL);
	errs	+= adadio_aout_ch_1_write	(fd, index, 0xFC,							NULL);
	errs	+= adadio_aout_ch_2_write	(fd, index, 0xFC,							NULL);
	errs	+= adadio_aout_ch_3_write	(fd, index, 0xFC,							NULL);
	errs	+= adadio_aout_strobe_enable(fd, index, ADADIO_AOUT_STROBE_ENABLE_NO,	NULL);

	errs	+= adadio_irq_sel			(fd, index, ADADIO_IRQ_SEL_INIT_DONE,		NULL);
	errs	+= adadio_irq_status		(fd, index, ADADIO_IRQ_STATUS_CLEAR,		NULL);
	errs	+= adadio_irq_enable		(fd, index, ADADIO_IRQ_ENABLE_NO,			NULL);
	errs	+= adadio_loopback_channel	(fd, index, 0,								NULL);

	errs	+= adadio_dio_pin_write		(fd, index, 0,								NULL);
	errs	+= adadio_dio_port_dir		(fd, index, ADADIO_DIO_PORT_DIR_INPUT,		NULL);
	errs	+= adadio_dio_port_write	(fd, index, 0,								NULL);

	errs	+= adadio_ain_buf_clear		(fd, index);
	return(errs);
}


