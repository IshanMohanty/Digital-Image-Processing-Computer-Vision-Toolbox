#include <vector>
#include "Edge_Detection.h"
#include <math.h>
#include <stdlib.h> 
#include <iostream>
#include <cstring>

using namespace std;

vector <double> gaussian_filter = { 
									  1/100.0, 2/100.0, 4/100.0,  2/100.0, 1/100.0, 
									  2/100.0, 4/100.0, 8/100.0,  4/100.0, 2/100.0, 
									  4/100.0, 8/100.0, 16/100.0, 8/100.0, 4/100.0, 
									  2/100.0, 4/100.0, 8/100.0,  4/100.0, 2/100.0, 
									  1/100.0, 2/100.0, 4/100.0,  2/100.0, 1/100.0 
									  
								  };								  
								  
vector <double> GX_SOBEL =  { 
	                          0.25,  0.00, -0.25,
							  0.50,  0.00, -0.50,
							  0.25,  0.00, -0.25
							};
							
vector <double> GY_SOBEL = {	0.25,  0.50,  0.25,
							    0.00,  0.00,  0.00,
							   -0.25, -0.50, -0.25
						   };		
					


unsigned char * getpixel(unsigned char* Image , int i , int j , int width , int height , int bpp)
{
	return (Image +((i*width +j)*bpp));
}

void convert_RGB_GRAY(unsigned char* Img, int width, int height, int bpp, unsigned char* Buffer)
{
	unsigned char* temp = NULL;
	for(int imgrow = 0 ; imgrow < height ; imgrow++)
	{
		for(int imgcol=0; imgcol < width ; imgcol++)
		{
			temp = getpixel(Img,imgrow,imgcol,width,height,bpp);
			double red   = *(temp+0);
			double green = *(temp+1);
			double blue  = *(temp+2);
			unsigned char gray = (unsigned char)(0.21*red +0.72*green +0.07*blue);
			*(Buffer + (imgrow*width + imgcol) ) = gray;	
		}
	}
}

void gaussian_noise_removal(unsigned char* Buffer, int width , int height)
{
    int N=5;
	unsigned char * temp = NULL;
	unsigned char* LocalBuffer = new unsigned char[width*height];

	for(int i = 0; i < height ; i++)
	{
		for(int j=0 ; j < width ; j++)
		{
			 double sum = 0;
			 int t = 0;
	               for(int k= (-1*(N/2)) ; k <= (N/2) ; k++)
	               {
		                for(int h = (-1*(N/2)) ; h <= (N/2) ; h++)
		                {

					                 int n = i + k;
					                 int m = j + h;

				                     if( n < 0)
					                 {
					                     n = abs(n) - 1;
					                 }

										if( m < 0)
										{
											m = abs(m) - 1;
										}

										if( n > (height - 1) )
										{
											n = (2*height) - n - 1;
										}

										if( m > (width - 1) )
										{
											m = (2*width) - m - 1;
										}
																	 
										temp = getpixel(Buffer,n,m,width,height,1);
										sum += (*(temp)*gaussian_filter[t]);
										t++;
						}	
					}
					
					if( sum > 255 )
					{
						sum = 255;
					}
				    *(LocalBuffer + (i*width + j) ) = (unsigned char)(sum); 	
				    	
	       }
	  }
	  
	  memcpy(Buffer,LocalBuffer,width*height);
	  
}

unsigned char sobel_operator(unsigned char* Buffer, int width , int height,int bpp, double* Gradient_Buffer)
{
	int N=3;
	unsigned char * temp = NULL;
	double max_grad_val = 0;
    
	for(int i = 0; i < height ; i++)
	{
		for(int j=0 ; j < width ; j++)
		{
			 double  grad_x = 0;
			 double  grad_y = 0;
			 int t = 0;
			 
	               for(int k= (-1*(N/2)) ; k <= (N/2) ; k++)
	               {
		                for(int h = (-1*(N/2)) ; h <= (N/2) ; h++)
		                {

					                 int n = i + k;
					                 int m = j + h;

				                     if( n < 0)
					                 {
					                     n = abs(n) - 1;
					                 }

										if( m < 0)
										{
											m = abs(m) - 1;
										}

										if( n > (height - 1) )
										{
											n = (2*height) - n - 1;
										}

										if( m > (width - 1) )
										{
											m = (2*width) - m - 1;
										}
																	 
										temp = getpixel(Buffer,n,m,width,height,1);
										grad_x += (*(temp)*GX_SOBEL[t]*4);
										grad_y += (*(temp)*GY_SOBEL[t]*4);
										t++;
						}	
					}
					
					double GX_square = pow(grad_x,2.0);
					double GY_square = pow(grad_y,2.0);
					
					double G = sqrtf(GX_square + GY_square);
					//cout<<G<<endl;
					//~ if(G > 255) 
					//~ {
						//~ *(Gradient_Buffer + (i*width + j) ) = 255;
					//~ }
					//~ else
					//~ {
			            //~ *(Gradient_Buffer + (i*width + j) ) = G;
			        //~ }
			        
			        *(Gradient_Buffer + (i*width + j) ) = G;
			        

					//~ if( max_grad_val < *( Gradient_Buffer + (i*width + j ) ) ) 
					//~ {
						//~ max_grad_val = *( Gradient_Buffer + (i*width + j ) ) ;
					//~ }
					
					if( max_grad_val < G ) 
					{
						max_grad_val =  G  ;
						
					}
									
		}
	}
			
	return max_grad_val;
}

void sobel_threshold(double final_threshold,unsigned char* Out,double* Gradient_Buffer,int width, int height)
{
	    for(int imgrow = 0 ; imgrow < height ; imgrow++)
	    {
			for(int imgcol = 0 ; imgcol < width ; imgcol++)
			{
				
		       if( *(Gradient_Buffer + (imgrow*width + imgcol) ) > final_threshold ) 
		       {
			        *(Out + (imgrow*width + imgcol) ) = 255;
		       } 
		       else 
		       {
			        *(Out + (imgrow*width + imgcol) ) = 0;
		       }

		    }
	     }
}						
					
					
					
					
					
						
	     
	
	
			
			
