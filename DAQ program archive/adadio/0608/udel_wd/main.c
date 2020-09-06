#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

    struct my_msgbuf {
        long mtype;
        char mtext[200];
    };


int main (void){
/*
	FILE *f;
	char buffer[1024*1024];
	f = fopen("/daqsbc/data/d1.dat","w+");
	int i;
	for ( i = 0; i<2000; i++)
	{
		fwrite( buffer, sizeof(buffer), 1, f);
	}
	fclose(f);
*/
        struct my_msgbuf buf;
        int msqid;
        key_t key;
	struct msqid_ds msqid_ds, *idbuf;
        idbuf = & msqid_ds;

       if ((key = ftok("../kirk.c", 'B')) == -1) {  /* same key as kirk.c */
            perror("ftok");
            exit(1);
        }

        if ((msqid = msgget(key, 0644)) == -1) { /* connect to the queue */
            perror("msgget");
            exit(1);
        }
        
        printf("spock: ready to receive messages, captain.\n");
	msgctl(msqid, IPC_STAT, idbuf);

        for(;;) { /* Spock never quits! */
//		while(idbuf->msg_qnum < 1)msgctl(msqid, IPC_STAT, idbuf);


//		msgrcv(msqid, (struct msgbuf *)&buf, sizeof(buf), 1, 0);

           if (msgrcv(msqid, (struct msgbuf *)&buf, sizeof(buf), 1, 0) == -1) {
                perror("msgrcv");
		printf("error\n");
                exit(1);
            }
            printf("%d \n",  (int)buf.mtext[0]);
        }

        return 0;


}
