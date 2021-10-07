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

//title 
char title(){
	char choice;
	cls();
	printf("\n_____                          _    \n| __ )  __ _ _ __ ___ ___   __| | ___\n|  _ \\ / _` | '__/ __/ _ \\ / _` |/ _ \\ \n| |_) | (_| | | | (_| (_) | (_| |  __/ \n|____/ \\__,_|_|  \\___\\___/ \\__,_|\\___|\n\n");


	printf("Enter one of the following numbers: \n");
	printf("1. Create a jpeg format bar code image from text.\n");
	printf("2. Read message from a type B barcode image file.\n");
	printf("3 Exit\n");	
	scanf(" %c", &choice);
	return choice;
}
void exitfunc(){
	cls();
	printf("Thank you for using our program!!\n");	
	printf("Created by:\nBIPUL\nHIMANSU\nISHWOR\nMAMTA\n\nSend us feedback at \nhttps://github.com/optimistic-ish/Bar-code/issues\n\n\n");
	printf("Press any key to exit\n\n");
	getch();	
}
int main()
{   while(1)
	{
		char choice=title();
		if(choice=='1'){
			writeBarCode();
		}
		else if(choice=='2'){
			readBarCode();
		}
		else if(choice=='3'){
			exitfunc();
			break;
		}
		else{
			printf("\nInvalid choice, please try again !!\n");
		}
		printf("\n\n\nDo you want to continue?(Y/N):");char c;fflush(stdin);
		if(c==getchar()=='y'||'Y')
			continue;
		else {
			exitfunc();
			break;
			}
	}
}

