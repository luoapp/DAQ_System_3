 

struct my_msgbuf {
    long mtype;
    char mtext[200];
};

char IPC_msg_path[] = "../shmem/shmsg";
char IPC_shmem_path[][128] = { "../shmem/shmem.0", "../shmem/shmem.1","../shmem/shmem.2",
				"../shmem/shmem.3","../shmem/shmem.4","../shmem/shmem.5",
				"../shmem/shmem.6","../shmem/shmem.7","../shmem/shmem.8",
				"../shmem/shmem.9"};

int shmclear( void);
