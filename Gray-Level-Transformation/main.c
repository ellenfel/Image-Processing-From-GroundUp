//negative image

#include <stdio.h>
#include <stdlib.h>

int main()
{
   FILE *fIn= fopen("girlface.bmp","rb");

   unsigned char *imageData;
   unsigned char *newImageData;

   unsigned char imgHeader[54];
   unsigned char colorTable[1024];

   if(fIn == NULL)
   {
       printf("Unable to open file\n");
   }

   //reads the image header 
   fread(imgHeader,sizeof(unsigned char),54,fIn);
   int height = *(int*)&imgHeader[22];
   int width  =  *(int *)&imgHeader[18];
   int bitDepth = *(int *)&imgHeader[28];

   int imageDataSize = width * height;

   imageData = (unsigned char *)malloc(imageDataSize * sizeof(unsigned char));
   newImageData = (unsigned char *)malloc(imageDataSize * sizeof(unsigned char));

   if(bitDepth <=8)
   {
       fread(colorTable,sizeof(unsigned char),1024,fIn);
   }

   fread(imageData,sizeof(unsigned char),imageDataSize, fIn);

    //Computing image negative
     for(int i =0; i<height;i++)
     {
         for(int j =0;j<width;j++)
         {
             newImageData[i*width+j] =  255 - imageData[i*width+j];
         }

     }

     FILE *fo = fopen("girlface_negative.bmp","wb");
     fwrite(imgHeader, sizeof(unsigned char),54,fo);

     if(bitDepth <=8)
     {
         fwrite(colorTable,sizeof(unsigned char),1024,fo);
     }

     fwrite(newImageData,sizeof(unsigned char),imageDataSize,fo);

     printf("Success !\n");

     fclose(fo);
     fclose(fIn);

    return 0;
}