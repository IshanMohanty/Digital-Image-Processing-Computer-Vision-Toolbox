#include "DitherFunc.h"
#include <time.h>

void FixedThresholding(unsigned char* Img, int width, int height, const int bpp, unsigned char* Fixed )
{ 
	unsigned char Threshold = 127;

	for(int imgrow =0; imgrow < height; imgrow++)
	{
		for(int imgcol=0 ; imgcol < width ; imgcol++)
		{ 		


			if( *(Img + ((imgrow*width) + imgcol) ) >= Threshold && *(Img + ((imgrow*width) + imgcol) ) < 256 )
			{
				*(Fixed + ((imgrow*width) + imgcol) )  = 255;
			}
			else
			{
				*(Fixed + ((imgrow*width) + imgcol) )   = 0;
			}

		}
	}
}

void RandomThresholding(unsigned char* Img, int width, int height, const int bpp, unsigned char* Random )
{	 
	srand(time(NULL));

	for(int imgrow =0; imgrow < height; imgrow++)
	{
		for(int imgcol=0 ; imgcol < width ; imgcol++)
		{ 		

			unsigned char RandomThreshold = rand() % 256;

			if( *(Img + ((imgrow*width) + imgcol) ) >= RandomThreshold )
			{
				*(Random + ((imgrow*width) + imgcol) )  = 255;
			}
			else
			{
				*(Random + ((imgrow*width) + imgcol) )  = 0;
			}

		}
	}	
}

void DitherMatrixMethod(unsigned char* Img, int width, int height, const int bpp, unsigned char* Dither, int N)
{

	int I2[2][2] = {   {1, 2},
		{3, 0} 	};

	int I4[4][4] = {   {5, 9, 6, 10},
		{13, 01, 14, 2},
		{07, 11, 04, 8},
		{15, 3, 12, 0} 	};

	int I8[8][8] = {   {21, 37, 25, 41, 22, 38, 26, 42},
		{53, 5, 57, 9, 54, 6, 58, 10},
		{29, 45, 17, 33, 30, 46, 18, 34},
		{61, 13, 49, 1, 62, 14, 50, 2},
		{23, 39, 27, 43, 20, 36, 24, 40},
		{55, 7, 59, 11, 52, 4, 56, 8},
		{31, 47, 19, 35, 28, 44, 16, 32},
		{63, 15, 51, 3, 60, 12, 48, 00}  };


	float T2[2][2] = { 	{95, 159},
		{223, 31} };

	float T4[4][4] = {  {87, 151, 103, 167},
		{215, 23, 231, 39},
		{119, 183, 71, 135},
		{247, 55, 199, 7}     };

	float T8[8][8] = {  {85, 149, 101, 165, 89, 153, 105, 169}, 
		{213, 21, 229, 37, 217, 25, 233, 41}, 
		{117, 181, 69, 133, 121, 185, 73, 137}, 
		{245, 53, 197, 5, 249, 57, 201, 9}, 
		{93, 157, 109, 173, 81, 145, 97, 161}, 
		{221, 29, 237, 45, 209, 17, 225, 33}, 
		{125, 189, 77, 141, 113, 177, 65, 129}, 
		{253, 61, 205, 13, 241, 49, 193, 1}      };


	for(int imgrow =0; imgrow < height; imgrow++)
	{
		for(int imgcol=0 ; imgcol < width ; imgcol++)
		{ 		
			if( N == 2 )
			{
				if( *(Img + ((imgrow*width)+ imgcol) ) > T2[imgrow % 2 ][imgcol % 2] )
				{
					*(Dither + ((imgrow*width)+ imgcol) ) = 255;
				}
				else
				{
					*(Dither + ((imgrow*width)+ imgcol) ) = 0;
				}
			}


			if( N == 4 )
			{
				if( *(Img + ((imgrow*width)+ imgcol) ) > T4[imgrow % 4 ][imgcol % 4] )
				{
					*(Dither + ((imgrow*width)+ imgcol) ) = 255;
				}
				else
				{
					*(Dither + ((imgrow*width)+ imgcol) ) = 0;
				}
			}

			if( N == 8 )
			{
				if( *(Img + ((imgrow*width)+ imgcol) ) > T8[imgrow % 8 ][imgcol % 8 ] )
				{
					*(Dither + ((imgrow*width)+ imgcol) ) = 255;
				}
				else
				{
					*(Dither + ((imgrow*width)+ imgcol) ) = 0;
				}
			}

		}
	}// end of for loop

}

			
				

