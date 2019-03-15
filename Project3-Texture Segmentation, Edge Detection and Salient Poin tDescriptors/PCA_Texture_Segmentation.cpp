#include <vector>
#include "PCA_Texture_Segmentation.h"
#include <math.h>
#include <stdlib.h> 
#include <time.h>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>

using namespace std;

vector <vector <double> > filter = {  
									{1  ,  4  ,  6  ,  4  ,  1, 
									 4  , 16  , 24  , 16  ,  4,
									 6  , 24  , 36  , 24  ,  6,
									 4  , 16  , 24  , 16  ,  4,
									 1  ,  4  ,  6  ,  4  ,  1},



								   { -1  , -4  , -6  , -4  , -1,
									-2  , -8  ,-12  , -8  , -2,
									 0  ,  0  ,  0  ,  0  ,  0,
									 2  ,  8  , 12  ,  8  ,  2,
									 1  ,  4  ,  6  ,  4  ,  1},



								  {  -1  , -4  , -6  , -4  , -1,
									 0  ,  0  ,  0  ,  0  ,  0,
									 2  ,  8  , 12  ,  8  ,  2,
									 0  ,  0  ,  0  ,  0  ,  0,
									-1  , -4  , -6  , -4  , -1},


								   { -1  , -4  , -6  , -4  , -1,
									 2  ,  8  , 12  ,  8  ,  2,
									 0  ,  0  ,  0  ,  0  ,  0,
									-2  , -8  ,-12  , -8  , -2,
									 1  ,  4  ,  6  ,  4  ,  1},



								   {  1  ,  4  ,  6  ,  4  ,  1,
									-4  ,-16  ,-24  ,-16  , -4,
									 6  , 24  , 36  , 24  ,  6,
									-4  ,-16  ,-24  ,-16  , -4,
									 1  ,  4  ,  6  ,  4  ,  1},



								   { -1  , -2  ,  0  ,  2  ,  1,
									-4  , -8  ,  0  ,  8  ,  4,
									-6  ,-12  ,  0  , 12  ,  6,
									-4  , -8  ,  0  ,  8  ,  4,
									-1  , -2  ,  0  ,  2  ,  1},



									{ 1  ,  2  ,  0  , -2  , -1,
									 2  ,  4  ,  0  , -4  , -2,
									 0  ,  0  ,  0  ,  0  ,  0,
									-2  , -4  ,  0  ,  4  ,  2,
									-1  , -2  ,  0  ,  2  ,  1},




								   {  1  ,  2  ,  0  , -2  , -1,
									 0  ,  0  ,  0  ,  0  ,  0,
									-2  , -4  ,  0  ,  4  ,  2,
									 0  ,  0  ,  0  ,  0  ,  0,
									 1  ,  2  ,  0  , -2  , -1},



								   {  1  ,  2  ,  0  , -2  , -1,
									-2  , -4  ,  0  ,  4  ,  2,
									 0  ,  0  ,  0  ,  0  ,  0,
									 2  ,  4  ,  0  , -4  , -2,
									-1  , -2  ,  0  ,  2  ,  1},



								   { -1  , -2  ,  0  ,  2  ,  1,
									 4  ,  8  ,  0  , -8  , -4,
									-6  ,-12  ,  0  , 12  ,  6,
									 4  ,  8  ,  0  , -8  , -4,
									-1  , -2  ,  0  ,  2  ,  1},



								   { -1  ,  0  ,  2  ,  0  , -1,
									-4  ,  0  ,  8  ,  0  , -4,
									-6  ,  0  , 12  ,  0  , -6,
									-4  ,  0  ,  8  ,  0  , -4,
									-1  ,  0  ,  2  ,  0  , -1},



								   {  1  ,  0  , -2  ,  0  ,  1,
									 2  ,  0  , -4  ,  0  ,  2,
									 0  ,  0  ,  0  ,  0  ,  0,
									-2  ,  0  ,  4  ,  0  , -2,
									-1  ,  0  ,  2  ,  0  , -1},



								   { 1  ,  0  , -2  ,  0  ,  1,
									 0  ,  0  ,  0  ,  0  ,  0,
									-2  ,  0  ,  4  ,  0  , -2,
									 0  ,  0  ,  0  ,  0  ,  0,
									 1  ,  0  , -2  ,  0  ,  1},



								   {  1  ,  0  , -2  ,  0  ,  1,
									-2  ,  0  ,  4  ,  0  , -2,
									 0  ,  0  ,  0  ,  0  ,  0,
									 2  ,  0  , -4  ,  0  ,  2,
									-1  ,  0  ,  2  ,  0  , -1},



								   { -1  ,  0  ,  2  ,  0  , -1,
									 4  ,  0  , -8  ,  0  ,  4,
									-6  ,  0  , 12  ,  0  , -6,
									 4  ,  0  , -8  ,  0  ,  4,
									-1  ,  0  ,  2  ,  0  , -1},




								   {-1  ,  2  ,  0  , -2  ,  1,
									-4  ,  8  ,  0  , -8  ,  4,
									-6  , 12  ,  0  ,-12  ,  6,
									-4  ,  8  ,  0  , -8  ,  4,
									-1  ,  2  ,  0  , -2  ,  1},



								  {  1  , -2  ,  0  ,  2  , -1,
									 2  , -4  ,  0  ,  4  , -2,
									 0  ,  0  ,  0  ,  0  ,  0,
									-2  ,  4  ,  0  , -4  ,  2,
									-1  ,  2  ,  0  , -2  ,  1},



								   { 1  , -2  ,  0  ,  2  , -1,
									 0  ,  0  ,  0  ,  0  ,  0,
									-2  ,  4  ,  0  , -4  ,  2,
									 0  ,  0  ,  0  ,  0  ,  0,
									 1  , -2  ,  0  ,  2  , -1},



								  {  1  , -2  ,  0  ,  2  , -1,
									-2  ,  4  ,  0  , -4  ,  2,
									 0  ,  0  ,  0  ,  0  ,  0,
									 2  , -4  ,  0  ,  4  , -2,
									-1  ,  2  ,  0  , -2  ,  1},



								   {-1  ,  2  ,  0  , -2  ,  1,
									 4  , -8  ,  0  ,  8  , -4,
									-6  , 12  ,  0  ,-12  ,  6,
									 4  , -8  ,  0  ,  8  , -4,
									-1  ,  2  ,  0  , -2  ,  1},




								   { 1  , -4  ,  6  , -4  ,  1,
									 4  ,-16  , 24  ,-16  ,  4,
									 6  ,-24  , 36  ,-24  ,  6,
									 4  ,-16  , 24  ,-16  ,  4,
									 1  , -4  ,  6  , -4  ,  1},



								   {-1  ,  4  , -6  ,  4  , -1,
									-2  ,  8  ,-12  ,  8  , -2,
									 0  ,  0  ,  0  ,  0  ,  0,
									 2  , -8  , 12  , -8  ,  2,
									 1  , -4  ,  6  , -4  ,  1},



								   {-1  ,  4  , -6  ,  4  , -1,
									 0  ,  0  ,  0  ,  0  ,  0,
									 2  , -8  , 12  , -8  ,  2,
									 0  ,  0  ,  0  ,  0  ,  0,
									-1  ,  4  , -6  ,  4  , -1},




								   {-1  ,  4  , -6  ,  4  , -1,
									 2  , -8  , 12  , -8  ,  2,
									 0  ,  0  ,  0  ,  0  ,  0,
									-2  ,  8  ,-12  ,  8  , -2,
									 1  , -4  ,  6  , -4  ,  1},




								   { 1  , -4  ,  6  , -4  ,  1,
									-4  , 16  ,-24  , 16  , -4,
									 6  ,-24  , 36  ,-24  ,  6,
									-4  , 16  ,-24  , 16  , -4,
									 1  , -4  ,  6  , -4  ,  1}
																 };
														 


																								
