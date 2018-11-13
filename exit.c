#include"headers.h"
node* exitt(node* head)
{
    int stat;
    if(head==NULL)
        return head;
    else{
	       node* temp=head;
	       while(temp!=NULL)
	       {
		      if(waitpid(temp->pid,&stat,WNOHANG))
		      {
			       kill(temp->pid,SIGKILL);
			       head=del_node(temp,head);
		      }
		      temp=temp->next;
	         }
	         return head;
         }
}
// for control Z
void z_key(int signal)
{
    if(stop==0)
        stop = 1;
    //return stop;
}
// for control C
void c_key(int signal)
{
	printf("\n");

	//if(singleline==0)
	   display(home);
	fflush(stdout);
}
