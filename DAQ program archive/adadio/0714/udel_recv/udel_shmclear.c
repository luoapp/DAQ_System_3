
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <linux/types.h>
#include "udel_daq.h"
#include "udel_ipc.h"

/******************************************************************************/

int main( void){

	int msqid;
	key_t key; 
    key_t mem_key[MAXBUFFERNUM];
    int shmid[MAXBUFFERNUM];
    __u32 *data[MAXBUFFERNUM];
    int ix;
    //int mode;

    for (ix = 0; ix < MAXBUFFERNUM; ix++) {
	    if ((mem_key[ix] = ftok(IPC_shmem_path[ix], 'R')) == -1) {
        	perror("ftok");
        	exit(1);
	    }	

	    if ((shmid[ix] = shmget(mem_key[ix], SHMLBA, 0644 | IPC_CREAT)) == -1) {
        	perror("shmget");
			printf("ix = %d\n",ix);
        	exit(1);
	    }

	    data[ix] = shmat(shmid[ix], (void *)0, 0);
	    if (data[ix] == (char *)(-1)) {
        	perror("shmat");
        	exit(1);
	    }
    }

	if ((key = ftok(IPC_msg_path, 'B')) == -1) {
        	perror("ftok");
        	exit(1);
    	}

	if ((msqid = msgget(key, 0644 | IPC_CREAT)) == -1) {
        	perror("msgget");
        	exit(1);
	}
    
	if (msgctl(msqid, IPC_RMID, NULL) == -1) 
	{
        	perror("msgctl");
	        exit(1);
	}

	for (ix = 0; ix<MAXBUFFERNUM; ix++)
	{
		if (shmdt(data[ix]) == -1) 
		{
	        	perror("shmdt");
	        	exit(1);
    		}
		if (shmctl(shmid[ix], IPC_RMID, NULL) == -1) 
		{
			perror("shmctl");
			exit(1);
		}
    	}
	return 0;
}


