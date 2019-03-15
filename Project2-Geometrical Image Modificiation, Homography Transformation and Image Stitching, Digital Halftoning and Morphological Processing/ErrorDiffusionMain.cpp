#include <iostream>
#include <fstream>

#include "ErrorDiffusionFunc.h"

using namespace std;

int main(int argc, char* argv[])
{
	// Check for proper syntax

	if (argc < 7)
	{
		cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
		cout << argv[0]<<"input_image.raw FloydStein.raw JJN.raw Stucki.raw  width height" << endl;
		return 0;
	}
	
	FILE* fptr1;
	const int bpp = 1;
	int width  = atoi(argv[5]);
	int height = atoi(argv[6]);
	
	unsigned char* Img              = new unsigned char[width*height*bpp];    
	unsigned char* BufferFloyd      = new unsigned char[width*height*bpp];
	unsigned char* BufferJJN        = new unsigned char[width*height*bpp];
	unsigned char* BufferStucki     = new unsigned char[width*height*bpp];
	unsigned char* OutputFloydStein = new unsigned char[width*height*bpp]; 
	unsigned char* OutputJJN        = new unsigned char[width*height*bpp]; 
	unsigned char* OutputStucki     = new unsigned char[width*height*bpp]; 
		
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
    
    
    //Floyd-Steinberg
    
    FloydSteinbergError(Img,width,height,bpp,BufferFloyd,OutputFloydStein);
    
    
    //write
	
	fptr1 =fopen(argv[2],"wb");
	if(!(fptr1 == NULL))
    { 
		fwrite(OutputFloydStein,sizeof(unsigned char),width*height*bpp,fptr1);
	    fclose(fptr1);
	}
	
	
	// Jarvis , Judice , Ninke ( JJN)
	
	JJN(Img,width,height,bpp,BufferJJN,OutputJJN);
	
	//write
	
	fptr1 =fopen(argv[3],"wb");
	if(!(fptr1 == NULL))
    { 
		fwrite(OutputJJN,sizeof(unsigned char),width*height*bpp,fptr1);
	    fclose(fptr1);
	}
	
	//Stucki
	
	Stucki(Img,width,height,bpp,BufferStucki,OutputStucki);
	
	//write
	
	fptr1 =fopen(argv[4],"wb");
	if(!(fptr1 == NULL))
    { 
		fwrite(OutputStucki,sizeof(unsigned char),width*height*bpp,fptr1);
	    fclose(fptr1);
	}
      
    delete[] Img;
	delete[] BufferFloyd;
	delete[] BufferJJN;      
	delete[] BufferStucki;     
	delete[] OutputFloydStein; 
	delete[] OutputJJN;     
	delete[] OutputStucki;    
	
	return 0;
}
