// $URL: http://subversion:8080/svn/gsc/trunk/drivers/gsc_common/linux/utils/gsc_utils.h $
// $Rev: 1592 $
// $Date: 2009-03-29 12:48:28 -0500 (Sun, 29 Mar 2009) $

#ifndef __GSC_UTILS_H__
#define __GSC_UTILS_H__

#include <asm/types.h>



// data types	***************************************************************

typedef struct		// For listing register values.
{
	const char*	name;
	int			reg;
	int			err;
	__u32		value;
	int			ask_support;	// Call below function for this.
	int			(*decode)(int fd, int supported, __u32 value, int width);
	const char*	desc;	// Description
} gsc_reg_def_t;



// prototypes	***************************************************************

int			gsc_count_boards(const char* base_name);

void		gsc_dev_close(unsigned int index, int fd);
int			gsc_dev_open(unsigned int index, const char* base_name);

int			gsc_id_driver(int fd, const char* base_name);
void		gsc_id_host(void);

void		gsc_kbd_close(void);
int			gsc_kbd_hit(void);
void		gsc_kbd_open(void);
int			gsc_kbd_read(void);

void		gsc_label(const char* label);
void		gsc_label_init(int width);
int			gsc_label_indent(int delta);
void		gsc_label_index(const char* label, int index);
void		gsc_label_level_dec(void);
void		gsc_label_level_inc(void);
void		gsc_label_long_comma(long value);

int			gsc_reg_list(int fd, gsc_reg_def_t* list, int detail);
const char*	gsc_reg_plx9056_get_desc(unsigned long reg);
const char*	gsc_reg_plx9056_get_name(unsigned long reg);
int			gsc_reg_plx9056_list_pci(int fd);
int			gsc_reg_plx9056_list_plx(int fd);
int			gsc_reg_plx9080_list_pci(int fd);
int			gsc_reg_plx9080_list_plx(int fd);

void		gsc_reg_field_show(
				int				label_width,
				int				name_width,
				__u32			value,
				int				hi_bit,
				int				low_bit,
				int				eol,
				const char**	list,
				const char*		name);

int			gsc_select_1_board(int qty, int* index);
int			gsc_select_2_boards(int qty, int* index_1, int* index_2);

// These are provided by the device specific code.
int			gsc_dev_reg_mod(int fd, __u32 reg, __u32 value, __u32 mask);
int			gsc_dev_reg_read(int fd, __u32 reg, __u32* value);
int			gsc_dev_reg_write(int fd, __u32 reg, __u32 value);



#endif
