#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<strings.h>

typedef struct listnode
{
	char line[100];
	char ch;
	struct listnode * next;	
}LNODE;

typedef struct list
{
	LNODE * front;
	LNODE * rear;	
}LIST;

void init(LIST *);
LNODE* createnode(char *, char);
void add(LIST *, char *, char);
void display(LIST * );
int check_LCS_data(LIST * );
int check_LCS_data(LIST *);
