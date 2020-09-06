// $URL: http://subversion:8080/svn/gsc/trunk/drivers/LINUX/16AO20/16AO20_Linux_2.x.x.x_GSC_DN/regs/main.c $
// $Rev: 2014 $
// $Date: 2009-05-19 12:39:09 -0500 (Tue, 19 May 2009) $

#include <stdio.h>
#include <stdlib.h>

#include "main.h"



/* variables	*************************************************************/

static	int	_index	= 0;



/*****************************************************************************
*
*	Function:	_parse_args
*
*	Purpose:
*
*		Parse the command line arguments.
*
*	Arguments:
*
*		argc	The number of command line arguments given.
*
*		argv	The list of command line arguments given.
*
*	Returned:
*
*		>= 0	The number of errors encounterred.
*
*****************************************************************************/

static int _parse_args(int argc, char** argv)
{
	char	c;
	int		errs	= 0;
	int		i;
	int		j;
	int		k;

	printf("USAGE: regs <index>\n");
	printf("   index  The index of the board to access.\n");

	for (i = 1; i < argc; i++)
	{
		j	= sscanf(argv[i], "%d%c", &k, &c);

		if ((j == 1) && (k >= 0))
		{
			_index	= k;
			continue;
		}
		else
		{
			errs	= 1;
			printf("ERROR: invalid board selection: %s\n", argv[i]);
			break;
		}
	}

	return(errs);
}



/*****************************************************************************
*
*	Function:	main
*
*	Purpose:
*
*		Control the overall flow of the application.
*
*	Arguments:
*
*		argc			The number of command line arguments.
*
*		argv			The list of command line arguments.
*
*	Returned:
*
*		EXIT_SUCCESS	We tested a device.
*		EXIT_FAILURE	We didn't test a device.
*
*****************************************************************************/

int main(int argc, char** argv)
{
	int		errs;
	int		fd		= 0;
	int		qty;
	int		ret		= EXIT_FAILURE;

	gsc_label_init(28);

	for (;;)
	{
		printf("regs - Register Access Application (Version %s)\n", VERSION);
		errs	= _parse_args(argc, argv);

		if (errs)
			break;

		qty		= gsc_count_boards(AO20_BASE_NAME);
		errs	= gsc_select_1_board(qty, &_index);

		if ((qty <= 0) || (errs))
			break;

		gsc_label("Accessing Board Index");
		printf("%d\n", _index);
		fd	= gsc_dev_open(_index, AO20_BASE_NAME);

		if (fd == -1)
		{
			errs	= 1;
			printf(	"ERROR: Unable to access device %d.", _index);
		}

		if (errs == 0)
		{
			ret		= EXIT_SUCCESS;
			main_menu(fd);
		}

		gsc_dev_close(_index, fd);
		break;
	}

	return(ret);
}



