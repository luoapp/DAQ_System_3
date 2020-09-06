// $URL: http://subversion:8080/svn/gsc/trunk/drivers/LINUX/ADADIO/ADADIO_Linux_3.x.x.x_GSC_DN/id/main.h $
// $Rev: 1620 $
// $Date: 2009-04-10 11:41:41 -0500 (Fri, 10 Apr 2009) $

#ifndef __MAIN_H__
#define __MAIN_H__

#include "adadio.h"
#include "adadio_utils.h"
#include "gsc_utils.h"



// #defines	*******************************************************************

#define	VERSION			"1.1"
// 1.1	Corrected the output of the FRR's Firmware Revision field value.
// 1.0	Initial release.



// prototypes	***************************************************************

int	id_device(int fd);



#endif
