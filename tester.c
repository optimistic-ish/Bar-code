#include <stdio.h>


int start(char[]);
int encode();
int draw();
void clear();

void lmain();
void mmain();

int main()
{

	char name[100];
	printf("Enter filename to write bar code on:");
	scanf("%s", name);

	if (start(name) < 0)
	{
		printf("Couldnot initialize image in RAM.\n");
		return -1;
	}

	if (encode() < 0)
	{
		printf("Couldnot encode the message to bar code.\n");
		clear();
		return -1;
	}

	if (draw() < 0)
	{
		printf("Couldnot create required image file.\n");
		clear();
		return -1;
	}
	clear();
	printf("Your barcode has been created in file named %s .", name);

	return 0;
}