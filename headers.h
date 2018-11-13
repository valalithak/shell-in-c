#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <pwd.h>
#include <netdb.h>
#include <limits.h>
#include <string.h>
#include <wait.h>
#include <stdlib.h>
#include <signal.h>

char *str[100005];
char home_buffer[2048];
char* home;
typedef struct node
{
	char name[200000];
	int pid;
	int type;
	struct node* next;
}node;
node* head;
int type_full;
int stat;
//int exit_status = 0;
int stop;
void cd(char *args[2000], char* home, char* temp, int x);
void pwd();
void display(char* home);
void echos(int argc,char* args);
void pinfo(char *token3[], int count, char tempdir2[]);
void remindme(char* args[]);
void clock_bonus(char* args[]);
node* exitt(node* head);
node* tokenise(int* exit_status, node* head, int stack[2000], int last, char proc[200][2000], char pip_arr[200][800], int stat, char tempdir[], char* f1[2000], char* input, char arr[400][2000], char* user_dir, char* temp);
void c_key(int signal);
void z_key(int signal);
node* jobs(node* head);
void redir_bg(int loopcount, char pip_arr[200][800],char arr[400][2000]);
node* overkill(node* head);
node* kjob(char *f1[2000], node* head);
node* fg (char* f1[2000]);
node* bg (char* f1[2000]);
node* del_node(node* n1, node* head);
node* addnew(node* head, int pid, int type, char* input[200000]);
int search(node* head,int pid);
node* background_kill(node* head);
