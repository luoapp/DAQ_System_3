// $URL: http://subversion:8080/svn/gsc/trunk/drivers/LINUX/ADADIO/ADADIO_Linux_3.x.x.x_GSC_DN/utils/util_id.c $
// $Rev: 1620 $
// $Date: 2009-04-10 11:41:41 -0500 (Fri, 10 Apr 2009) $

#include <stdio.h>

#include "adadio_dsl.h"
#include "adadio_utils.h"
#include "gsc_utils.h"



/******************************************************************************
*
*	Function:	_id_board_pci
*
*	Purpose:
*
*		Identify the board using the PCI registers.
*
*	Arguments:
*
*		fd		The handle used to access the device.
*
*	Returned:
*
*		>= 0	The number of errors encountered here.
*
******************************************************************************/

static int _id_board_pci(int fd)
{
	int		errs	= 0;
	__u32	reg;

	gsc_label("Vendor ID");
	errs	+= gsc_dev_reg_read(fd, GSC_PCI_9080_VIDR, &reg);
	printf("0x%04lX      ", (long) reg);

	if (reg == 0x10B5)
	{
		printf("(PLX)\n");
	}
	else
	{
		errs++;
		printf("(UNKNOWN) FAIL <---\n");
	}

	gsc_label("Device ID");
	errs	+= gsc_dev_reg_read(fd, GSC_PCI_9080_DIDR, &reg);
	printf("0x%04lX      ", (long) reg);

	if (reg == 0x9080)
	{
		printf("(PCI9080)\n");
	}
	else
	{
		errs++;
		printf("(UNKNOWN) FAIL <---\n");
	}

	gsc_label("Sub Vendor ID");
	errs	+= gsc_dev_reg_read(fd, GSC_PCI_9080_SVID, &reg);
	printf("0x%04lX      ", (long) reg);

	if (reg == 0x10B5)
	{
		printf("(PLX)\n");
	}
	else
	{
		errs++;
		printf("(UNKNOWN) FAIL <---\n");
	}

	gsc_label("Subsystem ID");
	errs	+= gsc_dev_reg_read(fd, GSC_PCI_9080_SID, &reg);
	printf("0x%04lX      ", (long) reg);

	if (reg == 0x2370)
	{
		printf("(ADADIO)\n");
	}
	else
	{
		errs++;
		printf("(UNKNOWN) FAIL <---\n");
	}

	return(errs);
}



/******************************************************************************
*
*	Function:	adadio_id_board
*
*	Purpose:
*
*		Identify the board.
*
*	Arguments:
*
*		fd		The handle to use to access the board.
*
*		index	The index of the board or -1 if we don't care.
*
*		desc	A description of the board or NULL if we don't care.
*
*	Returned:
*
*		>= 0	The number of errors encountered here.
*
******************************************************************************/

int adadio_id_board(int fd, int index, const char* desc)
{
	__s32	device_type;
	int		errs	= 0;

	gsc_label_index("Board", index);

	if (desc == NULL)
	{
		errs	= adadio_query_quiet(fd, ADADIO_QUERY_DEVICE_TYPE, &device_type);

		if (errs == 0)
		{
			switch (device_type)
			{
				default:

					errs	= 1;
					printf(	"FAIL <---  (unexpected device type: %ld)",
							(long) device_type);
					break;

				case GSC_DEV_TYPE_ADADIO:

					desc	= "ADADIO";
					break;
			}
		}
	}

	printf("%s\n", desc ? desc : "");
	gsc_label_level_inc();

	errs	+= _id_board_pci(fd);

	gsc_label_level_dec();

	return(errs);
	return(0);
}



