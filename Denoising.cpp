#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

using namespace std;

unsigned char * getpixel(unsigned char* Img , int i , int j , int width , int height , int bpp);

int compare (const void * a, const void * b); 

double CalcPSNR(double MSE);

unsigned char * getpixel(unsigned char* Img , int i , int j , int width , int height , int bpp)
{
	return (Img+((i*width +j)*bpp));
}

int compare (const void * a, const void * b) 
{
   return ( *(int*)a - *(int*)b );
}

double CalcPSNR(double MSE)
{
	return ( 10*log10((255*255)/(MSE)) );
}

int main(int argc, char *argv[])
{
	 // Check for proper syntax
	if (argc < 7)
	{
		cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
		cout << argv[0]<<"InputNoisyImage.raw InputOriginalImage.raw output_image.raw width height windowsize" << endl;
		return 0;
	}
	
	FILE* fptr1;
	FILE* fptr2;
  
    int width  = atoi(argv[4]);
    int height = atoi(argv[5]);  
    int bpp    = 3;
    int N      = atoi(argv[6]);  
    
    int s;
    
    int windowred[N*N]={0}; 
    int windowgreen[N*N]={0};
    int windowblue[N*N]={0};
    int sumred = 0 , sumgreen = 0 , sumblue = 0 , averagered = 0 , averagegreen = 0 , averageblue = 0;
    int FilterRed = 0 , FilterGreen = 0 , FilterBlue = 0;
    int OriginalRed = 0 , OriginalGreen = 0 , OriginalBlue = 0 ;
    int squared_sum_red = 0 , squared_sum_green = 0 , squared_sum_blue = 0;
    double MSE_Red = 0.0 , MSE_Green = 0.0 , MSE_Blue = 0.0;
    double PSNR_Red = 0.0 , PSNR_Green = 0.0 ,PSNR_Blue = 0.0 ; 
     
    unsigned char *Img        = new unsigned char[width*height*bpp];
    unsigned char *OrigImg    = new unsigned char[width*height*bpp];
    unsigned char *TempBuff   = new unsigned char[width*height*bpp];
    unsigned char *Out        = new unsigned char[width*height*bpp];
    
   
      
    fptr1 = fopen(argv[1],"rb");
    fptr2 = fopen(argv[2],"rb");
    
	if(!(fptr1 == NULL))
	{     
        fread(Img,sizeof(unsigned char),width*height*bpp,fptr1); //Reading RAW image into 3D image data matrix
	    fclose(fptr1);
		cout<<"Image can be read"<<endl;
		
	}
	else
	{
		cout<<"Image cannot be read"<<endl;
	}
	
	if(!(fptr2 == NULL))
	{
        fread(OrigImg,sizeof(unsigned char),width*height*bpp,fptr2); //Reading RAW image into 3D image data matrix
	    fclose(fptr2);
		cout<<"Image can be read"<<endl;
		
	}
	else
	{
		cout<<"Image cannot be read"<<endl;
	}

	unsigned char * temp = NULL;

	int n,m; //relative pixel position	
	
	for(int i = 0; i<height ; i++)
	{
		for(int j=0 ; j<width ; j++)
		{
			       memset(windowred, 0, sizeof(windowred));
			       memset(windowgreen, 0, sizeof(windowgreen));
			       memset(windowblue, 0, sizeof(windowblue));
			       
			       s=0;
			       
	               for(int k= (-1*(N/2)) ; k <= (N/2) ; k++)
	               {
		                for(int h = (-1*(N/2)) ; h <= (N/2) ; h++)
		                {
							        
					                n = i + k; 
					                m = j + h;

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
									
									temp = getpixel(Img,n,m,width,height,bpp);
									windowred[s] = *(temp + 0);
									windowgreen[s] = *(temp + 1);
									windowblue[s]  = *(temp + 2);
									
									s++;
						 }
					} // end of for loop for window
					
					
					// Perform Median Filtering 
					
                    qsort(windowred, (N*N) , sizeof(int), compare);
                    qsort(windowgreen, (N*N) , sizeof(int), compare);
                    qsort(windowblue, (N*N) , sizeof(int), compare);
                    
                    *(TempBuff + ((i*width + j)*bpp) + 0)      = windowred[ (int) ((N*N)/(2) + 1) ];
			        *(TempBuff +((i*width +j)*bpp)+ 1)         = windowgreen[ (int) ((N*N)/(2) + 1) ];
			        *(TempBuff +((i*width +j)*bpp)+2)          = windowblue[ (int) ((N*N)/(2) + 1) ];	
			        
			    }
		    }// end of i,j loop
		
			
		    for(int i = 0; i<height ; i++)
	        {
		        for(int j=0 ; j<width ; j++)
		        {
			       // Use Linear Filter
			        
			       memset(windowred, 0 , sizeof(windowred));
			       memset(windowgreen, 0 , sizeof(windowgreen));
			       memset(windowblue, 0 , sizeof(windowblue));
			       
			       s=0;
			       
			       sumred = 0;
			       sumgreen = 0;
			       sumblue = 0;
			       		       			        
			        for(int k= (-1*(N/2)) ; k <= (N/2) ; k++)
	                {
		                for(int h = (-1*(N/2)) ; h <= (N/2) ; h++)
		                {
							        
					                n = i + k; 
					                m = j + h;

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
									
									temp           = getpixel(TempBuff,n,m,width,height,bpp);
									windowred[s]   = *(temp + 0);
									sumred         = sumred + windowred[s];
									windowgreen[s] = *(temp + 1);
									sumgreen       = sumgreen + windowgreen[s];
									windowblue[s]  = *(temp + 2);
									sumblue        = sumblue + windowblue[s];
									
									s++;
						 }
					}
		
					averagered   = (int) ((sumred)/(float)(N*N));
					averagegreen = (int) ((sumgreen)/(float)(N*N));
					averageblue  = (int) ((sumblue)/(float)(N*N));
	
					*(Out + ((i*width + j)*bpp) + 0)      = averagered;
			        *(Out + ((i*width +j)*bpp)  + 1)      = averagegreen;
			        *(Out + ((i*width +j)*bpp)  + 2)      = averageblue;								
			        	        
		            }
		       } // end of i, j loop for linear filter
		      
		      
		       
		      squared_sum_red = 0 ;
		      squared_sum_green = 0;
		      squared_sum_blue = 0;
		      
		      for(int i=0 ; i < height ; i++)
		      {
				  for(int  j=0 ; j < width ; j++)
				  {
					  FilterRed   = *(Out + ((i*width + j)*bpp) + 0 );
					  FilterGreen = *(Out + ((i*width + j)*bpp) + 1 );
					  FilterBlue  = *(Out + ((i*width + j)*bpp) + 2 );
					  
					  OriginalRed   = *(OrigImg + ((i*width + j)*bpp) + 0 );
					  OriginalGreen = *(OrigImg + ((i*width + j)*bpp) + 1 );
					  OriginalBlue  = *(OrigImg + ((i*width + j)*bpp) + 2 );
					  
					  squared_sum_red   =  squared_sum_red + pow((FilterRed - OriginalRed) , 2 ); 
					  squared_sum_green =  squared_sum_green + pow((FilterGreen - OriginalGreen) , 2 ); 
					  squared_sum_blue  =  squared_sum_blue + pow((FilterBlue - OriginalBlue) , 2 ); 
					  
			      }
			  }
			  
			  MSE_Red =   (double) (squared_sum_red/ (double) (width*height));
		      MSE_Green =   (double) (squared_sum_green/ (double) (width*height));	 
		      MSE_Blue =   (double) (squared_sum_blue / (double) (width*height)); 
		      
		      PSNR_Red   = CalcPSNR(MSE_Red);
		      PSNR_Green = CalcPSNR(MSE_Green);
		      PSNR_Blue  = CalcPSNR(MSE_Blue);
		      
		      cout<<MSE_Red<<" MSE Red"<<endl;
		      cout<<MSE_Green<<" MSE Green"<<endl;
		      cout<<MSE_Red<<" MSE Blue"<<endl;
		      	      
		      cout<<PSNR_Red<<" db for Red Channel"<< endl;      
		      cout<<PSNR_Green<<" db for Green Channel"<< endl;		      
		      cout<<PSNR_Blue<<" db for Blue Channel"<< endl;       
		      	       
     
     //write
	
	fptr1 =fopen(argv[3],"wb");
	
	if(!(fptr1 == NULL))
    { 
            fwrite(Out,sizeof(unsigned char),width*height*bpp,fptr1);
	        fclose(fptr1);
	}
		
	delete[] Img;
	delete[] TempBuff;
	delete[] Out;
	delete[] OrigImg;
			
	return 0;
}
        
                    
                    
                    
					
					
									
									
									
									
									
									
									
						
									 
									
									
					
					
					