double* getpixel(double* Image , int i , int j , int width , int height , int bpp)
{
	return (Image +((i*width +j)*bpp));
}

void feat_ext_avg(unsigned char* Img, int width, int height, int bpp, vector<vector<double>> & feature_vector)
{
	double* Buffer = new double[width*height*bpp];
	double* Zero_Mean_Img = new double[width*height*bpp];
	double* mean_buffer = new double[width*height*bpp];
	double * temp = NULL;
	
	int N=31;
	
	
	for(int imgrow=0 ; imgrow < height ; imgrow++)
	{
		for(int imgcol=0 ; imgcol < width ; imgcol++)
		{
			double sum = 0;
			double windowed_avg = 0;
			
			 for(int k= (-1*(N/2)) ; k <= (N/2) ; k++)
			 {
					for(int h = (-1*(N/2)) ; h <= (N/2) ; h++)
					{

						 int n = imgrow + k;
						 int m = imgcol + h;

						 if( n < 0)
						 {
							 n = abs(n) - 1;
						 }

							if( m < 0)
							{
								m = abs(m) - 1;
							}

							if( n > (height - 1) )
							
							{
								n = (2*height) - n - 1;
							}

							if( m > (width - 1) )
							{
								m = (2*width) - m - 1;
							}
					
							sum += *(Img +((n*width +m)*bpp));
							
					}	
			}
				
			windowed_avg = (double)((sum)/(N*N));
			*(mean_buffer+ imgrow*width + imgcol) = windowed_avg;	
		}
	}
	
	
	for(int imgrow=0 ; imgrow <height ; imgrow++)
	{
		for(int imgcol=0 ; imgcol < width ; imgcol++)
		{
			 //*(Zero_Mean_Img + (imgrow*width + imgcol) ) =  ( (*(Img + (imgrow*width + imgcol) ) - mean)); //*(mean_buffer+ imgrow*width + imgcol)) ) ;			 
			 *(Zero_Mean_Img + (imgrow*width + imgcol) ) =  ( (*(Img + (imgrow*width + imgcol) ) -  *(mean_buffer+ imgrow*width + imgcol)) );
		}
		
	}
    
	for(int i=0 ; i < filter.size() ; i++)
	{
		
	    convolution(Zero_Mean_Img,Buffer,filter[i],width,height,bpp);
	    
	    for(int imgrow = 0 ; imgrow < height ; imgrow++)
	    {
			
			for(int imgcol = 0 ; imgcol < width ; imgcol++)
			{
				double sum = 0;
				double windowed_avg = 0;
				
				 for(int k= (-1*(N/2)) ; k <= (N/2) ; k++)
	             {
		                for(int h = (-1*(N/2)) ; h <= (N/2) ; h++)
		                {

					                 int n = imgrow + k;
					                 int m = imgcol + h;

				                     if( n < 0)
					                 {
					                     n = abs(n) - 1;
					                 }

										if( m < 0)
										{
											m = abs(m) - 1;
										}

										if( n > (height - 1) )
										{
											n = (2*height) - n - 1;
										}

										if( m > (width - 1) )
										{
											m = (2*width) - m - 1;
										}
																	 
										temp = getpixel(Buffer,n,m,width,height,bpp);
										sum += fabs(*(temp));
										
						}	
				}
				
				windowed_avg = (double)((sum)/(N*N));
			    feature_vector[ imgrow*width + imgcol][i] = windowed_avg;	
			    					
			}
		}	    
    }
    
    //perform normalization	
    int dimension = 0;  
    normalization(feature_vector,width,height,dimension);
    
    delete[] Buffer;
    delete[] Zero_Mean_Img;
    delete[] mean_buffer;
}

