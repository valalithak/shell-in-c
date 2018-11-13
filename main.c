#include"headers.h"
int stat;
int exitflag;
int exit_status;
int main()
{
    home = getcwd(home_buffer,2048);
    signal(SIGTSTP,z_key);
    signal(SIGINT, c_key);

    while(1)
    {
        char buffer[2048];
        char input[2048];
        char arr[400][2000];
        char* f1[2000];
        char temp[1000];
        int stack[2000];
        int last = -1;
        char proc[200][2000];
        char pip_arr[200][800];
        char tempdir[1024];

        getcwd(tempdir,sizeof(tempdir));

        char* user_dir = getcwd(buffer,2048);
        display(home);
        fgets(input,2048,stdin);
        //printf("%s\n",input);
        int length = strlen(input);
        //printf("%d\n",length);
        input[length-1] = '\0';
        //printf("%d\n",length);
        head = tokenise(&exit_status,head,stack,last,proc,pip_arr,stat,tempdir,f1, input, arr, home, temp);
        //printf("%d\n",head-type);
        head = exitt(head);
        //printf("In main\n");
        if(exit_status==1)
			break;
    }

    return 0;
}
