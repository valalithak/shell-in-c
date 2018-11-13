#include"headers.h"

void remindme(char* f1[])
{
    //printf("Executing %s process\n",f1[0]);
    signal(SIGCHLD,SIG_IGN);

    int tim = atoi(f1[1]);
    //printf("%d\n",tim);
    int fork_pid=fork();

    if(fork_pid==0) // child process
    {
        sleep(tim);
        int i =2;
        printf("Reminder: ");
        while(f1[i]!=NULL)
        {
            printf("%s",f1[i]);
            i++;
        }
        printf("\n");
    }
    return;
}
