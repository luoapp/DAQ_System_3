// $URL: http://subversion:8080/svn/gsc/trunk/drivers/LINUX/ADADIO/ADADIO_Linux_3.x.x.x_GSC_DN/sbtest/reg_write.c $
// $Rev: 1620 $
// $Date: 2009-04-10 11:41:41 -0500 (Fri, 10 Apr 2009) $

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
*		Perform a test of the IOCTL service ADADIO_IOCTL_REG_WRITE.
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
		// reg				value		mask
		{ ADADIO_GSC_DIOPR,	0x000004AA,	0x000006FF	},
		{ ADADIO_GSC_DIOPR,	0x00000655,	0x000006FF	},

		{ ADADIO_GSC_SRR,	0x0000AAAA,	0x0000FFFF	},
		{ ADADIO_GSC_SRR,	0x00005555,	0x0000FFFF	},
	};

	int			errs	= 0;
	int			i;
	int			j;
	gsc_reg_t	parm;

	gsc_label("ADADIO_IOCTL_REG_WRITE");

	for (i = 0; i < ARRAY_ELEMENTS(list); i++)
	{
		parm.reg	= list[i].reg;
		parm.value	= list[i].value;
		parm.mask	= 0xBEEFDEAD;
		j			= ioctl(fd, ADADIO_IOCTL_REG_WRITE, (void*) &parm);

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
		j	= ioctl(fd, ADADIO_IOCTL_REG_READ, (void*) &parm);

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


