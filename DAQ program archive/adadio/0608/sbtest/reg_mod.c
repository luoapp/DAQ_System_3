// $URL: http://subversion:8080/svn/gsc/trunk/drivers/LINUX/ADADIO/ADADIO_Linux_3.x.x.x_GSC_DN/sbtest/reg_mod.c $
// $Rev: 1620 $
// $Date: 2009-04-10 11:41:41 -0500 (Fri, 10 Apr 2009) $

#include <errno.h>
#include <stdio.h>
#include <sys/ioctl.h>

#include "main.h"



/******************************************************************************
*
*	Function:	reg_mod_test
*
*	Purpose:
*
*		Perform a test of the IOCTL service ADADIO_IOCTL_REG_MOD.
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

int reg_mod_test(int fd)
{
	static const struct
	{
		__u32	reg;
		__u32	mask;
	} list[]	=
	{
		// reg					mask
		{ ADADIO_GSC_BCR,	0x1F8F87DF	},
		{ ADADIO_GSC_SRR,	0x0000FFFF	},
	};

	__u32		bit;
	int			errs	= 0;
	int			i;
	int			j;
	gsc_reg_t	parm;
	__u32		value;

	gsc_label("ADADIO_IOCTL_REG_MOD");

	for (i = 0; (errs == 0) && (i < ARRAY_ELEMENTS(list)); i++)
	{

		for (bit = 0x1; bit; bit <<= 1)
		{
			if ((list[i].mask & bit) == 0)
				continue;

			// Read the register value so we can restore it later.
			parm.reg	= list[i].reg;
			j			= ioctl(fd, ADADIO_IOCTL_REG_READ, (void*) &parm);
			value		= parm.value;

			if (j)
			{
				errs	= 1;
				printf(	"FAIL <---  (%d. i %d, ioctl() failure, errno %d)\n",
						__LINE__,
						i,
						errno);
				break;
			}

			// Set the bit low.
			parm.value	= 0;
			parm.mask	= bit;
			j			= ioctl(fd, ADADIO_IOCTL_REG_MOD, (void*) &parm);

			if (j)
			{
				errs	= 1;
				printf(	"FAIL <---  (%d. i %d, ioctl() failure, errno %d)\n",
						__LINE__,
						i,
						errno);
				break;
			}

			// Now verify that the bit is low.
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

			if (parm.value & bit)
			{
				errs	= 1;
				printf(	"FAIL <---  (%d. i %d, bit not low, mask 0x%lX, got 0x%lX)\n",
						__LINE__,
						i,
						(long) bit,
						(long) parm.value);
				break;
			}

			// Now restore the register to its previous value.
			parm.value	= value;
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

			// Set the bit high.
			parm.value	= bit;
			parm.mask	= bit;
			j			= ioctl(fd, ADADIO_IOCTL_REG_MOD, (void*) &parm);

			if (j)
			{
				errs	= 1;
				printf(	"FAIL <---  (%d. i %d, ioctl() failure, errno %d)\n",
						__LINE__,
						i,
						errno);
				break;
			}

			// Now verify that the bit is high.
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

			if ((parm.value & bit) == 0)
			{
				errs	= 1;
				printf(	"FAIL <---  (%d. i %d, bit not high, mask 0x%lX, got 0x%lX)\n",
						__LINE__,
						i,
						(long) bit,
						(long) parm.value);
				break;
			}

			// Now restore the register to its previous value.
			parm.value	= value;
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
		}
	}

	if (errs == 0)
		printf("PASS\n");

	return(errs);
}


