#include <iostream>
#include <fstream>

#include "four_level_dither_func.h"

using namespace std;

int main(int argc, char* argv[])
{
	// Check for proper syntax

	if (argc < 6)
	{
		cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
		cout << argv[0]<<"input_image.raw Dither.raw width height Dithermatrix_size" << endl;
		return 0;
	}
	
	FILE* fptr1;
	const int bpp    = 1;
	int width  = atoi(argv[3]);
	int height = atoi(argv[4]);
	int N      = atoi(argv[5]);
	
	unsigned char* Img = new unsigned char[width*height*bpp];    
	unsigned char* Dither = new unsigned char[width*height*bpp];
		
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
	
	// Dither Matrix Method
	
	FourlevelDitherMatrixMethod(Img,width,height,bpp,Dither,N);
	
	//Write for Dither Matrix Method
	
	fptr1 =fopen(argv[2],"wb");
	if(!(fptr1 == NULL))
	{ 
		fwrite(Dither,sizeof(unsigned char),width*height*bpp,fptr1);
		fclose(fptr1);
	}
	
	delete[] Img;
	delete[] Dither;	
		
	return 0;
}
