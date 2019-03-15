#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <stdlib.h>
#include <math.h> 
#include <map>
#include "LoG.h"

using namespace std;

vector <double> LoG_Mask =  {
								 0,    -0.25,   0,
							    -0.25,     1,   -0.25,
								 0,    -0.25,   0
							};
							
vector <double> gaussian_filter = { 
									  1/100.0, 2/100.0, 4/100.0,  2/100.0, 1/100.0, 
									  2/100.0, 4/100.0, 8/100.0,  4/100.0, 2/100.0, 
									  4/100.0, 8/100.0, 16/100.0, 8/100.0, 4/100.0, 
									  2/100.0, 4/100.0, 8/100.0,  4/100.0, 2/100.0, 
									  1/100.0, 2/100.0, 4/100.0,  2/100.0, 1/100.0 
									  
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

void apply_LoG(unsigned char* Buffer, int* LoG_Buffer, int width ,int height, unsigned char* Normalized_Buffer)
{
	int N=3;
	unsigned char * temp = NULL;
	
	double maxval = -3000;
	double minval =  3000;

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
										sum += (*(temp)*LoG_Mask[t]);
										t++;
						}	
					}
					
				    *(LoG_Buffer + (i*width + j) ) = (floor)(sum); 	
				    
				    if( (floor)(sum) > maxval ) 
				    {
						maxval = (floor)(sum);
					}
		            if( (floor)(sum) < minval )
		            {
						 minval = (floor)(sum);
					}
				    	
	       }
	  }	
	   
	  //Shift negative and largely positive values properly within 0-255 range
	  
	  for(int i = 0; i < height ; i++)
	  {
			for(int j=0 ; j < width ; j++)
			{
				if( *(LoG_Buffer + (i*width + j) ) < 0 )
				{
					*(Normalized_Buffer + (i*width+j) ) = *(LoG_Buffer + (i*width + j)) + minval;
				}
				
				else if( *(LoG_Buffer + (i*width + j) ) > 255 )
				{
					*(Normalized_Buffer + (i*width+j) ) = *(LoG_Buffer + (i*width + j)) - (maxval - 255 );
				}
				
				else
				{
					*(Normalized_Buffer + (i*width+j) ) = *(LoG_Buffer + (i*width + j));
				}
			}
	  }
	  	  
}

int histogram(int* LoG_Buffer,int width, int height)
{
	  map<int,int> histogram_info;
	 
	  for(int i = 0; i < height ; i++)
	  {
			for(int j=0 ; j < width ; j++)
			{
				int key_val = *(LoG_Buffer + (i*width + j) );
				
				 if( histogram_info.find( key_val) != histogram_info.end() )
				 {
					 histogram_info[key_val]++;
				 }
				 else
				 {
					 histogram_info.insert( pair<int, int>(key_val, 1) );
				 }
			}
	  }
	
	map<int, int>::iterator it = histogram_info.begin();

	while (it != histogram_info.end())
	{
		// Accessing KEY from element pointed by it.
		int pixel_intensity = it->first;
 
		// Accessing VALUE from element pointed by it.
		int count = it->second;
 
		cout << pixel_intensity << " :: " << count << endl;
 
		// Increment the Iterator to point to next entry
		it++;
	}
	
	//Calculate Knee Theshold 
	
	int cum_count = 0;
	int first_knee_threshold = 0;
	
	map<int, int>::iterator it1 = histogram_info.begin();
	
	while( it1 != histogram_info.end() )
	{
		//cout<<it1->first<<endl;
		//0.075 --- noisy ----2 threshold --- noisy image
		// 0.075 ---- orig ---1 threshold --- orig image
		if( cum_count > (floor)(0.085*width*height) )
		{
			first_knee_threshold = it1->first;
			break;
		}
		else
		{ 
		    cum_count += it1->second;
		}
		
		it1++;
	}	
	
	return first_knee_threshold;
}

void Threshold_LoG_Buffer(int knee_threshold,int* LoG_Buffer,int width,int height,int* ternary_Buffer,unsigned char* tri_gray_buffer)				 
{
	 for(int i = 0; i < height ; i++)
	 {
			for(int j=0 ; j < width ; j++)
			{
				if( *(LoG_Buffer + (i*width + j) ) < (knee_threshold) )
				{
					*(ternary_Buffer + (i*width + j) ) = -1;
				    *( tri_gray_buffer + (i*width + j ) ) = 64;
				}
				
				if(  *(LoG_Buffer + (i*width + j) ) > (-1*knee_threshold) )
				{
					*(ternary_Buffer + (i*width + j) ) = 1;
				    *( tri_gray_buffer + (i*width + j ) ) = 192;
				}
				
				if( (*(LoG_Buffer + (i*width + j) ) >= (knee_threshold) ) && ( *(LoG_Buffer + (i*width + j) ) <= (-1*knee_threshold) )  )
				{
					*(ternary_Buffer + (i*width + j) ) = 0;
				    *( tri_gray_buffer + (i*width + j ) ) = 128;
				}
			}
	}	
}

void zero_crossing_algo(int* ternary_map ,unsigned char* Out,int width,int height)
{
	for(int i = 1 ; i < height ; i++ )
	{
		for( int j = 1 ; j < width ; j++ )
		{
			int top    = *( ternary_map + ( (i-1)*width + j )   );
			int bottom = *( ternary_map + ( (i+1)*width + j )   );
			int left   = *( ternary_map + ( (i)*width + (j-1))  );
			int right  = *( ternary_map + ( (i)*width + (j+1))  );
			
			if( *(ternary_map + (i*width + j ) ) == 0 )
			{
				if( ((top*bottom) == -1) || ((left*right) == -1) )
				{
					*(Out + (i*width + j) ) = 255;
				}
				else
				{
					*(Out + (i*width + j) ) = 0;
				}
			}
			
			if( *(ternary_map + (i*width + j ) ) == 1 )
			{
				if( ( (1*top) == -1) || ( (1*bottom) == -1 ) || ((1*left) == -1 ) || ((1*right) == -1) )
				{
					*(Out + (i*width + j) ) = 255;
				}
				else
				{
					*(Out + (i*width + j) ) = 0;
				}
			}
			
			if( *(ternary_map + (i*width + j ) ) == -1 )
			{
				if( ( (-1*top) == -1) || ( (-1*bottom) == -1 ) || ((-1*left) == -1 ) || ((-1*right) == -1) )
				{
					*(Out + (i*width + j) ) = 255;
				}
				else
				{
					*(Out + (i*width + j) ) = 0;
				}
			}
			
		}
	}	
}
