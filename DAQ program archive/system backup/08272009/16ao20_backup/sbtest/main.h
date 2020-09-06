// $URL: http://subversion:8080/svn/gsc/trunk/drivers/LINUX/16AO20/16AO20_Linux_2.x.x.x_GSC_DN/sbtest/main.h $
// $Rev: 2034 $
// $Date: 2009-05-26 14:45:21 -0500 (Tue, 26 May 2009) $

#ifndef __MAIN_H__
#define __MAIN_H__

#include "16ao20.h"
#include "16ao20_dsl.h"
#include "16ao20_utils.h"
#include "gsc_utils.h"



// #defines	*******************************************************************

#define	VERSION				"1.1"
// 1.1	Modified the Output Mode test for updated firmware.
// 1.0	Initial release.

#define	ARRAY_ELEMENTS(a)	(sizeof((a))/sizeof((a)[0]))



// data types	***************************************************************

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



// prototypes	***************************************************************


int	auto_calibrate_test(int fd);

int	buffer_clear_test(int fd);
int	buffer_mode_test(int fd);
int	buffer_over_data_test(int fd);
int	buffer_over_frame_test(int fd);
int	buffer_size_test(int fd);
int	buffer_status_test(int fd);
int	burst_ready_test(int fd);
int	burst_trg_src_test(int fd);
int	burst_trigger_test(int fd);

int	channel_sel_test(int fd);
int	clock_enable_test(int fd);
int	clock_osc_src_test(int fd);
int	clock_ready_test(int fd);
int	clock_src_test(int fd);
int	clock_sw_test(int fd);

int	data_format_test(int fd);

int	ground_sense_test(int fd);

int	initialize_test(int fd);
int	irq_enable_test(int fd);
int	irq_sel_test(int fd);
int	irq_state_test(int fd);

int	load_ready_test(int fd);
int	load_request_test(int fd);

int	nclk_test(int fd);
int	nrate_test(int fd);

int	output_mode_test(int fd);

int	query_test(int fd);

int	reg_mod_test(int fd);
int	reg_read_test(int fd);
int	reg_write_test(int fd);

int	sample_mode_test(int fd);
int	service_ioctl_reg_get_list(int fd, const service_data_t* list);
int	service_ioctl_set_get_list(int fd, const service_data_t* list);
int	service_ioctl_set_reg_list(int fd, const service_data_t* list);

int	tx_io_mode_test(int fd);
int	tx_io_over_data_test(int fd);
int	tx_io_over_frame_test(int fd);
int	tx_io_timeout_test(int fd);

int	xcvr_type_test(int fd);



#endif
