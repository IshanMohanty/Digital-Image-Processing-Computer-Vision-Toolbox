#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdlib.h>
#include "Texture_Segmentation.h"
#include <time.h>

using namespace std;

int main(int argc, char *argv[])
{
	// Check for proper syntax
	if (argc < 6){
		cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
		cout << argv[0]<<"   input_image.raw output_image.raw post_process.raw width height" << endl;
		return 0;
	}

	int width  = atoi(argv[4]);
	int height = atoi(argv[5]);

    FILE* fptr;
    vector <string> filename;
    vector <vector <double> > feature_vector(width*height , vector<double>(9,0.0));
    vector <cluster> clusters;
    
    int bpp = 1;
    int K=6;
   
    unsigned char* Img = new unsigned char[width*height*bpp];
    unsigned char* Out = new unsigned char[width*height*bpp];
    unsigned char* post_Out = new unsigned char[width*height*bpp];
    
    fptr = fopen(argv[1],"rb");
    
	if(!(fptr == NULL))
	{      
        fread(Img,sizeof(unsigned char),width*height*bpp,fptr); //Reading RAW image into 3D image data matrix
	    fclose(fptr);
		cout<<"Image can be read"<<endl;		
	}
	else
	{
		cout<<"Image cannot be read"<<endl;
	}	
 			
   feat_ext_avg(Img,width,height,bpp,feature_vector);	
    
   kmeans(K,feature_vector,clusters,100); 
   texture_segment(clusters,Out);
   print_results(clusters);
  
   //write
	
	fptr =fopen(argv[2],"wb");
	if(!(fptr == NULL))
    { 
		fwrite(Out,sizeof(unsigned char),width*height*bpp,fptr);
	    fclose(fptr);
	}
	
	
	//~ fptr = fopen("/home/ishan/Desktop/DIP/HW3Programs/YOYO_SEGMENT_ISHAN.raw","rb");
	
    
	//~ if(!(fptr == NULL))
	//~ {      
        //~ fread(Out,sizeof(unsigned char),width*height*bpp,fptr); //Reading RAW image into 3D image data matrix
	    //~ fclose(fptr);
		//~ cout<<"Image can be read"<<endl;		
	//~ }
	//~ else
	//~ {
		//~ cout<<"Image cannot be read"<<endl;
	//~ }	
	
	clock_t t;
	t = clock();
	
	post_process(Out,width,height,post_Out);
	t = clock() - t;
    cout<<"Post Process runs for "<<t<< " clicks " << ((float)t)/CLOCKS_PER_SEC <<" seconds"<< endl;
	//write
	
	fptr =fopen(argv[3],"wb");
	if(!(fptr == NULL))
    { 
		fwrite(post_Out,sizeof(unsigned char),width*height*bpp,fptr);
	    fclose(fptr);
	}
	
	delete[] Img;
	delete[] Out;
	delete[] post_Out;
	 
   return 0;

}
