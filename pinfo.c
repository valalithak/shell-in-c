#include"headers.h"
void pinfo(char *token3[], int count, char tempdir2[])
{
	char arr2[1024];
	char state;
	char arr[1024];
	char arr1[1024];
	int pid2;
	long long unsigned int memsize;
	FILE *filepointer;
	if(count==1)
	{
		sprintf(arr,"/proc/%d/stat",getpid());
		sprintf(arr1,"/proc/%d/exe",getpid());
	}
	else
	{
		sprintf(arr,"/proc/%s/stat",(token3[1]));
		sprintf(arr1,"/proc/%s/exe",(token3[1]));
	}
	if((filepointer=fopen(arr,"r"))!=NULL)
	{
		fscanf(filepointer,"%d %*s %c %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %llu %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d",&pid2,&state,&memsize);
		fclose(filepointer);
		printf("pid -- %d\nProcess Status -- %c\nmemory -- %llu\n",pid2,state,memsize);
		readlink(arr1,arr2,1024);
		if(strstr(arr2,tempdir2))
		{
			char arr3[1000]="~";
			strcat(arr3,arr2+strlen(tempdir2));
			printf("Executable Path -- %s\n",arr3);                                                                                               }
		else
			printf("Executable Path -- %s\n",arr2);
	}
	else
		printf("No such process\n");
}
