#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdlib.h>
#include "TextureClassify.h"

using namespace std;

int main()
{
    FILE* fptr;
    vector <string> filename;
    vector <vector <double> > feature_vector;
    vector <cluster> clusters;
    
    int width  = 128;
    int height = 128;
    int bpp = 1;
    int K=4;
    int N=1;
    
    filename = { "texture1.raw","texture2.raw","texture3.raw","texture4.raw","texture5.raw","texture6.raw",
		         "texture7.raw","texture8.raw","texture9.raw","texture10.raw","texture11.raw","texture12.raw"  };
     
    unsigned char* Img = new unsigned char[width*height*bpp];
    string inputpath = "/home/ishan/Desktop/DIP/HW3Programs/EE569_hw3_images/EE569_hw3_images/";
    
	for( int i =0 ; i < 12 ; i++ )
	{
		 string filepath = inputpath+ filename[i];
		 
	     fptr = fopen(filepath.c_str(),"rb");
	     
				if(!(fptr == NULL))
				{    
			 
					//Reading RAW image into 3D image data matrix

					fread(Img,sizeof(unsigned char),width*height*bpp,fptr); 
					fclose(fptr);
					//cout<<"Image can be read"<<endl;	
					//cout<<"Successful!"<<endl;	
				}
				else
				{
					cout<<"Image cannot be read"<<endl;
				}	
				
				feature_vector.push_back( feat_ext_avg(Img,width,height,bpp) );				
	}
	
   ofstream features;
   features.open("/media/sf_ShareDip/1aTextureClassifyfeatures.txt",ios::out);
   
   if (features.is_open())
   {
	   for(int i=0 ; i < feature_vector.size() ; i++)
	   {
		   for(int j=0 ; j < feature_vector[i].size() ; j++ )
		   {
			   
					features<<feature_vector[i][j]<<",";
		   }
		   features<<"\n";
	   }   
		features.close();
   }
   else 
   {
		cout << "Failed to open the file!"<<endl;
   }		
    
   kmeans(K,feature_vector,clusters,1000); 
	print_results(clusters);
	   
	   

return 0;

}
