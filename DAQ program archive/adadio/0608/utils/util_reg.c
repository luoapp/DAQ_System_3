// $URL: http://subversion:8080/svn/gsc/trunk/drivers/LINUX/ADADIO/ADADIO_Linux_3.x.x.x_GSC_DN/utils/util_reg.c $
// $Rev: 1620 $
// $Date: 2009-04-10 11:41:41 -0500 (Fri, 10 Apr 2009) $

#include <stdio.h>
#include <sys/ioctl.h>

#include "adadio_dsl.h"
#include "adadio_utils.h"
#include "gsc_utils.h"



// #defines	*******************************************************************

#define	_GSC_REG(a)		"GSC " #a, ADADIO_GSC_##a, 0, 0
#define	LABEL_WIDTH		13



// variables	***************************************************************

static	int	nw		= 24;	// Name Width



//*****************************************************************************
static int _brr_decode(int fd, int supported, __u32 value, int width)
{
	gsc_reg_field_show(width, nw, value, 31, 17, 1, NULL, "Reserved"			);
	gsc_reg_field_show(width, nw, value, 16,  0, 1, NULL, "Firmware Revision"	);
	return(0);
}



//*****************************************************************************
static int _bcr_decode(int fd, int supported, __u32 value, int width)
{
	static const char*	aim[]	=
	{
		"Single Ended, Continuous",
		"Single Ended, Burst",
		"Differential, Continuous",
		"Differential, Burst",
		"Loop Back Test",
		"+Vref Test",
		"RESERVED",
		"Zero Test"
	};

	static const char*	cal_mode[]	=
	{
		"Normal",
		"Load from EEPROM",
		"Auto-Calibration",
		"RESERVED"
	};

	static const char*	irq[]	=
	{
		"Initialization Done",
		"Auto-Calibration Done",
		"Input Buffer Empty",
		"Input Buffer Half Full",
		"Input Buffer Full",
		"Input Burst Done",
		"Output Strobe Done",
		"RESERVED"
	};

	static const char*	last[]	=
	{
		"0",
		"1",
		"2",
		"3",
		"4",
		"5",
		"6",
		"7"
	};

	static const char*	lbc[]	=
	{
		"Output Channel 0",
		"Output Channel 1",
		"Output Channel 2",
		"Output Channel 3"
	};

	static const char*	size[]	=
	{
		"1",
		"2",
		"4",
		"8",
		"16",
		"32",
		"64",
		"128",
		"256",
		"512",
		"1024",
		"2048",
		"4096",
		"8192",
		"16384",
		"32768"
	};

	static const char*	disable[]	= { "Disable",			"Enable"		};
	static const char*	idle[]		= { "Idle",				"Active"		};
	static const char*	negated[]	= { "Negated",			"Asserted"		};
	static const char*	no[]		= { "No",				"Yes"			};
	static const char*	no_dis[]	= { "No (Disabled)",	"Yes (Enabled)"	};
	static const char*	pass[]		= { "Pass",				"Fail"			};
	static const char*	twos[]		= { "Twos Compliment",	"Offset Binary"	};

	gsc_reg_field_show(width, nw, value, 31, 31, 1, idle,		"Initialize"				);
	gsc_reg_field_show(width, nw, value, 30, 30, 1, idle,		"Input Trigger"				);
	gsc_reg_field_show(width, nw, value, 29, 29, 1, idle,		"Output Strobe"				);
	gsc_reg_field_show(width, nw, value, 28, 27, 1, cal_mode,	"Calibration Mode"			);
	gsc_reg_field_show(width, nw, value, 26, 26, 1, negated,	"IRQ Status"				);
	gsc_reg_field_show(width, nw, value, 25, 23, 1, irq,		"IRQ Select"				);
	gsc_reg_field_show(width, nw, value, 22, 22, 1, no,			"Input Buffer Full"			);
	gsc_reg_field_show(width, nw, value, 21, 21, 1, no,			"Input Buffer Half Full"	);
	gsc_reg_field_show(width, nw, value, 20, 20, 1, no,			"Input Buffer Empty"		);
	gsc_reg_field_show(width, nw, value, 19, 19, 1, no_dis,		"Output Strobe Enable"		);
	gsc_reg_field_show(width, nw, value, 18, 18, 1, disable,	"Output Enable"				);
	gsc_reg_field_show(width, nw, value, 17, 15, 1, last,		"Last Channel"				);
	gsc_reg_field_show(width, nw, value, 14, 12, 1, NULL,		"Reserved"					);
	gsc_reg_field_show(width, nw, value, 11, 11, 1, idle,		"Clear Buffer"				);
	gsc_reg_field_show(width, nw, value, 10,  7, 1, size,		"Buffer Size"				);
	gsc_reg_field_show(width, nw, value,  6,  6, 1, twos,		"Data Format"				);
	gsc_reg_field_show(width, nw, value,  5,  5, 1, pass,		"Auto-Cal Status"			);
	gsc_reg_field_show(width, nw, value,  4,  3, 1, lbc,		"Loop Back Channel"			);
	gsc_reg_field_show(width, nw, value,  2,  0, 1, aim,		"Analog Input Mode"			);

	return(0);
}



