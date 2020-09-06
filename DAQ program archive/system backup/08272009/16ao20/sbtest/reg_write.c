// $URL: http://subversion:8080/svn/gsc/trunk/drivers/LINUX/16AO20/16AO20_Linux_2.x.x.x_GSC_DN/sbtest/reg_write.c $
// $Rev: 2014 $
// $Date: 2009-05-19 12:39:09 -0500 (Tue, 19 May 2009) $

#include <errno.h>
#include <stdio.h>
#include <sys/ioctl.h>

#include "main.h"



/******************************************************************************
*
*	Function:	reg_write_test
*
*	Purpose:
*
*		Perform a test of the IOCTL service AO20_IOCTL_REG_WRITE.
*
*	Arguments:
*
*		fd		The handle for the board to access.
*
*	Returned:
*
*		>= 0	The number of errors encounterred.
*
******************************************************************************/

int reg_write_test(int fd)
{
	static const struct
	{
		__u32	reg;
		__u32	value;
		__u32	mask;
	} list[]	=
	{
		// reg			value		mask
		{ AO20_GSC_BCR,	0x00000551,	0x000007F9	},
		{ AO20_GSC_BCR,	0x000002A8,	0x000007F9	},

		{ AO20_GSC_BOR,	0x00000115,	0x0000013F	},
		{ AO20_GSC_BOR,	0x000002A,	0x0000013F	},
	};

	int			errs	= 0;
	int			i;
	int			j;
	gsc_reg_t	parm;

	gsc_label("AO20_IOCTL_REG_WRITE");

	for (i = 0; i < ARRAY_ELEMENTS(list); i++)
	{
		parm.reg	= list[i].reg;
		parm.value	= list[i].value;
		parm.mask	= 0xBEEFDEAD;
		j			= ioctl(fd, AO20_IOCTL_REG_WRITE, (void*) &parm);

		if (j)
		{
			errs	= 1;
			printf(	"FAIL <---  (%d. i %d, ioctl() failure, errno %d)\n",
					__LINE__,
					i,
					errno);
			break;
		}

		if (parm.mask != 0xBEEFDEAD)
		{
			errs	= 1;
			printf("FAIL <---  (%d. i %d, mask changed)\n", __LINE__, i);
			break;
		}

		// Now read the register and verify the bits of interest.
		j	= ioctl(fd, AO20_IOCTL_REG_READ, (void*) &parm);

		if (j)
		{
			errs	= 1;
			printf(	"FAIL <---  (%d. i %d, ioctl() failure, errno %d)\n",
					__LINE__,
					i,
					errno);
			break;
		}

		if ((list[i].value & list[i].mask) != (parm.value & list[i].mask))
		{
			errs	= 1;
			printf(	"FAIL <---  (%d. i %d, mask 0x%lX, got 0x%lX, expected 0x%lX)\n",
					__LINE__,
					i,
					(long) list[i].mask,
					(long) parm.value,
					(long) list[i].value);
			break;
		}
	}

	if (errs == 0)
		printf("PASS\n");

	return(errs);
}


