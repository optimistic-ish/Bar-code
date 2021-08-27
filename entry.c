#include <stdio.h>
#include <stdlib.h>
#include "barcodeio.h"

//Providing a platform independent clear screen function
#ifdef __linux__
void cls()
{
	system("clear");
}
#else
void cls()
{
	system("cls");
}
#endif

int main()
{
	char choice;
	cls();

	printf("Enter one of the following numbers: \n");
	printf("1. Create a jpeg format bar code image from text.\n");
	printf("2. Read message from a type B barcode image file.\n");	
	scanf(" %c", &choice);
	if (choice == '1')
		writeBarCode();
	else if (choice == '2')
		readBarCode();
	else
		printf("Invalid choice.\n");
	
	printf("Press enter to continue...");
	getchar();
	getchar();
	return 0;
}