#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<strings.h>
#include<errno.h>  
#include<unistd.h>


void write_bothfile(FILE *, FILE *, int count);
void write_file2(FILE * , FILE *);
void write_file1(FILE * , FILE *, int);

int main(int argc, char * argv[])
{	
	FILE * fp1, * fp2;
	char arr[100], ch;
	int i = 0,k = 0, line_count = 0, flag = 0, count = 0, count_file_1 = 0;
	if(argc < 3)
	{
		perror("Inavlid Inputs\n");
		return errno;
	}
	
	//OPENING THE PATCHED FILE IN THE READ MODE :
	
	fp1 = fopen(argv[2], "r");
	if(fp1 == NULL)
	{
		perror("opening error :");
		return errno;
	}
	//OPENING THE ORGINAL FILE IN THE READ WRITE MODE :
	
	fp2 = fopen(argv[1], "r+");	
	if(fp2 == NULL)
	{
		perror("opening error :");
		return errno;
	}
	ch = fgetc(fp1);
	
	// IMPLEMENTATION OF -U PATCH COMMAND :
	
	if(ch == '+')
	{
		flag = 0; 
	}
	
	// IMPLEMENTATION OF -C PATCH COMMAND :
	
	else if(ch == '*')
	{
		flag = 1;
	}
	do 
	{
		ch = fgetc(fp1);
		if(ch == '\n')
		{
			line_count++;
		}
	}while(line_count != 3);

	// -U OPTION :
	
	if(flag == 0)
	{

		do 
		{
			if(ch == '\n')
			{
				line_count++;
			}
		}while(line_count != 3);
		while(fscanf(fp1, "%c", &ch) != EOF)
		{
			if(ch != '-')
			{						
				while( 1 )
				{
					fscanf(fp1, "%c", &ch);
					if(ch == '\n' || ch == EOF  )	
					{
						
						break;
					}
					arr[i++] = ch;
				}
				arr[i] = '\0';
				fwrite(arr, 1, strlen(arr), fp2);
				ftruncate(fileno(fp2), strlen(arr));	
				fwrite("\n", sizeof(char), 1, fp2);
				i = 0; 
			}
			else if(ch == '-')
			{
				do
				{
					if(ch == EOF)
					{
						break;
					}
					fscanf(fp1, "%c", &ch);
	
				}while(ch != '\n');
			}
		}
	}
	
	// -C OPTION :
		
	else if(flag == 1)
	{
		do
		{
			ch = fgetc(fp2);
			if(ch == '\n' || ch == EOF)
			{
				count_file_1++;
			}
		}while(ch != EOF);
		count_file_1 --;
		fseek(fp2, 0, SEEK_SET);
		line_count = 0;
		do
		{
			ch = fgetc(fp1);
			if(ch == '\n' || ch == EOF)
			{
				count++;
			}
		}while(ch != EOF);
		count = count + 2;
		fseek(fp1, 0, SEEK_SET);
		
		if(count == count_file_1 + 5)
		{
			while(i != 4)
			{
				fscanf(fp1, "%100[^\n]\n", arr);
				i++;
			}	
			write_file1(fp1, fp2, count_file_1);
		}
		else if(count > count_file_1 + 5)
		{
			write_bothfile(fp1, fp2, count_file_1);
		}
		else
		{
			write_file2(fp1, fp2);	
		}
	}
	fclose(fp1);
	fclose(fp2);
	return 0;
}
	
void write_bothfile(FILE * fp1, FILE * fp2, int count)
{
	char ch;
	char buffer[100];
	int temp = 0;
	while(temp != count + 5)
	{
		fscanf(fp1, "%100[^\n]\n", buffer);
		temp++;
	}
	write_file2(fp1, fp2);
}

void write_file2(FILE * fp1, FILE * fp2)
{
	char ch, arr[100];
	int i = 0;
	while(1)
	{
		ch = fgetc(fp1);
		ch = fgetc(fp1);
		while(ch != '\n' && ch != EOF)
		{
			ch = fgetc(fp1);
			arr[i++] = ch;
		}
		arr[i] = '\0';
		fwrite(	arr,1, strlen(arr), fp2);
		ftruncate(fileno(fp2), strlen(arr));
		i = 0;
		if(ch == EOF)
		{
			break;
		}
	}
			
}

void write_file1(FILE * fp1, FILE * fp2, int temp)
{
	int i = 0;
	char ch, arr[100];
	while(temp > 0)
	{
		ch = fgetc(fp1);
		if(ch == ' ')
		{		
			fgetc(fp1);				
			while( 1 )
			{
				fscanf(fp1, "%c", &ch);
				if(ch == '\n')	
				{
					
					break;
				}
				arr[i++] = ch;
			}
			arr[i] = '\0';
			printf("%s\n", arr);
			fwrite(arr, 1, strlen(arr), fp2);
			ftruncate(fileno(fp2), strlen(arr));	
			fwrite("\n", sizeof(char), 1, fp2);
			i = 0; 
		}
		else if(ch == '-')
		{
			do
			{
				fscanf(fp1, "%c", &ch);	
			}while(ch != '\n');
		}
		temp--;
	
	}
}
			
			
	
		
	
	
	

