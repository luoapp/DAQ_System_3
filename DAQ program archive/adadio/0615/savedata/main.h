// $URL: http://subversion:8080/svn/gsc/trunk/drivers/LINUX/ADADIO/ADADIO_Linux_3.x.x.x_GSC_DN/savedata/main.h $
// $Rev: 1620 $
// $Date: 2009-04-10 11:41:41 -0500 (Fri, 10 Apr 2009) $

#ifndef __MAIN_H__
#define __MAIN_H__

#include "adadio.h"
#include "adadio_dsl.h"
#include "adadio_utils.h"
#include "gsc_utils.h"



// #defines	*******************************************************************

#define	VERSION			"1.0"
// 1.0	Initial release.
 


// prototypes	***************************************************************

int	save_data(int fd, __s32 io_mode);
int _channels(int fd, __s32* chans);
int _save_data(int fd, int chans, int errs);
int _read_data(int fd);
#endif
