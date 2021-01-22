#include"LCS.c"
#include"help.c"

int main(int argc, char *argv[])
{
	int fd1, fd2;

	initintque(&p);
	initintque(&q);
	initintque(&r); 
	initintque(&s);
	init(&t);
	init(&u);
	
        // IMPLEMENTATION OF DIFF HELP COMMAND
	 
	if( strcmp(argv[1], "--help") == 0)   
	{
		help();
		exit(0);
	}	
	
	// CHECKING THE NUMBER OF COMMAND LINE ARGUMENTS:

	if(argc < 3 )
	{	
		perror("invalid inputs :");
		return errno;
	}
	switch(argc)
	{
		case 3:	
			fd1 = open(argv[1], O_RDONLY);

			// CHECK ON FILE OPENIENG ERROR :
			if(fd1 == -1)
			{
				perror("opening error:");
				return errno;	
			}
	
			fd2 = open(argv[2], O_RDONLY);

			// CHECK ON FILE OPNEING ERROR:

			if(fd2 == -1)
			{
				perror("opening error:");
				return errno;	
			}
			break;

		case 4:
			fd1 = open(argv[2], O_RDONLY);

			// CHECK ON FILE OPENIENG ERROR :
			if(fd1 == -1)
			{
				perror("opening error:");
				return errno;	
			}
	
			fd2 = open(argv[3], O_RDONLY);

			// CHECK ON FILE OPNEING ERROR:

			if(fd2 == -1)
			{
				perror("opening error:");
				return errno;	
			}
			break;
			
		default:
			break;
	}
	
	write_file(fd1, fd2, argv);
	
	int x = LCS(argv);
	
       /*   IMPLEMENTATION OF -u (unified output) COMMAND  :
	*   PRINTS THE OUPUT IN THE UNIFIED CONTEXT
	*/
	
	if(strcmp(argv[1], "-u") == 0 || strcmp(argv[1], "-c") == 0)	
	{		
		struct stat filestat1;
		struct stat filestat2;
		stat(argv[2], &filestat1);
		stat(argv[3], &filestat2);
		char t1[500], t2[500];
		strftime(t1, 500, "%F %H:%M:%S %z", localtime(&filestat1.st_mtime));
		strftime(t2, 500, "%F %H:%M:%S %z" , localtime(&filestat2.st_mtime));

		if(strcmp(argv[1], "-u") == 0)
		{
			printf("+++ %5s  	 %s\n", argv[2], t1);
			printf("--- %5s	 %s\n", argv[3], t2);
			printf("@@ -%d,%d +%d,%d @@\n", 1, count_file_1, 1, count_file_2);
			back_track(count_file_2 , count_file_1, 1);
		}
		
	       /*   IMPLEMENTATION OF -c (context output) COMMAND  :
   		*   PRINTS THE OUPUT IN THE COPIED CONTEXT
		*/
		
		else
		{
			printf("*** %5s  	%s\n", argv[2], t1);
			printf("--- %5s	%s\n", argv[3], t2);
			printf("****************\n");
			back_track(count_file_2 , count_file_1, 2);
			printf("*** %d,%d ***\n", 1, count_file_1);
			display(&t);
			printf("--- %d,%d ---\n", 1, count_file_2);		
			display(&u);
		}
				
	}
	
	//IMPLEMENTATION OF NORMAL DIFF COMMAMD.
		
	else	
	{
		back_track(count_file_2 , count_file_1, 0);
	}
	
	close(fd1);
	close(fd2);

	return 0;
}





