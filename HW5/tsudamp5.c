/* -----------------------------------------------------------------------------
Program file: tsudamp5.c 
Author:       Makiko Tsuda
Date:         11/6/2021
Class:		  Intro to Programming with C Part 2
Assignment:   #5 
Objective:    The program reads a text file with data about people. 
			  Then sorts the data based on a criterion and outputs
			  the result to the screen and a file.
------------------------------------------------------------------------------*/
#include <stdio.h>
#include <time.h>
#include <string.h> 
#include <stdlib.h>

/* Define values to be used */
#define FILE_NAME_LEN 	30 			/* file name length */
#define NUM_INFO		100			/* Number of Record to be processed */

/* Struct declarations */
struct date
{
	int yyyy;
	int mm;
	int dd;
};// end date

struct name
{
	char lname[15];
	char fname [10];
	char middle_initial;
};// end name

struct information
 {
	struct name lfm;
	char address[20];
	char city[15];
	char state[3];
	long zip;
	struct date fdate;
 }; // end struct info
 
/* Function Prototypes */
void 	sort_by_zip(struct information[], int);
void 	sort_by_name(struct information[], int);
void 	safer_gets(char[], int);
void 	nice_time(char[]);
int 	read_info(struct information[], FILE *);
int 	display_report(struct information[], int, char[]);
int 	display_labels(struct information[], int);
int 	print_report(FILE *, int, struct information[], char[]);
int 	print_labels(FILE *, int, struct information[]);
void	uppercase_it(char[], char[]);
void 	merge_name(char[], char[], char[], char);

 
int main(void)
{
	/* Variable Declarations */
	char		in_file_name[FILE_NAME_LEN];
	char		report_file_name[FILE_NAME_LEN] = "report5.txt";
	char		labels_file_name[FILE_NAME_LEN] = "label5.txt";
	struct 		information info_array[NUM_INFO];
	int			num_friend;
	int 		option;
	int 		fcount;
	FILE 		*in_file_ptr, *out_file_ptr;
	char 		c;													
	/* TIME STUFF */
	char		date_and_time[25]=" ";
 	char 		short_date_and_time[30]=" ";	
  	time_t 		rawtime;
    struct tm 	*timeptr;									
	
	/* Welcome Message and get the input file name */
	printf("Welcome to Intro to Programming Friends program.\n\n");
	
	do /* loop until a valid file name is entered */
	{
		printf("Enter File name: ");
		safer_gets (in_file_name, FILE_NAME_LEN);  

		/* Open the file */
		in_file_ptr = fopen (in_file_name, "r");
	
		/* anything goes wrong */
   		if ( in_file_ptr == NULL )
   		{
      		printf ("\n Cannot open file %s for reading.\n\n", in_file_name);
      		
   		}/* end if */
   		
	} while (in_file_ptr == NULL); /* end while */
		
	
	/* read data from the file and store it to an array of struct */
	fcount = read_info(info_array, in_file_ptr);
	printf("\nYou have %d Friends\n\n", fcount);
	
	/* Calculate time */
	nice_time(short_date_and_time); 
	
	/* Select an option */
	do /* loop until '3' is entered */
	{
		printf("Options: \n");
		printf("(1)	Print Report\n");	
		printf("(2)	Print Labels\n");
		printf("(3)	Exit Program\n\n");
	
		printf("Please enter your selection: ");
		scanf ("%d", &option); 
		while ((c = getchar() != '\n') && c != EOF); /* clear buffer */
		
		/* Display and create a report file */
		if (option == 1)
		{
			/* open the output file */
			out_file_ptr = fopen (report_file_name, "w");
			
			/* if an output file cannot be opened, exit */
			if ( out_file_ptr == NULL )
   			{
       			printf ("\n Cannot open file label5.txt for writing.\n");
       			return 1;
   			} /* end if */
   			
			sort_by_name(info_array, fcount);
			display_report(info_array, fcount, short_date_and_time);
			print_report(out_file_ptr, fcount, info_array, short_date_and_time);
			printf("\n\t\t(Report has been sent to %s)\n\n", report_file_name);
			
			/* close the output file */
			fclose (out_file_ptr);
			
		} /* end if */
		
		/* Display and create a label file */
		else if (option == 2)
		{
			out_file_ptr = fopen (labels_file_name, "w");
			
			/* if an output file cannot be opened, exit */
   			if ( out_file_ptr == NULL )
   			{
       			printf ("\n Cannot open file label5.txt for writing.\n");
       			return 1;
   			} /* end if */
   	
			sort_by_zip(info_array, fcount);
			display_labels(info_array, fcount);
			print_labels(out_file_ptr, fcount, info_array);
			printf("\n\t\t(Labels have been sent to %s)\n\n", labels_file_name);
			
			/* close the output file */
			fclose (out_file_ptr);
					
		} /* end option 2 else if */
		
		/* Exit the program */
		else if (option == 3)
		{
			printf("Thank you for using the program\n");
			return 0;
		} /* end option3 else if */
		
		else
		{
			printf("\nInvalid option. Please re-enter:\n\n");
		} /* end else */
		
	} while (option != 3); /* end while */
	
	/* Close the files. */
   	/* --------------------- */
 
   	fclose (in_file_ptr);
   	
   	getchar();  
   	
	return 0;
} /* end main */


