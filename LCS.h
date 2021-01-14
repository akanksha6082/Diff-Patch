#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<strings.h>
#include<ctype.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<errno.h>
#include<time.h>
#include"que1.c"
#include"list.c"
#define MAX_SIZE 100

typedef struct array
{
	char arr1[100];
	char arr2[100];
}ARRAY;

ARRAY brr[MAX_SIZE];

void write_file(int, int, char**);
int LCS(char **);
void back_track(int, int, int);
int print_diff1(int);
void print_diff2( int, int );
void print_diff3(int, int);
void print_diffaddbegin(int);
void print_diffaddmiddle(int, int);
void print_diffaddend(int);
void print_diffdelete(int);
void print_diffdeletebegin(int);






