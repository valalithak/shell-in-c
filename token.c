#include"headers.h"
int exec_type = 0; // check for execution
int position1 = 0;
int position2;
int var = 0;
int m = 0;
int bg_process=0;
int fg_process=0;
char* name;
int spaceflag = 0;
int waiting;
int dupfd = 0;
char tempdir2[1024];
int p, p_it = 0;
int gt, lt, append; // > < >>
int check1 = 0;
int check2 = 0;
int fd_rd, fd_in, fd;
int val;
int id;
int l = 0;


void redir_bg(int loopcount, char pip_arr[200][800],char arr[400][2000])
{

    if(pip_arr[loopcount][strlen(arr[loopcount])-1]=='&')
	{
		pip_arr[loopcount][strlen(arr[loopcount])-1]='\0';
		bg_process=1;
	}
    //printf("%d i the value of bg flag\n",bg_process);
    int pos = 0, i=0;
    char arr2[2000][2000];
    int we = strlen(pip_arr[loopcount]);
    //printf("%d\n",we);
    while(i<we+2)
    {
        //printf("%d is i and %d is strlen\n",i,we);
        if(pip_arr[loopcount][i]=='<')
		{
			arr2[loopcount][pos]=' ';
			arr2[loopcount][pos+1]='<';
			arr2[loopcount][pos+2]=' ';
			pos+=3;
		}
		if(pip_arr[loopcount][i+1]!='>' && pip_arr[loopcount][i]=='>' && i+1<we)
        {
                arr2[loopcount][pos]=' ';
			    arr2[loopcount][pos+1]='>';
			    arr2[loopcount][pos+2]=' ';
			    pos+=3;
        }
		else if(pip_arr[loopcount][i+1]=='>' && pip_arr[loopcount][i]=='>' && i+1<we)
	    {
                //printf("Appending\n");
			    arr2[loopcount][pos]=' ';
			    arr2[loopcount][pos+1]='>';
			    arr2[loopcount][pos+2]='>';
			    arr2[loopcount][pos+3]=' ';
			    pos+=4;
			    i++;
		}
        else
		{
			arr2[loopcount][pos]=pip_arr[loopcount][i];
			pos++;
            //printf("%d\t",arr2[loopcount][pos]);
			//printf("%d\n",pos);
		}
        i+=1;
    }
    int j = 0;
    for(j=0;j<pos;j++)
		pip_arr[loopcount][j]=arr2[loopcount][j];


	pip_arr[loopcount][i]='\0';
    return;
}


