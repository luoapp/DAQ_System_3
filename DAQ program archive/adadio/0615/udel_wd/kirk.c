/*
** kirk.c -- writes to a message queue
*/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <unistd.h>
#include "udel_ipc.h"
#include "udel_daq.h" 

int main(void)
{
    struct my_msgbuf buf;
    int msqid;
    key_t key;



    key_t mem_key[MAXBUFFERNUM];
    int shmid[MAXBUFFERNUM];
    char *data[MAXBUFFERNUM];
    int ix;
    //int mode;
    for ( ix = 3; ix<100; ix++){
    data[0] = malloc(1024l*1024l*ix*10);
    printf("%d0M ", ix); 
    if (data[0]==NULL) 
      {printf("malloc error\n"); break;}
    else printf("success\n");
    free(data[0]);
    }
    return 0;
    for (ix = 0; ix < MAXBUFFERNUM; ix++) {
	    if ((mem_key[ix] = ftok(IPC_shmem_path[ix], 'R')) == -1) {
        	perror("ftok");
        	exit(1);
	    }	

	    if ((shmid[ix] = shmget(mem_key[ix], SHM_SIZE, 0644 | IPC_CREAT)) == -1) {
        	perror("shmget");
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
    
    printf("Enter lines of text, ^D to quit:\n");

    buf.mtype = 1; /* we don't really care in this case */
    ix = 0;
     while(gets(data[ix]), !feof(stdin)) {
	//while(ix < 10){
	//sleep(1);
	buf.mtext[0] = ix +48 ;
	buf.mtext[1] = '\0';
        if (msgsnd(msqid, (struct msgbuf *)&buf, sizeof(buf), 0) == -1)
            perror("msgsnd");
        ix++;
        ix = ix % MAXBUFFERNUM;
    }

    if (msgctl(msqid, IPC_RMID, NULL) == -1) {
        perror("msgctl");
        exit(1);
    }

    for (ix = 0; ix<MAXBUFFERNUM; ix++){
    if (shmdt(data[ix]) == -1) {
        perror("shmdt");
        exit(1);
    }
    

    if (shmctl(shmid[ix], IPC_RMID, NULL) == -1) {
	perror("shmctl");
	

	exit(1);
    }
    }
//    printf("shmctl\n");
    return 0;
}

