#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <vector>
#include "STK.h"

using namespace std;

int main(int argc, char* argv[])
{
	// Check for proper syntax

	if (argc < 5)
	{
		cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
		cout << argv[0]<<"input_image.raw shrink.raw width height" << endl;
		return 0;
	}
	
	FILE* fptr1;
	const int bpp = 1;
	int width  = atoi(argv[3]);
	int height = atoi(argv[4]);
	int count = 0;
	
	unsigned char* Img     = new unsigned char[width*height*bpp];    
	unsigned char* MBuffer = new unsigned char[width*height*bpp];

	unsigned char* Out    = new unsigned char[width*height*bpp]; 
	
	
	unsigned char* LabelImg = new unsigned char[width*height*bpp];
		
	memset(Img,0,width*height);
	memset(MBuffer,0,width*height);
	memset(Out,0,width*height);
	
	memset(LabelImg,255,width*height);
	
		
	//Openfile and Read
	
	fptr1 = fopen(argv[1],"rb");

	if(!(fptr1 == NULL))
	{    
		//Reading RAW image into 3D image data matrix

		fread(Img,sizeof(unsigned char),width*height*bpp,fptr1); 
		fclose(fptr1);
		cout<<"Image can be read"<<endl;	
        cout<<"Successful!"<<endl;	
	}
	else
	{
		cout<<"Image cannot be read"<<endl;
	}
	

	for(int imgrow =0; imgrow < height; imgrow++)
	{
		for(int imgcol=0 ; imgcol < width ; imgcol++)
		{ 				
			int pix_value = *(Img + (imgrow*width + imgcol)) ;
		
			if( *(Img + (imgrow*width + imgcol) ) >= 127 )
			{
				  *(Img + (imgrow*width + imgcol))  = 255;
		    }
		    else
		    {
				  *(Img + (imgrow*width + imgcol))   = 0;
		    }
        }
     }
		 
    
  
    
    //shrink
    
    STK(Img,MBuffer,Out,width,height,1,100,255,0);
    count = counting(Img,LabelImg,width,height);
    
    int counter =0;
    
    for(int imgrow =0; imgrow < height; imgrow++)
	{
		for(int imgcol=0 ; imgcol < width ; imgcol++)
		{ 		
			if( *(Out + (imgrow*width + imgcol) ) == 255 )
			{
				counter=counter+1;
			}	
        }
    }
    
    cout<<"Count of stars after shrinking :" << counter <<endl;
   
    //write
	
	fptr1 =fopen(argv[2],"wb");
	if(!(fptr1 == NULL))
    { 
		fwrite(Out,sizeof(unsigned char),width*height*bpp,fptr1);
	    fclose(fptr1);
	}
     
     
	
     
	return 0;
}
