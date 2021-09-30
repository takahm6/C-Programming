#include <stdio.h> 

main() { /* Declare and initialize variables. */
	int nums[5] = {88, 80, 67, 80, 90}; 
	int value, x; 
	char found = 'F'; /* flag to indicate if value was found in array. */
	int marker;
	
	/* Prompt user for value to be searched. */
	printf ("\nEnter a number for which to search array: "); 
	scanf ("%i", &value);
	/* Use "linear search" algorithm to search for value in array. */
	for (x = 0; x < 5; x++) 
	{
		/* If the value is found in array, set flag and exit loop. */
		if ( nums[x] == value ) 
		{ 
			found = 'T'; 
			marker = x;
			break; 
		} /* end if */
	} /* end for */
	/* Output appropriate message based on findings. */
	if (found == 'T') 
		printf ("Number %i found in array. At position %d\n", value, marker); 
	else 
		printf ("Number %i not found in array.\n", value);
		
	return 0;
} /* end main */
