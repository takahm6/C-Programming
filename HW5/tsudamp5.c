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
void sort_by_zip(struct information[], int);
void sort_by_name(struct information[], int);
void safer_gets(char[], int);
int read_info(struct information[], FILE *);
int print_report();
int display_report(struct information[], int);
int print_labels();
void nice_time(char[]);
 
int main(void)
{
	/* Variable Declarations */
	char	in_file_name[FILE_NAME_LEN];
	char	report_file_name[FILE_NAME_LEN] = "report5.txt";
	char	labels_file_name[FILE_NAME_LEN] = "label5.txt";
	struct 	information info_array [NUM_INFO];
	int		num_friend;
	int 	option;
	int 	fcount;
	FILE 	*in_file_ptr, *out_file_ptr;
	char 	c;													/* buffer clearing */
	/* TIME STUFF */
	char	date_and_time[25]=" ";
 	char 	short_date_and_time[30]=" ";	
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
      		printf ("\n Cannot open file %s for reading.\n", in_file_name);
      		//return 1;
   		}// end if
   		
	} while (in_file_ptr == NULL); /* end while */
		
	
	/* read data from the file and store it to an array of struct */
	fcount = read_info(info_array, in_file_ptr);
	printf("You have %d Friends\n\n", fcount);
	printf("First Friend %s \n", info_array[0].lfm.lname);
	printf("Last Friend %s \n", info_array[4].lfm.lname);
	
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
		
		if (option == 1)
		{
			display_report(info_array, fcount);
			print_report();
			printf("(Report has been sent to %s)\n\n", report_file_name);
		}
		else if (option == 2)
		{
			print_labels();
			printf("(Labels have been sent to %s)\n\n", labels_file_name);
		}
		else if (option == 3)
		{
			printf("Thank you for using the program\n");
			return 0;
		}
		else
		{
			printf("Invalid option. Please re-enter:\n");
		}
		
	} while (option != 3); /* end while */
	
	/* Close the files. */
   	/* --------------------- */
 
   	fclose (in_file_ptr);
   	fclose (out_file_ptr);
   	
   	getchar();  
   	
	return 0;
}

/* safer_gets adapted from the course resource.   */
/* Accepts a string input and make sure the input */
/* does not over flow the allocated space		  */
void safer_gets (char array[], int max_chars)
{
	/* Variable */
	int i;		/* a counter */

  	for (i = 0; i < max_chars - 1; i++)
  	{
     	array[i] = getchar();

		/* if it was a new line character, end the loop */
     	if (array[i] == '\n')
     	{
        	break;
     	} /* End if */
  
   	} /* end for */


   	if (i == max_chars - 1 )
   	{
     	if (array[i] != '\n')
     	{
       		while (getchar() != '\n');
     	} /* End if */
     
   	} /* End if */

	/* Terminate the string */
 	array[i] = '\0';

} /* end safer_gets */

int read_info(struct information info_array[NUM_INFO], FILE * in_file_ptr)
{
	/* Variable Declarations */
	int i, count = 0;
	
	   	/* Obtain information from input data file, store in structure. */
   	/* ------------------------------------------------------------ */
 
   	for ( i = 0; !feof(in_file_ptr) && i < 100; i++ )
   	{
 
   		fscanf (in_file_ptr, "%[^\n]\n", &info_array[i].lfm.lname);   	/* last name  */
      	fscanf (in_file_ptr, "%[^\n]\n", &info_array[i].lfm.fname);   /* read addr  */
      	fscanf (in_file_ptr, "%[^\n]\n", &info_array[i].lfm.middle_initial);      /* read city  */
       	fscanf (in_file_ptr, "%[^\n]\n", &info_array[i].address);     /* read street addr */
       	fscanf (in_file_ptr, "%[^\n]\n", &info_array[i].city);     /* read city */
       	fscanf (in_file_ptr, "%[^\n]\n", &info_array[i].state);     /* read state */
      	fscanf (in_file_ptr, "%d\n", &info_array[i].zip);             /* read zip   */
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
}

/* outputs the given array to the screen and a file */
int print_report() 
{
	printf("print report\n");
	return 0;
	
} /* end of print_report */

int display_report(struct information info_array[], int count)
{
	/* Variable Declarations */
	int		i;
	
	printf("\n\n");
	printf("                       		Friends Report \n");
	printf("                       		---------------- \n\n");

   	printf("	Name 		Address 		City 		St 		Zip 		  Friended\n");
	printf("==========================================================================\n");

	printf("\n");
	
	printf("%-13s, %10s %c%10s%5s%6d%5s %d/%d/%d\n", info_array[1].lfm.fname, 
			info_array[1].lfm.lname,info_array[1].lfm.middle_initial,
			info_array[1].address,info_array[1].city,info_array[1].state,
			info_array[1].zip,info_array[1].fdate.mm, info_array[1].fdate.dd, 
			info_array[1].fdate.yyyy);
	/*
	for ( i = 0; i < count; i++ )
	{
		printf("%-13s, %10s %c%10s%5s%6d%5s %d/%d/%d\n", info_array[i].lfm.fname, 
			info_array[i].lfm.lname,info_array[i].lfm.middle_initial,
			info_array[i].address,info_array[i].city,info_array[i].state,
			info_array[i].zip,info_array[i].fdate.mm, info_array[i].fdate.dd, 
			info_array[i].fdate.yyyy);
	}
	*/
	return 0;
}

int print_labels()
{
	printf("print labels\n");
	
	return 0;
}

// function for time format

void nice_time(char str2[])
{

    char str1[27],  ampm[5] = "a.m.";
	char day[4],mon[4],dow[3],tim[9], yr[5];
	char hra[3];
	int i,j, hr;

	/* time stuff starts here */
	
	time_t rawtime;   
    struct tm *timeptr;
    
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

}// end nice time
