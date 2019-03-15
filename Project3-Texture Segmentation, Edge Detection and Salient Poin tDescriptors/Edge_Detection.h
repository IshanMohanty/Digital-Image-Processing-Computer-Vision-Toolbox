#ifndef EDGE_DETECTION_H
#define EDGE_DETECTION_H

#define SOBEL_THRESHOLD_1 50
#define SOBEL_THRESHOLD_2 80

unsigned char * getpixel(unsigned char* Image , int i , int j , int width , int height , int bpp);
void convert_RGB_GRAY(unsigned char* Img, int width, int height, int bpp, unsigned char* Buffer);
void gaussian_noise_removal(unsigned char* Buffer, int width , int height);
unsigned char sobel_operator(unsigned char* Buffer, int width , int height,int bpp, double* Gradient_buffer);
void sobel_threshold(double final_threshold,unsigned char* Out,double* Gradient_Buffer,int width, int height);

#endif /* EDGE_DETECTION_H */