void convolution(double* Img, double* Buffer, vector <double> filter, int width, int height,int bpp)
{
	int N=5;
	double * temp = NULL;

	for(int i = 0; i < height ; i++)
	{
		for(int j=0 ; j < width ; j++)
		{
			 double sum = 0;
			 int t = 0;
			 double weight_sum = 0.0;
	               for(int k= (-1*(N/2)) ; k <= (N/2) ; k++)
	               {
		                for(int h = (-1*(N/2)) ; h <= (N/2) ; h++)
		                {

					                 int n = i + k;
					                 int m = j + h;

				                     if( n < 0)
					                 {
					                     n = abs(n) - 1;
					                 }

										if( m < 0)
										{
											m = abs(m) - 1;
										}

										if( n > (height - 1) )
										{
											n = (2*height) - n - 1;
										}

										if( m > (width - 1) )
										{
											m = (2*width) - m - 1;
										}
																	 
										temp = getpixel(Img,n,m,width,height,bpp);
										weight_sum += filter[t];
										sum += (*(temp)*filter[t]);
										t++;
						}	
					}
					if(weight_sum == 0){
						*(Buffer + (i*width + j) ) = sum; 
					}
					else{
						*(Buffer + (i*width + j) ) = sum/weight_sum; 
					}	
	       }
	  }
	  
}

