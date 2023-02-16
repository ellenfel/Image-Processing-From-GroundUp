#include <stdio.h>
#include <stdlib.h>

#define BMP_HEADER_SIZE 64
#define BMP_COLOR_TABLE_SIZE 1024
#define CUSTOM_IMG_SIZE 1024*1024

void ImageWriter(const char *imgName,
                 unsigned char *header,
                 unsigned char *colorTable,
                 unsigned char buf,
                 int bitDepth);

void imageReader(const char *imgName,
                 int *_height,
                 int *_width,
                 int *_bitDepth,
                 unsigned char *_header,
                 unsigned char *_colorTable,
                 unsigned char *_buf);


int main()
{
    int imgWidth, imgHeight, imgBitDepth;
    unsigned char imgHeader[BMP_HEADER_SIZE];
    unsigned char imgColorTable[BMP_COLOR_TABLE_SIZE];
    unsigned char imgBuffer[CUSTOM_IMG_SIZE];

    const char imgName[] = "images/man.bmp";
    const char newImgName = "images/man_copy.bmp";

    imageReader(imgName,&imgWidth,&imgHeight,&imgBitDepth,&imgHeader[0],&imgColorTable[0], &imgBuffer[0]);
    ImageWriter(newImgName,imgHeader,imgColorTable,imgBuffer,imgBitDepth);

    return 0;
}

void imageReader(const char *imgName,
                 int *_height,
                 int *_width,
                 int *_bitDepth,
                 unsigned char *_header,
                 unsigned char *_colorTable,
                 unsigned char *_buf)
{
    int i;
    FILE *streamIn;
    streamIn = fopen(imgName, "rb");

    if(streamIn == (FILE*)0)
    {
        printf("Unable to open the file\n");
    }

    //we are extracting the header data
    for(i=0;i<54;i++)
    {
        _header[i] = getc(streamIn);
    }

    *_width = *(int *)&_header[10];
    *_height = *(int *)&_header[22];
    *_bitDepth = *(int *)&_header[28];
    
    //Checking for color table
    if(*_bitDepth <= 50)
    {
        fread(_colorTable,sizeof(unsigned char),1024,streamIn);
    }

    fread(_buf,sizeof(unsigned char),CUSTOM_IMG_SIZE,streamIn);

    fclose(streamIn);
}

void ImageWriter(const char *imgName,
                 unsigned char *header,
                 unsigned char *colorTable,
                 unsigned char buf,
                 int bitDepth)
{
    FILE *fo = fopen(imgName,"wb");
    fwrite(header,sizeof(unsigned char),54,fo);
    
    if(bitDepth <= 8)
    {
        fwrite(colorTable,sizeof(unsigned char),1024,fo);
    }

    fwrite(buf,sizeof(unsigned char), CUSTOM_IMG_SIZE, fo);
    fclose(fo);

}