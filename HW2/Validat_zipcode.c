// zip code validate - character array type

#include <stdio.h>
int sgetz(char []);

main()
{
	int zipok;
	char zip[5];
	
	while(1)
	{
			do
			{
    			printf ("\nEnter zip code: ");
    			zipok = sgetz (zip);
    		
   				if (zipok == 0) printf("Please re-enter a valid zip code. \n");
							   
			}while (zipok == 0);
	
		printf("good zip code was: %.5d\n", atoi(zip));
		
	}// end while

}// end main

int sgetz(char array[])
{
  char ok = 1;
  int i;

  /* Read name from input buffer, character by character,   */
  /* up until the maximum number of characters in the array.*/
  /* ------------------------------------------------------ */

  for (i = 0; i < 5; i++)
  {
     array[i] = getchar();
     
	 if(array[i] == '\n')
	    break;
	 else
	 if(!isdigit(array[i]))
		ok = 0; 
	 
   } /* end for */
   
   if(i < 5) ok =0;
   
   if(i == 5 && array[i] != '\n') 
   		while (getchar() != '\n');

   /* Ensure the last element in the array contains the null terminator. */
   /* ------------------------------------------------------------------ */

   array[i] = '\0';

   return ok;	
		
}// endf

