#ifndef FOUR_LEVEL_DITHER_FUNC_H
#define FOUR_LEVEL_DITHER_FUNC_H

#include <stdlib.h>

void FourlevelDitherMatrixMethod(unsigned char* Img, int width, int height, const int bpp, unsigned char* Dither, int N);

#endif /* FOUR_LEVEL_DITHER_FUNC_H */
