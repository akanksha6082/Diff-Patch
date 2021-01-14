#include<stdio.h>
#include<stdlib.h>

void help()
{
	char ch;
	printf("Usage: diff [OPTION]... FILES\n\n");
	printf("Compare FILES line by line.\n\n");
	printf("Mandatory arguments to long options are mandatory for short options too.\n\n");
	printf("--normal                        output a normal diff (the default).\n\n");
	printf("-q, --brief                     report only when files differ.\n\n");
	printf("-s, --report-identical-files    report when two files are the same.\n\n");
	printf("-c, -C NUM, --context[=NUM]     output NUM (default 3) lines of copied context.\n\n");
	printf("-u, -U NUM, --unified[=NUM]     output NUM (default 3) lines of unified context.\n\n");
	printf("-t, --expand-tabs               expand tabs to spaces in output.\n\n");
	printf("-i, --ignore-case               ignore case differences in file contents.\n\n");
	printf("-b, --ignore-space-change       ignore changes in the amount of white space.\n\n");
	printf("-w, --ignore-all-space          ignore all white space.\n\n");	
  	printf("press q to exit\n");
  	label:
  	scanf("%c", &ch);
  	if(ch == 'q')
  	{
  		exit(0);
  	}
	else
	{
		goto label;
	}
}
  

    

