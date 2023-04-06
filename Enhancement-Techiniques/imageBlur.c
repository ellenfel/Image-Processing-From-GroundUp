// Blurring an Image with a Filter Kernel

#include <stdio.h>
#include <stdlib.h>

int main()
{
   FILE *fIn= fopen("fruits.bmp","rb");
   FILE *fOut= fopen("fruits_blur.bmp","wb");

   unsigned char imgHeader[54];
   unsigned char colorTable[1024];

   if(fIn == NULL){printf("Unable to open file\n");}

   for(int i =0;i<54;i++){imgHeader[i] = getc(fIn);}

   fwrite(imgHeader,sizeof(unsigned char),54,fOut);

   int height = *(int*)&imgHeader[22];
   int width  =  *(int *)&imgHeader[18];
   int bitDepth = *(int *)&imgHeader[28];

   if(bitDepth <=8)
   {
       fread(colorTable,sizeof(unsigned char),1024,fIn);
       fwrite(colorTable,sizeof(unsigned char),1024,fOut);
   }

   int imgSize = height * width;

   unsigned char buffer[imgSize][3];
   unsigned char out_buffer[imgSize][3];

   // for extracting color
   for(int i =0;i<imgSize;i++)
   {
        buffer[i][2] = getc(fIn);
        buffer[i][1] = getc(fIn);
        buffer[i][0] = getc(fIn);
   }
   
   
   return 0;

}