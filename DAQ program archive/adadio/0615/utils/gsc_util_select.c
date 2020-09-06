// $URL: http://subversion:8080/svn/gsc/trunk/drivers/gsc_common/linux/utils/gsc_util_select.c $
// $Rev: 1593 $
// $Date: 2009-03-29 12:49:08 -0500 (Sun, 29 Mar 2009) $

#include <stdio.h>

#include "gsc_utils.h"



/******************************************************************************
*
*	Function:	gsc_select_1_board
*
*	Purpose:
*
*		Select the board to utilize when more than one is present.
*
*	Arguments:
*
*		qty		The number of installed boards.
*
*		index	The board to use. This starts as the default, which
*				we adjust here as appropriate.
*
*	Returned:
*
*		>= 0	The number of errors encountered here.
*
******************************************************************************/

int gsc_select_1_board(int qty, int* index)
{
	char	buf[128];
	int		errs	= 0;

	if (qty < 2)
	{
		if (index[0] > 0)
		{
			errs	= 1;
			printf("FAIL <---  (%d is an invalid selection)\n", index[0]);
		}

		index[0]	= 0;
	}
	else if ((index[0] >= 0) && (index[0] < qty))
	{
	}
	else
	{
		printf("Enter a board index from 0 to %d: ", qty - 1);
		fgets(buf, sizeof(buf), stdin);
		sscanf(buf, "%d", index);

		if ((index[0] < 0) || (index[0] >= qty))
		{
			errs	= 1;
			printf("%d is an invalid index.\n", index[0]);
		}
	}

	return(errs);
}



/******************************************************************************
*
*	Function:	gsc_select_2_boards
*
*	Purpose:
*
*		Select two boards to utilize when more than two are present.
*
*	Arguments:
*
*		qty		The number of installed boards.
*
*		index_1	The first board to use.
*
*		index_2	The second board to use.
*
*	Returned:
*
*		>= 0	The number of errors encountered here.
*
******************************************************************************/

int gsc_select_2_boards(int qty, int* index_1, int* index_2)
{
	char	buf[128];
	int		errs	= 0;

	for (;;)	// A convenience loop.
	{
		if (qty == 0)
		{
			errs	= 1;
			printf("FAIL <--- (no boards present, two are required)\n");
			break;
		}

		if (qty == 1)
		{
			errs	= 1;
			printf("FAIL <--- (only one board present, two are required)\n");
			break;
		}

		if ((qty == 2) && (index_1[0] < 0) && (index_2[0] < 0))
		{
			index_1[0]	= 0;
			index_2[0]	= 1;
		}

		if ((index_1[0] < 0) || (index_1[0] >= qty))
		{
			printf("Enter the index for the first board: ");
			fgets(buf, sizeof(buf), stdin);
			sscanf(buf, "%d", index_1);
		}

		if ((index_2[0] < 0) || (index_2[0] >= qty))
		{
			printf("Enter the index for the second board: ");
			fgets(buf, sizeof(buf), stdin);
			sscanf(buf, "%d", index_2);
		}

		gsc_label("Boards to Access");

		if ((index_1[0] < 0) || (index_1[0] >= qty))
		{
			errs	= 1;
			printf("FAIL <--- (the first index is invalid: %d)\n", index_1[0]);
			break;
		}

		if ((index_2[0] < 0) || (index_2[0] >= qty) || (index_2 == index_1))
		{
			errs	= 1;
			printf("FAIL <--- (the second index is invalid: %d)\n", index_2[0]);
			break;
		}

		printf("%d and %d\n", index_1[0], index_2[0]);
		break;
	}

	return(errs);
}