/* safer_gets adapted from the course resource.   */
/* Accepts a string input and make sure the input */
/* does not over flow the allocated space		  */
void safer_gets (char array[], int max_chars)
{
	/* Variable */
	int 	i;		/* a counter */

  	for (i = 0; i < max_chars - 1; i++)
  	{
     	array[i] = getchar();

		/* if it was a new line character, end the loop */
     	if (array[i] == '\n')
     	{
        	break;
     	} /* end if */
  
   	} /* end for */


   	if (i == max_chars - 1 )
   	{
     	if (array[i] != '\n')
     	{
       		while (getchar() != '\n');
     	} /* end if */
     
   	} /* end if */

	/* Terminate the string */
 	array[i] = '\0';

} /* end safer_gets */


/* A function to open an input file and read the contents */
int read_info(struct information info_array[], FILE * in_file_ptr)
{
	/* Variable Declarations */
	int 	i, count = 0;
	
	/* Obtain information from input data file, store in structure. */
   	/* ------------------------------------------------------------ */
 
   	for ( i = 0; !feof(in_file_ptr) && i < NUM_INFO; i++ )
   	{
 
   		fscanf (in_file_ptr, "%[^\n]\n", &info_array[i].lfm.lname);   	
      	fscanf (in_file_ptr, "%[^\n]\n", &info_array[i].lfm.fname);   	
      	fscanf (in_file_ptr, "%[^\n]\n", &info_array[i].lfm.middle_initial);      
       	fscanf (in_file_ptr, "%[^\n]\n", &info_array[i].address);     	
       	fscanf (in_file_ptr, "%[^\n]\n", &info_array[i].city);     
       	fscanf (in_file_ptr, "%[^\n]\n", &info_array[i].state);     
      	fscanf (in_file_ptr, "%lu\n", &info_array[i].zip);             
		fscanf (in_file_ptr, "%d/%d/%d", &info_array[i].fdate.mm, 
				&info_array[i].fdate.dd, &info_array[i].fdate.yyyy); 
     	
        count++;

      	/* ---------------------------------------------- */
      	/* Read in either the \n after the zipcode,       */
      	/* or the EOF indicator and end of input file.    */
      	/* ---------------------------------------------- */
 
      	fgetc (in_file_ptr);
 
   	}  /* end for loop */
	
	/* return the number of record */
	return count;
		
} /* end read_info */


/* outputs the given array to the screen and a file */
int print_report(FILE *out_file_ptr, int count, struct information info_array[], char short_date_and_time[]) 
{
	/* Variable Declarations */
	int		i;
	char	fullname[15]; 		/* store concat name */
	char	temp_middle[3]; 	/* for middle initial */
	
		
	fprintf(out_file_ptr, "\n\n");
	fprintf(out_file_ptr, "                       		Friends Report 	%s\n", short_date_and_time);
	fprintf(out_file_ptr, "                       		-------------------------------------------- \n\n");

   	fprintf(out_file_ptr, "Name 						  Address 		       City 		   St 	  Zip 	   Friended\n");
	fprintf(out_file_ptr, "===============================================================================================\n");

	fprintf(out_file_ptr, "\n");
		
	/* Concat the first, last, and the middle initial for all friends */
	
	for ( i = 0; i < count; i++ )
	{	
		/* concat the name elements */		
		merge_name(fullname, info_array[i].lfm.lname, info_array[i].lfm.fname, info_array[i].lfm.middle_initial);
		
		fprintf(out_file_ptr, "%-29s %-20s %-15s %-6s %5.5ld %5.02d/%02d/%d\n", fullname,
			info_array[i].address,info_array[i].city,info_array[i].state,
			info_array[i].zip,info_array[i].fdate.mm,info_array[i].fdate.dd, 
			info_array[i].fdate.yyyy);
	} /* end for */
		
	return 0;
	
} /* end of print_report */


