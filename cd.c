#include"headers.h"

void cd(char *args[2000], char* home, char* temp, int x)
{

	//printf("Inside cd");
	int flag  = 0;
	if(x>1)
	{
		if(args[1][0]=='~' && strlen(args[1])<=1)
		{
			if(chdir(home)!=0)
				perror("Error  ");
		}
		else if(args[1][0]=='~' && strlen(args[1])>1)
		{
			//	printf("inside if before seg fault\n");
			//printf("%s\n",home);
			flag = 1;
		}
		if(flag==1)
		{
			printf("%s is temp\n",temp);
			strcpy(temp,"");
			printf("%s\n",temp);
			strcpy(temp,home);
			printf("%s\n",temp);
			strcat(temp,&args[1][1]);
			printf("%s\n",temp);


			int z = chdir(temp);
			if(z!=0)
				error("Error ");

		}
		else
		// just the folder name
		{

			int val = chdir(args[1]);
			if(val!=0)
			perror("Error: ");
		}
	}
	else
	{
		//printf("\n Only cd just go home");
		chdir(home);
		//printf("\n%d",chdir(home));
	}
	return;
}