void kmeans(int K, vector <vector <double> > feature_vector, vector <cluster> & clusters, int N )
{
	vector <double> dist;
	
	
	//Find Initial K centroids
	initialization(clusters,feature_vector,K);
	
	for( int iter = 0 ; iter < N ; iter++)
	{
				//Assign Cluster group based on euclidean distance to centroids
				
				 for(int i=0 ; i < K ; i++)
				 {
					 clusters[i].cluster_points.clear();
					 clusters[i].feature_ID.clear();
				 }
				
				for(int i = 0; i < feature_vector.size(); i++)
				{
					for(int j=0 ; j < clusters.size() ; j++)
					{
						dist.push_back( calc_L1_distance(clusters[j].centroid , feature_vector[i]) );
					}
					
					int cluster_index = distance( dist.begin(), min_element( dist.begin(), dist.end() ) );
					
					clusters[cluster_index].cluster_points.push_back(feature_vector[i]);
					clusters[cluster_index].feature_ID.push_back(i);
					
					dist.clear();	
			   }
			   		   
			   // Update Step 
			   
			   for(int i= 0 ; i < clusters.size() ; i++ )
			   {

				   for(int j = 0 ; j < clusters[i].centroid.size() ; j++ )
				   {
					   double sum = 0;
						double average = 0;
					   for(int k = 0 ;  k < clusters[i].cluster_points.size() ; k++ )
					   {
						   sum += clusters[i].cluster_points[k][j];
					   }
					   average = sum /(clusters[i].cluster_points.size());
					   clusters[i].centroid[j] = average;			   
				   }   
			   } 
		}
}

// Kmeans++ ---- find centroids

void initialization( vector<cluster> & clusters , vector <vector <double> > feature_vector , int K)
{
	srand(time(NULL));
	
    int first_centroid_index = rand() % feature_vector.size();
    
    //~ cout<<"first centroid index" << first_centroid_index<<endl;
     
    clusters.push_back( {1, feature_vector[first_centroid_index]  });
    
    vector <double> L2_distance;
    vector <double> min_dist;
    
    while( clusters.size() < K )
    {
		for (int i = 0; i < feature_vector.size(); i++)
        {
		  for( int  j = 0 ; j < clusters.size() ; j++ ) 
		  {
			  L2_distance.push_back( calc_L1_distance(clusters[j].centroid, feature_vector[i]) );
		  }
		
		  min_dist.push_back( *min_element(L2_distance.begin(),L2_distance.end()) );
		  L2_distance.clear();
	    }
	  
	  int max_Element_Index = distance( min_dist.begin() , max_element( min_dist.begin(),min_dist.end() ) );
	  //~ cout<<"other centroid indices"<<max_Element_Index<<endl;
	  int cluster_ID = clusters.size()+1;
	  clusters.push_back( { cluster_ID , feature_vector[max_Element_Index] } );
	  min_dist.clear();
    }	
}
	
double calc_distance(vector <double> centroid, vector <double> feature_vector )
{
		double distance_square = 0;
		double euclidean_distance = 0;
	
		for( int i=0 ; i < feature_vector.size() ; i++)
		{
			distance_square += pow(feature_vector[i] - centroid[i],2);
		}
		
		euclidean_distance = sqrt(distance_square);
		
		return euclidean_distance;  
}	       

double calc_L1_distance(vector <double> centroid, vector <double> feature_vector )
{
		double sum=0;
		double L1_distance = 0;
	
		for( int i=0 ; i < feature_vector.size() ; i++)
		{
			sum += fabs(feature_vector[i] - centroid[i]);
		}
		
		L1_distance = sum;
		
		return L1_distance;  
}	          

