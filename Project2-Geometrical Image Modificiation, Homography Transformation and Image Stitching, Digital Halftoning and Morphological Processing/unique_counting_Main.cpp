#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <algorithm>
#include "unique_counting.h"

using namespace std;

int main(int argc, char* argv[])
{
	// Check for proper syntax

	if (argc < 4)
	{
		cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
		cout << argv[0]<<" input_image.raw width height" << endl;
		return 0;
	}
	
	FILE* fptr1;
	const int bpp = 1;
	int width  = atoi(argv[2]);
	int height = atoi(argv[3]);
	int total_jigsaws = 16;
	vector <int> No_Iterations;
	vector<int>::iterator it;
	
	unsigned char* Img     = new unsigned char[width*height*bpp];    
	unsigned char* CmpBuffer = new unsigned char[93*93];
	unsigned char* OrgBuffer = new unsigned char[93*93];
	unsigned char* Out = new unsigned char[93*93];

	memset(Img,BG,width*height);
	
	int total_matches = 0;
		
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
		
			if( *(Img + (imgrow*width + imgcol) ) > 128 )
			{
				  *(Img + (imgrow*width + imgcol))  = BG;
		    }
		    else
		    {
				  *(Img + (imgrow*width + imgcol))   = FG;
		    }
        }
     }		 
    
    for(int i = 0 ; i <= 14 ; i++)
    {
		memset(OrgBuffer,BG,93*93);
		int org_i = i / 4;
		int org_j = i % 4;
		for(int imgrow = org_i*93, u=0; imgrow <= (((org_i+1)*93)-1) ; imgrow++, u++)
		{
			for(int imgcol= org_j*93, v=0 ; imgcol <= (((org_j+1)*93)-1) ; imgcol++, v++)
			{ 	
				*(OrgBuffer + (u*93 + v ) ) = *(Img + (imgrow*width+ imgcol) );
			}      
		}
		for(int j =i+1; j <= 15 ; j++)
		{
			memset(CmpBuffer,BG,93*93);
			int cmp_i = j / 4;
			int cmp_j = j % 4;
			for(int imgrow = cmp_i*93, u=0; imgrow <= (((cmp_i+1)*93)-1) ; imgrow++, u++)
	        {
	         	for(int imgcol= cmp_j*93, v=0 ; imgcol <= (((cmp_j+1)*93)-1) ; imgcol++, v++)
		        { 	
					*(CmpBuffer + (u*93 + v ) ) = *(Img + (imgrow*width+ imgcol) );
				}      
			}
			
	
				int cmp_value = compare(OrgBuffer,CmpBuffer,93,93);
				
				total_matches = total_matches +  cmp_value;
		}
		         
	}  
	
	cout << "No of Unique pieces : "<< (total_jigsaws - total_matches) << endl;
    
	return 0;
}
