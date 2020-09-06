// $URL: http://subversion:8080/svn/gsc/trunk/drivers/LINUX/16AO20/16AO20_Linux_2.x.x.x_GSC_DN/docsrc/16ao20_dsl.h $
// $Rev: 2014 $
// $Date: 2009-05-19 12:39:09 -0500 (Tue, 19 May 2009) $

#ifndef __16AO20_DSL_H__
#define __16AO20_DSL_H__

#include <unistd.h>

#include "16ao20.h"



// prototypes	***************************************************************

int	ao20_dsl_close(int fd);
int	ao20_dsl_ioctl(int fd, int request, void *arg);
int	ao20_dsl_open(unsigned int board);
int	ao20_dsl_write(int fd, const __u32 *buf, size_t samples);



#endif
