// $URL: http://subversion:8080/svn/gsc/trunk/drivers/gsc_common/linux/utils/gsc_util_label.c $
// $Rev: 1593 $
// $Date: 2009-03-29 12:49:08 -0500 (Sun, 29 Mar 2009) $

#include <errno.h>
#include <stdio.h>
#include <string.h>

#include "gsc_utils.h"



// variables	***************************************************************

static	int	_width	= 0;
static	int	_level	= 0;



/******************************************************************************
*
*	Function:	gsc_label_indent
*
*	Purpose:
*
*		Print the space that preceeds the label.
*
*	Arguments:
*
*		delta	Adjust the indenting by this amount.
*
*	Returned:
*
*		The number of spaces printed.
*
******************************************************************************/

int gsc_label_indent(int delta)
{
	int	i;
	int	spaces	= 0;

	for (i = 0; i < (_level + delta); i++, spaces += 2)
		printf("  ");

	fflush(stdout);
	return(spaces);
}



/******************************************************************************
*
*	Function:	gsc_label
*
*	Purpose:
*
*		Print a message introducing a test.
*
*	Arguments:
*
*		label	The test name. If this is NULL, then we just output spaces.
*
*	Returned:
*
*		None.
*
******************************************************************************/

void gsc_label(const char* label)
{
	int	spaces;

	if (label)
	{
		spaces	= _width - strlen(label);
		spaces	= (spaces < 0) ? 0 : spaces;
		spaces	-= gsc_label_indent(0);
		printf("%s: %*s", label, spaces, "");
	}
	else
	{
		spaces	= _width;
		spaces	= (spaces < 0) ? 0 : spaces;
		spaces	-= gsc_label_indent(0);
		printf("  %*s", spaces, "");
	}

	fflush(stdout);
}



/******************************************************************************
*
*	Function:	gsc_label_index
*
*	Purpose:
*
*		Print a message introducing a test. If the index number is >= 0, then
*		append the index number to the label.
*
*	Arguments:
*
*		label	The test name.
*
*	Returned:
*
*		None.
*
******************************************************************************/

void gsc_label_index(const char* label, int index)
{
	char	buf[128];

	strcpy(buf, label);

	if (index >= 0)
		sprintf(buf + strlen(buf), " #%d", index);

	gsc_label(buf);
}



/******************************************************************************
*
*	Function:	gsc_label_init
*
*	Purpose:
*
*		Initialize the label code.
*
*	Arguments:
*
*		width	The default width for the label field.
*
*	Returned:
*
*		None.
*
******************************************************************************/

void gsc_label_init(int width)
{
	_width	= width;
}



/******************************************************************************
*
*	Function:	gsc_label_level_dec
*
*	Purpose:
*
*		Decrease the label indenting.
*
*	Arguments:
*
*		None.
*
*	Returned:
*
*		None.
*
******************************************************************************/

void gsc_label_level_dec(void)
{
	_level--;
}



/******************************************************************************
*
*	Function:	gsc_label_level_inc
*
*	Purpose:
*
*		Increase the label indenting.
*
*	Arguments:
*
*		None.
*
*	Returned:
*
*		None.
*
******************************************************************************/

void gsc_label_level_inc(void)
{
	_level++;
}



/******************************************************************************
*
*	Function:	gsc_label_long_comma
*
*	Purpose:
*
*		Print a value with commas.
*
*	Arguments:
*
*		value	The positive value to print.
*
*	Returned:
*
*		None.
*
******************************************************************************/

void gsc_label_long_comma(long value)
{
	char	buf[32];
	int		i;
	int		len;

	if (value < 0)
	{
		printf("-");
		value	= -value;
	}

	sprintf(buf, "%ld", value);
	len	= strlen(buf);

	for (i = len; i; i--)
	{
		if (i == len)
			;
		else if ((i % 3) == 0)
			printf(",");

		printf("%c", buf[len - i]);
	}
}


