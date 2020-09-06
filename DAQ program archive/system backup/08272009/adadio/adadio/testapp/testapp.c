// $URL: http://subversion:8080/svn/gsc/trunk/drivers/LINUX/ADADIO/ADADIO_Linux_3.x.x.x_GSC_DN/testapp/testapp.c $
// $Rev: 1620 $
// $Date: 2009-04-10 11:41:41 -0500 (Fri, 10 Apr 2009) $

#include <asm/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include <sys/ioctl.h>

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

#include "adadio.h"
#include "gsc_utils.h"

char driver_name[80]=ADADIO_DEV_BASE_NAME;

#define WORDS_TO_SEND 10

#define BUFFER_SIZE 32*1024

//#define BUFFER_SIZE (1024*16)
//#define BUFFER_SIZE (1024*256)
#define BUFFER_BYTES (BUFFER_SIZE*sizeof(__u32))

// number of channels for each board supported.

int channels[] = {
	12,
};

int main(int argc, char *argv[])
{
	gsc_reg_t		rw_q;
	unsigned long	buffer[BUFFER_SIZE], total;
	int				fd, res, i, print;
	__s32			param;
    time_t			startTime,lastDisplay=0,now,lapse;
    int				bytesRead;
    int				buffersRead	= 0;
    int				wordsRead	= 0;
    int				passes		= 0;

	if (argc < 2) {
		printf("%s: missing argument\nusage: testapp [0|1|2|...]\n", argv[0]);
		return (1);
	}

	strcat(driver_name, argv[1]);
	printf("about to open %s\n",driver_name);

	fd = open(driver_name, O_RDWR);
	if (fd < 0) {
		printf("%s: can not open device %s\n", argv[0], driver_name);
		return (1);
	}
    gsc_kbd_open();

	rw_q.reg	= ADADIO_GSC_BCR;
	res			= ioctl(fd, ADADIO_IOCTL_REG_READ, &rw_q);
	if (res < 0) {
		printf("%s: ioctl ADADIO_IOCTL_REG_READ failed\n", argv[0]);
		goto OUT;
	}
	printf("before init: BCR is 0x%lX\n", (long) rw_q.value);

    // set timeout for init, autocal, read operations.
    param = 5;
    res = ioctl(fd,ADADIO_IOCTL_RX_IO_TIMEOUT, &param);
    if (res < 0) {
        printf("%s: ioctl ADADIO_IOCTL_RX_IO_TIMEOUT failed\n", argv[0]);
        goto OUT;
    }

    res = ioctl(fd, ADADIO_IOCTL_INITIALIZE, NULL);
	if (res < 0) {
		printf("%s: ioctl ADADIO_IOCTL_INITIALIZE failed\n", argv[0]);
		goto OUT;
    }
	printf("board init OK\n");

	rw_q.reg	= ADADIO_GSC_BCR;
	res			= ioctl(fd, ADADIO_IOCTL_REG_READ, &rw_q);
	if (res < 0) {
		printf("%s: ioctl ADADIO_IOCTL_REG_READ failed\n", argv[0]);
		goto OUT;
	}
	printf("after init: BCR is 0x%lX\n", (long) rw_q.value);

	res = ioctl(fd, ADADIO_IOCTL_AUTO_CALIBRATE, NULL);
	if (res < 0) {
		printf("%s: ioctl ADADIO_IOCTL_AUTO_CALIBRATE failed %d\n", argv[0],i);
		goto OUT;
	}

	printf("auto calibration OK\n");

    // clear the input buffer.

    res = ioctl(fd, ADADIO_IOCTL_AIN_BUF_CLEAR, NULL);
    if (res < 0) {
        printf("%s: ioctl ADADIO_IOCTL_AIN_BUF_CLEAR failed %d\n", argv[0],i);
        goto OUT;
    }

	//	set the analog input to single-ended burst mode.

	param	= ADADIO_AIN_MODE_SE_CONT;
	res		= ioctl(fd,ADADIO_IOCTL_AIN_MODE, &param);
	if (res < 0) {
		printf("%s: ioctl ADADIO_IOCTL_AIN_MODE failed\n", argv[0]);
		goto OUT;
	}

    //	two's comp data format.

    param	= ADADIO_DATA_FORMAT_2S_COMP;
    res		= ioctl(fd, ADADIO_IOCTL_DATA_FORMAT, &param);
    if (res < 0) {
        printf("%s: ioctl ADADIO_IOCTL_DATA_FORMAT failed\n", argv[0]);
        goto OUT;
    }

    //	Set the size of the input buffer.

    param	= ADADIO_AIN_BUF_SIZE_256;
    res		= ioctl(fd, ADADIO_IOCTL_AIN_BUF_SIZE, &param);
    if (res < 0) {
        printf("%s: ioctl ADADIO_IOCTL_AIN_BUF_SIZE failed\n", argv[0]);
        goto OUT;
    }

    //	Enable the outputs.

    param	= ADADIO_AOUT_ENABLE_YES;
    res		= ioctl(fd, ADADIO_IOCTL_AOUT_ENABLE, &param);
    if (res < 0) {
        printf("%s: ioctl ADADIO_IOCTL_AOUT_ENABLE failed\n", argv[0]);
        goto OUT;
    }

    //	Set the DIO to outputs.

    param	= ADADIO_DIO_PORT_DIR_OUTPUT;
    res		= ioctl(fd, ADADIO_IOCTL_DIO_PORT_DIR, &param);
    if (res < 0) {
        printf("%s: ioctl ADADIO_IOCTL_DIO_PORT_DIR failed\n", argv[0]);
        goto OUT;
    }

    //	Set the DIO outputs to all ones.

    param	= 0xff;
    res		= ioctl(fd, ADADIO_IOCTL_DIO_PORT_WRITE, &param);
    if (res < 0) {
        printf("%s: ioctl ADADIO_IOCTL_DIO_PORT_WRITE failed\n", argv[0]);
        goto OUT;
    }

    //	Write a value to one of the analog output registers.

    param	= 0x0ff0;
    res		= ioctl(fd, ADADIO_IOCTL_AOUT_CH_0_WRITE, &param);
    if (res < 0) {
        printf("%s: ioctl ADADIO_IOCTL_AOUT_CH_0_WRITE failed\n", argv[0]);
        goto OUT;
    }

    //	Set the data sampling rate.

    param	= 0xc9; // 99,502 samples per second, per hardware manual
    res		= ioctl(fd, ADADIO_IOCTL_AIN_NRATE, &param);
    if (res < 0) {
        printf("%s: ioctl ADADIO_IOCTL_AIN_NRATE failed\n", argv[0]);
        goto OUT;
    }

    //	Select DMA or PIO data transfers.

	param	= GSC_IO_MODE_PIO;
    param	= GSC_IO_MODE_DMA;
    res		= ioctl(fd, ADADIO_IOCTL_RX_IO_MODE, &param);
    if (res < 0) {
        printf("%s: ioctl ADADIO_IOCTL_RX_IO_MODE failed\n", argv[0]);
        goto OUT;
    }

    total=0;
    startTime=time(NULL);
    /*******************************************/
    printf("Starting main loop...press any key to exit...\n");

    while (!gsc_kbd_hit()) {

        // size of read is in bytes.

        memset(buffer,0xbaaaaaab,sizeof(buffer));
        bytesRead = read(fd, buffer, BUFFER_BYTES);
        buffersRead++;
        //      printf("read: %lX\n", (long) numread);
        if (bytesRead < 0){
            printf("\nread error -> after read...res = %d\n",bytesRead);
            goto OUT;
        }

        wordsRead = bytesRead / sizeof (long);
        total += wordsRead;
        passes++;

        now=time(NULL);
        if (now != lastDisplay)
        {
            lastDisplay=now;
            print = (total >> 20);
            {
                int j;
                lapse = time(NULL)-startTime;
                if (lapse != 0 )
                {
                    printf(	"seconds: %.8ld Minutes: %ld Words read: %.8lX samples/sec: %.8ld - ",
							(long) lapse,
							(long) lapse / 60,
							(long) wordsRead,
							(long) (total / lapse));
                    j=0;
                }
            }
            printf("      \r");
            fflush(stdout);
        }
    }

    printf("\n Total samples: %ld ",total);

OUT:
    gsc_kbd_close();
    printf("\n\n");
    fflush(stdout);

    // read the last hardware/driver error.
	printf("%s: ioctl failed, errno %d\n", argv[0], errno);
    close(fd);

    return 0;
}
