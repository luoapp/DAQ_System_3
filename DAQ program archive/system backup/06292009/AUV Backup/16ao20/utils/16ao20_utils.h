// $URL: http://subversion:8080/svn/gsc/trunk/drivers/LINUX/16AO20/16AO20_Linux_2.x.x.x_GSC_DN/utils/16ao20_utils.h $
// $Rev: 2014 $
// $Date: 2009-05-19 12:39:09 -0500 (Tue, 19 May 2009) $

#ifndef __16AO20_UTILS_H__
#define __16AO20_UTILS_H__

#include "16ao20.h"



// #defines	*******************************************************************

#define	ARRAY_ELEMENTS(a)	(sizeof((a))/sizeof((a)[0]))



// prototypes	***************************************************************

int			ao20_auto_calibrate(int fd, int index);

int			ao20_buffer_clear(int fd, int index);
int			ao20_buffer_mode(int fd, int index, __s32 set, __s32* get);
int			ao20_buffer_over_data(int fd, int index, __s32 set, __s32* get);
int			ao20_buffer_over_frame(int fd, int index, __s32 set, __s32* get);
int			ao20_buffer_size(int fd, int index, __s32 set, __s32* get);
int			ao20_buffer_status(int fd, int index, __s32* get);
int			ao20_burst_ready(int fd, int index, __s32* get);
int			ao20_burst_trig_src(int fd, int index, __s32 set, __s32* get);
int			ao20_burst_trigger(int fd, int index);

int			ao20_channel_sel(int fd, int index, __s32 set, __s32* get);
int			ao20_channel_sel_quiet(int fd, __s32 set, __s32* get);
int			ao20_clock_enable(int fd, int index, __s32 set, __s32* get);
int			ao20_clock_osc_src(int fd, int index, __s32 set, __s32* get);
int			ao20_clock_osc_src_quiet(int fd, __s32 set, __s32* get);
int			ao20_clock_ready(int fd, int index, __s32* get);
int			ao20_clock_src(int fd, int index, __s32 set, __s32* get);
int			ao20_clock_src_quiet(int fd, __s32 set, __s32* get);
int			ao20_clock_sw(int fd, int index);
int			ao20_config_board(int fd, int index, __s32 fsamp);

int			ao20_data_format(int fd, int index, __s32 set, __s32* get);
int			ao20_data_format_quiet(int fd, __s32 set, __s32* get);

int			ao20_fref_compute(int fd, int index, __s32* get);
int			ao20_fref_compute_quiet(int fd, __s32* get);
int			ao20_fsamp_compute(int fd, __s32 fsamp, __s32* osc_src, __s32* nclk, __s32* nrate);
int			ao20_fsamp_get(int fd, int title, __s32* get);
int			ao20_fsamp_report(int fd, int index, int chan, __s32* get);
int			ao20_fsamp_report_all(int fd, int index);

int			ao20_ground_sense(int fd, int index, __s32 set, __s32* get);

int			ao20_id_board(int fd, int index, const char* desc);
int			ao20_initialize(int fd, int index);
int			ao20_initialize_quiet(int fd);
int			ao20_irq_enable(int fd, int index, __s32 set, __s32* get);
int			ao20_irq_sel(int fd, int index, __s32 set, __s32* get);
int			ao20_irq_state(int fd, int index, __s32 set, __s32* get);

int			ao20_load_ready(int fd, int index, __s32* get);
int			ao20_load_request(int fd, int index);

int			ao20_nclk(int fd, int index, __s32 set, __s32* get);
int			ao20_nclk_quiet(int fd, __s32 set, __s32* get);
int			ao20_nrate(int fd, int index, __s32 set, __s32* get);
int			ao20_nrate_quiet(int fd, __s32 set, __s32* get);

int			ao20_output_mode(int fd, int index, __s32 set, __s32* get);

int			ao20_query(int fd, __s32 query, __s32* answer);
int			ao20_query_channel_mask(int fd, int index, int quiet, __s32* get);
int			ao20_query_range(int fd, int index, int quiet, __s32* get);

int			ao20_reg_list(int fd, int detail);
const char*	ao20_reg_name(int fd, __u32 reg);

int			ao20_sample_mode(int fd, int index, __s32 set, __s32* get);

int			ao20_tx_io_mode(int fd, int index, __s32 set, __s32* get);
int			ao20_tx_io_over_data(int fd, int index, __s32 set, __s32* get);
int			ao20_tx_io_over_frame(int fd, int index, __s32 set, __s32* get);
int			ao20_tx_io_timeout(int fd, int index, __s32 set, __s32* get);

int			ao20_xcvr_type(int fd, int index, __s32 set, __s32* get);



#endif
