#ifndef ERRORDIFFUSIONFUNC_H
#define ERRORDIFFUSIONFUNC_H

#include <stdlib.h>

unsigned char * getpixelpos(unsigned char* Img , int i , int j , int width, int bpp);

void FloydSteinbergError(unsigned char*Img,int width, int height, const int bpp, unsigned char* Buffer,unsigned char* OutputFloydStein);
void JJN(unsigned char* Img,int width, int height, const int bpp,unsigned char* Buffer,unsigned char* OutputJJN );
void Stucki(unsigned char* Img,int width, int height, const int bpp,unsigned char* Buffer,unsigned char* OutputStucki );

#endif /* ERRORDIFFUSIONFUNC_H */
