#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "counting_game.h"


using namespace std;

int main(int argc, char* argv[])
{
	// Check for proper syntax

	if (argc < 3)
	{
		cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
		cout << argv[0]<<"input_image width height" << endl;
		return 0;
	}
	
	FILE* fptr1;
	const int bpp = 1;
	int width  = atoi(argv[2]);
	int height = atoi(argv[3]);
	
	
	unsigned char* Img      = new unsigned char[width*height*bpp];    
	unsigned char* LabelImg = new unsigned char[width*height*bpp];

	memset(LabelImg,255,width*height);
	
	int count = 0;
	
		
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
	
	
	//Thresholding of input image
	for(int imgrow =0; imgrow < height; imgrow++)
	{
		for(int imgcol=0 ; imgcol < width ; imgcol++)
		{ 				
			int pix_value = *(Img + (imgrow*width + imgcol)) ;
			
			if( *(Img + (imgrow*width + imgcol) ) > 127 )
			{
				  *(Img + (imgrow*width + imgcol))  = 255;
		    }
		    else
		    {
				  *(Img + (imgrow*width + imgcol))   = 0;
		    }
        }
     }
    
    //Count No of Jigsaw's
    
    count = counting(Img,LabelImg,width,height);
    
    cout <<"Count of Jigsaw's in the board : " << count<<endl;
   
	return 0;
}
