#include "barcode.h"
#include <stdio.h>
int main()
{
	//FILE* f = fopen("lala.txt", "w");
	for (int i = 0; i < MAX_REF; i++)
	{
		printf("%s\t", reference[i]);
		//fprintf(f,"'%d',\n",reference[i]);
	}
	return 0;
}