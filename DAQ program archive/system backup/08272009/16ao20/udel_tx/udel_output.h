// $URL: http://subversion:8080/svn/gsc/trunk/drivers/LINUX/16AO20/16AO20_Linux_2.x.x.x_GSC_DN/aout/main.h $
// $Rev: 2014 $
// $Date: 2009-05-19 12:39:09 -0500 (Tue, 19 May 2009) $

#ifndef __MAIN_H__
#define __MAIN_H__

#include <asm/types.h>
#include <sys/ioctl.h>

#include "16ao20.h"
#include "16ao20_dsl.h"
#include "16ao20_utils.h"
#include "gsc_utils.h"
#include "udel_daq.h"


/* #defines	**************************************************************/

#define	VERSION				"1.0"
// 1.00	Initial release.



/* prototypes	**************************************************************/

int	aio_out(int fd, int seconds, UDELctl udelctl);
__u32 * udelreaddatafromfile(UDELctl udelctl, long int * buffer_size_inbyte);


#endif
