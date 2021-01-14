#include"LCS.h"

static int count_file_1 = 0, count_file_2 = 0;
QUE p, q, r, s;
LIST t, u;

char b[MAX_SIZE][MAX_SIZE];
int  c[MAX_SIZE][MAX_SIZE];


/*  FUNCTION ACCEPTS THE ARGUMENTA AS THE FILE POINTRES AND
 *  WRITES THE DATA FROM THE FILE INTO TWO DIMENSIONAL ARRAY.
 *  INCLUDES THE IMPLEMENTATION OF THE -b , -W AND -t COMMANDS.
 */
 
void write_file(int fd1, int fd2, char**argv)
{
	
	char ch;
	int i = 0,  j = 0, m = 0, space_count = 0, tab_count = 0;
	if(strcmp(argv[1], "-b") == 0 || strcmp(argv[1], "-w") == 0 )
	{
		m = 1;
	}
	else if(strcmp(argv[1], "-t") == 0)
	{
		m = 2;
	}
	while( read(fd1, &ch, 1))
	{
		while(ch != '\n')
		{		
			brr[i].arr1[j++] = ch;
			read(fd1, &ch, 1);
			if(m == 1 && ( ch == ' ' || ch == '\t') )
			{
				space_count++;
				tab_count ++;
				if(space_count == 2 || tab_count == 2)
				{
					while(ch == ' ' || ch == '\t')
						read(fd1, &ch, 1);
					space_count = 0;
					tab_count = 0;
				}
			}
			else if(m == 2 && ch == '\t')
			{
				while(ch == '\t')
				{
					for(int n = 0; n < 8; n++)
					{
						brr[i].arr1[j++] = ' ';
					}
					read(fd1, &ch, 1);
				}
			}			
		}
		brr[i].arr1[j] = '\0';
		i++;
		j  = 0;
		count_file_1++;
		
	}

        // READING FROM FILE 2 INTO 2-D ARRAY:
	
	i = 0;	
	j = 0;
	space_count = tab_count = 0; 

 	while( read(fd2, &ch, 1))
	{
		
		while(ch != '\n')
		{		
			brr[i].arr2[j++] = ch;
			read(fd2, &ch, 1);
			if(m == 1 && ( ch == ' ' || ch == '\t') )
			{
				space_count++;
				tab_count ++;
				if(space_count == 2 || tab_count == 2)
				{
					while(ch == ' ' || ch == '\t')
						read(fd2, &ch, 1);
					space_count = 0;
					tab_count = 0;
				}
			}
			else if(m == 2 && ch == '\t')
			{
				while(ch == '\t')
				{
					for(int n = 0; n < 8; n++)
					{
						brr[i].arr2[j++] = ' ';
					}
					read(fd2, &ch, 1);
				}
			}
		}
		brr[i].arr2[j] = '\0';
		i++;
		j  = 0;
		count_file_2++;	
	}	
}
	

/*   IMPLEMENTATION OF THE LONGEST COMMON SUBSEQUENCE
 *   FINDS THE LARGEST POSSIBLE COMMON SEQUENCES OF LINES FROM FILE 1 AMD FILE 2
 */
 
int LCS(char ** argv)
{
	int i , j, k, l, x, m;
	for(i = 0; i <= count_file_2 ; i++)
	{
		c[i][0] = 0;
		
	}

	for(j = 0; j <= count_file_1; j++)
	{
		c[0][j] = 0;
	
	}


	for(i = 1, k = 0; i <= count_file_2 && k < count_file_2; i++, k++)
	{
		for(j = 1, l = 0; j <= count_file_1 && l < count_file_1; j++, l++)
		{
			// IMPLEMENTATION OF -i COMMAND OF DIFF
			
			if( strcmp(argv[1], "-i") == 0)
				x = strcasecmp(brr[k].arr2, brr[l].arr1);
			else
				x = strcmp(brr[k].arr2, brr[l].arr1);
			if( x == 0)
			{
				
				c[i][j] = c[i-1][j-1] + 1;
				b[i][j] = 'c';
				if(i == 1 && j ==1)
					m = 1;
			}
			else
			{
				if(c[i-1][j] >= c[i][j-1])
				{
					c[i][j] = c[i-1][j];	
					b[i][j] = 'u';
					m = 0;
				
				}
				else 
				{
					c[i][j] = c[i][j-1];	
					b[i][j] = 'l';
					m = 0;	
				}
			}
		}
	}
	/*for(int i = 1; i<=count_file_2; i++)
	{
		for(int j = 0; j<=count_file_1; j++)
		{
			printf("%5c", b[i][j]);
		}
		printf("\n");
	}*/
}
	

