// $URL: http://subversion:8080/svn/gsc/trunk/drivers/LINUX/ADADIO/ADADIO_Linux_3.x.x.x_GSC_DN/regs/reg.c $
// $Rev: 1620 $
// $Date: 2009-04-10 11:41:41 -0500 (Fri, 10 Apr 2009) $

#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include "main.h"



/* variables	*************************************************************/

static menu_item_t	_name_list[65];	// Null terminate the list!!!
static int			_reg_id[65];
static menu_t		_reg_names;



/*****************************************************************************
*
*	Function:	_trim_ws
*
*	Purpose:
*
*		Trim the white space from the given string.
*
*	Arguments:
*
*		str		The string to process.
*
*	Returned:
*
*		The resulting string.
*
*****************************************************************************/

static char* _trim_ws(char* str)
{
	int	i;

	if (str)
	{
		for (; (str) && (isspace(str[0]));)
			str++;

		i	= (int) strlen(str);

		for (; i > 0;)
		{
			i--;

			if (isspace(str[i]))
				str[i]	= 0;
		}
	}

	return(str);
}



/*****************************************************************************
*
*	Function:	_reg_mod
*
*	Purpose:
*
*		Edit a register via its offset.
*
*	Arguments:
*
*		fd		The handle for the board to access.
*
*		name	The text to display for the register to access.
*
(		desc	The description of the register.
*
*		reg		The identifier for the register to access.
*
*	Returned:
*
*		None.
*
*****************************************************************************/

static void _reg_mod(int fd, const char* name, const char* desc, int reg)
{
	char	buf[1024];
	char	c		= 0;
	int		errs	= 0;
	int		i;
	long	l;
	char*	psz;
	__u32	value;

	printf("    %s", name);

	if (desc)
		printf("  (%s)\n", desc);
	else
		printf("\n");

	errs	= gsc_dev_reg_read(fd, reg, &value);

	if (errs == 0)
	{
		printf("    Current Value:  %08lX\n", (long) value);
		printf("    Value To Write: ");

		// Get the user's input.
		fgets(buf, sizeof(buf), stdin);
		psz	= _trim_ws(buf);

		if ((psz[0] == '0') && (psz[1] == 'x'))
			psz	+= 2;

		i	= sscanf(psz, "%lX%c", &l, &c);

		if (i != 1)
		{
			printf("ERROR: Invalid input\n");
			errs	= 1;
		}
		else if (l != (l & 0xFFFFFFFF))
		{
			printf("ERROR: Invalid value\n");
			errs	= 1;
		}
		else
		{
			errs	= gsc_dev_reg_write(fd, reg, l);
		}
	}

	if (errs == 0)
		errs	= gsc_dev_reg_read(fd, reg, &value);

	if (errs == 0)
		printf("    Updated Value:  %08lX\n", (long) value);
}



/*****************************************************************************
*
*	Function:	reg_mod_by_name
*
*	Purpose:
*
*		Edit a register via its name.
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

void reg_mod_by_name(int fd)
{
	const gsc_reg_def_t*	def;
	int						i;
	int						index	= 0;
	const char*				name;

	memset(_name_list, 0, sizeof(_name_list));

	for (i = 0;; i++)
	{
		def	= adadio_reg_get_def_index(i);

		if (def == NULL)
			break;

		if (def->ask_support)
			continue;

		name	= def->name;

		if (memcmp(name, "GSC ", 4) == 0)
			name	+= 4;

		_reg_id[index]			= def->reg;
		_name_list[index].name	= name;
		_name_list[index].desc	= def->desc;
		_name_list[index].func	= NULL;
		index++;
	}

	_name_list[index].name	= NULL;
	_name_list[index].func	= NULL;
	_reg_names.title		= "GSC General Register List";
	_reg_names.list			= _name_list;
	i	= menu_select(&_reg_names);
	_reg_mod(fd, _name_list[i].name, _name_list[i].desc, _reg_id[i]);
}



/*****************************************************************************
*
*	Function:	reg_mod_by_offset
*
*	Purpose:
*
*		Edit a register via its offset.
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

void reg_mod_by_offset(int fd)
{
	char	buf[1024];
	char	c		= 0;
	int		i;
	long	l;
	char*	psz;
	int		reg;

	printf("Edit a register by an offset.\n");
	printf("  Enter a 4-byte aligned, hex offset from 0x00 to 0xFC: ");

	// Get the user's input.
	fgets(buf, sizeof(buf), stdin);
	psz	= _trim_ws(buf);

	if ((psz[0] == '0') && (psz[1] == 'x'))
		psz	+= 2;

	i	= sscanf(psz, "%lX%c", &l, &c);

	if (i != 1)
	{
		printf("ERROR: Invalid input\n");
	}
	else if ((l < 0) || (l > 0xFC))
	{
		printf("ERROR: The value is out of range.\n");
	}
	else if (l % 4)
	{
		printf("ERROR: The value is not 4-byte aligned.\n");
	}
	else
	{
		sprintf(buf, "Offset 0x%02lX", (long) l);
		reg	= GSC_REG_ENCODE(GSC_REG_GSC, 4, l);
		_reg_mod(fd, buf, NULL, reg);
	}
}



