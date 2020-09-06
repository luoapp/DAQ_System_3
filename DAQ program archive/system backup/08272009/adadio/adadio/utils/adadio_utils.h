// $URL: http://subversion:8080/svn/gsc/trunk/drivers/LINUX/ADADIO/ADADIO_Linux_3.x.x.x_GSC_DN/utils/adadio_utils.h $
// $Rev: 1620 $
// $Date: 2009-04-10 11:41:41 -0500 (Fri, 10 Apr 2009) $

#ifndef __ADADIO_UTILS_H__
#define __ADADIO_UTILS_H__

#include "adadio.h"
#include "gsc_utils.h"



// #defines	*******************************************************************

#define	ARRAY_ELEMENTS(a)	(sizeof((a))/sizeof((a)[0]))



// prototypes	***************************************************************

int	adadio_ain_buf_clear(int fd, int index);
int	adadio_ain_buf_size(int fd, int index, __s32 set, __s32* get);
int adadio_ain_buf_sts(int fd, int index, __s32* get);
int adadio_ain_chan_last(int fd, int index, __s32 set, __s32* get);
int	adadio_ain_mode(int fd, int index, __s32 set, __s32* get);
int adadio_ain_nrate(int fd, int index, __s32 set, __s32* get);
int	adadio_ain_trigger(int fd, int index);
int	adadio_aout_enable(int fd, int index, __s32 set, __s32* get);
int	adadio_aout_strobe(int fd, int index);
int	adadio_aout_strobe_enable(int fd, int index, __s32 set, __s32* get);
int adadio_aout_ch_0_write(int fd, int index, __s32 set, __s32* get);
int adadio_aout_ch_1_write(int fd, int index, __s32 set, __s32* get);
int adadio_aout_ch_2_write(int fd, int index, __s32 set, __s32* get);
int adadio_aout_ch_3_write(int fd, int index, __s32 set, __s32* get);
int	adadio_auto_calibrate(int fd, int index);

int	adadio_config(int fd, int index);

int	adadio_data_format(int fd, int index, __s32 set, __s32* get);
int	adadio_dio_pin_read(int fd, int index, __s32* get);
int	adadio_dio_pin_write(int fd, int index, __s32 set, __s32* get);
int	adadio_dio_port_dir(int fd, int index, __s32 set, __s32* get);
int	adadio_dio_port_read(int fd, int index, __s32* get);
int	adadio_dio_port_write(int fd, int index, __s32 set, __s32* get);

int adadio_fsamp_report(int fd, int index, int chan, int quiet, __s32* sps);
int adadio_fsamp_report_all(int fd, int index, int safe);

int adadio_id_board(int fd, int index, const char* desc);
int	adadio_initialize(int fd, int index);
int	adadio_initialize_quiet(int fd);
int	adadio_irq_enable(int fd, int index, __s32 set, __s32* get);
int	adadio_irq_sel(int fd, int index, __s32 set, __s32* get);
int adadio_irq_status(int fd, int index, __s32 set, __s32* get);

int adadio_loopback_channel(int fd, int index, __s32 set, __s32* get);

int	adadio_query_model(int fd, int index, int quiet, __s32* model);
int	adadio_query_quiet(int fd, __s32 query, __s32* answer);

int adadio_reg_list(int fd, int detail);
int	adadio_rx_io_mode(int fd, int index, __s32 set, __s32* get);
int	adadio_rx_io_timeout(int fd, int index, __s32 set, __s32* get);

int gsc_dev_reg_read(int fd, __u32 reg, __u32* value);
int gsc_dev_reg_write(int fd, __u32 reg, __u32 value);

const gsc_reg_def_t*	adadio_reg_get_def_index(int index);
const char*				adadio_reg_get_desc(unsigned long reg);
const char*				adadio_reg_get_name(unsigned long reg);



#endif