/* A function to display a report on screen */
int display_report(struct information info_array[], int count, char short_date_and_time[])
{
	/* Variable Declarations */
	int		i;
	char	fullname[15]; 		/* store concat name */
	char	temp_middle[3]; 	/* for middle initial */	
		
		
	printf("\n\n");
	printf("                       		Friends Report 	%s\n", short_date_and_time);
	printf("                       		-------------------------------------------- \n\n");

   	printf("Name 			      Address 	    	   City 	   St     Zip 	   Friended\n");
	printf("===================================================================================================\n");

	printf("\n");
		
	/* Concat the first, last, and the middle initial for all friends */
	for ( i = 0; i < count; i++ )
	{
		/* concat the name elements */		
		merge_name(fullname, info_array[i].lfm.lname, info_array[i].lfm.fname, info_array[i].lfm.middle_initial);
		
		printf("%-29s %-20s %-15s %-6s %5.5ld %5.02d/%02d/%d\n", fullname,
			info_array[i].address,info_array[i].city,info_array[i].state,
			info_array[i].zip,info_array[i].fdate.mm,info_array[i].fdate.dd, 
			info_array[i].fdate.yyyy);
	} /* end for */
	
	return 0;
} /* end display_report */


/* display the sorted labels to screen */
int display_labels(struct information info_array[], int count)
{
	/* Variable Declarations */
	int		i;
	
	/* just some spacer */
	printf("\n\n");
	
	for ( i = 0; i < count; i++ )
	{
		printf("%s %c %s\n", info_array[i].lfm.fname,
				info_array[i].lfm.middle_initial,info_array[i].lfm.lname);
		printf("%s\n",info_array[i].address);
		printf("%s, %s %5.5ld\n\n\n", info_array[i].city,info_array[i].state,
				info_array[i].zip); 
	} /* end for */
	
	return 0;
} /* end display_labels */


/* print sorted (by zip) labels to a file */
int print_labels(FILE *out_file_ptr, int count, struct information info_array[])
{
	/* Variable Declarations */
	int 	i;
		
	for ( i = 0; i < count; i++ )
	{
		fprintf(out_file_ptr, "%s %c %s\n", info_array[i].lfm.fname,
				info_array[i].lfm.middle_initial,info_array[i].lfm.lname);
		fprintf(out_file_ptr, "%s\n",info_array[i].address);
		fprintf(out_file_ptr, "%s, %s %5.5ld\n\n\n", info_array[i].city,info_array[i].state,
				info_array[i].zip); 
	} /* end for */
	
	return 0;
} /* end print_labels */


/* function for time format, adapted from s sample program for this class */
void nice_time(char str2[])
{
	/* Variable Declarations */
    char 		str1[27],  ampm[5] = "a.m.";
	char 		day[4],mon[4],dow[3],tim[9], yr[5];
	char 		hra[3];
	int 		i,j, hr;

	/* time stuff starts here */	
	time_t 		rawtime;   
    struct tm 	*timeptr;
    
    time(&rawtime);
  	timeptr = localtime(&rawtime);

   	/* time stuff ends here */
	strncpy(str1, asctime(timeptr),24);

	strncpy(str2,str1,4);
	strncat(str2,&str1[4],4);
	strncat(str2,&str1[8],2);
	strcat(str2,", ");
	strncat(str2,&str1[20],4);
	strcat(str2," ");	
	strncpy(tim, &str1[11],8);
 	
    hr = atoi(tim);

   	if(hr >= 12)  
   	  ampm[0] = 'p';
   	  
   	if (hr==24) strcat(str2, "12");
	if (hr==23) strcat(str2, "11");
	if (hr==22) strcat(str2, "10");
	if (hr==21) strcat(str2, "9");
	if (hr==20) strcat(str2, "8");
	if (hr==19) strcat(str2, "7");
	if (hr==18) strcat(str2, "6");
	if (hr==17) strcat(str2, "5");
	if (hr==16) strcat(str2, "4");
	if (hr==15) strcat(str2, "3");
	if (hr==14) strcat(str2, "2");
	if (hr==13) strcat(str2, "1");
	if (hr==12) strcat(str2, "12");
   	if (hr==11) strcat(str2, "11");
	if (hr==10) strcat(str2, "10");
	if (hr==9) strcat(str2, "9");               
	if (hr==8) strcat(str2, "8");
	if (hr==7) strcat(str2, "7");
	if (hr==6) strcat(str2, "6");
	if (hr==5) strcat(str2, "5");
	if (hr==4) strcat(str2, "4");
	if (hr==3) strcat(str2, "3");
	if (hr==2) strcat(str2, "2");
	if (hr==1) strcat(str2, "1");


	strncat(str2,&tim[2],3);
	strcat(str2," ");
	strcat(str2,ampm);

}/* end nice time */


