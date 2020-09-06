// $URL: http://subversion:8080/svn/gsc/trunk/drivers/LINUX/ADADIO/ADADIO_Linux_3.x.x.x_GSC_DN/docsrc/adadio_dsl.h $
// $Rev: 1620 $
// $Date: 2009-04-10 11:41:41 -0500 (Fri, 10 Apr 2009) $

#ifndef __ADADIO_DSL_H__
#define __ADADIO_DSL_H__

#include <fcntl.h>

#include "adadio.h"



/* prototypes	**************************************************************/

int	adadio_dsl_close(int fd);
int	adadio_dsl_ioctl(int fd, int request, void *arg);
int	adadio_dsl_open(unsigned int board);
int	adadio_dsl_read(int fd, __u32 *buf, size_t samples);



#endif
