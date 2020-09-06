// $URL: http://subversion:8080/svn/gsc/trunk/drivers/LINUX/ADADIO/ADADIO_Linux_3.x.x.x_GSC_DN/regs/main.h $
// $Rev: 1620 $
// $Date: 2009-04-10 11:41:41 -0500 (Fri, 10 Apr 2009) $

#ifndef __MAIN_H__
#define __MAIN_H__

#include "adadio.h"
#include "adadio_dsl.h"
#include "adadio_utils.h"
#include "gsc_utils.h"



/* #defines	***************************************************************/

#define	VERSION			"1.0"
// 1.0	Initial release.



/* data types	**************************************************************/

typedef struct
{
	const char*	name;				// NULL terminates list.
	const char*	desc;				// optional
	void		(*func)(int fd);	// NULL terminates list.
} menu_item_t;

typedef struct
{
	const char*			title;
	const menu_item_t*	list;
} menu_t;



/* prototypes	**************************************************************/

void	main_menu(int fd);
void	menu_call(int fd, const menu_t* menu);
int		menu_select(const menu_t* menu);
void	reg_mod_by_name(int fd);
void	reg_mod_by_offset(int fd);



#endif
