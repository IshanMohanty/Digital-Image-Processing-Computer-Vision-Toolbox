#include <iostream>
#include <fstream>
#include <stdlib.h>

#include "MBVQ.h"

using namespace std;

int main(int argc, char* argv[])
{
	// Check for proper syntax

	if (argc < 5)
	{
		cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
		cout << argv[0]<<"input_image.raw Output_image.raw  width height" << endl;
		return 0;
	}
	
	FILE* fptr1;
	const int bpp = 3;
	int width  = atoi(argv[3]);
	int height = atoi(argv[4]);
	
	unsigned char* Img     = new unsigned char[width*height*bpp];   
	unsigned char* Out     = new unsigned char[width*height*bpp];  
	unsigned char* Buffer  = new unsigned char[width*height*bpp];  
	
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
	
	MBVQ(Img,width,height,bpp,Buffer,Out);
	
	//write
	
	fptr1 =fopen(argv[2],"wb");
	if(!(fptr1 == NULL))
    { 
		fwrite(Out,sizeof(unsigned char),width*height*bpp,fptr1);
	    fclose(fptr1);
	}
      
    delete[] Img;
    delete[] Out;
    delete[] Buffer;
    
    return 0;

}
	