static char state = 'S', prevstate = 'n';
static int temp, count, ucount, temp2, flag1, flag, lcount, flag2;
int pos1[10];


/*  IMPLEMENTATION OF THE BACK TRACKING OF THE LONGEST COMMON SUBSEQUENCE MATRIX (LCS MATRIX) .
 *  VAR = 1 :- IMPLEMENTATION OF THE -u COMMAND USING QUEQUE.
 *  VAR = 2 :- IMPLEMENTATION OF THE -c COMMAND USING LIST.
 *  VAR = 0 :- IMPLEMENTATION OF THE --normal diff COMMAND USING QUEUQUE.
 */
 
void back_track(int i, int j, int var)
{		
	if(b[i][j] == 'c')
	{
		back_track( i - 1, j - 1, var);

		if(state == 'S')
		{
			state = 'c';
			enqueque(&r, i);
			enqueque(&s, j);
			if(getfrontint(&s) != 1)
			{
				print_diffdeletebegin(var);
			}
			if(getfrontint(&r) != 1)
			{
				print_diffaddbegin(var);
			}			
			if(var == 1) 
			{
	
				printf(" %s\n",brr[i - 1].arr2);
			}
			else if(var == 2)
			{
				add(&t, brr[j - 1].arr1, ' ');
				add(&u, brr[i - 1].arr2, ' ');
			}
			count ++;
		}
		else
		{ 
			if(state == 'u')
			{

				if(ucount != 1 && flag == 0 && flag2 == 0)
				{	
					//printf("why did u enter here !\n");				
					//prevstate  = 'u';
					enqueque(&r, i);
					enqueque(&s, j);
				
				}
				else if(ucount >=1 && flag == 1)
				{
					temp2 =  getfrontint(&r);
					print_diffaddmiddle(temp2, var);
					enqueque(&r, i);
					enqueque(&s, j);   	
				}
				
				else if(ucount >= 1)
				{
					enqueque(&r, i);
					enqueque(&s, j);
					if(flag2 == 1)
					{
						printf("ru entering from here baby\n");
						print_diff3(getfrontint(&s) - 1, var);
						flag2 = 0;
					}
							
				}	
				if(ucount >=1 && flag1 == 1)  
				{
					print_diff2(temp, var);
					enqueque(&r, i);
					enqueque(&s, j);
				}
			}

			else if(state == 'l')
			{
				
				
				enqueque(&r, i);
				enqueque(&s, j);
				print_diffdelete(var);
				
			}
			else if(state == 'c')
			{
				
				enqueque(&r ,i);
				enqueque(&s ,j);
				
			}
			count++; 
			if(var == 1)
			{	
			
				//printf("it is from here\n");
				printf(" %s\n",brr[i - 1].arr2);
				
			}	
			else if(var == 2)
			{
				add(&t, brr[j - 1].arr1, ' ');
				add(&u, brr[i - 1].arr2, ' ');
			}
		
				
		}
		state = 'c';
	}

	else if(b[i][j] == 'u')
	{
		
		back_track( i - 1, j, var );
		
		if(state == 'S')
		{
			state = 'u';
			flag2 = 1;
		}	
		if( state == 'c')
		{	
			if(flag == 0)
			{
				flag = 1;
				enqueque(&q ,i);
				if(i == count_file_2) // ekach u ahee ani at the end ahhee after c
				{
					print_diffaddend(var);
				}
			}
			if( count > 1 && prevstate == 'n')
			{
				if(getfrontint(&r) != 1 && getfrontint(&s) < getfrontint(&r))
				{
					enqueque(&q, i); 
				}
			}
		}
		else if(state == 'l')
		{	
			temp = print_diff1(var);
			enqueque(&q, i);
			if( i == count_file_2)
			{
				print_diff2(temp, var);
			}
			flag1 = 1;
		}	
		else if(state == 'u')
		{	
			enqueque(&q, i);
			if(i == count_file_2)
			{
				if( ( flag == 1 && flag2 == 0 ))  // after c continously u till end
				{
					print_diffaddend(var);
				}
				else if(flag2 == 1)
				{
					print_diff3(j, var);
				}
				else
				{
					print_diff2(temp, var);	
				}
			}
		}
		state = 'u';
		ucount ++;
		lcount = 0;
		count = 0;
	}
	


	else if(b[i][j] == 'l')
	{
		back_track( i, j - 1, var );

		if(state == 'S')
		{
			state = 'l';
		}		
		if(state == 'c')
		{

			if(prevstate == 'n')
			{
				if( getfrontint(&r) > 1 )
				{
					if(getfrontint(&r)!=1) // he nanatr akdhun tak 
					{
						enqueque(&p, j);
						lcount++;
					}	
				}	
				else if(count >=1 ) 
				{
					enqueque(&p, j);
					lcount++;
					if(j == count_file_1 && i == count_file_2)
					{
						print_diffdelete(var);
					}
				}
			}
			if(prevstate == 'u')
			{
				if(count == 1)
				{
					enqueque(&p, j);
					lcount++;
				}	
				else if(flag == 0) 
				{
					print_diff2(temp, var);
					enqueque(&p, j);
					lcount++;
				}
				else if(flag == 1)
				{	
					enqueque(&p, j);
					lcount++;
				}
			}
		}
		else if(state == 'l')
		{
			enqueque(&p, j);
			lcount++;
			if(j == count_file_1 && i == count_file_2)
			{
				print_diffdelete(var);
			}
			
		}
		else if(state == 'u' ) // this is laso changed 
		{
			enqueque(&p, j);
			lcount ++;
		}
		
		state = 'l';
		flag = 0;
		count = 0;
	}
	if(i == 0 || j == 0)
	{
		return;
	}	
}

