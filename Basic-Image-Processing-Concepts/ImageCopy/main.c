#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *streamIn = fopen("images/cameraman.bmp","rb");  //input
    FILE *fo = fopen("images/cameraman_copy.bmp","wb");   //output

    //Checks for errors
    if(streamIn == (FILE*)0)
    {
        printf("Unable to open the file\n");
    }

    unsigned char header[54];
    unsigned char colorTable[1024];

    for(int i = 0; i<54;i++)
    {
        header[i] = getc(streamIn);
    }

    int width = *(int *)&header[18];
    int height = *(int *)&header[22];
    int bitDepth = *(int *)&header[28];

    if(bitDepth<=8)
    {
        fread(colorTable,sizeof(unsigned char), 1024,streamIn);
    }

    fwrite(header,sizeof(unsigned char),54,fo);
    unsigned char buf[height * width];
    fread(buf,sizeof(unsigned char), (height * width), streamIn);

    if(bitDepth<=8)
    {
        fwrite(colorTable,sizeof(unsigned char), 1024,fo);
    }

    fwrite(buf,sizeof(unsigned char), (height * width),fo);

    fclose(fo);
    fclose(streamIn);

    printf("SUCCESS\n");
    printf("Width: %d\n", width);
    printf("Height: %d\n", height);
    return 0;
}