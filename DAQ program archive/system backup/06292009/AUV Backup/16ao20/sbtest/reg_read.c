// $URL: http://subversion:8080/svn/gsc/trunk/drivers/LINUX/16AO20/16AO20_Linux_2.x.x.x_GSC_DN/sbtest/reg_read.c $
// $Rev: 2014 $
// $Date: 2009-05-19 12:39:09 -0500 (Tue, 19 May 2009) $

#include <errno.h>
#include <stdio.h>
#include <sys/ioctl.h>

#include "main.h"



/******************************************************************************
*
*	Function:	reg_read_test
*
*	Purpose:
*
*		Perform a test of the IOCTL service AO20_IOCTL_REG_READ.
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

int reg_read_test(int fd)
{
	static const struct
	{
		__u32	reg;
		__u32	value;
	} list[]	=
	{
		// reg					value
		{ AO20_GSC_BCR,			0		},
		{ AO20_GSC_CSR,			0		},
		{ AO20_GSC_SRR,			0		},
		{ AO20_GSC_BOR,			0		},
		{ AO20_GSC_AVR,			0		},
		{ AO20_GSC_FOR,			0		},
		{ AO20_GSC_AVR,			0		},
		{ AO20_GSC_ODBR,		0		},
		{ AO20_GSC_ACR,			0		},

		{ GSC_PCI_9080_VIDR,	0x10B5	},
		{ GSC_PCI_9080_DIDR,	0x9080	},
		{ GSC_PCI_9080_SVID,	0x10B5	},
		{ GSC_PCI_9080_SID,		0x3102	},

		{ GSC_PLX_9080_VIDR,	0x10B5	},
		{ GSC_PLX_9080_DIDR,	0x9080	}
	};

	int			errs	= 0;
	int			i;
	int			j;
	gsc_reg_t	parm;

	gsc_label("AO20_IOCTL_REG_READ");

	for (i = 0; i < ARRAY_ELEMENTS(list); i++)
	{
		parm.reg	= list[i].reg;
		parm.value	= 0xDEADBEEF;
		parm.mask	= 0xBEEFDEAD;
		j			= ioctl(fd, AO20_IOCTL_REG_READ, (void*) &parm);

		if (j)
		{
			errs	= 1;
			printf(	"FAIL <---  (%d. i %d, ioctl() failure, errno %d)\n",
					__LINE__,
					i,
					errno);
			break;
		}

		if (parm.value == 0xDEADBEEF)
		{
			errs	= 1;
			printf("FAIL <---  (%d. i %d, value not changed)\n", __LINE__, i);
			break;
		}

		if (parm.mask != 0xBEEFDEAD)
		{
			errs	= 1;
			printf("FAIL <---  (%d. i %d, mask changed)\n", __LINE__, i);
			break;
		}

		if ((list[i].value) && (parm.value != list[i].value))
		{
			errs	= 1;
			printf(	"FAIL <---  (%d. i %d, got 0x%lX, expected 0x%lX)\n",
					__LINE__,
					i,
					(long) parm.value,
					(long) list[i].value);
			break;
		}
	}

	if (errs == 0)
		printf("PASS\n");

	return(errs);
}


