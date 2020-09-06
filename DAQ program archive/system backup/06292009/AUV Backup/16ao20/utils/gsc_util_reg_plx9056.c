// $URL: http://subversion:8080/svn/gsc/trunk/drivers/gsc_common/linux/utils/gsc_util_reg_plx9056.c $
// $Rev: 1638 $
// $Date: 2009-04-17 11:28:02 -0500 (Fri, 17 Apr 2009) $

#include <stdio.h>
#include <asm/types.h>

#include "gsc_pci9056.h"
#include "gsc_utils.h"



// #defines	*******************************************************************

#define	_PCI_REG(a)	"PCI " #a, GSC_PCI_9056_##a, 0, 0, 0
#define	_PLX_REG(a)	"PLX " #a, GSC_PLX_9056_##a, 0, 0, 0



// variables	***************************************************************

static gsc_reg_def_t	_pci[]	=
{
	{ _PCI_REG(BAR0),		NULL	},
	{ _PCI_REG(BAR1),		NULL	},
	{ _PCI_REG(BAR2),		NULL	},
	{ _PCI_REG(BAR3),		NULL	},
	{ _PCI_REG(BAR4),		NULL	},
	{ _PCI_REG(BAR5),		NULL	},
	{ _PCI_REG(BISTR),		NULL	},
	{ _PCI_REG(CAP_PTR),	NULL	},
	{ _PCI_REG(CCR),		NULL	},
	{ _PCI_REG(CIS),		NULL	},
	{ _PCI_REG(CLSR),		NULL	},
	{ _PCI_REG(CR),			NULL	},
	{ _PCI_REG(DIDR),		NULL	},
	{ _PCI_REG(ERBAR),		NULL	},
	{ _PCI_REG(HS_CNTL),	NULL	},
	{ _PCI_REG(HS_CSR),		NULL	},
	{ _PCI_REG(HS_NEXT),	NULL	},
	{ _PCI_REG(HTR),		NULL	},
	{ _PCI_REG(ILR),		NULL	},
	{ _PCI_REG(IPR),		NULL	},
	{ _PCI_REG(LTR),		NULL	},
	{ _PCI_REG(MGR),		NULL	},
	{ _PCI_REG(MLR),		NULL	},
	{ _PCI_REG(PMCAPID),	NULL	},
	{ _PCI_REG(PMC),		NULL	},
	{ _PCI_REG(PMCSR_BSE),	NULL	},
	{ _PCI_REG(PMCSR),		NULL	},
	{ _PCI_REG(PMDATA),		NULL	},
	{ _PCI_REG(PMNEXT),		NULL	},
	{ _PCI_REG(PVPDAD),		NULL	},
	{ _PCI_REG(PVPDATA),	NULL	},
	{ _PCI_REG(PVPDID),		NULL	},
	{ _PCI_REG(PVPD_NEXT),	NULL	},
	{ _PCI_REG(REV),		NULL	},
	{ _PCI_REG(SID),		NULL	},
	{ _PCI_REG(SR),			NULL	},
	{ _PCI_REG(SVID),		NULL	},
	{ _PCI_REG(VIDR),		NULL	},
	{ NULL, 0, 0, 0, 0,		NULL	}
};

