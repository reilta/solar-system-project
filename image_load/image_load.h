#ifndef IMAGE_LOAD_H_INCLUDED
#define IMAGE_LOAD_H_INCLUDED
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>

GLuint texture[1];      // storage for textures

/* Image type - contains height, width, and data */
struct Image
{
      unsigned long sizeX;
      unsigned long sizeY;
      GLubyte *data;
};

// getint and getshort are helper functions to load larger data types
// in Big Endian CPUs such as those in older Mac (PowerPC) or Solaris
// (SPARC) workstations. They are needed because BMP files are
// designed for Little Endian CPUs like the Intel x86 series.
//
// Originally from the Xv bmp loader.

// Ensure that Little Endian ints are read into memory correctly on Big Endian platforms
static unsigned int getint(FILE *fp)
{
   unsigned int c, c1, c2, c3;
   c  = ((unsigned int)getc(fp));  // get 4 bytes
   c1 = ((unsigned int)getc(fp)) << 8;
   c2 = ((unsigned int)getc(fp)) << 16;
   c3 = ((unsigned int)getc(fp)) << 24;
   return c | c1 | c2 | c3;
}

// Ensure that Little Endian shorts are read into memory correctly on Big Endian platforms
static unsigned short getshort(FILE* fp)
{
   unsigned short c, c1;
   //get 2 bytes
   c  = ((unsigned short)getc(fp));
   c1 = ((unsigned short)getc(fp)) << 8;
   return c | c1;
}

// Quick and dirty bitmap loader...for 24 bit bitmaps with 1 plane only.
bool ImageLoad(char *filename, Image *image)
{
   FILE *file;
   unsigned long size;          // size of the image in bytes.
   size_t i,j,k, linediff;		     // standard counter.
   unsigned short int planes;   // number of planes in image (must be 1)
   unsigned short int bpp;      // number of bits per pixel (must be 24)
   char temp;                   // temporary storage for bgr-rgb conversion.

   // Make sure the file is there.
   if ((file = fopen(filename, "rb"))==NULL) {
      printf("File Not Found : %s\n",filename);
      return false;
   }

   // Seek through the bmp header, up to the width/height:
   fseek(file, 18, SEEK_CUR);

   // Read the width
   image->sizeX = getint (file);
   printf("Width of %s: %lu\n", filename, image->sizeX);

   // Read the height
   image->sizeY = getint (file);
   printf("Height of %s: %lu\n", filename, image->sizeY);

   // Calculate the size (assuming 24 bits or 3 bytes per pixel).
   // BMP lines are padded to the nearest double word boundary.
   // fortunat
   size = 4.0*ceil(image->sizeX*24.0/32.0) * image->sizeY ;

   // Read the planes
   planes = getshort(file);
   if (planes != 1){
      printf("Planes from %s is not 1: %u\n", filename, planes);
      return false;
   }

   // Read the bpp
   bpp = getshort(file);
   if (bpp != 24) {
      printf("Bpp from %s is not 24: %u\n", filename, bpp);
      return 0;
   }

   // Seek past the rest of the bitmap header.
   fseek(file, 24, SEEK_CUR);

   // Allocate space for the data.
   image->data = new GLubyte[size];
   if (image->data == NULL) {
      printf("Error allocating memory for color-corrected image data");
      return false;
   }

   // Read the data
   i = fread(image->data, size, 1, file);
   if (i != 1) {
      printf("Error reading image data from %s.\n", filename);
      return false;
   }

   // Reverse all of the colors (bgr -> rgb)
   // Calculate distance to 4 byte boundary for each line
   // if this distance is not 0, then there will be a color reversal error
   //  unless we correct for the distance on each line.
   linediff = 4.0*ceil(image->sizeX*24.0/32.0) - image->sizeX*3.0;
   k = 0;
   for (j=0;j<image->sizeY;j++) {
      for (i=0;i<image->sizeX;i++) {
        temp = image->data[k];
        image->data[k] = image->data[k+2];
        image->data[k+2] = temp;
        k+=3;
      }
      k+= linediff;
   }
   return true;
}

// Load Bitmaps And Convert To Textures
void LoadGLTextures(char *filename) {
   // Load Texture
   Image *image1;

   // Allocate space for texture
   image1 = new Image();
   if (image1 == NULL) {
      printf("Error allocating space for image");
      exit(0);
   }

   // Load picture from file
   if (!ImageLoad(filename, image1)) {
      exit(1);
   }

   // Create Texture Name and Bind it as current
   glGenTextures(1, &texture[0]);
   glBindTexture(GL_TEXTURE_2D, texture[0]);   // 2d texture (x and y size)

   // Set Texture Parameters
   //  Scale linearly when image bigger than texture
   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
   //  Scale linearly when image smaller than texture
   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);

   glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
   // Load texture into OpenGL RC
   glTexImage2D(GL_TEXTURE_2D,     // 2D texture
        0,                  // level of detail 0 (normal)
        3,	                // 3 color components
        image1->sizeX,      // x size from image
        image1->sizeY,      // y size from image
        0,	                // border 0 (normal)
        GL_RGB,             // rgb color data order
        GL_UNSIGNED_BYTE,   // color component types
        image1->data        // image data itself
      );
};


#endif // IMAGE_LOAD_H_INCLUDED
