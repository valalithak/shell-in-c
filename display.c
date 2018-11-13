#include <sys/types.h>
#include <pwd.h>
#include "headers.h"
int flag1 = 0;
int flag2 = 0;
int count  = 0;
int i, j, k, l;
void display(char* home)
{
    printf("<");
    struct passwd* p;
    p = getpwuid(getuid());
    printf("%s",p->pw_name);
    printf("@");
    char hname[2000];
    char buffer[2000];
    gethostname(hname,2000);
    printf("%s",hname);
    printf(":");
    char* cwd;
    cwd = getcwd(buffer,2000);

    /* If the current working directory is actually the directory from where the user runs this shell,
     we need to display it as home directory*/

        int result = strcmp(cwd,home);
        //printf("%d", result);
        int l =  strlen(cwd);
        int k = strlen(home);
        while(i<l)
        {
                if(home[i]==cwd[i])
                    count+=1;
                else
                    flag1 = 1;
                //printf("%d\n",count);
                i++;
        }
        //printf("%s",cwd);
        if(count!=l)
        {
            flag1 =0;
            flag2 =1;
        }
        if(k>l)
            flag1 = 1;
        if(flag1==1)
            printf("%s",cwd);
        else
        {
            if(flag2==1)
                printf("~/%s",&cwd[k+1]);
            else
                printf("~");
        }


    printf(">");

    return;


}
