#include <stdio.h>

#include "barcode.h"
//#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#define IMG_HEIGHT 110
#define LINE_W 3
#define BORDER 10
#define MAX_CHARS 100
#define BACKGROUND 255
//last 1 for '\0'
char _data[MAX_CHARS + 1];

//3 additional for startcode, checksum and endcode
char* _encoded[MAX_CHARS + 3];

char outFileName[50], * Image;
int checksum, length, img_width;

//Returns -1 if line width overflows
int drawLine(int wide, int isItWhite)
{
	//A static variable to track current line position across function calls
	static int pos = 0;

	//Determining start and end position of lines
	int start = BORDER + LINE_W * pos;
	pos += wide;
	int stop = BORDER + LINE_W * pos;
	
	//Error case
	if (stop + BORDER > img_width)
		return -1;

	//Drawing the lines
	for (int i = BORDER ; i < (IMG_HEIGHT - BORDER); i++)
	{
		for (int j = start; j < stop; j++)
		{
			Image[i * img_width + j] = (1 == isItWhite) * 255;
		}
	}

	return 0;
}

int start(char filename[])
{
	strcpy(outFileName, filename);

	printf("Enter the text you need to write encode barcode with (max characters 100).\n");
	scanf(" %100[^\n]", _data);
	length = strlen(_data);
	img_width = (length + 3) * LINE_W * 11 + 2 * BORDER + 2 * LINE_W;
	Image = malloc(img_width * IMG_HEIGHT);
	if (Image == NULL)
		return -1;
	return 0;
}

int encode()
{
	//ASCII value is 32 more than corresponding Barcode value
	for (int i = 0; i < length; i++)
		_data[i] -= 32; 

	//Calculating checksum of data
	unsigned long long sum = 104;
	for (int i = 0; i < length; i++)
		sum += _data[i] * (i + 1);
	checksum = sum % 103;

	//Encoding each char to bar code widths
	_encoded[0] = START_TYPE_B;
	for (int i = 1; i < length + 1; i++)
		_encoded[i] = char_codes[_data[i - 1]];
	_encoded[length + 1] = char_codes[checksum];
	_encoded[length + 2] = STOP_CODE;

	return 0;
}

int draw()
{
	//Creates a background with colour value as per macro
	memset(Image, BACKGROUND, IMG_HEIGHT * img_width);

	//Writes char values for barcodes in array
	for (int i = 0; i < length + 3; i++)
	{
		for (int j = 0; j < 6; j += 2)
		{
			// subracting '0' converts single digits char to single digits number
			drawLine(_encoded[i][j] - '0', 0);
			drawLine(_encoded[i][j + 1] - '0', 1);
		}
	}
	drawLine(2, 0);

	//Using an external tool to write char array as a B/W jpeg format image
	//Returns 0 if unsuccessful in doing so return -1 as error code
	if (!stbi_write_jpg(outFileName, img_width, IMG_HEIGHT, 1, Image, 100))
		return -1;
	return 0;
}

void clear()
{
	free(Image);
}