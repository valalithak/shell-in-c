#include"headers.h"

void clock_bonus(char* f1[])
{
    //printf("Executing %s process\n",f1[0]);
    signal(SIGCHLD,SIG_IGN);


    int fork_pid=fork();

    if(fork_pid==0) // child process
    {
        int freq = atoi(f1[2]);
        int dur = atoi(f1[4]);
    //    printf("%d\t%d\n",freq,dur);
        int h = dur/freq;
        int i;
        for(i=0;i<h;i++)
        {
            sleep(freq);
            char buffer1[100];
            char buffer2[100];
            int fd = open("/sys/class/rtc/rtc0/date", O_RDONLY);
            int fd2 = read(fd,buffer1,sizeof(buffer1)-1);
            int fd3 = open("/sys/class/rtc/rtc0/time", O_RDONLY);
            int fd4 = read(fd3,buffer2,sizeof(buffer2)-1);

        //printf("%d\",freq);
            int j;
            int k;
            for(j=0;j<10;j++)
                printf("%c",buffer1[j]);
            printf("\t");
            for(k=0;k<8;k++)
                printf("%c",buffer2[k]);
            printf("\n");
            close(fd);
            close(fd4);
            close(fd2);
            close(fd3);

        }
    }
    return;
}
