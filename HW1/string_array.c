#include <stdio.h>

int main(void) 
{
	char name[30][20] =
	{
		"Jeorge Sanchez", "Ali Wang", "Jane Smith", "Ginika Adichie", 
		"Bill Bailey", "Carl Marks", "Joy Fully", "Chris Tal", "Miki Yamada"
	};
	int i;
	
	for(i = 0; i <9; i++)
		printf("%s\n", name[i]);
	return 0;
}
