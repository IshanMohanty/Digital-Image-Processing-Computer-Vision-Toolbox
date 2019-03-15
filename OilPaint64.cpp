#include <iostream>
#include <fstream>
#include <cmath> 
#include <cstdio>
#include <stdlib.h>

using namespace std;

//function for getting pixel value

unsigned char * getpixel(unsigned char* Img , int i , int j , int width , int height , int bpp);

//function for 64 color quantization

void quantize_64(unsigned char* Img,int width , int height , int bpp, unsigned char * Tempbuff, unsigned char* tempred,unsigned char* tempgreen, unsigned char* tempblue);

//function for implementing oil paint effect

void oilpaint(unsigned char* Tempbuff,int width , int height , int bpp, unsigned char* Out, int N);

unsigned char * getpixel(unsigned char* Image , int i , int j , int width , int height , int bpp)
{
	return (Image +((i*width +j)*bpp));
}

void quantize_64(unsigned char* Img,int width , int height , int bpp, unsigned char * Tempbuff, unsigned char* tempred,unsigned char* tempgreen, unsigned char* tempblue)
{
	for(int i = 0 ;i< height ;i++)
	{
		for(int j=0 ; j<width ; j++)
		{
			//red
			tempred = (Img + ((i*width + j)*bpp) + 0);
			if( *(tempred) >=0 && *(tempred) <= 63)
			{
				*(Tempbuff + ((i*width + j)*bpp) + 0) = 31;
			}
			else if( *(tempred) > 63 && *(tempred) <= 127)
			{
				*(Tempbuff + ((i*width + j)*bpp) + 0) = 95;
			}
			else if(*(tempred) > 127 && *(tempred) <= 191)
			{
				*(Tempbuff + ((i*width + j)*bpp) + 0) = 159;
			}
			else if(*(tempred) > 191 && *(tempred) <= 255)
			{
				*(Tempbuff + ((i*width + j)*bpp) + 0) = 223;
			}
			else
			{
				cout<<"wrong gray level in input pixel"<<endl;
			}
			
			//green
			
			tempgreen = (Img + ((i*width + j)*bpp) + 1);
			if( *(tempgreen) >=0 && *(tempgreen) <= 63)
			{
				*(Tempbuff + ((i*width + j)*bpp) + 1) = 31;
			}
			else if( *(tempgreen) > 63 && *(tempgreen) <= 127)
			{
				*(Tempbuff + ((i*width + j)*bpp) + 1) = 95;
			}
			else if(*(tempgreen) > 127 && *(tempgreen) <= 191)
			{
				*(Tempbuff + ((i*width + j)*bpp) + 1) = 159;
			}
			else if(*(tempgreen) > 191 && *(tempgreen) <= 255)
			{
				*(Tempbuff + ((i*width + j)*bpp) + 1) = 223;
			}
			else
			{
				cout<<"wrong gray level in input pixel"<<endl;
			}
						
			//blue
			
			tempblue = (Img + ((i*width + j)*bpp) + 2);
			if( *(tempblue) >=0 && *(tempblue) <= 63)
			{
				*(Tempbuff + ((i*width + j)*bpp) + 2) = 31;
			}
			else if( *(tempblue) > 63 && *(tempblue) <= 127)
			{
				*(Tempbuff + ((i*width + j)*bpp) + 2) = 95;
			}
			else if(*(tempblue) > 127 && *(tempblue) <= 191)
			{
				*(Tempbuff + ((i*width + j)*bpp) + 2) = 159;
			}
			else if(*(tempblue) > 191 && *(tempblue) <= 255)
			{
				*(Tempbuff + ((i*width + j)*bpp) + 2) = 223;
			}
			else
			{
				cout<<"wrong gray level in input pixel"<<endl;
			}						
	    }
	   }
}	

