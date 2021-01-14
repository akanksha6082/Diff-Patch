#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<strings.h>

typedef struct intnode
{
	int number;
	struct intnode * next;
}INTNODE;

typedef struct queue
{
	INTNODE	* front;
	INTNODE * rear;
}QUE;

void initintque(QUE *);
int isempty(QUE *);
INTNODE * createintnode(int );
void enqueque(QUE *, int);
int dequeque(QUE *);
void displayque1(QUE *);
int getfrontint(QUE *);
int getrearint(QUE *);

