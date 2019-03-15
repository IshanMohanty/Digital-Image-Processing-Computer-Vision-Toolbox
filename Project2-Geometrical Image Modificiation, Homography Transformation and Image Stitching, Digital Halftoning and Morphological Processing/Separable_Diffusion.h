#ifndef SEPARABLE_DIFFUSION_H
#define SEPARABLE_DIFFUSION_H

unsigned char* getpixelpos(unsigned char* Img , int i , int j , int width, const int bpp);
void separable_diffusion(unsigned char* Img,int width, int height, const int bpp,unsigned char* Buffer,unsigned char* Out );


#endif /* SEPARABLE_DIFFUSION_H */
