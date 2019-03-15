#ifndef STK_H
#define STK_H

#include <stdio.h>

using namespace std;

struct window_pos
{
    int row;
    int col;
};


void STK(unsigned char* Img, unsigned char* MBuffer, unsigned char* Out,int width, int height, int action, int Run_Times,int FG, int BG);
int counting(unsigned char* Img, unsigned char* LabelImg, int width, int height);
int FindCompDFS(unsigned char* Img, unsigned char* LabelImg, int imgrow, int imgcol, int Label_Comp,int width);


#endif /* STK_H */
