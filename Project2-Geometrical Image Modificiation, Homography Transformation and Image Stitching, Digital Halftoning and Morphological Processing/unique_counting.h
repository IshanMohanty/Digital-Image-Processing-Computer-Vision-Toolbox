#ifndef UNIQUE_COUNTING_H
#define UNIQUE_COUNTING_H

#include <stdio.h>

#define FG 0
#define BG 255

#define PI 3.14159265

int compare(unsigned char* OrgBuffer,unsigned char* CmpBuffer, int width , int height);
double similarity(unsigned char* OrgBuffer,unsigned char* CmpBuffer, int width , int height);
void rotate(unsigned char* CmpBuffer, int width, int height, int angle);
unsigned char bilinear(unsigned char* Img,double new_image_col , double new_image_row, int width , int bpp, int height,int channel);
void flip(unsigned char* CmpBuffer, int width, int height);

#endif /* UNIQUE_COUNTING_H */
