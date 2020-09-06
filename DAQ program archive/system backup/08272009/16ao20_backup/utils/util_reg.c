// $URL: http://subversion:8080/svn/gsc/trunk/drivers/LINUX/16AO20/16AO20_Linux_2.x.x.x_GSC_DN/utils/util_reg.c $
// $Rev: 2014 $
// $Date: 2009-05-19 12:39:09 -0500 (Tue, 19 May 2009) $

#include <stdio.h>
#include <sys/ioctl.h>

#include "16ao20_dsl.h"
#include "16ao20_utils.h"
#include "gsc_utils.h"



// #defines	*******************************************************************

#define	_GSC_REG(a)		"GSC " #a, AO20_GSC_##a
#define	LABEL_WIDTH		18
#define	NAME_WIDTH		21



/* prototypes	*************************************************************/

static int	_0x00_decode_bcr	(int fd, int supported, __u32 value, int width);
static int	_0x04_decode_csr	(int fd, int supported, __u32 value, int width);
static int	_0x08_decode_srr	(int fd, int supported, __u32 value, int width);
static int	_0x0c_decode_bor	(int fd, int supported, __u32 value, int width);
static int	_0x10_decode_for	(int fd, int supported, __u32 value, int width);
static int	_0x1c_decode_acr	(int fd, int supported, __u32 value, int width);



// variables	***************************************************************

