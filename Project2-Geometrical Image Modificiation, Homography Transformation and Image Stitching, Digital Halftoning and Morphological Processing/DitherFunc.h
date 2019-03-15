#ifndef DITHERFUNC_H
#define DITHERFUNC_H

#include <stdlib.h>

void FixedThresholding(unsigned char* Img, int width, int height, const int bpp, unsigned char* Fixed);
void RandomThresholding(unsigned char* Img, int width, int height, const int bpp, unsigned char* Random);
void DitherMatrixMethod(unsigned char* Img, int width, int height, const int bpp, unsigned char* Dither, int N);

#endif /* DITHERFUNC_H */

