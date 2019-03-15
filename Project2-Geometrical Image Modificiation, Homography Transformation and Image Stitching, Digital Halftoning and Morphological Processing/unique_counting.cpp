#include <vector>
#include <math.h>
#include <algorithm>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "unique_counting.h"


using namespace std;

int compare(unsigned char* OrgBuffer,unsigned char* CmpBuffer, int width , int height)
{
	double matchpercent = 0, max_matchpercent = 0;
	
	for( int i = 0; i < 4 ; i++)
	{
		rotate(CmpBuffer,width,height,90);
		matchpercent = similarity(OrgBuffer, CmpBuffer, width , height);
		if( matchpercent > max_matchpercent  )
		{
			max_matchpercent = matchpercent;
		}
		
	}
		
	flip(CmpBuffer,width,height);
	for( int i = 0; i < 4 ; i++)
	{
		rotate(CmpBuffer,width,height,90);
		matchpercent = similarity(OrgBuffer, CmpBuffer, width , height);
		if( matchpercent > max_matchpercent)
		{
			max_matchpercent = matchpercent;
		}
	}	
	
	if( max_matchpercent > 96.5 )
	{
		return 1;
	}
	return 0;
				
}

void flip(unsigned char* CmpBuffer, int width, int height)
{
	unsigned char* Buffer = new unsigned char[width*height]; 
	for(int i=0;i<height;i++)
	{
		for(int j=0;j<width;j++)
		{
    
               *(Buffer+ (i*width + j)) = *(CmpBuffer+ (i*width + width-1-j));
         }
   }
   memcpy(CmpBuffer,Buffer,(width*height));
   delete [] Buffer;
}

void rotate(unsigned char* CmpBuffer, int width, int height, int angle)
{
	const double Offset = height/2;
	double cartesian_x = 0.0;
	double cartesian_y = 0.0;
	double rot_trans_cartesian_x = 0.0;
    double rot_trans_cartesian_y = 0.0;
    double rad_angle = (angle*PI)/180;
    
    unsigned char* Buffer = new unsigned char[width*height]; 
    
    unsigned char pixelValue;
	
	for(int imgrow =0; imgrow < height; imgrow++)
	{
		for(int imgcol=0 ; imgcol < width ; imgcol++)
		{ 
			cartesian_x = imgcol + 0.5 - Offset;
			cartesian_y = height - 0.5 - imgrow - Offset;
			
			//Rotate
			
			rot_trans_cartesian_x = cartesian_x*cos(rad_angle) - cartesian_y*sin(rad_angle);
			rot_trans_cartesian_y = cartesian_y*cos(rad_angle) + cartesian_x*sin(rad_angle);
			
	        double out_image_col     =   (rot_trans_cartesian_x - 0.5 + Offset);
			double out_image_row     =   (height - rot_trans_cartesian_y - 0.5 - Offset);
			
			pixelValue = bilinear(CmpBuffer,out_image_col,out_image_row,width,1,height,0);
		    
		    if( pixelValue > 127)
		    {
				pixelValue = BG;
			}
			else
			{
				pixelValue = FG;
			}
			
			*(Buffer + ((imgrow*width + imgcol)) ) = pixelValue;
		}
	}
	 
	memcpy(CmpBuffer,Buffer,(width*height));
}
			 
unsigned char bilinear(unsigned char* Img,double new_image_col , double new_image_row, int width , int bpp, int height,int channel)
{
	int refpoint_i =0 , refpoint_j = 0 ;
	refpoint_i = (int)new_image_row;
	refpoint_j = (int)new_image_col;
	double pix_val1, pix_val2;
	double pix_val;
	unsigned char Qref, Qright, Qdown, Qdiag;
	unsigned char pix_value;
	double delta_x = 0.0 , delta_y = 0.0;

	Qref = 0;

	if( refpoint_j < 0)
	{
		refpoint_j = 0;
		new_image_col = 0.0;
	}
	if( refpoint_i < 0)
	{
		refpoint_i = 0;
		new_image_row = 0.0;
	}
	if( refpoint_i >= height)
	{
		refpoint_i = height -1;
		new_image_row = height - 1;
	}
	if( refpoint_j >= width -1 )
	{
		refpoint_j = width -1;
		new_image_col = width-1;
	}

	Qref = *(Img+ ((refpoint_i*width + refpoint_j)*bpp) + channel );
	Qright = Qref;
	Qdown = Qref;
	Qdiag = Qref;

	if( (refpoint_j + 1) <  width)
	{    
		Qright = *(Img+ (((refpoint_i)*width + refpoint_j+1)*bpp ) + channel );
	}
	if( (refpoint_i + 1) < height)
	{
		Qdown = *(Img+ (((refpoint_i + 1)*width + refpoint_j)*bpp) + channel);
	}
	if( (refpoint_j + 1)  < width && (refpoint_i +1) < height )
	{
		Qdiag = *(Img+ (((refpoint_i + 1)*width + refpoint_j + 1 )*bpp) + channel);
	}

	delta_x = new_image_col - refpoint_j;
	delta_y = new_image_row - refpoint_i;

	pix_val1 = Qref*(1-delta_x) + (delta_x*Qright);
	pix_val2 = Qdown*(1-delta_x) + (delta_x*Qdiag);
	pix_val = pix_val1*(1-delta_y) + (delta_y*pix_val2);
	pix_value = (unsigned char)pix_val;

	return pix_value;
}   

double similarity(unsigned char* OrgBuffer,unsigned char* CmpBuffer, int width , int height )
{
	double Matching_FG_Counter = 0;
	double Orig_FG_Counter = 0;
	
    for(int imgrow =0; imgrow < height; imgrow++)
	{
		for(int imgcol=0 ; imgcol < width ; imgcol++)
		{ 
			
			if( *(OrgBuffer + (imgrow*width + imgcol) ) == *(CmpBuffer + (imgrow*width + imgcol) ) )
			{
				Matching_FG_Counter++;
			}
		}
	}	
	double result = (Matching_FG_Counter/(93*93))*100;
			
	return result;
}
	

			
