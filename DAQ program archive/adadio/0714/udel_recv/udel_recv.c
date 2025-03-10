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


int main(int argc, char **argv)
{
	struct my_msgbuf buf;
	int msqid;
	key_t key;

	key_t mem_key[MAXBUFFERNUM];
	int shmid[MAXBUFFERNUM];
	__u32 *data[MAXBUFFERNUM];
	__u16 *datas;
	float *dataf;
	//int mode;
	int ix;

	nice(20);

	DaqBoard board;
	udelboardinit( &board, gscADADIO );
	UDELctl udelctl;
	udelctlinit( &udelctl);
	udelargparser(argc, argv, &board, &udelctl );

	UDELxwin uxwin;
	if ( udelctl.flag_disp == 1)udelxwininit( &uxwin );

	for(;;) {
		if ((key = ftok(IPC_msg_path, 'B')) == -1) {  
			perror("ftok");
			sleep(1);
			continue;
		}

		if ((msqid = msgget(key, 0644)) == -1) { 
			perror("msgget");
			sleep(1);
			continue;
		}
 


		for (ix = 0; ix < MAXBUFFERNUM; ix++) {
			if ((mem_key[ix] = ftok(IPC_shmem_path[ix], 'R')) == -1) {
				perror("ftok");
				exit(1);
			}	

			if ((shmid[ix] = shmget(mem_key[ix], BUFFERSIZE, 0644 )) == -1) {
				perror("shmget");
				exit(1);
			}

			data[ix] = shmat(shmid[ix], (void *)0, 0);
			if (data[ix] == (__u32 *)(-1)) {
				perror("shmat");
				exit(1);
			}
		}



		datas = malloc( BUFFERSIZE / sizeof(__u32) * sizeof(__u16));
		dataf = malloc( BUFFERSIZE / sizeof(__u32) * sizeof(float));
		printf("Ready to receive.\n");
		int first_dt = 1, ix2;
		for (ix=0; ; ) { 
			if (msgrcv(msqid, (struct msgbuf *)&buf, sizeof(buf), 0, 0) == -1) {
				if (first_dt == 1)
				{
					printf("shmdt\n");
					for (ix = 0; ix<MAXBUFFERNUM; ix++){
	 					if (shmdt(data[ix]) == -1) {
	 						perror("shmdt");
							exit(1);
						}
					}
				}
				first_dt = 0;
				perror("msgrcv");
				break;
			}
			printf("spock msg: \"%s\"\n", buf.mtext);
			//printf("segment contains: \"%s\"\n", data[buf.mtext[0]-48]);

			for ( ix2 = 0; ix2 < BUFFERSIZE / sizeof(__u32); ix2 ++)
			{
				datas[ix2] = 0xffff & data[buf.mtext[0]-48][ix2];
				dataf[ix2] = (datas[ix2] - 0x8000) * 10.0 / 0x8000;	
				//if ( ix2 % 8 == 0)
				//printf("%x ",data[buf.mtext[0]-48][ix2]);	
			}

			if ( udelctl.flag_hd == 1)
			{
				////FILE *daq_file = fopen("/daqsbc/data/data.dat", "a+");
				//FILE *daq_file = udeldaqfileinit((DaqBoard *)NULL, 0); 				
				////fwrite(data[buf.mtext[0]-48], BUFFERSIZE, 1, daq_file);
				//fwrite(datas, BUFFERSIZE/2, 1, daq_file);
				//fclose(daq_file);
				udelwritedatatofile( datas, BUFFERSIZE/2);
			}
			if ( udelctl.flag_disp == 1)
			{
				int NDATA = BUFFERSIZE / sizeof(__u32);
				_udeldrawdata(&uxwin, board.ctl.ictl.nchans, udelctl.xwin_chan, dataf, NDATA);		
			}
			
			ix++;
		}
		if ( udelctl.flag_hd == 1)udelfileclose();
		getchar();
		exit(0);
	}
	
	return 0;
}

