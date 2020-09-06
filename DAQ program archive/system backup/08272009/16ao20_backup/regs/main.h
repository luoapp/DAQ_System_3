// $URL: http://subversion:8080/svn/gsc/trunk/drivers/LINUX/16AO20/16AO20_Linux_2.x.x.x_GSC_DN/regs/main.h $
// $Rev: 2014 $
// $Date: 2009-05-19 12:39:09 -0500 (Tue, 19 May 2009) $

#ifndef __MAIN_H__
#define __MAIN_H__

#include "16ao20.h"
#include "16ao20_dsl.h"
#include "16ao20_utils.h"
#include "gsc_utils.h"



/* #defines	***************************************************************/

#define	VERSION			"1.0"
// 1.0	initial release.



/* data types	**************************************************************/

typedef struct
{
	const char*	name;				// NULL terminates list.
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
