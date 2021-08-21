#include <stdio.h>

#include "barcode.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#define IMG_HEIGHT 100
#define LINE_W 3
#define BORDER 10
#define MAX_CHARS 100

//last 1 for '\0'
char _data[MAX_CHARS + 1];

//3 additional for startcode, checksum and endcode
char* _encoded[MAX_CHARS + 3];

char* Image;
int checksum, length, img_width;

int start(char filename[])
{
	printf("Enter the text you need to write encode barcode with (max characters 100).\n");
	scanf(" %100[^\n]", _data);
	length = strlen(_data);
	img_width = (length + 3) * LINE_W + 2 * BORDER;
	Image = malloc(img_width * IMG_HEIGHT);
	if (Image == NULL)
		return -1;
}

int encode()
{
	//ASCII value is 32 more than corresponding Barcode value
	for (int i = 0; i < length; i++)
		data[i] -= 32; 

	//Calculating checksum of data
	unsigned long long sum = 104;
	for (int i = 0; i < length; i++)
		sum += data[i] * (i + 1);
	checksum = sum % 103;

	//Encoding each char to bar code widths
	_encoded[0] = START_TYPE_B;
	for (int i = 1; i < length + 1; i++)
		_encoded[i] = char_codes[data[i - 1]];
	_encoded[length + 1] = char_codes[checksum];
	_encoded[length + 2] = STOP_CODE;

}