node* tokenise(int* exit_status, node* head, int stack[2000], int last, char proc[200][2000], char pip_arr[200][800], int stat, char tempdir[], char* f1[2000], char* input, char arr[400][2000], char* user_dir, char* temp)
{

    char* x;
    char* y;
    char* pip;

    position1 = 0;
    x = strtok(input,";");
    while(x!=NULL)
    {

        strcpy(arr[position1],x);
        x = strtok(NULL,";");
        position1++;
    }

    //var = 0;
    for (var=0;var<position1;var++)
    {
        //printf("%d is var\n",var);
        p = 0;
        fd_in = 0;
        int piping[2];
        pip = strtok(arr[var],"|");
        while(pip!=NULL)
        {

            strcpy(pip_arr[p],pip);
            pip=strtok(NULL,"|");
            p+=1;

        }
        //printf("%d is the value of p\n",p);
        //printf("%d is the value of p_it\n",p_it);

        for(p_it=0;p_it < p;p_it++)
        {

            check1 = 0;
            check2 = 0;
            exec_type = 0;
            gt = 0;
            lt = 0;
            l = 0;
            append = 0;
            bg_process = 0;
            fg_process = 0;

            while(l<strlen(pip_arr[p_it]))
            {

                if(pip_arr[p_it][l]=='\'' || pip_arr[p_it][l]=='"')
                {
					pip_arr[p_it][l]=' ';
                }
                int len_flag = 0;

                if(l + 1 - strlen(pip_arr[p_it])< 0)
                    len_flag = 1;

                    if(len_flag == 1 && pip_arr[p_it][l]=='>' && pip_arr[p_it][l+1]=='<'){

                    	exec_type=2;
                    }
    				if(len_flag == 1 && pip_arr[p_it][l]=='<' && pip_arr[p_it][l+1]=='>' ){
    					exec_type=1;

                    }
    				if(len_flag == 1 && pip_arr[p_it][l]=='<' && pip_arr[p_it][l+1]=='<' ){
    					exec_type=1;

                    }

                stop = 0;
                l+=1;
    }
        redir_bg(p_it,pip_arr,arr);
        y=strtok(pip_arr[p_it]," \t");
        int var = 0;
        int app[2];
        app[0]=0;
        app[1] = 0;
        stop=0;
        int a = 0;
        int g = 0;
        char* temp_buf;
        while(y!=NULL)
        {

                temp_buf = y;
                if(strcmp(temp_buf, ">")==0 && exec_type == 0)
                {
                    f1[var]=NULL;
                    var++;
                    gt = 1;
                    y=strtok(NULL," ");
                    f1[var] = y;
                    var+=1;
                    fd = open(f1[var-1],O_WRONLY | O_CREAT | O_TRUNC, 0644);
                    a = var -1;
                    check1 =1;

                }
                else if(strcmp(temp_buf,">>")==0 && exec_type == 0)
                {
                    //printf("app\n");
                    append =1;
                    f1[var]=NULL;
                    var++;
                    y=strtok(NULL," ");
                    f1[var] = y;
                    //printf("%s\n",y);
                    gt = 1;
                    var+=1;
                    fd = open(f1[var-1],O_WRONLY | O_CREAT | O_APPEND, 0644);
                    //printf("%d\n",fd);
                    a = var -1;
                    check1 =1;

                }
                else if(strcmp(temp_buf,"<")==0 && exec_type == 0)
                {
                    lt = 1;
                    f1[var] = NULL;
                    var++;
                    y=strtok(NULL," ");
                    f1[var] = y;
                    var+=1;
                    fd_rd = open(f1[var-1], O_RDONLY, 0644);
                    char * name = f1[var-1];
                    if(check2!=0)
					    app[1]=var-1;
					else
						app[0]=var-1;
					check2=1;

                }

                else if(strcmp(temp_buf,"&")==0){
                    bg_process=1;
                    //printf("bg1\n");
            }
            else
			{
                f1[var]=y;
				var+=1;
			}

            y=strtok(NULL," \t");
        }
        f1[var]=NULL;
        while(m<var-1)
        {
            int g1= 0;
            int g2 = 0;
            if(f1[m]==NULL)
                g1 = 1;
            if(f1[m+1]==NULL)
                g2=1;
            if(g1*g2==1)
                g = 1;

            m+=1;
        }
        str[0]=f1[0];
        if(a+1<var && f1[a+1]==NULL && check1==1)
            exec_type=1;
        if(app[0]+1==app[1])
            exec_type=2;

        if(f1[0]!=NULL && exec_type==0 && fd_rd!=-1 && g==0)
        {

            if(strcmp(f1[0],"quit")==0)
            {
                head=overkill(head);
                printf("Quitting from the shell\n");
                exit(0);
            }
            if(lt==1 && var<2)
                printf("Command not found\n");


        else
        {

                if(strcmp(f1[0],"cd")==0)
                {
                    //printf("Going to cd\n");
                    cd(f1,user_dir,temp,var);
                }
                else if(strcmp(f1[0],"echo")==0 && gt!=1 && append!=1 && lt!=1)
                {
                    //printf("Going to echo\n");
                    //printf("%s is the string in token\n",input);
                    //printf("%d\n",strlen(input));
                    echos(strlen(input),input);
                }
                else if(strcmp(f1[0],"pwd")==0)
                {
                    //printf("Going to pwd\n");
                    pwd();
                }
                else if(strcmp(f1[0],"pinfo")==0)
                {
                    //printf("Going to pinfo\n");
                    pinfo(f1,var,tempdir2);
                }
                else if(strcmp(f1[0],"remindme")==0)
                {
                    //printf("Going to remindme\n");
                    //printf("%s",f1[1]);

                    remindme(f1);
                }
                else if(strcmp(f1[0],"clock")==0)
                {
                    //printf("Going to clock\n");
                    //printf("%s",f1[1]);

                    clock_bonus(f1);
                }
                else if(strcmp(f1[0],"jobs")==0)
                {
                    head = jobs(head);
                }
                else if(strcmp(f1[0],"kjob")==0)
                {
                    head = kjob(f1,head);
                }
                else if(strcmp(f1[0],"fg")==0)
                {
                      // printf("before\n");
                        head = fg(f1);

                }
                else if(strcmp(f1[0],"bg")==0)
                {
                      // printf("before\n");
                        head = bg(f1);

                }
                else if(strcmp(f1[0],"overkill")==0)
                {
                    //printf("going to killbg\n");
                    head = overkill(head);
                }
                else if(strcmp(f1[0],"setenv")==0)
                {
                    //printf("going to killbg\n");
                    setenv(f1[1],f1[2],1);
                    if(f1[1]==NULL || f1[2]== NULL)
                        printf("Mention atleast two arguments\n");

                }
                else if(strcmp(f1[0],"unsetenv")==0)
                {
                    //printf("going to killbg\n");
                    unsetenv(f1[1]);
                    if(f1[1]==NULL)
                        printf("Mention atleast one argument\n");

                }
                else
                {

                        int d = pipe(piping);
                        int proc_id = fork();
                        if(proc_id==-1)
                            printf("Fork failed\n");

                        else if(proc_id==0)
                        {
                            //printf("In the child process\n");

                            if(check1==1)
                                dup2(fd,1);

                            else
                                dup2(fd_in,0);
                            if(check2!=1)
                            {
                                //printf("hello\n");
                                int il= dup2(fd_in,0);
                                //printf("%d\n", il);
                            }
                            else
                            {
                                dup2(fd_rd,0);
                            }
                            if(p_it!=p-1 && p>=2)
                                d=dup2(piping[1],1);

                            close(piping[0]);

                            if(check2==1)
                                close(fd_rd);
                            if(check1==1)
                                close(fd);
                            check2=0;
                            check1=0;

                            val=execvp(f1[0],f1);
                            exit(127);
                        //    printf("Exited child process\n");
                        }
                        else
                        {
                            id = proc_id;
                            //printf("%d\n",proc_id);
                            if(bg_process==0)
                            {
                                int temp;
                                waitpid(proc_id,&temp,WUNTRACED);

                            }
                            else
                            {
                                //printf("Near\n");
                                head=addnew(head,proc_id,0,f1);
                                //if(head!=NULL)
                            //    printf("%s\n",head->name);
                                // add the background process in the linked list
                            }
                            //printf("Came out\n");
                            close(piping[1]);
                            fd_in=piping[0];

                        }
                        if(val!=0)
                            printf("Command not found\n");
                    }

            }
        }
            else if(fd_rd==-1){
				printf("-bash: %s: No such file or directory\n",name);
                fd_rd==0;
            }
			else if(exec_type==1)
				printf("-bash: syntax error near unexpected token `newline'\n");

			else if(exec_type==2)
			    printf("-bash: syntax error near unexpected token `<'\n");

			else
				printf("Command not found\n");
			//ctrl-z is pressed
			if(stop==1)
			{
                //printf("check in stop\n");
				head=addnew(head,id,1,str);
				stop=0;
			}

        }
        if(*exit_status==1)
		{
        //    printf("going here and stopping\n");
			break;
		}
    //    var++;
    }
       //printf("going till end of tokenise\n");
        return head;
}
