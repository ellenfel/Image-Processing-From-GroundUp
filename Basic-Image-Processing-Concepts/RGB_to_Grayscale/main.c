#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *fIn = fopen("images/lena_color.bmp", "rb");
    FILE *fOut = fopen("images/lena_gray.bmp", "wb");

    unsigned char imgHeader[54];

    if(fIn == NULL)
    {
        printf("Unable the open the file");
    }

    for(int i = 0; i<54;i++)
    {
        imgHeader[i] = getc(fIn);
    }

    fwrite(imgHeader, sizeof(unsigned char),54,fOut);

    int height = *(int *)&imgHeader[22];
    int width = *(int *)&imgHeader[18];
    int bitDepth = *(int *)&imgHeader[28];

    int imgSize = height * width;
    unsigned char buffer[imgSize][3];

    for(int i = 0;i<imgSize;i++)
    {
        buffer[i][0] = getc(fIn); //R
        buffer[i][1] = getc(fIn); //G
        buffer[i][2] = getc(fIn); //B

        int temp=0;
        
        temp = (buffer[i][0] *0.3)+(buffer[i][1]*0.59)+(buffer[i][2]*0.11);
        putc(temp,fOut);
        putc(temp,fOut);
        putc(temp,fOut);
    }

    printf("Success\n");

    fclose(fIn);
    fclose(fOut);

    return 0;
}