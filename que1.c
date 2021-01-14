#include"que1.h"

// IMPLEMENTATION OF QUEQUE USING LINKED LIST REPRESENTATION :

// FUNCTION TO INITIALISE THE QUEQUE :

void initintque(QUE * t)
{
	t->front = t->rear = NULL;
}

// FUNCTION TO CHECK WHETHER QUEQUE IS EMPTY :

int isempty(QUE * t)
{
	return(t->front == NULL);
}

// FUNCTION TO CREATE A NEW NODE AND INITIALISE IT :

INTNODE * createintnode(int number)
{
	INTNODE * a = (INTNODE*)malloc(sizeof(INTNODE));
	if(a == NULL)
	{	
		printf("Malloc unsuccessful\n");
		exit(0);
	}
	else
	{
		a->next = NULL;
		a->number = number;
	}
	return a;
}

// FUNCTION TO ADD THE DATA TO THE QUEQUE:

void enqueque(QUE * t, int number)
{	
	INTNODE *a = createintnode(number), *b;
	if(t->front == NULL)
	{
		t->front = a;
		t->rear = a;
	}
	else
	{
		t->rear->next = a;
		t->rear = a;
	}
}

// FUNCTION TO REMOVE THE DATA FROM QUEQUE:

int dequeque(QUE * t)
{
	INTNODE * a = t->front;	
	int temp;
	if(isempty(t) == 0)
	{
		temp = a->number;
		t->front = a->next;
		free(a);
		return temp;
	}
	else
	{
		printf("empty list\n");
		exit(0);
	}
}

// FUNCTION TO DISPLAY THE QUEQUE:

void displayque1(QUE * t)
{
	
	INTNODE * a = t->front;
	
	while(a != NULL)
	{
		
		printf("%5d",a->number);
		a = a->next;
	}
}

// FUNCTION TO RETRIEVE THE FIRST ELEMENT OF THE QUEQUE:

int getfrontint(QUE * t)
{
	return(t->front->number);
}

// FUNCTION TO RETRIEVE THE LAST ELEMENT OF THE QUEQUE:

int getrearint(QUE * t)
{
	return(t->rear->number);
}
