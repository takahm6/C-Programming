/* -----------------------------------------------------------------------------
Program file: tsudamp1.c 
Author:       Makiko Tsuda
Date:         9/10/2021
Class:		  Intro to Programming with C Part 2
Assignment:   #1 
Objective:    The program determines the minimum grade, maximum grade, median grade and 
 			  average of a class. The program should first prompt for class name, 
			  and then allow user to select how many grades validated(at least 5, 
			  but no more than the number of data). The student grades are sorted
			  in descending order and the Class Grade
			  Report is printed.
------------------------------------------------------------------------------*/

#include <stdio.h>

/* Function Prototypes */
int bubble_sort(int[], int[], char[][20], int);

int main(void) 
{
	/* Variable Declarations */
	char class_name[50];		/* For the name of the class */
	int  num_grades;			/* How many grades to stor   */
	int  grade[30];				/* Store the grades in the original order */
	int  idno[30] = {11111,22222,33333,44444,55555,66666,77777,12345,67890,56789};
	char name[30][20] =
	{
		"Jeorge Sanchez", "Ali Wang", "Jane Smith", "Ginika Adichie", 
		"Bill Bailey", "Carl Marks", "Joy Fully", "Chris Tal", 
		"Miki Yamada", "Junyuan Kim"
	};							/* Students' Names */
	int   total_grade = 0;		/* Initialize it to zero */
	float avg_grade = 0;		/* Initialize it to zero */
	char  c; 					/* For buffer clearing */
	int   i;	 				/* Counter value */
	int   input;				/* Grade value entered by a user */
	char  changed = 'T';   		/* a flag to indicate if a swap was made */
	float median = 0;			/* Median */
	
	/* Prompt for the Name of the class and the number of grades */
	printf("Enter Class Name: ");
	scanf("%50[^\n]s", class_name);
 	while ((c = getchar() != '\n') && c != EOF); /* clear buffer */
 	
 	/* At least 5, at most 10 grades to process */
 	do
 	{
		printf("The number of grades to process: ");
		scanf("%d", &num_grades);
 		while((c = getchar() != '\n') && c != EOF); /* clear buffer */
 		
 		if (num_grades < 5 || num_grades > 10)
 		{
 			printf("Please enter the number between 5 and 10.\n\n");
 		}
 		
 	} while (num_grades < 5 || num_grades > 10); /* End while */
 	
 	/* Have the uer enter the grades */
 	printf("Enter grade for %d students: ", num_grades);
 	printf("\n\n");
 	printf("Enter Class Name: %s\n", class_name);	 
 	printf("The number of grades to process: %d\n", num_grades);
 	printf("Enter grade for %d students: \n", num_grades);
 	
	/* Get the grade for each student and store them in the grade array */
 	for (i = 0; i < num_grades; i++) 
 	{ 
 		/* Trap Loop to check the input value  */
		do
		{	
	 		printf("%s %d: ", name[i], idno[i]);
	 		scanf("%d", &input);
	 		while ( (c = getchar() != '\n') && c != EOF); /* clear buffer */
	 		
			/* A grade should be between 0 and 100 */
			if (input < 0 || input > 100)
			{
				printf("\nA grade should be between 0 and 100.\nPlease re-enter!\n\n");
			} /* End if */
			else
			{
				grade[i] = input;
			} /* End else */
			
		} while (input < 0 || input > 100); /* End do while */
		
		total_grade = total_grade + grade[i]; /* Keep the running total */
		
 	} /* End of for */
	
	/* Sort the arrays */
	bubble_sort(grade, idno, name, num_grades);
		
	/* Print the grade report */
	printf("\n\n");	
 	printf("Sorted Grade Report for %s ", class_name);	
 	printf("\n\n");	
 	printf("Student Name \t\t ID \t\t Grade \n");
	
	/* Print the sorted grages */
	for (i = 0; i < num_grades; i++)
	{
		printf("%s \t\t %d \t\t %d\n", name[i], idno[i], grade[i]);		
	} /* End for */
	
	/* Find a median */
	if (num_grades%2 == 0) /* if even number of data */
	{
		
		median = (float)(grade[num_grades/2 - 1] + grade[num_grades/2])/2;	
	} /* End if */
	else /* if odd number of data */
	{
		median = grade[(num_grades-1)/2];
	} /* End else */
	
	/* Print the min, max, median */
	printf("\n\n");
	printf("The maximum is %d\n", grade[0]);
	printf("The minimum is %d\n", grade[num_grades-1]);
	printf("The median is %.1f\n", median);
	printf("\n\n");
	 	
	 /* Finally Calculate the average */	
	avg_grade = (float)total_grade / num_grades;
	printf("The average of %s is %.1f", class_name, avg_grade);
	
 	getchar(); /* to suspend the program before exiting */
	  
 	return 0;
} /* End Main */

/************************** Functions *********************************/

/* Use the "Bubble Sort" algorithm to sort array in descending order. */
/* adapted from class notes Sorting Arrays.pdf						  */
int bubble_sort(int grade[], int idno[], char name[][20], int num_elements)
{
	/* Declare and initialize variables */
	
	char changed = 'T';			/* a flag to indicate if a swap happened */
	int  i, j, tempg, tempid;	/* Use them for swapping and sorting	 */
	char tempc;					/* Use it for char swap					 */
	
	while (changed == 'T') /* if no swap made, we are done.*/
 	{
 		changed = 'F';
 		/* For every element in the array starting at first, test if "this" */
 		/* element is greater than the "next" element. If so, swap them. */
 		for (i = 0; i < num_elements-1; i++)
 		{
 			if ( grade[i] < grade[i+1])
 			{
 				/* Swap the grade value */
 				tempg = grade[i];
 				grade[i] = grade[i+1];
 				grade[i+1] = tempg;
 				
 				/* swap the idno */
 				tempid = idno[i];
 				idno[i] = idno[i+1];
 				idno[i+1] = tempid;
				 
				/* swap the name */
				for (j = 0; j < 20; j++)
				{
					tempc = name[i][j];
					name[i][j] = name[i+1][j];
					name[i+1][j] = tempc;
				} /* end for */
				
 				/* Set flag indicating that a swap was made. This ensures that */
 				/* processing will continue, until nothing needs to be swapped. */
 				changed = 'T';
 			} /* end if */
 		} /* end for */
 	} /* end while*/
 	return 0;
} /* end bubble_sort */


