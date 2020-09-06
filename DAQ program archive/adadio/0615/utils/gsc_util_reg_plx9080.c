// $URL: http://subversion:8080/svn/gsc/trunk/drivers/gsc_common/linux/utils/gsc_util_reg_plx9080.c $
// $Rev: 1616 $
// $Date: 2009-04-10 11:36:35 -0500 (Fri, 10 Apr 2009) $

#include <stdio.h>
#include <asm/types.h>

#include "gsc_pci9080.h"
#include "gsc_utils.h"



// #defines	*******************************************************************

#define	_PCI_REG(a)	"PCI " #a, GSC_PCI_9080_##a, 0, 0, 0
#define	_PLX_REG(a)	"PLX " #a, GSC_PLX_9080_##a, 0, 0, 0



// variables	***************************************************************

static gsc_reg_def_t	_pci[]	=
{
	{ _PCI_REG(BAR0),	NULL	},
	{ _PCI_REG(BAR1),	NULL	},
	{ _PCI_REG(BAR2),	NULL	},
	{ _PCI_REG(BAR3),	NULL	},
	{ _PCI_REG(BAR4),	NULL	},
	{ _PCI_REG(BAR5),	NULL	},
	{ _PCI_REG(BISTR),	NULL	},
	{ _PCI_REG(CCR),	NULL	},
	{ _PCI_REG(CIS),	NULL	},
	{ _PCI_REG(CLSR),	NULL	},
	{ _PCI_REG(CR),		NULL	},
	{ _PCI_REG(DIDR),	NULL	},
	{ _PCI_REG(ERBAR),	NULL	},
	{ _PCI_REG(HTR),	NULL	},
	{ _PCI_REG(ILR),	NULL	},
	{ _PCI_REG(IPR),	NULL	},
	{ _PCI_REG(LTR),	NULL	},
	{ _PCI_REG(MGR),	NULL	},
	{ _PCI_REG(MLR),	NULL	},
	{ _PCI_REG(REV),	NULL	},
	{ _PCI_REG(SID),	NULL	},
	{ _PCI_REG(SR),		NULL	},
	{ _PCI_REG(SVID),	NULL	},
	{ _PCI_REG(VIDR),	NULL	},
	{ NULL, 0, 0, 0, 0,	NULL	}
};

static gsc_reg_def_t	_plx[]	=
{
	{ _PLX_REG(BIGEND),		NULL	},
	{ _PLX_REG(CNTRL),		NULL	},
	{ _PLX_REG(DIDR),		NULL	},
	{ _PLX_REG(DMAARB),		NULL	},
	{ _PLX_REG(DMACSR0),	NULL	},
	{ _PLX_REG(DMADPR0),	NULL	},
	{ _PLX_REG(DMALADR0),	NULL	},
	{ _PLX_REG(DMAMODE0),	NULL	},
	{ _PLX_REG(DMAPADR0),	NULL	},
	{ _PLX_REG(DMASIZ0),	NULL	},
	{ _PLX_REG(DMACSR1),	NULL	},
	{ _PLX_REG(DMADPR1),	NULL	},
	{ _PLX_REG(DMALADR1),	NULL	},
	{ _PLX_REG(DMAMODE1),	NULL	},
	{ _PLX_REG(DMAPADR1),	NULL	},
	{ _PLX_REG(DMASIZ1),	NULL	},
	{ _PLX_REG(DMATHR),		NULL	},
	{ _PLX_REG(DMCFGA),		NULL	},
	{ _PLX_REG(DMLBAI),		NULL	},
	{ _PLX_REG(DMLBAM),		NULL	},
	{ _PLX_REG(DMPBAM),		NULL	},
	{ _PLX_REG(DMRR),		NULL	},
	{ _PLX_REG(EROMBA),		NULL	},
	{ _PLX_REG(EROMRR),		NULL	},
	{ _PLX_REG(INTCSR),		NULL	},
	{ _PLX_REG(L2PDBELL),	NULL	},
	{ _PLX_REG(LAS0BA),		NULL	},
	{ _PLX_REG(LAS0RR),		NULL	},
	{ _PLX_REG(LBRD0),		NULL	},
	{ _PLX_REG(LAS1BA),		NULL	},
	{ _PLX_REG(LAS1RR),		NULL	},
	{ _PLX_REG(LBRD1),		NULL	},
	{ _PLX_REG(MARBR),		NULL	},
	{ _PLX_REG(MBOX0),		NULL	},
	{ _PLX_REG(MBOX1),		NULL	},
	{ _PLX_REG(MBOX2),		NULL	},
	{ _PLX_REG(MBOX3),		NULL	},
	{ _PLX_REG(MBOX4),		NULL	},
	{ _PLX_REG(MBOX5),		NULL	},
	{ _PLX_REG(MBOX6),		NULL	},
	{ _PLX_REG(MBOX7),		NULL	},
	{ _PLX_REG(P2LDBELL),	NULL	},
	{ _PLX_REG(REV),		NULL	},
	{ _PLX_REG(VIDR),		NULL	},
	{ NULL, 0, 0, 0, 0,		NULL	}
};



//*****************************************************************************
int gsc_reg_plx9080_list_pci(int fd)
{
	int	errs;

	gsc_label("PCI9080 PCI Registers");
	printf("\n");

	errs	= gsc_reg_list(fd, _pci, 0);

	return(errs);
}



//*****************************************************************************
int gsc_reg_plx9080_list_plx(int fd)
{
	int	errs;

	gsc_label("PCI9080 PLX Registers");
	printf("\n");

	errs	= gsc_reg_list(fd, _plx, 0);

	return(errs);
}