static gsc_reg_def_t	_gsc[]	=
{
	// name	reg			err	value	ask_support	decode				desc
	{ _GSC_REG(BCR),	0,	0,		0,			_0x00_decode_bcr,	"Board Control Register"		},
	{ _GSC_REG(CSR),	0,	0,		0,			_0x04_decode_csr,	"Channel Selection Register"	},
	{ _GSC_REG(SRR),	0,	0,		0,			_0x08_decode_srr,	"Sample Rate Register"			},
	{ _GSC_REG(BOR),	0,	0,		0,			_0x0c_decode_bor,	"Buffer Operations Register"	},
	{ _GSC_REG(FOR),	0,	0,		0,			_0x10_decode_for,	"Firmware Options Register"		},
	{ _GSC_REG(AVR),	0,	0,		0,			NULL,				"Autocal Values Register"		},
	{ _GSC_REG(ODBR),	0,	0,		0,			NULL,				"Output Data Buffer Register"	},
	{ _GSC_REG(ACR),	0,	0,		0,			_0x1c_decode_acr,	"Adjustable Clock Register"		},
	{ NULL }
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
static int _0x00_decode_bcr(int fd, int supported, __u32 value, int width)
{
	static const char*	acal[]	= { "Done",					"In Progress"			};
	static const char*	brst[]	= { "Enabled (External)",	"Disabled (Software)"	};
	static const char*	bufm[]	= { "Sequential",			"Simultaneous"			};
	static const char*	disa[]	= { "Disable",				"Enable"				};
	static const char*	idle[]	= { "Idle",					"Active"				};
	static const char*	init[]	= { "Idle",					"Initializing"			};
	static const char*	irqf[]	= { "Inactive",				"Active"				};
	static const char*	offb[]	= { "No (Twos Compliment)",	"Yes (Offset Binary)"	};
	static const char*	outm[]	= { "Continuous",			"Trigger Burst"			};
	static const char*	pass[]	= { "Pass",					"Fail"					};
	static const char*	redy[]	= { "Idle",					"Ready"					};
	static const char*	xcvr[]	= { "TTL",					"LVDS"					};

	static const char*	irq[]	=
	{
		"Initialization Completed",
		"Autocall Completed",
		"Buffer Empty",
		"Buffer Low Quarter (<1/4 full)",
		"Buffer High Quarter (>3/4 full)",
		"Burst Trigger Ready",
		"Load Ready (low-to-high)",
		"End Load Ready (high-to-low)"
	};

	gsc_reg_field_show(LABEL_WIDTH, NAME_WIDTH, value, 31, 16, 1, NULL,	"Reserved"				);
	gsc_reg_field_show(LABEL_WIDTH, NAME_WIDTH, value, 15, 15, 1, init,	"Initialize"			);
	gsc_reg_field_show(LABEL_WIDTH, NAME_WIDTH, value, 14, 14, 1, pass,	"AutoCal Status"		);
	gsc_reg_field_show(LABEL_WIDTH, NAME_WIDTH, value, 13, 13, 1, acal,	"AutoCal"				);
	gsc_reg_field_show(LABEL_WIDTH, NAME_WIDTH, value, 12, 12, 1, NULL,	"Reserved"				);
	gsc_reg_field_show(LABEL_WIDTH, NAME_WIDTH, value, 11, 11, 1, irqf,	"Int Request Flag"		);
	gsc_reg_field_show(LABEL_WIDTH, NAME_WIDTH, value, 10,  8, 1, irq,	"Interrupt"				);
	gsc_reg_field_show(LABEL_WIDTH, NAME_WIDTH, value,  7,  7, 1, bufm,	"Buffer Mode"			);
	gsc_reg_field_show(LABEL_WIDTH, NAME_WIDTH, value,  6,  6, 1, brst,	"Ext Burst Trigger"		);
	gsc_reg_field_show(LABEL_WIDTH, NAME_WIDTH, value,  5,  5, 1, xcvr,	"Transceivers"			);
	gsc_reg_field_show(LABEL_WIDTH, NAME_WIDTH, value,  4,  4, 1, offb,	"Offset Binary"			);
	gsc_reg_field_show(LABEL_WIDTH, NAME_WIDTH, value,  3,  3, 1, disa,	"Remote Ground Sense"	);
	gsc_reg_field_show(LABEL_WIDTH, NAME_WIDTH, value,  2,  2, 1, idle,	"Burst Trigger"			);
	gsc_reg_field_show(LABEL_WIDTH, NAME_WIDTH, value,  1,  1, 1, redy,	"Burst Ready"			);
	gsc_reg_field_show(LABEL_WIDTH, NAME_WIDTH, value,  0,  0, 1, outm,	"Burst Enable"			);

	return(0);
}



//*****************************************************************************
static int _0x04_decode_csr(int fd, int supported, __u32 value, int width)
{
	static const char*	idle[]	= { "Idle", "Active" };

	__s32	chans;
	int		ret;

	gsc_reg_field_show(LABEL_WIDTH, NAME_WIDTH, value,  31, 20, 1, NULL, "Reserved");

	ret	= ao20_query(fd, AO20_QUERY_CHANNEL_QTY, &chans);

	if (chans > 12)
	{
		gsc_reg_field_show(LABEL_WIDTH, NAME_WIDTH, value,  19, 19, 1, idle, "Channel 19");
		gsc_reg_field_show(LABEL_WIDTH, NAME_WIDTH, value,  18, 18, 1, idle, "Channel 18");
		gsc_reg_field_show(LABEL_WIDTH, NAME_WIDTH, value,  17, 17, 1, idle, "Channel 17");
		gsc_reg_field_show(LABEL_WIDTH, NAME_WIDTH, value,  16, 16, 1, idle, "Channel 16");
		gsc_reg_field_show(LABEL_WIDTH, NAME_WIDTH, value,  15, 15, 1, idle, "Channel 15");
		gsc_reg_field_show(LABEL_WIDTH, NAME_WIDTH, value,  14, 14, 1, idle, "Channel 14");
		gsc_reg_field_show(LABEL_WIDTH, NAME_WIDTH, value,  13, 13, 1, idle, "Channel 13");
		gsc_reg_field_show(LABEL_WIDTH, NAME_WIDTH, value,  12, 12, 1, idle, "Channel 12");
	}
	else
	{
		gsc_reg_field_show(LABEL_WIDTH, NAME_WIDTH, value,  19, 13, 1, NULL, "Reserved");
	}

	if (chans > 6)
	{
		gsc_reg_field_show(LABEL_WIDTH, NAME_WIDTH, value,  11, 11, 1, idle, "Channel 11");
		gsc_reg_field_show(LABEL_WIDTH, NAME_WIDTH, value,  10, 10, 1, idle, "Channel 10");
		gsc_reg_field_show(LABEL_WIDTH, NAME_WIDTH, value,   9,  9, 1, idle, "Channel 9");
		gsc_reg_field_show(LABEL_WIDTH, NAME_WIDTH, value,   8,  8, 1, idle, "Channel 8");
		gsc_reg_field_show(LABEL_WIDTH, NAME_WIDTH, value,   7,  7, 1, idle, "Channel 7");
		gsc_reg_field_show(LABEL_WIDTH, NAME_WIDTH, value,   6,  6, 1, idle, "Channel 6");
	}
	else
	{
		gsc_reg_field_show(LABEL_WIDTH, NAME_WIDTH, value,  12, 7, 1, NULL, "Reserved");
	}

	gsc_reg_field_show(LABEL_WIDTH, NAME_WIDTH, value, 5, 5, 1, idle, "Channel 5");
	gsc_reg_field_show(LABEL_WIDTH, NAME_WIDTH, value, 4, 4, 1, idle, "Channel 4");
	gsc_reg_field_show(LABEL_WIDTH, NAME_WIDTH, value, 3, 3, 1, idle, "Channel 3");
	gsc_reg_field_show(LABEL_WIDTH, NAME_WIDTH, value, 2, 2, 1, idle, "Channel 2");
	gsc_reg_field_show(LABEL_WIDTH, NAME_WIDTH, value, 1, 1, 1, idle, "Channel 1");
	gsc_reg_field_show(LABEL_WIDTH, NAME_WIDTH, value, 0, 0, 1, idle, "Channel 0");

	return(ret);
}



//*****************************************************************************
static int _0x08_decode_srr(int fd, int supported, __u32 value, int width)
{
	__u32	v;

	gsc_reg_field_show(LABEL_WIDTH, NAME_WIDTH, value, 31, 16, 1, NULL, "Reserved");

	gsc_reg_field_show(LABEL_WIDTH, NAME_WIDTH, value,  15, 0, 0, NULL, "Nrate"		);
	v	= GSC_FIELD_DECODE(value, 15, 0);
	gsc_label_long_comma(v);
	printf("\n");
	return(0);
}



//*****************************************************************************
static int _0x0c_decode_bor(int fd, int supported, __u32 value, int width)
{
	static const char*	idle[]	= { "Idle",				"Active"			};
	static const char*	no[]	= { "No",				"Yes"				};
	static const char*	no_1[]	= { "No (>= 1/4)",		"Yes (< 1/4)"		};
	static const char*	no_3[]	= { "No (<= 3/4)",		"Yes (> 3/4)"		};
	static const char*	no_d[]	= { "No (Disabled)",	"Yes (Enabled)"		};
	static const char*	no_o[]	= { "No (Open)",		"Yes (Circular)"	};
	static const char*	no_x[]	= { "No (Internal)",	"Yes (External/SW)"	};

	static const char*	size[]	=
	{
		"8 Samples",
		"16 Samples",
		"32 Samples",
		"64 Samples",
		"128 Samples",
		"256 Samples",
		"512 Samples",
		"1K Samples",
		"2K Samples",
		"4K Samples",
		"8K Samples",
		"16K Samples",
		"32K Samples",
		"64K Samples",
		"128K Samples",
		"256K Samples"
	};

	gsc_reg_field_show(LABEL_WIDTH, NAME_WIDTH, value, 31, 18, 1, NULL,	"Reserved"				);
	gsc_reg_field_show(LABEL_WIDTH, NAME_WIDTH, value, 17, 17, 1, no,	"Frame Overflow"		);
	gsc_reg_field_show(LABEL_WIDTH, NAME_WIDTH, value, 16, 16, 1, no,	"Buffer Overflow"		);
	gsc_reg_field_show(LABEL_WIDTH, NAME_WIDTH, value, 15, 15, 1, no,	"Buffer Full"			);
	gsc_reg_field_show(LABEL_WIDTH, NAME_WIDTH, value, 14, 14, 1, no_3,	"Buffer High Quarter"	);
	gsc_reg_field_show(LABEL_WIDTH, NAME_WIDTH, value, 13, 13, 1, no_1,	"Buffer Low Quarter"	);
	gsc_reg_field_show(LABEL_WIDTH, NAME_WIDTH, value, 12, 12, 1, no,	"Buffer Empty"			);
	gsc_reg_field_show(LABEL_WIDTH, NAME_WIDTH, value, 11, 11, 1, idle,	"Clear Buffer"			);
	gsc_reg_field_show(LABEL_WIDTH, NAME_WIDTH, value, 10, 10, 1, no,	"Load Ready"			);
	gsc_reg_field_show(LABEL_WIDTH, NAME_WIDTH, value,  9,  9, 1, no,	"Load Request"			);
	gsc_reg_field_show(LABEL_WIDTH, NAME_WIDTH, value,  8,  8, 1, no_o,	"Circular Buffer"		);
	gsc_reg_field_show(LABEL_WIDTH, NAME_WIDTH, value,  7,  7, 1, idle,	"SW Clock"				);
	gsc_reg_field_show(LABEL_WIDTH, NAME_WIDTH, value,  6,  6, 1, no,	"Clock Ready"			);
	gsc_reg_field_show(LABEL_WIDTH, NAME_WIDTH, value,  5,  5, 1, no_d,	"Enable Clock"			);
	gsc_reg_field_show(LABEL_WIDTH, NAME_WIDTH, value,  4,  4, 1, no_x,	"External Clock"		);
	gsc_reg_field_show(LABEL_WIDTH, NAME_WIDTH, value,  3,  0, 1, size,	"Buffer Size"			);

	return(0);
}



//*****************************************************************************
static int _0x10_decode_for(int fd, int supported, __u32 value, int width)
{
	static const char*	chan[]	=
	{
		"6 Channels",
		"12 Channels",
		"20 Channels",
		"RESERVED"
	};

	static const char*	filt[]	=
	{
		"No Filter",
		"10K Hz",
		"100K Hz",
		"RESERVED"
	};

	static const char*	volt[]	=
	{
		"+-2.5 V",
		"+-5 V",
		"+-10 V",
		"RESERVED"
	};

	__u32	v;

	gsc_reg_field_show(LABEL_WIDTH, NAME_WIDTH, value, 31, 22, 1, NULL,	"Reserved"			);
	gsc_reg_field_show(LABEL_WIDTH, NAME_WIDTH, value, 21, 20, 1, chan,	"Output Channels"	);
	gsc_reg_field_show(LABEL_WIDTH, NAME_WIDTH, value, 19, 18, 1, filt,	"Filter Frequency"	);
	gsc_reg_field_show(LABEL_WIDTH, NAME_WIDTH, value, 17, 16, 1, volt,	"Voltage Range"		);
	gsc_reg_field_show(LABEL_WIDTH, NAME_WIDTH, value, 15, 12, 1, NULL,	"Reserved"			);

	gsc_reg_field_show(LABEL_WIDTH, NAME_WIDTH, value, 11,  0, 0, NULL,	"Firmware Version"	);
	v	= GSC_FIELD_DECODE(value, 11, 0);
	printf("Version %03lX\n", (long) v);

	return(0);
}



//*****************************************************************************
static int _0x1c_decode_acr(int fd, int supported, __u32 value, int width)
{
	static const char*	alt[]	= { "No (Primary)", "Yes (Alternate)" };

	long	ref;
	__u32	v;

	gsc_reg_field_show(LABEL_WIDTH, NAME_WIDTH, value, 31, 10, 1, NULL,	"Reserved"				);
	gsc_reg_field_show(LABEL_WIDTH, NAME_WIDTH, value,  9,  9, 1, alt,	"Alternate Reference"	);

	gsc_reg_field_show(LABEL_WIDTH, NAME_WIDTH, value,  8,  0, 0, NULL,	"Nclk"					);
	v	= GSC_FIELD_DECODE(value, 8, 0);
	ref	= (long) (16000000.0 * (1.0 + (1.0 * v) / 511));
	gsc_label_long_comma(v);
	printf(" (AltRef = ");
	gsc_label_long_comma(ref);
	printf(" Hz)\n");
	return(0);
}



/*****************************************************************************
*
*	Function:	ao20_reg_list
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

int ao20_reg_list(int fd, int detail)
{
	int	errs;

	errs	= gsc_reg_list(fd, _gsc, detail);
	return(errs);
}



/*****************************************************************************
*
*	Function:	ao20_reg_name
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

const char* ao20_reg_name(int fd, __u32 reg)
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
	i			= ioctl(fd, AO20_IOCTL_REG_READ, &parm);

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
	i			= ioctl(fd, AO20_IOCTL_REG_WRITE, &parm);
	errs		= (i == -1) ? 1 : 0;
	return(errs);
}


