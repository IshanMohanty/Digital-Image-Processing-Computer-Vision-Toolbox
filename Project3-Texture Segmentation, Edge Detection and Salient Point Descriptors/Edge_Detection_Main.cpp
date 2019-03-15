#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <stdlib.h>
#include "Edge_Detection.h"

using namespace std;

int main(int argc, char *argv[])
{
	// Check for proper syntax
	if (argc < 7){
		cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
		cout << argv[0]<<"  input_image_original.raw   input_image_noisy.raw   output_image_orig.raw   output_image_noisy.raw   width   height" << endl;
		return 0;
	}

	int width  = atoi(argv[5]);
	int height = atoi(argv[6]);
	
	cout<<width<<" "<<height<<endl;

    FILE* fptr;
    unsigned char* Img1    = new unsigned char[width*height*3];
    unsigned char* Img2    = new unsigned char[width*height*3]; 
    unsigned char* Out_Img1 = new unsigned char[width*height];
    unsigned char* Out_Img2 = new unsigned char[width*height];
    unsigned char* Buffer_Img1 = new unsigned char[width*height];
    unsigned char* Buffer_Img2 = new unsigned char[width*height]; 
    double* Gradient_Buffer_Img1 = new double[width*height];
    double* Gradient_Buffer_Img2 = new double[width*height];
    
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
	
	//Sobel Operator
	
	double maximum_gradient_value_Img1 = sobel_operator(Buffer_Img1,width,height,1, Gradient_Buffer_Img1);

	double maximum_gradient_value_Img2 = sobel_operator(Buffer_Img2,width,height,1,Gradient_Buffer_Img2);

	
	//Calculate Threshold
	
	double final_threshold_Img1 =   ( (100 - SOBEL_THRESHOLD_1)* (maximum_gradient_value_Img1) )/100;
	cout<<final_threshold_Img1<<endl;

	double final_threshold_Img2 =   ( (100 - SOBEL_THRESHOLD_2)*(maximum_gradient_value_Img2) )/100;
	cout<< final_threshold_Img2 <<endl;

	//Threshold Image
	
	sobel_threshold(final_threshold_Img1,Out_Img1,Gradient_Buffer_Img1,width,height);
	
	
	sobel_threshold(final_threshold_Img2,Out_Img2,Gradient_Buffer_Img2,width,height);

	
   //write original image output after sobel operation

	fptr =fopen(argv[3],"wb");
	if(!(fptr == NULL))
    { 
		fwrite(Out_Img1,sizeof(unsigned char),width*height,fptr);
	    fclose(fptr);
	}
	
	
	//~ //Write noisy image output after sobel operation
	
	fptr =fopen(argv[4],"wb");
	if(!(fptr == NULL))
    { 
		fwrite(Out_Img2,sizeof(unsigned char),width*height,fptr);
	    fclose(fptr);
	}
	
	delete[] Img1;
	delete[] Img2;
	delete[] Out_Img1;
	delete[] Out_Img2;
    delete[] Buffer_Img1;
    delete[] Buffer_Img2;
    delete[] Gradient_Buffer_Img1;
    delete[] Gradient_Buffer_Img2;
 
   return 0;

}