void oilpaint(unsigned char* Tempbuff,int width , int height , int bpp, unsigned char* Out,int N)
{ 
	
	  int arrayred_4[4]={0};
	  int arraygreen_4[4]={0};
	  int arrayblue_4[4]={0};
	
	
	int n,m; //relative pixel position	
	
	unsigned char * temp = NULL;
	
	for(int i = 0; i<height ; i++)
	{
		for(int j=0 ; j<width ; j++)
		{
			 
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
																	 
										temp = getpixel(Tempbuff,n,m,width,height,bpp);
										
										//red

										switch( *(temp+0) )
										{
											
											case 31: arrayred_4[0]++;

												 break;

											case 95: arrayred_4[1]++;
												 break;

											case 159: arrayred_4[2]++;
												  break;

											case 223: arrayred_4[3]++;
												  break; 

											default:  cout<<"incorrect quantized red value"<<endl;
												  break;
										}
								
										//green

										switch(*(temp+1))
										{
											case 31: arraygreen_4[0]++;
												 break;

											case 95: arraygreen_4[1]++;
												 break;

											case 159: arraygreen_4[2]++;
												  break;

											case 223: arraygreen_4[3]++;
												  break;

											default:  cout<<"incorrect quantized green value"<<endl;
												  break;
										}


										//blue
										
										switch(*(temp+2))
										{
											case 31: arrayblue_4[0]++;
												 break;

											case 95: arrayblue_4[1]++;
												 break;

											case 159: arrayblue_4[2]++;
												  break;

											case 223: arrayblue_4[3]++;
												  break;

											default:  cout<<"incorrect quantized blue value"<<endl;
												  break;
										}
									
				   }
		        } // end of k and h for loop
		        
           
		       //red
		       // Check which gray level among the 4 gray levels occurs the most and assign to output
		       
		       int maxredindex = 0;
		       
		       for(int l=0; l<3; l++)
		       {
				  if(arrayred_4[maxredindex] <= arrayred_4[l+1])
				  {
					   maxredindex = l+1;
				  }
			   }			   

		       if( maxredindex == 0)
		       {
			       *(Out + ((i*width + j)*bpp) + 0) = 31;
		       }
		       else if( maxredindex == 1)
		       {
			       *(Out + ((i*width + j)*bpp) + 0) = 95;
		       }
		       else if( maxredindex == 2)
		       {
			       *(Out + ((i*width + j)*bpp) + 0) = 159;
		       }
		       else if( maxredindex == 3 )
		       {
			       *(Out + ((i*width + j)*bpp) + 0) = 223;
		       }

		       //green
               
               int maxgreenindex = 0;
		       
		       for(int l=0; l<3; l++)
		       {
				  if(arraygreen_4[maxgreenindex] <= arraygreen_4[l+1])
				  {
					   maxgreenindex = l+1;
				  }
			   }

		       if( maxgreenindex == 0)
		       {
			       *(Out + ((i*width + j)*bpp) + 1) = 31;
		       }
		       else if( maxgreenindex == 1)
		       {
			       *(Out + ((i*width + j)*bpp) + 1) = 95;
		       }
		       else if( maxgreenindex == 2)
		       {
			       *(Out + ((i*width + j)*bpp) + 1) = 159;
		       }
		       else if( maxgreenindex == 3 )
		       {
			       *(Out + ((i*width + j)*bpp) + 1) = 223;
		       }

		       //Blue

		       int maxblueindex=0;
		       for( int l=0 ; l < 3 ; l++)
		       {
			       if(arrayblue_4[maxblueindex] <= arrayblue_4[l+1])
			       {
				       maxblueindex = l+1;
			       }
		       }

		       if( maxblueindex == 0)
		       {
			       *(Out + ((i*width + j)*bpp) + 2) = 31;
		       }
		       else if( maxblueindex == 1)
		       {
			       *(Out + ((i*width + j)*bpp) + 2) = 95;
		       }
		       else if( maxblueindex == 2)
		       {
			       *(Out + ((i*width + j)*bpp) + 2) = 159;
		       }
		       else if( maxblueindex == 3 )
		       {
			       *(Out + ((i*width + j)*bpp) + 2) = 223;
		       }
		     
		       
		       for(int x=0 ; x < 4 ; x++)
               {
						 arrayred_4[x] = 0;
						 arraygreen_4[x] = 0;
						 arrayblue_4[x] = 0;
			   }		
			 			 			   
		}
	}//end of for loops i , j	
}

	
int main(int argc, char *argv[])
{
    FILE* fptr1;
    int width  = atoi(argv[3]);
    int height = atoi(argv[4]);
    int bpp    = 3;
    int N      = atoi(argv[5]);
    
    unsigned char *Img        = new unsigned char[width*height*bpp];
    unsigned char *Tempbuff   = new unsigned char[width*height*bpp];
    unsigned char *Out        = new unsigned char[width*height*bpp];
    unsigned char *tempred    = NULL;
    unsigned char *tempgreen  = NULL;
    unsigned char *tempblue   = NULL;
    
    // Check for proper syntax
	if (argc < 5){
		cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
		cout << argv[0]<<"    input_image.raw output_image.raw width height windowsize" << endl;
		return 0;
	}
    
    fptr1 = fopen(argv[1],"rb");
    
	if(!(fptr1 == NULL))
	{     
        fread(Img,sizeof(unsigned char),width*height*bpp,fptr1); //Reading RAW image into 3D image data matrix
	    fclose(fptr1);
		cout<<"Image can be read"<<endl;
		cout<<"Successfully Done!"<<endl;		
	}
	else
	{
		cout<<"Image cannot be read"<<endl;
	}
	
	
	quantize_64(Img,width,height,bpp,Tempbuff,tempred,tempgreen,tempblue);
	
	oilpaint(Tempbuff,width,height,bpp,Out,N);
	
	//write
	fptr1 =fopen(argv[2],"wb");
	if(!(fptr1 == NULL))
    { 
		fwrite(Out,sizeof(unsigned char),width*height*bpp,fptr1);
	    fclose(fptr1);
	}
	
	delete[] Img;
	delete[] Tempbuff;
	delete[] Out;
	
	return 0;
}	
