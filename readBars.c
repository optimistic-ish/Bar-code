#include "barcode.h"

//Includes the external tool required for reading image files
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define MAX_CHARS 100

//last 1 for '\0'
static char _data[MAX_CHARS + 1];

//3 additional for startcode, checksum and endcode, 1 for garbage support
static char _encoded[MAX_CHARS + 3 + 1][7], outFileName[50];

static unsigned char *Image;
static int img_width, img_height, line_w, s_row, s_col, lastIndex;

//Decodes the particular provided index of _encoded
//Returns 0 for failure any other for success
//Returns -1 for start code, -2 for stop code
char decode(int index)
{
    if (strcmp(_encoded[index], START_TYPE_B) == 0)
        return -1;
    if (strcmp(_encoded[index], STOP_CODE) == 0)
        return -2;
    for (int i = 0; i < MAX_REF; i++)
        if (strcmp(_encoded[index], char_codes[i]) == 0)
            return (char)(i + 32);
    return 0;
}

//Loads the image and finds the starting point
int loadImg(char filename[])
{
	int channel;
	Image = stbi_load(filename, &img_width, &img_height, &channel, 1);
	if (Image == NULL)
		return -1;

    for (int i = 0; i < img_height; i++) {
        for (int j = 0; j < img_width; j++) {
            if (Image[i * img_width + j] < 100) {
                s_row = i;
                s_col = j;
                return 0;
            }
        }
    }
    return -2;
}

//Loads encoded values and stores in _encoded from image
int load_encoded()
{
    memset(_encoded, 0, (MAX_CHARS + 3) * 7);
    memset(_data, 0, MAX_CHARS + 1);

    int index = 0, col = s_col, leastW = 256, exitFlag = 0;
    while (!exitFlag)
    {
        for (int k = 0; k < 6; k+=2)
        {
            int wide = 0;
            while (Image[s_row * img_width + col] < 100) 
            {
                wide++;
                col++;
            }
            _encoded[index][k] = wide;

            if (col > img_width)
            {
                exitFlag = 1;
                break;
            }

            if (wide < leastW)
                leastW = wide;

            wide = 0;
            while (Image[s_row * img_width + col] > 100) 
            {
                wide++;
                col++;
            }
            _encoded[index][k + 1] = wide;
            
            if (col > img_width)
            {
                exitFlag = 1;
                break;
            }
            if (wide < leastW)
                leastW = wide;
        }
        index++;
    }

    for (int i = 0; i < index; i++)
        for (int j = 0; j < 6; j++)
        {
            //Dividing by smallest to get simple ratio 
            _encoded[i][j] /= leastW;

            //Converting numeric values to corresponding characters
            _encoded[i][j] += '0';
        }
    lastIndex = index;
    return 0;
}

//Returns -1 for error in finding stop code
int findStop()
{
    for (int i = lastIndex - 1; i >= 0; i--)
        if (decode(i) == -2)
        {
            lastIndex = i + 1;
            return 0;
        }
    return -1;
}

//Returns -1 if start code is not detected
int decodeStr()
{
    int k, startflag = 0;
    for (k = 0 ;k < lastIndex; k++)
    {
        if (decode(k) == -1)
        {
            startflag = 1;
            break;
        }
    }
    if (!startflag)
        return -1;
    k++;
    for (int i = k; i < lastIndex - 2; i++)
    {
        _data[i - k] = decode(i);
    }
    return 0;
}

int readBarCode()
{
    printf("Enter name of file { with extension } to read bar code from : ");
    char name[100];
    scanf("%s", name);

    if (loadImg(name) < 0)
    {
        printf("Error in loading image file.\n");
        return -1;
    }
    if (load_encoded() < 0)
    {
        printf("Error in loading encoded image file data.\n");
        stbi_image_free(Image);
        return -1;
    }
    if (findStop() < 0)
    {
        printf("No stop code detected.\n");
        stbi_image_free(Image);
        return -1;
    }
    if (decodeStr() < 0)
    {
        printf("No start code detected.\n");
        stbi_image_free(Image);
        return -1;
    }
    printf("The decoded data from bar code is %s\n", _data);
    stbi_image_free(Image);
    return 0;
}
