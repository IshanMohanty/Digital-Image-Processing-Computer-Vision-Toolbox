#ifndef MBVQ_H
#define MBVQ_H


unsigned char* getpixelpos(unsigned char* Img , int i , int j , int width, const int bpp);
void MBVQ(unsigned char* Img,int width, int height, const int bpp,unsigned char* Buffer,unsigned char* Out );
int Get_MBVQ_Type(unsigned char* Img, int i , int j , int bpp, int width);
int getminvertex(unsigned char* Buffer,int i , int j , int bpp , unsigned char tetra_color[4][3] , int width );


#endif /* MBVQ_H */
