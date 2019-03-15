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

	if (argc < 5 )
	{
		cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
		cout << argv[0]<<"input_image.raw thin.raw width height" << endl;
		return 0;
	}
	
	FILE* fptr1;
	const int bpp = 1;
	int width  = atoi(argv[3]);
	int height = atoi(argv[4]);
	int count = 0;
	
	unsigned char* Img     = new unsigned char[width*height*bpp];    
	unsigned char* MBuffer = new unsigned char[width*height*bpp];
	unsigned char* Out     = new unsigned char[width*height*bpp]; 
		
	memset(Img,255,width*height);
	memset(MBuffer,255,width*height);
	memset(Out,255,width*height);
	
	
		
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
			
			if( *(Img + (imgrow*width + imgcol) ) >= 104 )
			{
				  *(Img + (imgrow*width + imgcol))  = 255;
		    }
		    else
		    {
				  *(Img + (imgrow*width + imgcol))   = 0;
		    }
        }
     }
	 

     
    // Thin
     
    STK(Img,MBuffer,Out,width,height,2,2000,0,255);
      
    fptr1 =fopen(argv[2],"wb");
	if(!(fptr1 == NULL))
    { 
		fwrite(Out,sizeof(unsigned char),width*height*bpp,fptr1);
	    fclose(fptr1);
	}
    
	return 0;
}
