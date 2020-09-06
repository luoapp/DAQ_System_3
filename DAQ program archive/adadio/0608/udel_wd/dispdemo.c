
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <linux/types.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <unistd.h>

#include "udel_daq.h"
#include "udel_ipc.h" 

int main (void)
{
	UDELxwin uxwin;
	udelxwininit( &uxwin );
	getchar();
	return 0; 
}
