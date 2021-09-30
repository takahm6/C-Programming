/* Bubble sort and its test */

#include <stdio.h>

int main(void) 
{
	/* Declare and initialize variables */
	char changed = 'T'; /* a "flag" to indicate if a swap was made. */
	int nums[5] = {88, 80, 67, 80, 90}; int x, temp;
	
	/* Display the contents of the array before they are sorted. */ 
	printf ("The array before sort is:\n");
	for (x = 0; x < 5; x++)
		printf ("%i ", nums[x]); printf ("\n");
	/* Use the "Bubble Sort" algorithm to sort array in ascending order. */ 
	while (changed == 'T') /* if no swap made, we are done. */
	{
		changed = 'F';
		/* For every element in the array starting at first, test if "this" */
		/* element is greater than the "next" element. If so, swap them. */
		for (x = 0; x < 4; x++)
		{
			if ( nums[x] > nums[x + 1])
			{
				/* Swap needs to be made. */
				temp = nums[x]; 
				nums[x] = nums[x+1]; 
				nums[x+1] = temp;
				changed = 'T';
			} /* end if */
		} /* end for */
	} /* end while */
	/* Display the contents of the array, now in sorted order. */ printf ("The array after sort is:\n");
	for (x = 0; x < 5; x++)
		printf ("%i ", nums[x]); printf ("\n");
		
	return 0;
} /* end main */

