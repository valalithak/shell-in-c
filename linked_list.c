#include"headers.h"
int stat;
int search(node* head, int pid)
{
    int c=0,found=0,p;
	node* t;
	t=head;
	t=head;
	while(t!=NULL)
	{
		c++;
		if(c==pid)
		{
			found=1;
			p=t->pid;
			type_full=t->type;
		}
		t=t->next;
	}
	if(found==0)
		return -1;
	else
		return p;
}

node* del_node(node* n1, node* head)
{
    //printf("in delete function\n");
    node* temp1;
    temp1=head;
    int one_flag = 0;
    if(head==n1)
        one_flag = 1;
    //printf("%d\n", one_flag);
    if(one_flag==1)
    {
        printf("%s with pid %d exited normally\n",head->name,head->pid);
        head=head->next;
    }
    else
    {
        while(temp1->next!=n1)
            temp1=temp1->next;

        printf("%s with pid %d exited normally\n",n1->name,n1->pid);
        temp1->next=n1->next;
    }
    return head;
}

node* addnew(node* head, int pid, int type, char* input[200000])
{
    node* temp;
    temp=malloc(sizeof(node));
    temp->pid=pid;
    temp->type=type;
    int i=0;
    if(head==NULL)
	{
		head=malloc(sizeof(node));
		head->pid=pid;
		head->type=type;

		strcpy(head->name,input[0]);
		head->next=NULL;
	}
	else
	{

		strcpy(temp->name,input[0]);
		node* temp1;
		temp1=head;
		while(temp1->next!=NULL)
		{
			temp1=temp1->next;
		}
		temp1->next=temp;
		temp->next=NULL;
	}
    return head;

}

node* background_kill(node* head)
{
    node* temp = head;
    node* temp2 = temp;
    int waitflag = 0;
    if(temp==NULL)
        return temp;
    else
    {
        while(temp!=NULL)
        {
            if(waitpid(getpid(),&stat,WNOHANG))
		    {
			     kill(getpid(),SIGKILL);
			     head=del_node(temp,head);
                 waitflag = 1;
		    }
		    temp=temp->next;
	    }
        //printf("%d\n",waitflag);
	    return head;

    }
}