//*****************************************************************************
static int _diopr_decode(int fd, int supported, __u32 value, int width)
{
	static const char*	input[]	= { "Input",		"Output"	};
	static const char*	zero[]	= { "0 (Clear)",	"1 (Set)"	};

	gsc_reg_field_show(width, nw, value, 31, 11, 1, NULL,	"Reserved"			);
	gsc_reg_field_show(width, nw, value, 10, 10, 1, input,	"Data Direction"	);
	gsc_reg_field_show(width, nw, value,  9,  9, 1, zero,	"Dedicated Output"	);
	gsc_reg_field_show(width, nw, value,  8,  8, 1, zero,	"Dedicated Input"	);
	gsc_reg_field_show(width, nw, value,  7,  0, 1, NULL,	"I/O Data"			);

	return(0);
}



//*****************************************************************************
static int _aocr_decode(int fd, int supported, __u32 value, int width)
{
	gsc_reg_field_show(width, nw, value, 31, 16, 1, NULL,	"Inactive"	);
	gsc_reg_field_show(width, nw, value, 15,  0, 1, NULL,	"Data"		);

	return(0);
}



//*****************************************************************************
static int _aidr_decode(int fd, int supported, __u32 value, int width)
{
	gsc_reg_field_show(width, nw, value, 31, 16, 1, NULL,	"Extension"	);
	gsc_reg_field_show(width, nw, value, 15,  0, 1, NULL,	"Data"		);

	return(0);
}



//*****************************************************************************
static int _srr_decode(int fd, int supported, __u32 value, int width)
{
	gsc_reg_field_show(width, nw, value, 31, 16, 1, NULL,	"Inactive"	);
	gsc_reg_field_show(width, nw, value, 15,  0, 1, NULL,	"Nrate"		);

	return(0);
}



// variables	***************************************************************