// FUNCTION TO PRINT THE LINES THAT ARE TO BE CHANGED FROM FILE 1.

int print_diff1(int var)
{
	
	int  i = 0 , j = 0 , ch;
	while(isempty(&p) == 0)
	{
		ch = dequeque(&p);
		pos1[i++] = ch;	
	}
	if(i == 1)
	{
		if(var == 0)
		{
			printf("%d", pos1[0]);
		}
	}
	else
	{
		if(var == 0)
		{
			printf("%d,%d", pos1[0], pos1[i-1]);
		}
	}
	if(var == 0)	
		printf("c");
	
	return i;	
}

// FUNCTION TO PRINT THE LINES THAT ARE TO BE CHANGED FROM FILE 2 .

void print_diff2(int temp, int var)
{
	
	int pos2[10], i = 0 , j = 0 , ch;
	while(isempty(&q) == 0)
	{
		ch = dequeque(&q);
		pos2[i++] = ch;	
	}	
	if(i > 1)
	{	
		if(var == 0)
		printf("%d,%d\n", pos2[0], pos2[i - 1]); 

		for(j = 0; j < temp; j++ )
		{ 
			if(var == 1)
			{
				printf("-%s\n", brr[pos1[j] - 1].arr1);
			}
			else if(var == 2)
			{
				add(&t, brr[pos1[j] - 1].arr1, '!');
			}
			else
			{
				printf("< %s\n", brr[pos1[j] - 1].arr1); // changed to -1
			}
		}
		if(var == 0)
		{
			printf("---\n");
		}
		for(int j = 0 ; j < i; j++)
		{
			if(var == 1)
			{
				printf("+%s\n",brr[pos2[j] - 1].arr2);
			}
			else if(var == 2)
			{
				add(&u, brr[pos2[j] - 1].arr2, '!');
			}
			else
			{
				printf("> %s\n",brr[pos2[j]-1].arr2);
			}
		}
	}
	else
	{
		if(var == 0)
		{
			
			printf("%d\n", pos2[0]);
		}
		
		for(j = 0; j < temp; j++ )
		{
			if(var == 1)
			{
				printf("-%s\n", brr[pos1[j] - 1].arr1);
			}
			else if(var == 2)
			{
				
				add(&t, brr[pos1[j] - 1].arr1, '!');
			}
			else
			{
				printf("< %s\n",brr[pos1[j] - 1 ].arr1);
			}
		}
		if(var == 1)
		{
			printf("+%s\n",brr[ pos2[0] - 1].arr2);
		}
		else if(var == 2)
		{
			add(&u, brr[ pos2[0] - 1].arr2, '!');
		}
		else
		{
			printf("---\n");
			printf("> %s\n",brr[ pos2[0] - 1].arr2);
		}
	}
		
}	

