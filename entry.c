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
{   while(1){
	char choice;
	cls();
	printf("\n_____                          _    \n| __ )  __ _ _ __ ___ ___   __| | ___\n|  _ \\ / _` | '__/ __/ _ \\ / _` |/ _ \\ \n| |_) | (_| | | | (_| (_) | (_| |  __/ \n|____/ \\__,_|_|  \\___\\___/ \\__,_|\\___|\n\n");


	printf("Enter one of the following numbers: \n");
	printf("1. Create a jpeg format bar code image from text.\n");
	printf("2. Read message from a type B barcode image file.\n");	
	scanf(" %c", &choice);
	if (choice == '1'){
		writeBarCode();
		printf("Do you want to continue? Enter 1 to continue: \n");int check;
		scanf("%d",&check);
		if(check!=1)
			break;}
	else if (choice == '2')
		{readBarCode();
		printf("Do you want to continue? Enter 1 to continue: \n");int check;
		scanf("%d",&check);
		if(check!=1)
			break;}
	else
		{printf("Invalid choice. Please enter the given options\n");
		getch();}
	}
	
	printf("Press enter to continue...");
	getchar();
	getchar();
	return 0;
}