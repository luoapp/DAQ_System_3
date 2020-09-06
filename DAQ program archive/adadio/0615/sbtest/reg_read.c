// $URL: http://subversion:8080/svn/gsc/trunk/drivers/LINUX/ADADIO/ADADIO_Linux_3.x.x.x_GSC_DN/sbtest/reg_read.c $
// $Rev: 1620 $
// $Date: 2009-04-10 11:41:41 -0500 (Fri, 10 Apr 2009) $

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
*		Perform a test of the IOCTL service ADADIO_IOCTL_REG_READ.
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
		{ ADADIO_GSC_BRR,		0		},
		{ ADADIO_GSC_BCR,		0		},
		{ ADADIO_GSC_DIOPR,		0		},
		{ ADADIO_GSC_AOC0R,		0		},
		{ ADADIO_GSC_AOC1R,		0		},
		{ ADADIO_GSC_AOC2R,		0		},
		{ ADADIO_GSC_AOC3R,		0		},
		{ ADADIO_GSC_AIDR,		0		},
		{ ADADIO_GSC_SRR,		0		},

		{ GSC_PCI_9080_VIDR,	0x10B5	},
		{ GSC_PCI_9080_DIDR,	0x9080	},
		{ GSC_PCI_9080_SVID,	0x10B5	},
		{ GSC_PCI_9080_SID,		0x2370	},

		{ GSC_PLX_9080_VIDR,	0x10B5	},
		{ GSC_PLX_9080_DIDR,	0x9080	}
	};

	int			errs	= 0;
	int			i;
	int			j;
	gsc_reg_t	parm;

	gsc_label("ADADIO_IOCTL_REG_READ");

	for (i = 0; i < ARRAY_ELEMENTS(list); i++)
	{
		parm.reg	= list[i].reg;
		parm.value	= 0xDEADBEEF;
		parm.mask	= 0xBEEFDEAD;
		j			= ioctl(fd, ADADIO_IOCTL_REG_READ, (void*) &parm);

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


