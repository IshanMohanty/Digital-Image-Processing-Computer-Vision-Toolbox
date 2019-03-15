#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "LoG.h"

using namespace std;

int main(int argc, char *argv[])
{
	// Check for proper syntax
	if (argc < 11){
		cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
		cout<<argv[0]<<"orig.raw  noisy.raw   Normal_Img1.raw   Normal_Img2.raw    Ternary_Img1.raw    Ternary_Img2.raw   BestEdgeMap_Img1.raw    BestEdgeMap_Img2.raw   width   height" << endl;
		return 0;
	}

	//~ int width  = atoi(argv[9]);
	//~ int height = atoi(argv[10]);
	
	int width = 321;
	int height = 481;
	
	cout<<width<<height<<endl;

    FILE* fptr;
    unsigned char* Img1    = new unsigned char[width*height*3];
    unsigned char* Img2    = new unsigned char[width*height*3]; 
    unsigned char* Out_Img1 = new unsigned char[width*height];
    unsigned char* Out_Img2 = new unsigned char[width*height];
    
    unsigned char* Buffer_Img1 = new unsigned char[width*height];
    unsigned char* Buffer_Img2 = new unsigned char[width*height]; 
    
    unsigned char* Normalized_LoG_Buffer_Img1 = new unsigned char[width*height];
    unsigned char* Normalized_LoG_Buffer_Img2 = new unsigned char[width*height];
    
    int* LoG_Buffer_Img1 = new int[width*height];
    int* LoG_Buffer_Img2 = new int[width*height];
    
    int* ternary_Buffer_Img1 = new int[width*height];
    int* ternary_Buffer_Img2 = new int[width*height];
    
    unsigned char* tri_gray_buffer_Img1 = new unsigned char[width*height];
    unsigned char* tri_gray_buffer_Img2 = new unsigned char[width*height];
    
    memset(Out_Img1,0,width*height);
    memset(Out_Img2,0,width*height);
    
    //read Img1
    fptr = fopen(argv[1],"rb");
    
	if(!(fptr == NULL))
	{      
        fread(Img1,sizeof(unsigned char),width*height*3,fptr); //Reading RAW image into 3D image data matrix
	    fclose(fptr);
		cout<<"Image can be read"<<endl;		
	}
	else
	{
		cout<<"Image cannot be read"<<endl;
	}	
	
	//read Img2
	fptr = fopen(argv[2],"rb");
    cout << argv[2] << endl;
	if(!(fptr == NULL))
	{      
        fread(Img2,sizeof(unsigned char),width*height*3,fptr); //Reading RAW image into 3D image data matrix
	    fclose(fptr);
		cout<<"Image can be read"<<endl;		
	}
	else
	{
		cout<<"Image cannot be read"<<endl;
	}	
	
	//convert RGB to Gray Scale
	
	convert_RGB_GRAY(Img1,width,height,3,Buffer_Img1);
	convert_RGB_GRAY(Img2,width,height,3,Buffer_Img2);
	
	//Apply Gaussian filter to denoise
	
	gaussian_noise_removal(Buffer_Img2,width,height);
	
	//Apply LoG Mask
	
	apply_LoG(Buffer_Img1,LoG_Buffer_Img1,width,height,Normalized_LoG_Buffer_Img1);
	apply_LoG(Buffer_Img2,LoG_Buffer_Img2,width,height,Normalized_LoG_Buffer_Img2);
	
	//Write Out Normalized LoG Buffer Img1
	
	fptr =fopen(argv[3],"wb");
	if(!(fptr == NULL))
    { 
		fwrite(Normalized_LoG_Buffer_Img1,sizeof(unsigned char),width*height,fptr);
	    fclose(fptr);
	}
	
	//Write Out Normalized LoG Buffer Img2
	
	fptr =fopen(argv[4],"wb");
	if(!(fptr == NULL))
    { 
		fwrite(Normalized_LoG_Buffer_Img2,sizeof(unsigned char),width*height,fptr);
	    fclose(fptr);
	}
	
	//Compute Histogram and check knee threshold
	
	int knee_threshold_Img1 = histogram(LoG_Buffer_Img1,width,height);
	cout<<endl;
	cout<<endl;
	cout<<"knee img1  " << knee_threshold_Img1 << endl;
	cout<<endl;
	int knee_threshold_Img2 = histogram(LoG_Buffer_Img2,width,height);
	
	//~ cout<<"knee img1  " << knee_threshold_Img1 << endl;
	cout<<"knee img2  " << knee_threshold_Img2 << endl;
	
	//Threshold the LoG Output and display the ternary gray level image
	Threshold_LoG_Buffer(knee_threshold_Img1,LoG_Buffer_Img1,width,height, ternary_Buffer_Img1,tri_gray_buffer_Img1);
	
	Threshold_LoG_Buffer(knee_threshold_Img2,LoG_Buffer_Img2,width,height, ternary_Buffer_Img2,tri_gray_buffer_Img2);
	
    //Write Ternary Gray level Image for Img1
	
	fptr =fopen(argv[5],"wb");
	if(!(fptr == NULL))
    { 
		fwrite(tri_gray_buffer_Img1,sizeof(unsigned char),width*height,fptr);
	    fclose(fptr);
	}
	
	//Write Ternary Gray level Image for Img2
	
	fptr =fopen(argv[6],"wb");
	if(!(fptr == NULL))
    { 
		fwrite(tri_gray_buffer_Img1,sizeof(unsigned char),width*height,fptr);
	    fclose(fptr);
	} 
		
	//Zero crossing algorithm and output best edge map
	
	zero_crossing_algo(ternary_Buffer_Img1,Out_Img1,width,height);
	zero_crossing_algo(ternary_Buffer_Img2,Out_Img2,width,height);
	
	//Write out best edge map for Image 1
	
	fptr =fopen(argv[7],"wb");
	if(!(fptr == NULL))
    { 
		fwrite(Out_Img1,sizeof(unsigned char),width*height,fptr);
	    fclose(fptr);
	}
	
	//Write out best edge map for Image 2
	
	fptr =fopen(argv[8],"wb");
	if(!(fptr == NULL))
    { 
		fwrite(Out_Img2,sizeof(unsigned char),width*height,fptr);
	    fclose(fptr);
	}
	
    //Free Memory
    
	delete[] Img1;
	delete[] Img2;
	delete[] Out_Img1;
	delete[] Out_Img2;
    delete[] Buffer_Img1;
    delete[] Buffer_Img2;
    delete[] Normalized_LoG_Buffer_Img1;
    delete[] Normalized_LoG_Buffer_Img2;
    delete[] LoG_Buffer_Img1;
    delete[] LoG_Buffer_Img2;
    delete[] ternary_Buffer_Img1;
    delete[] ternary_Buffer_Img2;
    delete[] tri_gray_buffer_Img1;
    delete[] tri_gray_buffer_Img2;
 
   return 0;

}
