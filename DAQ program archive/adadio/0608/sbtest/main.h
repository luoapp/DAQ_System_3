// $URL: http://subversion:8080/svn/gsc/trunk/drivers/LINUX/ADADIO/ADADIO_Linux_3.x.x.x_GSC_DN/sbtest/main.h $
// $Rev: 1620 $
// $Date: 2009-04-10 11:41:41 -0500 (Fri, 10 Apr 2009) $

#ifndef __MAIN_H__
#define __MAIN_H__

#include "adadio.h"
#include "adadio_utils.h"
#include "gsc_utils.h"



/* data types	**************************************************************/

typedef enum
{
	SERVICE_END_LIST,	// Ends list of service_data_t structures.
	SERVICE_NORMAL,
	SERVICE_REG_MOD,
	SERVICE_REG_READ,
	SERVICE_REG_SHOW,
	SERVICE_REG_TEST,
	SERVICE_SLEEP,
	SERVICE_IOCTL_GET,
	SERVICE_IOCTL_SET
} service_t;

typedef struct
{
	service_t		service;
	unsigned long	cmd;	// IOCTL code
	__s32			arg;	// The IOCTL data argument.
	__u32			reg;	// The register to access. Use -1 to ignore.
	__u32			mask;	// The register bits of interest.
	__u32			value;	// The value expected for the bits of interest.
} service_data_t;



/* prototypes	**************************************************************/

int	ain_buf_clear_test(int fd);
int	ain_buf_size_test(int fd);
int	ain_buf_sts_test(int fd);
int	ain_chan_last_test(int fd);
int	ain_mode_test(int fd);
int	ain_nrate_test(int fd);
int	ain_trigger_test(int fd);
int	aout_ch_0_write_test(int fd);
int	aout_ch_1_write_test(int fd);
int	aout_ch_2_write_test(int fd);
int	aout_ch_3_write_test(int fd);
int	aout_enable_test(int fd);
int	aout_strobe_test(int fd);
int	aout_strobe_enable_test(int fd);
int	auto_calibrate_test(int fd);

int	data_format_test(int fd);
int	dio_pin_read_test(int fd);
int	dio_pin_write_test(int fd);
int	dio_port_dir_test(int fd);
int	dio_port_read_test(int fd);
int	dio_port_write_test(int fd);

int	initialize_test(int fd);
int	irq_enable_test(int fd);
int	irq_sel_test(int fd);
int	irq_status_test(int fd);

int	loopback_channel_test(int fd);

int	query_test(int fd);

int	reg_mod_test(int fd);
int	reg_read_test(int fd);
int	reg_write_test(int fd);
int rx_io_mode_test(int fd);
int rx_io_timeout_test(int fd);

int	service_ioctl_reg_get_list(int fd, const service_data_t* list);
int	service_ioctl_set_get_list(int fd, const service_data_t* list);
int	service_ioctl_set_reg_list(int fd, const service_data_t* list);



#endif
