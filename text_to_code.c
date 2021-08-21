#include <stdio.h>
#include <math.h>
#include <string.h>
#define startB 211214 //This code is to generade tybe B code 128 barcode
#define stop 233111   //This is the stooping character to terminate the barcode

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#define height 100
#define channel 1
#define line 3

int reference[95] = {
    212222,
    222122,
    222221,
    121223,
    121322,
    131222,
    122213,
    122312,
    132212,
    221213,
    221312,
    231212,
    112232,
    122132,
    122231,
    113222,
    123122,
    123221,
    223211,
    221132,
    221231,
    213212,
    223112,
    312131,
    311222,
    321122,
    321221,
    312212,
    322112,
    322211,
    212123,
    212321,
    232121,
    111323,
    131123,
    131321,
    112313,
    132113,
    132311,
    211313,
    231113,
    231311,
    112133,
    112331,
    132131,
    113123,
    113321,
    133121,
    313121,
    211331,
    231131,
    213113,
    213311,
    213131,
    311123,
    311321,
    331121,
    312113,
    312311,
    332111,
    314111,
    221411,
    431111,
    111224,
    111422,
    121124,
    121421,
    141122,
    141221,
    112214,
    112412,
    122114,
    122411,
    142112,
    142211,
    241211,
    221114,
    413111,
    241112,
    134111,
    111242,
    121142,
    121241,
    114212,
    124112,
    124211,
    411212,
    421112,
    421211,
    212141,
    214121,
    412121,
    111143,
    111341,
    131141};

char data[50];
int length, checksum, encrypt[20];
char *img;
int width;

void initializePic()
{
    width = ((length + 3) * 11 * line) + 20 * line + 2 * line; //A character in bar code has 12 lines or digits.
    img = malloc(width * height * channel);
    if (img == NULL)
    {
        printf("File could not be created!\n");
        exit(1);
    }
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
            img[row * width + col] = 255; //creating a white background.
    }
}

void drawVertical(int oneforwhite)
{
    static int x = 0; //doesn't let x return to 0 in next loop
    for (int i = 0; i < height; i++)
    {

        for (int j = 0; j < line; j++)
        {
            img[i * width + x * line + j] = (1 == oneforwhite) * 255;
        }
    }
    x++;
}

void logic()
{
    int sum = 104;
    for (int i = 0; i < length; i++)
        sum += data[i] * (i + 1);
    checksum = sum % 103;
    encrypt[0] = startB;
    for (int i = 1; i < length + 1; i++)
        encrypt[i] = reference[data[i - 1]];
    encrypt[length + 1] = reference[checksum];
    encrypt[length + 2] = stop;
}

void pattern()
{
    for (int i = 0; i < length + 3; i++)
    {
        int x[6], temp = encrypt[i];
        for (int j = 0; j < 6; j++)
        {
            x[5 - j] = temp % 10;
            temp /= 10;
        }
        for (int j = 0; j < 3; j++)
        {
            for (int k = 0; k < x[2 * j]; k++)
                drawVertical(0);
            for (int k = 0; k < x[2 * j + 1]; k++)
                drawVertical(1);
        }
    }
}

void mmain()
{
    printf("Enter the text you want the bar code of:\n");
    gets(data);
    length = strlen(data);

    initializePic();
    for (int i = 0; i < 10; i++)
        drawVertical(1);
    for (int i = 0; i < length; i++)
        data[i] -= 32; //ASCII value is 32 more than Barcode value
    logic();
    //for (int i = 0; i < length + 3; i++)
    //  printf("%d ", encrypt[i]);

    pattern();
    drawVertical(0);
    drawVertical(0);
    stbi_write_jpg("result.jpg", width, height, channel, img, 100);
    free(img);
    printf("\nThe image of the bar code has been generated in the file 'result.jpg'.\n");
}