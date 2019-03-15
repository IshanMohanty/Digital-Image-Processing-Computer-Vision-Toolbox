#include <iostream>
#include <fstream>
#include <stdlib.h>	

using namespace std;

int main(int argc, char *argv[])
{   
	//File pointer and Image Data
	FILE* fptr2;
	
	int width  = atoi(argv[5]);
	int height = atoi(argv[6]);   
    int bpp    = 3;

	unsigned char Img2[height][width][bpp];

    unsigned char Temp4[height][width];
    unsigned char Temp5[height][width];
    unsigned char Temp6[height][width];
  
    unsigned char red , green , blue , cyan , magenta , yellow ;
    
    // Check for proper syntax
	if (argc < 5){
		cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
		cout << argv[0]<<"input_image.raw output_image1.raw output_image2.raw output_image3.raw width height" << endl;
		return 0;
	}
    
    //Opening file
	fptr2 = fopen(argv[1],"rb");
    
	if(!(fptr2 == NULL))
	{      
        fread(Img2,sizeof(unsigned char),width*height*bpp,fptr2); //Reading RAW image into 3D image data matrix
	    fclose(fptr2);
		cout<<"Image can be read"<<endl;
		
	}
	else
	{
		cout<<"Image cannot be read"<<endl;
	}

	//CMYK Color space operations
	
	for(int i=0;i<height;i=i+1)
	{
		for(int j=0;j<width;j=j+1)
		{
			red   = Img2[i][j][0];
		    green = Img2[i][j][1];
		    blue  = Img2[i][j][2];
            cyan  = 255-red;
            magenta = 255 - green;
            yellow = 255 - blue;
            Temp4[i][j]=cyan;
            Temp5[i][j]=magenta;
            Temp6[i][j]=yellow;            
		}
	}   	
	
	//Write image into the file - Cyan grayscale image
	
	fptr2 =fopen(argv[2],"wb");
	if(!(fptr2 == NULL))
    { 
		fwrite(Temp4,sizeof(unsigned char),width*height,fptr2);
	    fclose(fptr2);
	}	
	
	//Write image into the file - Magenta grayscale image
	
	fptr2 =fopen(argv[3],"wb");
	if(!(fptr2 == NULL))
    { 
		fwrite(Temp5,sizeof(unsigned char),width*height,fptr2);
	    fclose(fptr2);
	}	
	
	//Write image into the file - Yellow grayscale image
	
	fptr2 =fopen(argv[4],"wb");
	if(!(fptr2 == NULL))
    { 
		fwrite(Temp6,sizeof(unsigned char),width*height,fptr2);
	    fclose(fptr2);
	}	
	    	    
	return 0;
}
