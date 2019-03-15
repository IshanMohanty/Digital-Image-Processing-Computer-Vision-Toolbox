#include <iostream>
#include <fstream>
#include <cmath>
#include <stdlib.h>

using namespace std;

unsigned char * getpixel(unsigned char* Img , int i , int j , int width , int height , int bpp);

void TransferMathFunction(double logvalues[] ,double TX[] , unsigned char ScaledTX[]);

unsigned char * getpixel(unsigned char* Img , int i , int j , int width , int height , int bpp)
{
	return (Img+((i*width +j)*bpp));
}

void TransferMathFunction(double logvalues[] ,double TX[] , unsigned char ScaledTX[])
{
	for(int i=0 ; i< 1020 ; i++)
    {
		       logvalues[i] = log( (i+1) );
    }
            
    for(int j=0 ; j < 256; j++)
    {
		       TX[j] = (logvalues[300+j] - logvalues[300])/ (logvalues[555] - logvalues[300]);
		       ScaledTX[j] = TX[j]*255;
	}
}
	
int main(int argc, char *argv[])
{
	// Check for proper syntax
	if (argc < 5){
		cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
		cout << argv[0]<<"input_image.raw output_image.raw width height" << endl;
		return 0;
	}
	
    FILE* fptr1;
    int bpp    = 3;
    double logvalues[1020]={0}; // 255*4;
	double TX[256]={0};
	unsigned char ScaledTX[256]={0};
	
	int width  = atoi(argv[3]);
	int height = atoi(argv[4]);
    
    unsigned char *Img  = new unsigned char[width*height*bpp];
    unsigned char *Out  = new unsigned char[width*height*bpp];
    unsigned char *Buff = new unsigned char[width*height*bpp];
    
    unsigned char *temp = NULL;
    unsigned char red , green , blue , cyan , magenta , yellow;
    int val = 0;
    
    fptr1 = fopen(argv[1],"rb");
    
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
	
	//Transfer function
	
	TransferMathFunction(logvalues,TX,ScaledTX);
	
	//CMYK
	
	for(int i=0;i<height ;i++)
	{
		for(int j=0; j<width ; j++)
		{
			red = *(Img + ((i*width + j)*bpp) + 0 );
			green = *(Img + ((i*width + j)*bpp) + 1 );
			blue = *(Img + ((i*width + j)*bpp) + 2);
						
			cyan    = 255 - red;
			magenta = 255 - green;
            yellow  = 255 - blue;

		    val = cyan * 1.3;
		    if(val > 255)
			val = 255;

		    *(Buff + ((i*width + j)*bpp) + 0) = ScaledTX[val];
		    *(Buff + ((i*width + j)*bpp) + 1) = ScaledTX[(int)(magenta * 0.65)];
			*(Buff + ((i*width + j)*bpp) + 2) = ScaledTX[(int) (yellow * 0.75)];	    
			 	  	   	   
		}
    }	
    
    for(int i=0;i<height;i++)
	{
		for(int j=0;j<width;j++)
		{
    
               temp                            = getpixel(Buff,i,(width-j-1),width,height,bpp);
			   *(Out+ ((i*width + j)*bpp) + 0) = *(temp+0);
			   *(Out+((i*width +j)*bpp)+ 1)    = *(temp+1);
			   *(Out+((i*width +j)*bpp)+2)     = *(temp+2);	
         }
   }	 
  	
	//write
	
	fptr1 =fopen(argv[2],"wb");
	if(!(fptr1 == NULL))
    { 
		fwrite(Out,sizeof(unsigned char),width*height*bpp,fptr1);
	    fclose(fptr1);
	}
	
	delete[] Img;
	delete[] Out;
	
			
	return 0;
}
	
	
	
	
	
