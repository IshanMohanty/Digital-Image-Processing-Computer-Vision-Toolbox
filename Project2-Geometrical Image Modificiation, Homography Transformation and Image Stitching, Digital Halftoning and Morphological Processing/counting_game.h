#ifndef COUNTING_GAME_H
#define COUNTING_GAME_H

struct window_pos_count
{
    int row;
    int col;
};

int counting(unsigned char* Img, unsigned char* LabelImg, int width, int height);
void FindCompDFS(unsigned char* Img, unsigned char* LabelImg, int imgrow, int imgcol, int Label_Comp,int width);

#endif /* COUNTING_GAME_H */