static gsc_reg_def_t	_gsc[]	=
{
	{ _GSC_REG(BRR),	0,	_brr_decode,	"Board Revision Register"		},
	{ _GSC_REG(BCR),	0,	_bcr_decode,	"Board Control Register"		},
	{ _GSC_REG(DIOPR),	0,	_diopr_decode,	"Digital I/O Port Register"		},
	{ _GSC_REG(AOC0R),	0,	_aocr_decode,	"Analog Output Ch 0 Register"	},
	{ _GSC_REG(AOC1R),	0,	_aocr_decode,	"Analog Output Ch 1 Register"	},
	{ _GSC_REG(AOC2R),	0,	_aocr_decode,	"Analog Output Ch 2 Register"	},
	{ _GSC_REG(AOC3R),	0,	_aocr_decode,	"Analog Output Ch 3 Register"	},
	{ _GSC_REG(AIDR),	0,	_aidr_decode,	"Analog Input Data Register"	},
	{ _GSC_REG(SRR),	0,	_srr_decode,	"Sample Rate Register"			},

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



/*****************************************************************************
*
*	Function:	adadio_reg_get_def_index
*
*	Purpose:
*
*		Retrieve the register definition structure based on an index.
*
*	Arguments:
*
*		index	The index of the register to access.
*
*	Returned:
*
*		NULL	The index doesn't correspond to a known register.
*		else	A pointer to the register definition.
*
*****************************************************************************/

const gsc_reg_def_t* adadio_reg_get_def_index(int index)
{
	const gsc_reg_def_t*	def;

	if (index < 0)
		def	= NULL;
	else if (index >= (ARRAY_ELEMENTS(_gsc) - 1))
		def	= NULL;
	else
		def	= &_gsc[index];

	return(def);
}



/*****************************************************************************
*
*	Function:	adadio_reg_get_desc
*
*	Purpose:
*
*		Retrieve the description of the specified register.
*
*	Arguments:
*
*		The register whose description is desired.
*
*	Returned:
*
*		The register's name.
*
*****************************************************************************/

const char* adadio_reg_get_desc(unsigned long reg)
{
	const gsc_reg_def_t*	def;
	const char*				desc;

	def	= _find_reg(reg, _gsc);

	if (def)
		desc	= def->desc;
	else
		desc	= "UNKNOWN";

	return(desc);
}



/*****************************************************************************
*
*	Function:	adadio_reg_get_name
*
*	Purpose:
*
*		Retrieve the name of the specified register.
*
*	Arguments:
*
*		The register whose name is desired.
*
*	Returned:
*
*		The register's name.
*
*****************************************************************************/

const char* adadio_reg_get_name(unsigned long reg)
{
	const gsc_reg_def_t*	def;
	const char*				name;

	def	= _find_reg(reg, _gsc);

	if (def)
		name	= def->name;
	else
		name	= "UNKNOWN";

	return(name);
}



/*****************************************************************************
*
*	Function:	adadio_reg_list
*
*	Purpose:
*
*		List the GSC registers and their values.
*
*	Arguments:
*
*		fd		The handle to access the device.
*
*		detail	List the register details?
*
*	Returned:
*
*		>= 0	The number of errors encountered here.
*
*****************************************************************************/

int adadio_reg_list(int fd, int detail)
{
	int	errs;

	errs	= gsc_reg_list(fd, _gsc, detail);
	return(errs);
}



/*******************************************************************************
*
*	Function:	gsc_dev_reg_read
*
*	Purpose:
*
*		Read a device register.
*
*	Arguments:
*
*		fd		The handles to access all four channels.
*
*		reg		The register to access.
*
*		value	The value read goes here.
*
*	Returned:
*
*		>= 0	The number of errors encountered here.
*
*******************************************************************************/

int gsc_dev_reg_read(int fd, __u32 reg, __u32* value)
{
	int			errs;
	int			i;
	gsc_reg_t	parm;

	parm.reg	= reg;
	parm.value	= 0xDEADBEEF;
	parm.mask	= 0;	// Unused here.
	i			= ioctl(fd, ADADIO_IOCTL_REG_READ, &parm);

	if (value)
		value[0]	= parm.value;

	errs	= (i == -1) ? 1 : 0;
	return(errs);
}



/*******************************************************************************
*
*	Function:	gsc_dev_reg_write
*
*	Purpose:
*
*		Write to a device register.
*
*	Arguments:
*
*		fd		The handles to access all four channels.
*
*		reg		The register to access.
*
*		value	The value read goes here.
*
*	Returned:
*
*		>= 0	The number of errors encountered here.
*
*******************************************************************************/

int gsc_dev_reg_write(int fd, __u32 reg, __u32 value)
{
	int			errs;
	int			i;
	gsc_reg_t	parm;

	parm.reg	= reg;
	parm.value	= value;
	parm.mask	= 0;	// Unused here.
	i			= ioctl(fd, ADADIO_IOCTL_REG_WRITE, &parm);
	errs		= (i == -1) ? 1 : 0;
	return(errs);
}