// FUNCTION TO PRINT THE LINES THAT ARE TO BE ADDED AT BEGIN.

void print_diffaddbegin(int var)			
{
	
	int i, m;
	if( (m = getfrontint(&r) ) > 2)	
	{
		if(var == 0)
			printf("0a%d,%d\n",1,m - 1);
		for(i = 0 ; i < m - 1; i++)
		{
			
				
			if(var == 1)
			{
				printf("+%s\n",brr[i].arr2);	
			}
			else if(var == 2)
			{
				add(&u, brr[i].arr2, '+');
			}
			else
			{
				printf("> %s\n",brr[i].arr2);
			}
	
		}
	}
	else
	{
		if(var == 0)
			printf("0a%d\n",1);
		if(var == 1)
		{
			printf("+%s\n",brr[0].arr2);
		}
		else if(var == 2)
		{
			add(&u, brr[0].arr2, '+');
		}
		else
		{	
			printf("> %s\n",brr[0].arr2);
		}
	}

}

// FUNCTION TO PRINT THE LINES THAT ARE ADDED IN THE MIDDLE.
	
void print_diffaddmiddle(int i, int var)
{
	int pos2[10], m = 0;
	while(isempty(&q) == 0)
	{
		pos2[m++] = dequeque(&q);
	}
	
	if(var == 0)
	{
		printf("%da", getrearint(&s)); // cahnged to s 
		if(m == 1)
		{
			printf("%d\n", pos2[m - 1]);
		}	
		else
		{
			printf("%d,%d\n", pos2[0], pos2[m-1]);
		}
	}
	for(i = 0; i < m ; i++)
	{
		
		if(var == 1)
		{
			printf("+%s\n", brr[ pos2[i] -1 ].arr2);	
		}
		else if(var == 2)
		{
			add(&u, brr[pos2[i] - 1].arr2, '+');
		}
		else
			printf("> %s\n", brr[ pos2[i] -1 ].arr2);

	}
}

// FUNCTION TO PRINT THE LINES THAT ARE TO BE ADDED AT END.

void print_diffaddend(int var)
{
	int pos2[10], m = 0;
	while(isempty(&q) == 0)
	{
		pos2[m++] = dequeque(&q);	
	}
	
	if(var == 0)
	{
		printf("%da", count_file_1);
		if(m > 1)
		{
			printf("%d,%d\n", pos2[0], pos2[m-1]);
		}
		else if(m == 1)
		{
			printf("%d\n", pos2[m-1]);
		}
	}	
	for(int i = 0; i < m ; i++)
	{	
		if(var == 1)
		{
			printf("+%s\n", brr[ pos2[i] -1 ].arr2);	
		}
		else if(var == 2)
		{
			add(&u, brr[pos2[i] - 1].arr2, '+');
		}
		else
		{
			printf("> %s\n", brr[ pos2[i] -1 ].arr2);
		}

	}
}

// FUNCTION TO PRINT THE LINES THAT ARE TO BE DELETED.

void print_diffdelete(int var)
{
	int i = 0, j = 0, m;
	int pos[10];
	if(lcount == 1)
	{
		m = dequeque(&p);
		if(var == 0)
		{		
			if(getrearint(&r) == 2 && m == getrearint(&s) - 1)
			{
				printf("%dd%d\n", m, getrearint(&r)- 1/*m-1*/);
			}
			else if(getrearint(&r) == 2)
			{
				printf("%dd%d\n", getrearint(&s) , m);
			}
			else if(getrearint(&r) != 1)
			{
				if(m == count_file_1)
					printf("%dd%d\n", m, getrearint(&r));
				else
					//printf("please enter from here\n");
					printf("%dd%d\n", m, getrearint(&r) - 1);
			}
			else if(getrearint(&r) == 1)
				printf("%dd%d\n", m, getrearint(&r));
		}
		if(var == 2)
			add(&t, brr[m-1].arr1, '-'); // changed to m-1
		else
		{
			if(var == 0)
			{
				printf("> %s\n",brr[m - 1].arr1);
			}
			else
			{
				printf("-%s\n",brr[m - 1].arr1);
			}
				
		}
	}
	else
	{
		while(lcount > 0)
		{
			pos[i++] = dequeque(&p);
			lcount--;
		}
		if(var == 0)
		{
			if( pos[i-1] == count_file_1 )
			{	
				printf("%d,%dd%d\n", pos[0], pos[i-1],count_file_2);
			} 
			else if(state == 'l' && getrearint(&r) != 1)
			{
				printf("%d,%dd%d\n", pos[0], pos[i-1], getrearint(&r) - 1 );
			}
			else if(state == 'l' && getrearint(&r) == 1)
			{
				printf("%d,%dd%d\n", pos[0], pos[i-1], getrearint(&r));
			}
		}
	
		for( j = 0; j < i ; j++)
		{
			if(var == 1)
			{
				printf("-%s\n", brr[ pos[j] - 1].arr1);	
			}
			else if(var == 2)
			{
				add(&t, brr[pos[j] - 1].arr1, '-');
			}
			else
			{
				printf("< %s\n", brr[ pos[j] - 1].arr1);
			}
		}
	}	
	lcount = 0;
}
	
