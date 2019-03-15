#include <iostream>
#include <fstream>
#include <stdlib.h>

using namespace std;

unsigned char * pixel(unsigned char* Img , int i , int j , int width , int height , int bpp);

unsigned char * pixel(unsigned char* Img , int i , int j , int width , int height , int bpp)
{
	return (Img+((i*width +j)*bpp));
}

void resize(unsigned char * Img , unsigned char * Out , int width , int height , int newwidth , int newheight, int bpp); //declaration

void resize(unsigned char* Img, unsigned char * Out , int width , int height , int newwidth, int newheight, int bpp)
{
	float ScaledWidthRatio  = width/(float)newwidth;
	float ScaledHeightRatio = height/(float)newheight;
        
        for(int i =0; i< newheight ; i++)
        {
           for(int j=0 ; j < newwidth ; j++)
           {
               float mappedheight       = i*ScaledHeightRatio;  //rf
               float mappedwidth        = j*ScaledWidthRatio;   //cf
               int   OriginalPosHeight  = mappedheight;         //ro
               int   OriginalPosWidth   = mappedwidth;          //co
               float deltaheight          = mappedheight - OriginalPosHeight; //delta r
	           float deltawidth           = mappedwidth - OriginalPosWidth;   //delta c
	       
	            unsigned char * temp1 = pixel(Img,OriginalPosHeight , OriginalPosWidth , width , height , bpp);
	            unsigned char * temp2 = pixel(Img,OriginalPosHeight+1 , OriginalPosWidth , width , height , bpp);
	            unsigned char * temp3 = pixel(Img,OriginalPosHeight , OriginalPosWidth+1 , width , height , bpp);
	            unsigned char * temp4 = pixel(Img,OriginalPosHeight+1 , OriginalPosWidth+1 , width , height , bpp);
	            
                 
               *(Out + ((i*newwidth + j)*bpp) + 0) = *(temp1+0)*(1-deltaheight)*(1-deltawidth) \
                                                 + *(temp2+0)*(deltaheight)*(1-deltawidth) \
                                                 + *(temp3+0)*(1-deltaheight)*(deltawidth) \
                                                 + *(temp4+0)*(deltaheight)*(deltawidth);
                                                 
               *(Out + ((i*newwidth + j)*bpp) + 1) = *(temp1+1)*(1-deltaheight)*(1-deltawidth) \
                                                 + *(temp2+1)*(deltaheight)*(1-deltawidth) \
                                                 + *(temp3+1)*(1-deltaheight)*(deltawidth) \
                                                 + *(temp4+1)*(deltaheight)*(deltawidth);
                                                 
               *(Out + ((i*newwidth + j)*bpp) + 2) = *(temp1+2)*(1-deltaheight)*(1-deltawidth) \
                                                 + *(temp2+2)*(deltaheight)*(1-deltawidth) \
                                                 + *(temp3+2)*(1-deltaheight)*(deltawidth) \
                                                 + *(temp4+2)*(deltaheight)*(deltawidth);

           }
        }
}


int main(int argc, char *argv[])
{
    FILE* fptr1;
    int width   = atoi(argv[3]);
	int height  = atoi(argv[4]);   
    int bpp     = 3;
    
    int newwidth  = atoi(argv[5]);
    int newheight = atoi(argv[6]);   
   
    
    unsigned char *Img   = new unsigned char[width*height*bpp];
    unsigned char *Out   = new unsigned char[newwidth*newheight*bpp];
    
    // Check for proper syntax
	if (argc < 5){
		cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
		cout << argv[0]<<"input_image.raw output_image.raw width height resizedwidth resizedheight" << endl;
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
	
	resize(Img,Out,width,height,newwidth,newheight,bpp);	
	
	fptr1 =fopen(argv[2],"wb");
	if(!(fptr1 == NULL))
    { 
		fwrite(Out,sizeof(unsigned char),newwidth*newheight*bpp,fptr1);
	    fclose(fptr1);
	}
	
	delete[] Img;
	delete[] Out;
	
	
	
   return 0;
}