void print_results(vector<cluster> & clusters)
{
	for(int i=0 ; i < clusters.size() ; i++ )
	{
		cout<<endl;
		cout<<endl;
		cout<<" cluster ID:" << clusters[i].ID << endl;
		cout<<endl;
		cout<<" Feature ID:" << endl;
		cout<<endl;
		cout << clusters[i].feature_ID.size() << endl;
		for(int j = 0 ; j < clusters[i].feature_ID.size() ; j++ )
		{
			//~ cout<<" "<<clusters[i].feature_ID[j]<<"  ";
		}
		cout<<endl;
		cout<<endl;
	}	
}	

void normalization(vector <vector <double> > & feature_vector,int width,int height,int dimension)
{
	//~ vector <double> feature;	
	//~ for( int i=0 ; i < (width*height-1) ; i++ )
	//~ {
	     //~ feature.push_back(feature_vector[i][dimension]);
	//~ }
	 //~ double max_element = *std::max_element(feature.begin(), feature.end());
	 //~ double min_element = *std::min_element(feature.begin(), feature.end());
	     
	//~ for(int i=0 ; i < (width*height-1) ; i++ )
	//~ {
		//~ feature_vector[i][dimension] = (feature_vector[i][dimension] - min_element)/(max_element - min_element);
	//~ }
	for(int i=0; i < feature_vector[0].size(); i++){
		for(int j=0; j < feature_vector.size(); j++){
			feature_vector[j][i] /= feature_vector[j][dimension];
		}
	}	
}

void texture_segment(vector<cluster> & clusters, unsigned char* Out)
{
	int gray_levels[6] = {0,51, 102, 153, 204, 255};
	
    for(int i=0 ; i < clusters.size() ; i++ )
	{
		cout << clusters[i].feature_ID.size() << endl;
		for(int j=0; j < clusters[i].feature_ID.size() ; j++ )
		{
			
			*(Out + clusters[i].feature_ID[j] ) = gray_levels[i];
		}
	}
}

vector<vector<double>> read_file()
{
	 string lines;
    vector<vector<double> > data; 

    ifstream infile("/media/sf_ShareDip/HW3/Report3_images/PCA_features_ISHAN_NEW_REPORT_FINAL_20.txt"); //read in text file

    while (getline(infile, lines))
    {
        data.push_back(vector<double>());
        stringstream ss(lines);
        string value;
        //while (ss >> value)
        while (getline(ss, value, ','))
        {	
            data.back().push_back(atof(value.c_str() )); //enter data from text file into array
            
        }
    }
//  Outputs the array to make sure it works.
 
     return data;
}

void post_process(unsigned char* Out, int width, int height, unsigned char* post_Out )
{
	int N=11;
	
	int temp = 0;

    cout<<"Post Process Start!"<<endl;
	for(int i = 0; i < height ; i++)
	{
		for(int j=0 ; j < width ; j++)
		{
			 double sum = 0;
			 int t = 0;
			 int max = 0;
			 int most_common = -1;
			 map<int,int> mapped = { {0,0}, {51,0}, {102,0} , {153,0} ,  {204,0} ,  {255,0} };
			 
	               for(int k= (-1*(N/2)) ; k <= (N/2) ; k++)
	               {
		                for(int h = (-1*(N/2)) ; h <= (N/2) ; h++)
		                {

					                 int n = i + k;
					                 int m = j + h;

				                     if( n < 0)
					                 {
					                     n = abs(n) - 1;
					                 }

										if( m < 0)
										{
											m = abs(m) - 1;
										}

										if( n > (height - 1) )
										{
											n = (2*height) - n - 1;
										}

										if( m > (width - 1) )
										{
											m = (2*width) - m - 1;
										}
																	 
										temp = *(Out + (n*width + m) );
                  
										mapped[temp]++;
										if (mapped[temp] > max) 
										{
											max = mapped[temp]; 
											most_common = temp;
										}
														
						}	
					}
			   
				*(post_Out + (i*width + j) ) = most_common; 		
	       }
	  }
	  
	  cout<<"Post Process Done!"<<endl;
	  
}
			
