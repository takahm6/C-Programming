/* -----------------------------------------------------------------------------
Program file: tsudamp4.c 
Author:       Makiko Tsuda
Date:         10/24/2021
Class:		  Intro to Programming with C Part 2
Assignment:   #4 
Objective:    The program print out an Inventory Report using pointers.	   
------------------------------------------------------------------------------*/
#include <stdio.h>

struct inven
{
 
	char name[19];
	int	 items[6];
}; 

int main(void)
{
    struct inven inventory_array[] =
	{	{"elbows",	 	87, 43,-98, 77,-69,0}, 
    	{"2''x6' pipe",	35,-21, 89,-57,  0,0}, 
    	{"cap",			78, 89, 98,-94,  0,0}, 
    	{"whatsit",		55, 66,-75,  0,  0,0}, 
    	{"gizmo",		65, 71, 87,-76,  0,0}, 
    	{"cuff",		79,-49, 98,-97,-31,0}, 
    	{"c clamp",		74,-62, 79,  0,  0,0}, 
    	{"X filter",	39, 81, 20,-73,  0,0}, 
    	{"Y filter",	68, 85,-98, 77, 94,0}, 
    	{"Sealer tape",	89,-69, 77, 68, 96,0}, 
	};
	
	/* A pointer to the struct inven */
	struct 	inven *inventory_ptr = inventory_array;
	/* Use them for iteration */
	int  	x,i, count = sizeof(inventory_array)/sizeof(*inventory_ptr);
	/* Holds a running total for the inventory quantity */
    int  	temp = 0; 
	/* a pointer to the items array inside the struct. Initialized later */ 
    int		*item_ptr;   


	x = 0;
	i = 0;
	 
  	while ( x < count )
    {
		/* pointing to the first item in the items array of the first struct member */
 		item_ptr = inventory_ptr->items;
 		
 		/* Sum the item quantities to get the total for each item */
 		do
		{
			/* Referencing what item_ptr points to */
	 		temp = temp + *(item_ptr++);
		 	i++;
			 	 
		} while(i < 5); /* End while */
 
 		/* Store the total for the item in the last array position */
 		*(item_ptr++) = temp;
		
		/* Reset the values for the next inventory */
	  	temp = 0;

     	i = 0;
     	x++;
    	
    	/* Move the pointer to the next inventory */
    	inventory_ptr++;
    } /* En while */
 
 	/* Print the inventory report */
	printf("\n\n");
	printf("                       Inventory Report \n");
	printf("                       ---------------- \n\n");

	printf("   Item Name     Tran 1    Tran 2    Tran 3    Tran 4    Tran 5    Balance\n");
	printf("==========================================================================\n");

	printf("\n");

    i = 0;
    
    /* points to the first element of inventory_array */
    inventory_ptr = inventory_array;
    
	while(i < count)
    {
    	/* Points to the first item in the array */
    	item_ptr = inventory_ptr->items;
    	
        printf("%-13s", inventory_ptr->name);

		for(x = 0; x < 6; x++)
        {
        	/* Referencing what item_ptr points to */
			printf("%8i  ", *(item_ptr++));

        } /* End for */
        
        i++;
        
       	/* Move the pointer to the next inventory */
    	inventory_ptr++;
 		printf("\n");

    }  /* End while */

 
	printf("===========================================================================\n\n\n");

	getchar();  

	return 0;

}  /* End main */


