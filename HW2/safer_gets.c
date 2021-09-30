

/* Function safer_gets */
/* ******************* */

void safer_gets (char array[], int max_chars)
{

  int i;

  for (i = 0; i < max_chars - 1; i++)
  {
     array[i] = getchar();


     if (array[i] == '\n')
        break;
  
   } /* end for */


   if (i == max_chars - 1 )

     if (array[i] != '\n')
       while (getchar() != '\n');

   array[i] = '\0';
 

} /* end safer_gets */