// FUNCTION TO PRINT THE LINES THAT ARE TO BE DELTED AT BEGIN :

void print_diffdeletebegin(int var)
{
	int i, m =  getfrontint(&s);
	if(var == 0)	
	{
		if(m <= 3 )
		{
			for( i = 1; i < m ; i++ )
			{	
				printf("%d", i);
				if(i % 2 != 0 && i != m - 1 )
				{
					printf(",");
				}		 
			}
		}	
		else
		{
			printf("%d,%d", 1, m -1);
			
		}
		printf("d0\n");
	}
	
	for(i = 1; i < m ;i++ )
	{
		if(var == 1)
		{
			printf("-%s\n", brr[ i - 1 ].arr1);
		}
		else if(var == 2)
		{
			add(&t, brr[i-1].arr1, '-');
		}
		else
		{		
			printf("< %s\n", brr[i -1 ].arr1);
		}
	}
}

// FUNCTION TO PRINT THE LINES THAT CHANGE :

void print_diff3(int m, int var)
{
	int pos2[10], i = 0 , j = 0;
	while(isempty(&q) == 0)
	{
		pos2[i++] = dequeque(&q);
	}	
	if(i > 1 || m > 1)
	{
		if(var == 0)
		{
			if(i != 1 && m != 1)
				printf("%d,%dc%d,%d\n", pos2[0], m, pos2[0], pos2[i - 1]);		
			else if (m == 1)
				printf("%dc%d,%d\n", m, pos2[0], pos2[i-1] );
			else
				printf("%d,%dc%d\n", pos2[0], m, pos2[0]);
		} 

		for(j = 0; j < m ; j++ )
		{
			if(var == 1)
			{
				printf("-%s\n", brr[j].arr1);	
			}
			else if(var == 2)
			{
				add(&t, brr[j ].arr1,'!');
			}
			else
			{
				printf("< %s\n", brr[/*pos2[j]*/ j ].arr1);
			}  
		}
		if(var == 0)
			printf("---\n");
		for(int j = 0 ; j < i; j++) 
		{
			if(var == 1)
			{
				printf("+%s\n",brr[pos2[j] - 1].arr2);
			}
			else if(var == 2)
			{
				add(&u, brr[ pos2[j] - 1].arr2, '!');
			}			
			else
			{
				printf("> %s\n",brr[pos2[j] - 1].arr2);
			}
		}
	}
	else
	{
		if(var == 0)
		{
			printf("%dc%d\n", pos2[0], pos2[0]);
		}
	
		for(j = 0; j < m; j++ )
		{
			if(var == 1)
			{
				printf("-%s\n",brr[pos1[j]].arr1);	
			}
			else if(var == 2)
			{
				add(&t, brr[pos1[j]].arr1, '!');
			}
			else
			{
				printf("< %s\n",brr[pos1[j]].arr1);
			}
		}
		if(var == 1 )
		{
			printf("+%s\n",brr[ pos2[0] - 1].arr2);	
		}
		else if(var == 2)
		{
			add(&u, brr[pos2[0] - 1].arr2, '!');
		}
		else
		{
			printf("---\n");
			printf("> %s\n",brr[ pos2[0] - 1].arr2);
		}
	}
}




