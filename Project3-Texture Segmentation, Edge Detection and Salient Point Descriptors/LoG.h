#ifndef LOG_H
#define LOG_H

unsigned char * getpixel(unsigned char* Image , int i , int j , int width , int height , int bpp);
void convert_RGB_GRAY(unsigned char* Img, int width, int height, int bpp, unsigned char* Buffer);
void gaussian_noise_removal(unsigned char* Buffer, int width , int height);
void apply_LoG(unsigned char* Buffer, int* LoG_Buffer, int width ,int height, unsigned char* Normalized_Buffer);
int histogram(int* LoG_Buffer,int width,int height);
void Threshold_LoG_Buffer(int knee_threshold,int* LoG_Buffer,int width,int height,int* ternary_Buffer,unsigned char* tri_gray_buffer);
void zero_crossing_algo(int* ternary_map ,unsigned char* Out,int width,int height);

#endif /* LOG_H */
