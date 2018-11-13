#include"headers.h"
int jobcount = 1;
node* temp;
node* bg_kill_head;
int nflag1 = 0;
int nflag2 = 0;

node* jobs(node* head)
{
    int len=0;
	node* t;
	t=head;
    char arr[1024];
    char c[100];
    int x;
    int flag1 = 0;

	while(t!=NULL)
	{
        len+=1;
        sprintf(arr,"/proc/%d/stat",t->pid);
        //printf("%s\n",arr);
        int fd = open(arr,O_RDONLY);
        x = read(fd,c,50);
        //printf("%s\n",c);
        int i;

		printf("[%d] %s %d ",len,t->name,t->pid);
        for(i=0; i<30; i++)
        {
            if(c[i]=='T')
                flag1 = 1;

        }
        if(flag1==1){
            printf("Stopped\n");
            flag1 = 0;
        }
        else
            printf("Running\n");
		len++;
		t=t->next;
        close(fd);
        close(x);
	}
	return head;
}
node* overkill(node* head)
{
	int k=0;
	node* killbg = head;
    //printf("In killbg\n");
	while(killbg!=NULL)
	{
        kill(killbg->pid,9);
		printf("[%d] ",k+1);
        printf("%s ", killbg->name);
        printf("%d",killbg->pid);
        printf("killed\n");
		killbg=killbg->next;
        k+=1;
	}
	head=NULL;
	return head;
}
node* kjob(char *first[2000],node* head)
{

	int pd;
    int sig,p;
    int status = 0;
	char a[10005];
	if(first[1]!='\0' && first[2]!='\0')
	{
		strcpy(a,first[1]);
		pd=atoi(a);
		p=search(head,pd);

		strcpy(a,first[2]);
		sig=atoi(a);

        if(p==-1)
			printf("No such job\n");
		else
		{
			status=kill(p,sig);
			{
				if(status==-1)
					perror("Error");
			}
		}

	}
	else
		printf("Give atleast 2 arguments\n");
	return head;
}


node* fg(char* f1[2000])
{
    //printf("in fg\n");
    // should handle both cases, type1 when we send it to background normally and type2 when we stop it by controlz
    int stat,pd,p;
	char b[10005];
    int temp = strlen(f1[1]);
    //printf("%d\n", temp);
    if(temp==0)
    {
        printf("Enter valid arguments\n");
        return head;
    }
	strcpy(b,f1[1]);
	pd=atoi(b);
    //printf("%d\n",pd);

	p=search(head,pd);
    //printf("%d\n",p);


	if(p!=-1 && type_full==1)
		waitpid(p,&stat,0);

	else if(p!=-1 && type_full==0)
	{
		kill(p,SIGCONT);
		waitpid(p,&stat,0);
	}
	else
		printf("No such job\n");
	return head;

}

node* bg(char* f1[2000])
{
    //printf("in fg\n");
    int stat,pd,p;
	char b[10005];
    int temp = strlen(f1[1]);
    //printf("%d\n", temp);
    if(temp==0)
    {
        printf("Enter valid arguments\n");
        return head;
    }
	strcpy(b,f1[1]);
	pd=atoi(b);

	p=search(head,pd);
    //printf("%d\n",p);
    if(p!=-1 && type_full==1)
		waitpid(p,&stat,0);

	else if(p!=-1 && type_full==0)
	{
		kill(p,SIGCONT);
//		waitpid(p,&stat,0);
	}
	else
		printf("No such job\n");
	return head;

}