/* sort the struct of people information by zip code */
void  sort_by_zip(struct information info_array[], int count)
{
	/* Variable Declarations */
    int    i, j;
    struct information temp_info;
    
 	for ( i = 0;  i < count - 1;  ++i )
 	{
        for ( j = i + 1;  j < count;  ++j )
        {
            if ( info_array[i].zip > info_array[j].zip ) 
			{
                temp_info = info_array[i];
                info_array[i] = info_array[j];
                info_array[j] = temp_info;
            } /* end if */
            
        } /* end for */
        
	} /* end for */
	
} /* end sort_by_zip */


/* A function to sort by last name, then first name, then middle initial */
void sort_by_name(struct information info_array[], int count)
{
	/* Variable Declarations */
    int    i, j, k, comp_lname, comp_fname;
    char   temp_lname1[15], temp_lname2[15], temp_fname1[10], temp_fname2[10];
    struct information temp_info;
    
    for ( i = 0; i < count - 1;  ++i )
    {
    	for ( j = i + 1;  j < count;  ++j )
        {
        	/* Uppercae names to compare */
        	uppercase_it(info_array[i].lfm.lname, temp_lname1);
        	uppercase_it(info_array[j].lfm.lname, temp_lname2);
        	
        	/* compare last names and store the result */
        	comp_lname = strcmp(temp_lname1, temp_lname2);
        	
        	if ( comp_lname > 0 )
        	{	
        		/* swap */
          		temp_info = info_array[i];
                info_array[i] = info_array[j];
                info_array[j] = temp_info;
                
        	}/* end if swap needed */
        	
			/* Same last names, compare first names */
        	else if ( comp_lname == 0 )
        	{ 	
        		/* Uppercae names to compare */
        		uppercase_it(info_array[i].lfm.fname, temp_fname1);
        		uppercase_it(info_array[j].lfm.fname, temp_fname2);
        		
        		/* Compare firts names */
        		comp_fname = strcmp(temp_fname1, temp_fname2);

       			if ( comp_fname > 0 )
        		{
        			/* swap */
          			temp_info = info_array[i];
                	info_array[i] = info_array[j];
                	info_array[j] = temp_info;
        		} /* end if to compare first name */
        		
				/* First names also the same,*/
        		else if ( comp_fname == 0 )
        		{
        			/* compare middle initials */
        			if ( toupper(info_array[i].lfm.middle_initial) > toupper(info_array[j].lfm.middle_initial) ) 
					{
        				/* swap */
          				temp_info = info_array[i];
                		info_array[i] = info_array[j];
                		info_array[j] = temp_info;
        			} /* end if to compare middle initials */
        			
        		} /*end else if */
        		
        	} /* end else if the same last names */
        	
        } /* end for inner loop */
        
    } /* end for outer loop */
    
} /* end sort by name */


/* Uppercase the array passed to it */
void uppercase_it(char char_array[], char uppercase_array[])
{
	/* Variable Declarations */
	int		array_size = strlen(char_array)+1;
	int		i;
	
	for ( i = 0; i < array_size; i++ )
	{
		uppercase_array[i] = toupper(char_array[i]);
	} /* end for */
	
	/* put null terminate character */
	uppercase_array[i+1] = '\0';
}

/* Concat the name elements, and create a merged full name string */
void merge_name(char fullname[], char lastname[], char firstname[], char mid_initial) 
{
	char	temp_middle[3]; 	/* for middle initial */
	
	/* copy the middle initial to an array */
	temp_middle[0] = ' ';
	temp_middle[1] = mid_initial;
	temp_middle[2] = '\0';
	
	/* concat the name elements */
	strcpy(fullname, lastname);
	strcat(fullname, ", ");
	strcat(fullname, firstname);
	strcat(fullname, temp_middle);
	/* terminate the string*/
	fullname[strlen(fullname)] = '\0';	
	
} /* end merge_name */
