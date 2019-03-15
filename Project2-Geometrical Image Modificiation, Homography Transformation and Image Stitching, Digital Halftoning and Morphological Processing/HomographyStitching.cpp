
#include "HomographyStitching.h"
#include <stdio.h>


double mult_homo_x( double out_cart_x , double out_cart_y , double Hinv[] )
{
	double x = Hinv[0]*out_cart_x + Hinv[1]*out_cart_y + Hinv[2];
	return x;
}

double mult_homo_y( double out_cart_x , double out_cart_y , double Hinv[] )
{
	double y = Hinv[3]*out_cart_x + Hinv[4]*out_cart_y + Hinv[5];
	return y;
}

double mult_homo_w( double out_cart_x , double out_cart_y , double Hinv[] )
{
	double w = Hinv[6]*out_cart_x + Hinv[7]*out_cart_y + Hinv[8];
	return w;
}

void HomographyStitching(unsigned char* middle_Img,unsigned char* left_Img,unsigned char* right_Img,unsigned char* Buffer,
                         int height,int width,int height_output,int width_output,const int bpp)
{
   
   int tx = 800;
   int ty = 800;
 
   double out_cart_x = 0.0;
   double out_cart_y = 0.0;
   double cart_x     = 0.0;
   double cart_y     = 0.0;
   double trans_x    = 0.0;
   double trans_y   = 0.0;
   
   double Hinv_left[9] = {   0.555512   ,   0.021690 ,	 -253.923738 , -0.188588  ,   0.763377 ,  -443.593258   , -0.000576  ,   0.000017 ,  1.260170          };
   double Hinv_right[9] = { 1.159958 , -0.011384 ,-1154.524288, 0.208937 ,  1.073586 ,-1094.069909,0.000609 , -0.000017 ,    0.404287 };
   
   
   //Paste Middle Image to Output
   
   for( int imgrow = 0 ; imgrow < height ; imgrow++)
   {
	   for(int imgcol = 0; imgcol < width ; imgcol++)
	   {
		    //Convert Middle image coordinates to cartesian plane
		    
	        cart_x = imgcol + 0.5;
	        cart_y = height - 0.5 - imgrow;
	      
	        //translate Middle Image in cartesian plane
	        
	        trans_x = cart_x + tx;
	        trans_y = cart_y + ty;
	        
	        //Convert Cartesian coordinates to output image coordinates
	        
	        int  out_imgcol = (int)(trans_x - 0.5);
	        int  out_imgrow = (int)(height_output - 0.5 - trans_y);
	        
	        //printf("Input %d , %d : Output : %d , %d \n", imgrow , imgcol , out_imgcol , out_imgrow );  
	        
	        //use coordinates of output image for Buffer and put in values from input inside this Buffer
	        
	        *(Buffer + (( out_imgrow*width_output + out_imgcol)*bpp) + 0)  = *(middle_Img + ((imgrow*width + imgcol)*bpp) + 0);
	        *(Buffer + ((out_imgrow*width_output + out_imgcol)*bpp) + 1)  = *(middle_Img + ((imgrow*width + imgcol)*bpp) + 1);
	        *(Buffer + ((out_imgrow*width_output + out_imgcol)*bpp) + 2)  = *(middle_Img + ((imgrow*width + imgcol)*bpp) + 2);
	        
	      }
	  }
	  
	  
	  
	  // Use homography and paste left to output
	  
	  for( int out_row = 0 ; out_row < height_output ; out_row++)
	  {
		  for( int out_col = 0 ; out_col < width_output ; out_col++)
		  {
			   out_cart_x = out_col + 0.5;
			   out_cart_y = height_output - 0.5 - out_row;
			   
			   double intermediate_left_x  = mult_homo_x( out_cart_x , out_cart_y , Hinv_left);
			   double intermediate_left_y  = mult_homo_y( out_cart_x , out_cart_y , Hinv_left);
			   double w_factor             = mult_homo_w( out_cart_x , out_cart_y , Hinv_left);
			   
			   double final_left_x = (intermediate_left_x)/(w_factor);
			   double final_left_y = (intermediate_left_y)/(w_factor);
			   
			   int left_img_row = (int)(height - 0.5 - final_left_y); 
			   int left_img_col = (int)(final_left_x - 0.5);
			
			   if(out_row == 1680 && out_col == 758)
				printf("[%d %d] <- [%d %d]\n", out_row, out_col, left_img_row, left_img_col);
			   
			   
               if( left_img_row >=0 && left_img_row <= height -1 && left_img_col >=0 && left_img_col <= width-1 )
               {			   
				 *(Buffer + ((out_row*width_output+ out_col)*bpp) + 0)  = *(left_Img + ( (left_img_row*width + left_img_col)*bpp) + 0);
				 *(Buffer + ((out_row*width_output+ out_col)*bpp) + 1)  = *(left_Img + ( (left_img_row*width + left_img_col)*bpp) + 1);
				 *(Buffer + ((out_row*width_output+ out_col)*bpp) + 2)  = *(left_Img + ((left_img_row*width+ left_img_col)*bpp) + 2);		
			   }   
		 }
	  }   
	   
	  
	  
		   
	  //Use homography and paste Right to output
	  
	  for( int out_row = 0 ; out_row < height_output ; out_row++)
	  {
		  for( int out_col = 0 ; out_col < width_output ; out_col++)
		  {
			   out_cart_x = out_col + 0.5;
			   out_cart_y = height_output - 0.5 - out_row;
			   
			   double intermediate_right_x  = mult_homo_x( out_cart_x , out_cart_y , Hinv_right);
			   double intermediate_right_y  = mult_homo_y( out_cart_x , out_cart_y , Hinv_right);
			   double w_factor              = mult_homo_w( out_cart_x , out_cart_y , Hinv_right);
			   
			   double final_right_x = (intermediate_right_x)/(w_factor);
			   double final_right_y = (intermediate_right_y)/(w_factor);
			   
			   int right_img_row = (int)(height - 0.5 - final_right_y); 
			   int right_img_col = (int)(final_right_x - 0.5);
			   
			 if( right_img_row >=0 && right_img_row <= height -1 && right_img_col >=0 && right_img_col <= width-1 )
               {			
			      
					*(Buffer + ((out_row*width_output)+ out_col)*bpp + 0)  = *(right_Img + ((right_img_row*width)+ right_img_col)*bpp + 0);
					*(Buffer + ((out_row*width_output)+ out_col)*bpp + 1)  = *(right_Img + ((right_img_row*width)+ right_img_col)*bpp + 1);
					*(Buffer + ((out_row*width_output)+ out_col)*bpp + 2)  = *(right_Img + ((right_img_row*width)+ right_img_col)*bpp + 2);
			   }
		 }
	  }   
	  		   
	   
}