static gsc_reg_def_t	_plx[]	=
{
	{ _PLX_REG(ARB),		NULL	},
	{ _PLX_REG(BIGEND),		NULL	},
	{ _PLX_REG(CNTRL),		NULL	},
	{ _PLX_REG(DIDR),		NULL	},
	{ _PLX_REG(DMAARB),		NULL	},
	{ _PLX_REG(DMACSR0),	NULL	},
	{ _PLX_REG(DMACSR1),	NULL	},
	{ _PLX_REG(DMADAC0),	NULL	},
	{ _PLX_REG(DMADAC1),	NULL	},
	{ _PLX_REG(DMADPR0),	NULL	},
	{ _PLX_REG(DMADPR1),	NULL	},
	{ _PLX_REG(DMALADR0),	NULL	},
	{ _PLX_REG(DMALADR1),	NULL	},
	{ _PLX_REG(DMAMODE0),	NULL	},
	{ _PLX_REG(DMAMODE1),	NULL	},
	{ _PLX_REG(DMAPADR0),	NULL	},
	{ _PLX_REG(DMAPADR1),	NULL	},
	{ _PLX_REG(DMASIZ0),	NULL	},
	{ _PLX_REG(DMASIZ1),	NULL	},
	{ _PLX_REG(DMATHR),		NULL	},
	{ _PLX_REG(DMCFGA),		NULL	},
	{ _PLX_REG(DMDAC),		NULL	},
	{ _PLX_REG(DMLBAI),		NULL	},
	{ _PLX_REG(DMLBAM),		NULL	},
	{ _PLX_REG(DMPBAM),		NULL	},
	{ _PLX_REG(DMRR),		NULL	},
	{ _PLX_REG(EROMBA),		NULL	},
	{ _PLX_REG(EROMRR),		NULL	},
	{ _PLX_REG(IFHPR),		NULL	},
	{ _PLX_REG(IFTPR),		NULL	},
	{ _PLX_REG(INTCSR),		NULL	},
	{ _PLX_REG(IPHPR),		NULL	},
	{ _PLX_REG(IPTPR),		NULL	},
	{ _PLX_REG(IQP),		NULL	},
	{ _PLX_REG(L2PDBELL),	NULL	},
	{ _PLX_REG(LAS0BA),		NULL	},
	{ _PLX_REG(LAS0RR),		NULL	},
	{ _PLX_REG(LAS1BA),		NULL	},
	{ _PLX_REG(LAS1RR),		NULL	},
	{ _PLX_REG(LBRD0),		NULL	},
	{ _PLX_REG(LBRD1),		NULL	},
	{ _PLX_REG(LMISC1),		NULL	},
	{ _PLX_REG(LMISC2),		NULL	},
	{ _PLX_REG(MARBR),		NULL	},
	{ _PLX_REG(MBOX0),		NULL	},
	{ _PLX_REG(MBOX1),		NULL	},
	{ _PLX_REG(MBOX2),		NULL	},
	{ _PLX_REG(MBOX3),		NULL	},
	{ _PLX_REG(MBOX4),		NULL	},
	{ _PLX_REG(MBOX5),		NULL	},
	{ _PLX_REG(MBOX6),		NULL	},
	{ _PLX_REG(MBOX7),		NULL	},
	{ _PLX_REG(MQCR),		NULL	},
	{ _PLX_REG(OFHPR),		NULL	},
	{ _PLX_REG(OFTPR),		NULL	},
	{ _PLX_REG(OPHPR),		NULL	},
	{ _PLX_REG(OPQIM),		NULL	},
	{ _PLX_REG(OPQIS),		NULL	},
	{ _PLX_REG(OPTPR),		NULL	},
	{ _PLX_REG(OQP),		NULL	},
	{ _PLX_REG(P2LDBELL),	NULL	},
	{ _PLX_REG(PABTADR),	NULL	},
	{ _PLX_REG(REV),		NULL	},
	{ _PLX_REG(PROT_AREA),	NULL	},
	{ _PLX_REG(QBAR),		NULL	},
	{ _PLX_REG(QSR),		NULL	},
	{ _PLX_REG(VIDR),		NULL	},
	{ NULL, 0, 0, 0, 0,		NULL	}
};



//*****************************************************************************
static const gsc_reg_def_t* _find_reg(unsigned long reg, const gsc_reg_def_t* list)
{
	const gsc_reg_def_t*	def	= NULL;
	int						i;

	for (i = 0; list[i].name; i++)
	{
		if (reg == list[i].reg)
		{
			def	= &list[i];
			break;
		}
	}

	return(def);
}


//*****************************************************************************
int gsc_reg_plx9056_list_pci(int fd)
{
	int	errs;

	gsc_label("PCI9056 PCI Registers");
	printf("\n");

	errs	= gsc_reg_list(fd, _pci, 0);

	return(errs);
}



//*****************************************************************************
int gsc_reg_plx9056_list_plx(int fd)
{
	int	errs;

	gsc_label("PCI9056 PLX Registers");
	printf("\n");

	errs	= gsc_reg_list(fd, _plx, 0);

	return(errs);
}



//*****************************************************************************
const char* gsc_reg_plx9056_get_desc(unsigned long reg)
{
	const gsc_reg_def_t*	def;
	const char*				desc;

	def	= _find_reg(reg, _pci);

	if (def == NULL)
		def	= _find_reg(reg, _plx);

	if (def)
		desc	= def->desc;
	else
		desc	= "UNKNOWN";

	return(desc);
}



//*****************************************************************************
const char* gsc_reg_plx9056_get_name(unsigned long reg)
{
	const gsc_reg_def_t*	def;
	const char*				name;

	def	= _find_reg(reg, _pci);

	if (def == NULL)
		def	= _find_reg(reg, _plx);

	if (def)
		name	= def->name;
	else
		name	= "UNKNOWN";

	return(name);
}


