#include"headers.h"
void pwd()
{
    char* dir_name;
    dir_name = getcwd(NULL,0);
    printf("%s",dir_name);
    printf("\n");
    return;

}
