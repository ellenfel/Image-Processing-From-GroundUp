#include <stdio.h>
#include <stdlib.h>

#define WHITE       255
#define BLACK       0
#define TRESHOLD    150

#define BMP_HEADER_SIZE         54
#define BMP_COLOR_TABLE_SIZE    1024

int main()
{
    FILE *fIn = ("lighthouse.bmp","rb");
    FILE *fOut = ("lighthouse_bw.bmp","wb");

    unsigned char imgHeader[BMP_HEADER_SIZE];
    unsigned char colorTable[BMP_COLOR_TABLE_SIZE];

    if(fIn=NULL){printf("Unable to open image \n");}

    fwrite(imgHeader,sizeof(unsigned char),BMP_HEADER_SIZE,fOut);

    //Extracting info aboout image from Header
    int height = *(int *)&imgHeader[22];
    int width  = *(int *)&imgHeader[18];
    int BitDepth  = *(int *)&imgHeader[28];

    int imgSize = height*width;

    //Sorting out the Color Table
    if(BitDepth<=8)
    {
        fread(colorTable, sizeof(unsigned char), BMP_COLOR_TABLE_SIZE,fIn);
        fwrite(colorTable,sizeof(unsigned char),BMP_COLOR_TABLE_SIZE,fOut);
    }

    //Sorting out the pixsel data
    unsigned char buffer[imgSize];
    fread(buffer, sizeof(unsigned char), imgSize,fIn);
    for(int i = 0; i<imgSize;i++)
    {
        buffer[i] = (buffer[i]>TRESHOLD)?WHITE:BLACK;
    }
    
    fwrite(buffer,sizeof(unsigned char),imgSize,fOut);
    fclose(fIn);
    fclose(fOut);
    return 0;
}