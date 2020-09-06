// $URL: http://subversion:8080/svn/gsc/trunk/drivers/LINUX/16AO20/16AO20_Linux_2.x.x.x_GSC_DN/utils/util_config.c $
// $Rev: 2014 $
// $Date: 2009-05-19 12:39:09 -0500 (Tue, 19 May 2009) $

#include <stdio.h>
#include <string.h>

#include "16ao20_dsl.h"
#include "16ao20_utils.h"
#include "gsc_utils.h"



/******************************************************************************
*
*	Function:	ao20_config_board
*
*	Purpose:
*
*		Configure the given board using common defaults.
*
*	Arguments:
*
*		fd		The handle to use to access the driver.
*
*		index	The index of the board to access. Ignore if < 0.
*
*		fsamp	This is the desired Fsamp rate, of -1 to use the default.
*
*	Returned:
*
*		>= 0	The number of errors encountered here.
*
******************************************************************************/

int	ao20_config_board(int fd, int index, __s32 fsamp)
{
	int		errs	= 0;
	__s32	mask	= 0;
	__s32	nclk;
	__s32	nrate;
	__s32	osc_src;

	errs	+= ao20_tx_io_mode			(fd, index, GSC_IO_MODE_PIO, NULL);
	errs	+= ao20_tx_io_over_data		(fd, index, AO20_TX_IO_OVER_DATA_CHECK, NULL);
	errs	+= ao20_tx_io_over_frame	(fd, index, AO20_TX_IO_OVER_FRAME_CHECK, NULL);
	errs	+= ao20_tx_io_timeout		(fd, index, 30, NULL);
	errs	+= ao20_initialize			(fd, index);
	errs	+= ao20_buffer_mode			(fd, index, AO20_BUFFER_MODE_OPEN, NULL);
	errs	+= ao20_buffer_size			(fd, index, AO20_BUFFER_SIZE_256K, NULL);
	errs	+= ao20_output_mode			(fd, index, AO20_OUTPUT_MODE_SIM, NULL);
	errs	+= ao20_query_range			(fd, index, 0, NULL);
	errs	+= ao20_sample_mode			(fd, index, AO20_SAMPLE_MODE_CONT, NULL);
	errs	+= ao20_burst_trig_src		(fd, index, AO20_BURST_TRIG_SRC_SW, NULL);
	errs	+= ao20_query_channel_mask	(fd, index, 1, &mask);
	errs	+= ao20_channel_sel			(fd, index, mask, 0);
	errs	+= ao20_data_format			(fd, index, AO20_DATA_FORMAT_OFF_BIN, NULL);
	errs	+= ao20_ground_sense		(fd, index, AO20_GROUND_SENSE_DISABLE, NULL);

	errs	+= ao20_fsamp_compute		(fd, fsamp, &osc_src, &nclk, &nrate);
	errs	+= ao20_clock_osc_src		(fd, index, osc_src, NULL);
	errs	+= ao20_clock_src			(fd, index, AO20_CLOCK_SRC_INT, NULL);
	errs	+= ao20_nclk				(fd, index, nclk, NULL);
	errs	+= ao20_nrate				(fd, index, nrate, NULL);

	errs	+= ao20_xcvr_type			(fd, index, AO20_XCVR_TYPE_LVDS, NULL);
	errs	+= ao20_clock_enable		(fd, index, AO20_CLOCK_ENABLE_YES, NULL);
	errs	+= ao20_auto_calibrate		(fd, index);
	errs	+= ao20_buffer_clear		(fd, index);
	errs	+= ao20_buffer_over_data	(fd, index, AO20_BUFFER_OVER_DATA_CLR, NULL);
	errs	+= ao20_buffer_over_frame	(fd, index, AO20_BUFFER_OVER_FRAME_CLR, NULL);
	errs	+= ao20_buffer_status		(fd, index, NULL);

	return(errs);
}


