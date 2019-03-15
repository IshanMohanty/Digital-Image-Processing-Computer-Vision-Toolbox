#include <iostream>
#include <fstream>
#include <stdlib.h>				

using namespace std;

void histogram(unsigned char* Img , int width , int height , int bpp, int* PixelCountRed, int* PixelCountGreen , int* PixelCountBlue);

void cdfcalc(unsigned char* Img , unsigned char* Out, int width , int height , int bpp, float* ProbRed , float* ProbGreen , float* ProbBlue, int* PixelCountRed, int* PixelCountGreen , int* PixelCountBlue);

void histogram(unsigned char* Img , int width , int height , int bpp, int *PixelCountRed, int* PixelCountGreen , int* PixelCountBlue)
{
	
	for(int i=0 ; i< width*height ; i++)
	{
		PixelCountRed[*(Img + (i*bpp) + 0)]++;
		PixelCountGreen[*(Img + (i*bpp) + 1)]++;
		PixelCountBlue[*(Img + (i*bpp) + 2)]++;
	}	
		
}

void cdfcalc(unsigned char* Img , unsigned char* Out, int width , int height , int bpp , float* ProbRed , float* ProbGreen , float* ProbBlue , int* PixelCountRed, int* PixelCountGreen , int* PixelCountBlue) 
{
	for(int i=0 ; i< 256 ; i++)
	{
        ProbRed[i]   = (float)(PixelCountRed[i])/(float)(width*height);
        ProbGreen[i] = (float)(PixelCountGreen[i])/(float)(width*height);
        ProbBlue[i]  = (float)(PixelCountBlue[i])/(float)(width*height);
        
    }
    
    float CdfRed[256];
    float CdfGreen[256];
    float CdfBlue[256];
    
    int ScaledCdfRed[256];
    int ScaledCdfGreen[256];
    int ScaledCdfBlue[256];
    
    CdfRed[0]=ProbRed[0];
    CdfGreen[0]=ProbGreen[0];
    CdfBlue[0]=ProbBlue[0];
    
    for(int i=1 ; i<256 ; i++)
	{
        CdfRed[i]     = CdfRed[i-1] + ProbRed[i];
        CdfGreen[i]   = CdfGreen[i-1] + ProbGreen[i];
        CdfBlue[i]    = CdfBlue[i-1] + ProbBlue[i];
        
        
    }
    
    for(int j=0; j<256 ; j++)
    {
		ScaledCdfRed[j]   = CdfRed[j]*255;
		ScaledCdfGreen[j]  = CdfGreen[j]*255;
		ScaledCdfBlue[j] = CdfBlue[j]*255;
		
		
	}
	
    for(int i=0; i<height ; i++)
    {
		for(int j=0;j<width; j++)
		{
			*(Out + ((i*width + j)*bpp) + 0) = ScaledCdfRed[*(Img + ((i*width + j)*bpp) + 0)];
			*(Out + ((i*width + j)*bpp) + 1) = ScaledCdfGreen[*(Img + ((i*width + j)*bpp) + 1)];
			*(Out + ((i*width + j)*bpp) + 2) = ScaledCdfBlue[*(Img + ((i*width + j)*bpp) + 2)];
		}
	}	
}

int main(int argc, char *argv[])
{
	 // Check for proper syntax
	if (argc < 5){
		cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
		cout << argv[0]<<" input_image.raw output_image.raw width height" << endl;
		return 0;
	}
	
    FILE* fptr1;
    int width  = atoi(argv[3]);
	int height = atoi(argv[4]);   
    int bpp    = 3;
    
    
    unsigned char *Img   = new unsigned char[width*height*bpp];
    unsigned char *Out   = new unsigned char[width*height*bpp];
    
    int  PixelCountRed[256]={0}; // initiliaze all elements of array to zero
    int  PixelCountGreen[256]={0};
    int  PixelCountBlue[256]={0};
    float ProbRed[256];
    float ProbGreen[256];
    float ProbBlue[256];
     
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
	
	//Histogram equalization
	
	histogram(Img,width,height,bpp,PixelCountRed,PixelCountGreen,PixelCountBlue);
	cdfcalc(Img,Out,width,height,bpp,ProbRed,ProbGreen,ProbBlue,PixelCountRed,PixelCountGreen,PixelCountBlue);
	
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
