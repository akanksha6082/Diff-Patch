#include"list.h"

// FUNCTION TO INITIALISE THE LIST :

void init(LIST * t)
{
	t->front = t->rear= NULL;
}

// FUCNTION TO CREATE NODE AND INITIALISE IT:

LNODE* createnode(char * line, char ch)
{
	LNODE * a = (LNODE*)malloc(sizeof(LNODE));
	strcpy(a->line, line);
	a->ch = ch;
	a->next = NULL;
	return a;
}

// FUNCTION TO ADD THE ELEMENT TO THE LIST :

void add(LIST * t, char * line, char ch)
{
	
	LNODE * a = createnode(line, ch), *b = t->rear;
	if(a == NULL)
	{
		printf("MALLOC UNSUCCESSFUL \n");
		exit(0);
	}
	else
	{
		if( t->front == NULL)
		{
			t->front = a;
		}
		else
		{
			b->next = a;
		}
		t->rear = a;
	}
}

// FUNCTION TO DISPLAY THE LIST :

void display(LIST * t)
{
	LNODE * a = t->front;
	if(check_LCS_data(t) == 0)
	{
		while(a != NULL)
		{
			printf("%c %s\n", a->ch, a->line);
			a = a->next;
		}
	}
}

// FUNCTION TO CHECK THE DATA FROM THE LIST RELATED TO LCS :

int check_LCS_data(LIST * t)
{	
	LNODE * a = t->front;
	while(a != NULL)
	{
		if(a->ch == ' ')
		{
			a = a->next;
		}
		else
			break;
	}
	if(a == NULL)
		return 1;
	else
		return 0;
}
		
