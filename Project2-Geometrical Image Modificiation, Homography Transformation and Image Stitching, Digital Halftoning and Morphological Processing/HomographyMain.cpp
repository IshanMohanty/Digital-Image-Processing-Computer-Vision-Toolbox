#include <iostream>
#include <fstream>
#include "HomographyStitching.h"
#include <stdlib.h>



using namespace std;

int main(int argc, char* argv[])
{
	// Check for proper syntax

	if (argc < 7)
	{
		cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
		cout << argv[0]<<"left.raw Middle.raw Right.raw output_image.raw  width height" << endl;
		return 0;
	}
	
	FILE* fptr1;
	const int bpp = 3;
	int width  = atoi(argv[5]);
	int height = atoi(argv[6]);
	int height_output = 2000;
	int width_output  = 2000;
	
	unsigned char* middle_Img = new unsigned char[width*height*bpp];    
	unsigned char* left_Img = new unsigned char[width*height*bpp];
	unsigned char* right_Img = new unsigned char[width*height*bpp];
	unsigned char* Buffer     = new unsigned char[width_output*height_output*bpp];
	
	//Openfile and Read
	
	fptr1 = fopen(argv[1],"rb");

	if(!(fptr1 == NULL))
	{    
 
		//Reading RAW image into 3D image data matrix

		fread(left_Img,sizeof(unsigned char),width*height*bpp,fptr1); 
		fclose(fptr1);
		cout<<"left Image can be read"<<endl;	
        cout<<"Successful!"<<endl;	
	}
	else
	{
		cout<<"Image cannot be read"<<endl;
	}
		
	//Openfile and Read
	
	fptr1 = fopen(argv[2],"rb");

	if(!(fptr1 == NULL))
	{    
 
		//Reading RAW image into 3D image data matrix

		fread(middle_Img,sizeof(unsigned char),width*height*bpp,fptr1); 
		fclose(fptr1);
		cout<<"Middle Image can be read"<<endl;	
        cout<<"Successful!"<<endl;	
	}
	else
	{
		cout<<"Image cannot be read"<<endl;
	}
	
	//Openfile and Read
	
	fptr1 = fopen(argv[3],"rb");

	if(!(fptr1 == NULL))
	{    
 
		//Reading RAW image into 3D image data matrix

		fread(right_Img,sizeof(unsigned char),width*height*bpp,fptr1); 
		fclose(fptr1);
		cout<<"Image can be read"<<endl;	
        cout<<"Successful!"<<endl;	
	}
	else
	{
		cout<<"Image cannot be read"<<endl;
	}
    
    HomographyStitching(middle_Img,left_Img,right_Img,Buffer,height,width,height_output,width_output,bpp);
    
    //write
	
	fptr1 =fopen(argv[4],"wb");
	if(!(fptr1 == NULL))
    { 
		fwrite(Buffer,sizeof(unsigned char),width_output*height_output*bpp,fptr1);
	    fclose(fptr1);
	}
      
	return 0;
}
