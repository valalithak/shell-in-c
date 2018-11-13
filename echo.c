#include"headers.h"

void echos(int argc,char* args)
{
    //printf("In echo\n");
    int length = strlen(args);
    //printf("%s is the string in echo with length %d\n",args, length);
    int start;
    int spaceflag = 0;
    int initialspace = 0;
    for(start=5; start<=length; start++)
    {
    //    printf("%d\n",start);
        while(args[start]==' ' && initialspace == 0)
            start++;

        initialspace =1 ;

        if(args[start] == '"'){

            int new = start +1;
            while(args[new]!= '"')
            {
                printf("%c",args[new]);
                new++;
            }
            break;

        }

        else
        {
            if(args[start]==' ' && spaceflag == 0)
            {
                printf("%c",args[start]);
                spaceflag =1;
            }
            if(args[start]==' ' && spaceflag==1)
                continue;
            else if(spaceflag==1 && args[start]!= ' ')
            {
                printf("%c",args[start]);
                spaceflag =0;
            }
            else
                printf("%c",args[start]);
        }

    }
    printf("\n");
    return;
}
