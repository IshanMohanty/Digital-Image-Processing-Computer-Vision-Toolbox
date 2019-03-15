#ifndef HOMOGRAPHYSTITCHING_H
#define HOMOGRAPHYSTITCHING_H



double mult_homo_x( double out_cart_x , double out_cart_y , double Hinv[] );

double mult_homo_y( double out_cart_x , double out_cart_y , double Hinv[] );

double mult_homo_w( double out_cart_x , double out_cart_y , double Hinv[] );

void HomographyStitching(unsigned char* middle_Img,unsigned char* left_Img,unsigned char* right_Img,unsigned char* Buffer, 
                         int height,int width,int height_output,int width_output,const int bpp);

#endif /* HOMOGRAPHYSTITCHING_H */
