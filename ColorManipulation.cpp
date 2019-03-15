#include <iostream>
#include <fstream>
#include <stdlib.h>	

using namespace std;

int main(int argc, char *argv[])
{   
	//File pointer and Image Data
	FILE* fptr1;
	
	int width  = atoi(argv[5]);
	int height = atoi(argv[6]);   
    int bpp    = 3;
	
	unsigned char Img1[height][width][bpp];
	
	unsigned char Temp1[height][width];
    unsigned char Temp2[height][width];
    unsigned char Temp3[height][width];
  
    unsigned char red , green , blue , gray, min , max ; 
    
    // Check for proper syntax
	if (argc < 5)
	{
		cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
		cout << argv[0]<<"input_image.raw output_image1.raw output_image2.raw output_image3.raw width height" << endl;
		return 0;
	}
		
	//Opening file
	fptr1 = fopen(argv[1],"rb");
    
	if(!(fptr1 == NULL))
	{     
        fread(Img1,sizeof(unsigned char),width*height*bpp,fptr1); //Reading RAW image into 3D image data matrix
	    fclose(fptr1);
		cout<<"Image can be read"<<endl;
		
	}
	else
	{
		cout<<"Image cannot be read"<<endl;
	}
	
	// Luminosity method
	
	for(int i=0;i<height;i=i+1)
	{
		for(int j=0;j<width;j=j+1)
		{
			red   = Img1[i][j][0];
			green = Img1[i][j][1];
			blue  = Img1[i][j][2];
            gray  = (0.21*red + 0.72*green + 0.07*blue);
            Temp1[i][j]=gray;            
		}
	}   			
	
	//Average method
	
	for(int i=0;i<height;i=i+1)
	{
		for(int j=0;j<width;j=j+1)
		{
			red   = Img1[i][j][0];
			green = Img1[i][j][1];
			blue  = Img1[i][j][2];
            gray  = (red+green+blue)/3;
            Temp2[i][j]=gray;
		}
	}   	
	
	//Min Max Method
	
	for(int i=0;i<height;i=i+1)
	{
		for(int j=0;j<width;j=j+1)
		{
			red   = Img1[i][j][0];
			green = Img1[i][j][1];
			blue  = Img1[i][j][2];
			//Maximum of 3 colors
			
			if( red>=green && red>=blue)
			{
				max=red;
			}
			else
			{
				if(green>=blue)
				{
					max=green;
			    }
			    else
			    {
					max=blue;
				}
			}
			
			//Minimum of 3 colors
			
			if( red<=green && red<=blue)
			{
				min=red;
			}
			else
			{
				if(green<=blue)
				{
					min=green;
			    }
			    else
			    {
					min=blue;
				}
			}		
			
            gray=(max+min)/2;
            
            Temp3[i][j]=gray;
		}
	}   	
		
	
	//Write image into the file - luminosity
	
	fptr1 =fopen(argv[2],"wb");
	if(!(fptr1 == NULL))
    { 
		fwrite(Temp1,sizeof(unsigned char),width*height,fptr1);
	    fclose(fptr1);
	}
    
	
	//Write image into the file - Average
	
	fptr1 =fopen(argv[3],"wb");
	if(!(fptr1 == NULL))
    { 
		fwrite(Temp2,sizeof(unsigned char),width*height,fptr1);
	    fclose(fptr1);
	}
	
	//Write image into the file - Min & Max
	
	fptr1 =fopen(argv[4],"wb");
	if(!(fptr1 == NULL))
    { 
		fwrite(Temp3,sizeof(unsigned char),width*height,fptr1);
	    fclose(fptr1);
	}
	
	cout<<"Successfully Done !"<<endl;
	
    return 0;
    
}
	
