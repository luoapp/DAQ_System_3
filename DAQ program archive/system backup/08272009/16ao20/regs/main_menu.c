// $URL: http://subversion:8080/svn/gsc/trunk/drivers/LINUX/16AO20/16AO20_Linux_2.x.x.x_GSC_DN/regs/main_menu.c $
// $Rev: 2014 $
// $Date: 2009-05-19 12:39:09 -0500 (Tue, 19 May 2009) $

#include <stdio.h>

#include "main.h"



/*****************************************************************************
*
*	Function:	_dump_everything
*
*	Purpose:
*
*		Dump all available data to the screen.
*
*	Arguments:
*
*		fd		The handle for the board to access.
*
*	Returned:
*
*		None.
*
*****************************************************************************/

static void _dump_everything(int fd)
{
	gsc_id_host();
	printf("\n");
	gsc_id_driver(fd, AO20_BASE_NAME);
	printf("\n");
	ao20_id_board(fd, -1, NULL);
	printf("\n");
	gsc_reg_plx9080_list_pci(fd);
	printf("\n");
	gsc_reg_plx9080_list_plx(fd);
	printf("\n");
	ao20_reg_list(fd, 1);
}



/*****************************************************************************
*
*	Function:	_dump_gsc
*
*	Purpose:
*
*		Dump the GSC registers.
*
*	Arguments:
*
*		fd		The handle for the board to access.
*
*	Returned:
*
*		None.
*
*****************************************************************************/

static void _dump_gsc(int fd)
{
	ao20_reg_list(fd, 0);
}



/*****************************************************************************
*
*	Function:	_dump_gsc_detail
*
*	Purpose:
*
*		Dump the GSC register details.
*
*	Arguments:
*
*		fd		The handle for the board to access.
*
*	Returned:
*
*		None.
*
*****************************************************************************/

static void _dump_gsc_detail(int fd)
{
	ao20_reg_list(fd, 1);
}



/*****************************************************************************
*
*	Function:	_dump_pci
*
*	Purpose:
*
*		Dump the PCI registers.
*
*	Arguments:
*
*		fd		The handle for the board to access.
*
*	Returned:
*
*		None.
*
*****************************************************************************/

static void _dump_pci(int fd)
{
	gsc_reg_plx9080_list_pci(fd);
}



/*****************************************************************************
*
*	Function:	_dump_plx
*
*	Purpose:
*
*		Dump the PLX registers.
*
*	Arguments:
*
*		fd		The handle for the board to access.
*
*	Returned:
*
*		None.
*
*****************************************************************************/

static void _dump_plx(int fd)
{
	gsc_reg_plx9080_list_plx(fd);
}



/*****************************************************************************
*
*	Function:	_id_board
*
*	Purpose:
*
*		Identify the device being accessed.
*
*	Arguments:
*
*		fd		The handle for the board to access.
*
*	Returned:
*
*		None.
*
*****************************************************************************/

static void _id_board(int fd)
{
	ao20_id_board(fd, -1, NULL);
}



/*****************************************************************************
*
*	Function:	_id_driver
*
*	Purpose:
*
*		Identify the device driver.
*
*	Arguments:
*
*		fd		The handle for the board to access.
*
*	Returned:
*
*		None.
*
*****************************************************************************/

static void _id_driver(int fd)
{
	gsc_id_driver(fd, AO20_BASE_NAME);
}



/*****************************************************************************
*
*	Function:	_id_host
*
*	Purpose:
*
*		Identify the host OS.
*
*	Arguments:
*
*		fd		The handle for the board to access.
*
*	Returned:
*
*		None.
*
*****************************************************************************/

static void _id_host(int fd)
{
	gsc_id_host();
}



/*****************************************************************************
*
*	Function:	main_menu
*
*	Purpose:
*
*		Present the main menu.
*
*	Arguments:
*
*		fd		The handle for the board to access.
*
*	Returned:
*
*		None.
*
*****************************************************************************/

void main_menu(int fd)
{
	static const menu_item_t	list[]	=
	{
		// name								func
		{ "Dump Everything",				_dump_everything	},
		{ "Host OS Identification",			_id_host			},
		{ "Driver Identification",			_id_driver			},
		{ "Board Identification",			_id_board			},
		{ "PCI Register Dump",				_dump_pci			},
		{ "PLX Register Dump",				_dump_plx			},
		{ "GSC Register Dump",				_dump_gsc			},
		{ "GSC Register Detail Dump",		_dump_gsc_detail	},
		{ "Edit GSC Register By Name",		reg_mod_by_name		},
		{ "Edit GSC Register By Offset",	reg_mod_by_offset	},
		{ NULL,								NULL				}
	};

	static const menu_t	menu	=
	{
		/* title	*/	"Main Menu",
		/* list		*/	list
	};

	printf("\n\n");
	printf("Register Access Application (version %s)\n", VERSION);
	menu_call(fd, &menu);
}



