#include<stdio.h>
#include<string.h>

#define MAXL 30
#define MAXF 20
#define MAX 10
void safer_gets (char [], int);
 
struct name
{
    char    first_name[MAXL];
	char	last_name[MAXF];   
	int		other; 	
};

struct employee
{
	int 			empnum;
	float 			emp_pay_rate;
 	struct name 	empname;
	char			empssn[9];
};


 
void main()
{

     /* declare variables*/

    char    		c; 
	struct employee company[MAX];   	
	char			big_name[MAXF+MAXL+2];
	int 			n, count;
	 
    do
	{
	 	printf ("How many names: ");
     	scanf ("%i", &n);      
     	while ((c = getchar() != '\n') && c != EOF);
     	
     	if (n <= 0) return;
     	
	}while(n > MAX);
 

	for(count = 0; count < n; count++)
	{
     /* Prompt user for first name. */

     	printf ("Please enter first name #%i: ",count+1);
     	safer_gets (company[count].empname.first_name, MAXF);  

     /* Prompt user for last name. */

     	printf ("Please enter last name #%i: ",count+1);
     	safer_gets (company[count].empname.last_name, MAXL);  

	}// end for loop
	
	printf ("\n");
	
	
     /* Display names back to user. */
     
    for(count = 0; count < n; count++)
	{

     	printf ("Hi %s %s. Nice to meet you!\n", 
		   company[count].empname.first_name , company[count].empname.last_name);

	}// end for loop
	
	printf ("\n");
	
     /* Display names back to user. */
     
    for(count = 0; count < n; count++)
	{
		strcpy(big_name,company[count].empname.last_name);
		strcat(big_name,", ");
		strcat(big_name,company[count].empname.first_name);
		
     	printf ("Hi %s. Nice to meet you!\n", big_name);
     	
     	
     	if(strcmp(company[count].empname.first_name, "Jim")==0 &&  
		       strcmp(company[count].empname.last_name, "Sears")==0)
     	  printf("  Hey that's my name!");
     	  

	}// end for loop
	
	printf ("\n");
	
		
	
	getchar(); 
	
} /* end main*/

/* Function safer_gets */
/* ******************* */

void safer_gets (char array[], int max_chars)
{
  int i;

  /* Read name from input buffer, character by character,   */
  /* up until the maximum number of characters in the array.*/
  /* ------------------------------------------------------ */

  for (i = 0; i < max_chars; i++)
  {
     array[i] = getchar();

     /* If "this" character is the carriage return,      */
     /* replace it with a null terminator and exit loop. */
     /* ------------------------------------------------ */

     if (array[i] == '\n')
     {
       array[i] = '\0';
       break;
     }
   } /* end for */

   /* If we have pulled out the most we can,       */
   /* and, if there are more chars in the buffer,  */
   /* clear out the remaining chars in the buffer. */
   /* This is equivalent to the fflush() function. */
   /* -------------------------------------------- */

   if (i == max_chars )
     if (array[i-1] != '\0')
       while (getchar() != '\n');

   /* Ensure the last element in the array contains the null terminator. */
   /* ------------------------------------------------------------------ */

   array[max_chars-1] = '\0';


} /* end safer_gets */


