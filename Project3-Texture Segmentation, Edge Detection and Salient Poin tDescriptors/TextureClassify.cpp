#include <vector>
#include "TextureClassify.h"
#include <math.h>
#include <stdlib.h> 
#include <time.h>
#include <algorithm>
#include <iostream>

using namespace std;

/*
//5x5 Laws Filter

vector <vector <double> > filter = { 
												//E5*E5 
									 {  0.0278  ,       0.0556 ,          0 ,       -0.0556   ,          -0.0278 ,  
										0.0556     ,  0.1111      ,       0    ,    -0.1111      ,       -0.0556,
											 0     ,       0      ,       0    ,          0      ,             0,
									   -0.0556     , -0.1111      ,       0    ,     0.1111      ,        0.0556,
									   -0.0278     , -0.0556      ,       0    ,     0.0556      ,        0.0278 },

											 //S5*S5
									   { 0.0625     ,       0      , -0.1250    ,          0      ,        0.0625,
											 0     ,       0      ,       0    ,          0      ,             0,
									   -0.1250     ,       0      ,  0.2500    ,          0      ,       -0.1250,
											 0     ,       0      ,       0    ,          0      ,             0,
										0.0625     ,       0      , -0.1250    ,          0      ,        0.0625 },

											//W5*W5
									  { 0.0278      ,-0.0556       ,      0     ,    0.0556       ,        -0.0278,
									   -0.0556     ,  0.1111      ,       0    ,    -0.1111      ,        0.0556,
											 0     ,       0      ,       0    ,          0      ,             0,
										0.0556     , -0.1111      ,       0    ,     0.1111      ,       -0.0556,
									   -0.0278     ,  0.0556      ,       0    ,    -0.0556      ,        0.0278 },
										   
										   //E5*S5
									   { 0.0417     ,       0      , -0.0833    ,          0      ,        0.0417,
										0.0833     ,       0      , -0.1667    ,          0      ,        0.0833,
											 0     ,       0      ,       0    ,          0      ,             0,
									   -0.0833     ,       0      ,  0.1667    ,          0      ,       -0.0833,
									   -0.0417     ,       0      ,  0.0833    ,          0      ,       -0.0417 },

										 //E5*W5
									   { 0.0278     , -0.0556      ,       0    ,     0.0556      ,       -0.0278,
										0.0556     , -0.1111      ,       0    ,     0.1111      ,       -0.0556,
											 0     ,       0      ,       0    ,          0      ,             0,
									   -0.0556     ,  0.1111      ,       0    ,    -0.1111      ,        0.0556,
									   -0.0278     ,  0.0556      ,       0    ,    -0.0556      ,        0.0278 },

										 //S5*E5
										{0.0417     ,  0.0833      ,       0    ,    -0.0833      ,       -0.0417,
											 0     ,       0      ,       0    ,          0      ,             0,
									   -0.0833     , -0.1667      ,       0    ,     0.1667      ,        0.0833,
											 0     ,       0      ,       0    ,          0      ,             0,
										0.0417     ,  0.0833      ,       0    ,    -0.0833      ,       -0.0417},

										 //S5*W5
										{0.0417     , -0.0833      ,       0    ,     0.0833      ,       -0.0417,
											 0     ,       0      ,       0    ,          0      ,             0,
									   -0.0833     ,  0.1667      ,       0    ,    -0.1667      ,        0.0833,
											 0     ,       0      ,       0    ,          0      ,             0,
										0.0417     , -0.0833      ,       0    ,     0.0833      ,       -0.0417},

										 //W5*E5
										{0.0278     ,  0.0556      ,       0    ,    -0.0556      ,       -0.0278,
									   -0.0556     , -0.1111      ,       0    ,     0.1111      ,        0.0556,
											 0     ,       0      ,       0    ,          0      ,             0,
										0.0556     ,  0.1111      ,       0    ,    -0.1111      ,       -0.0556,
									   -0.0278     , -0.0556      ,       0    ,     0.0556      ,        0.0278},

									   //W5*S5
									 {  0.0417     ,       0      , -0.0833    ,          0      ,        0.0417,
									   -0.0833     ,       0      ,  0.1667    ,          0      ,       -0.0833,
											 0     ,       0      ,       0    ,          0      ,             0,
										0.0833     ,       0      , -0.1667    ,          0      ,        0.0833,
									   -0.0417     ,       0      ,  0.0833    ,          0      ,       -0.0417 }    
																													 };

*/


//5x5 Laws Filter

vector <vector <double> > filter =
									 //E5*E5
									{    {1  ,  2  ,  0  , -2  , -1  ,
										  2  ,  4  ,  0  , -4  , -2,
										  0  ,  0  ,  0  ,  0  ,  0,
										 -2  , -4  ,  0  ,  4  ,  2,
										 -1  , -2  ,  0  ,  2  ,  1},
										 
										 
										 //s5*s5,
										 
										 { 1  ,  0  , -2  ,  0  ,  1,
										  0  ,  0  ,  0  ,  0  ,  0,
										 -2  ,  0  ,  4  ,  0  , -2,
										  0  ,  0  ,  0  ,  0  ,  0,
										  1  ,  0  , -2  ,  0  ,  1},
										 
										 
										 //w5*w5,
										 
										{  1  , -2  ,  0  ,  2  , -1,
										 -2  ,  4  ,  0  , -4  ,  2,
										  0  ,  0  ,  0  ,  0  ,  0,
										  2  , -4  ,  0  ,  4  , -2,
										 -1  ,  2  ,  0  , -2  ,  1},
										 
										 
										 //5*S5,
										 
										 { 1  ,  0  , -2  ,  0  ,  1,
										  2  ,  0  , -4  ,  0  ,  2,
										  0  ,  0  ,  0  ,  0  ,  0,
										 -2  ,  0  ,  4  ,  0  , -2,
										 -1  ,  0  ,  2  ,  0  , -1},
										 
										 
										 //E5*W5,
										 { 1  , -2  ,  0  ,  2  , -1,
										  2  , -4  ,  0  ,  4  , -2,
										  0  ,  0  ,  0  ,  0  ,  0,
										 -2  ,  4  ,  0  , -4  ,  2,
										 -1  ,  2  ,  0  , -2  ,  1},
										 
										 
										 //S5*E5,
										 
										 { 1  ,  2  ,  0  , -2  , -1,
										  0  ,  0  ,  0  ,  0  ,  0,
										 -2  , -4  ,  0  ,  4  ,  2,
										  0  ,  0  ,  0  ,  0  ,  0,
										  1  ,  2  ,  0  , -2  , -1},
										 
										 
										   //S5*W5
										 
										 { 1  , -2  ,  0  ,  2  , -1,
										  0  ,  0  ,  0  ,  0  ,  0,
										 -2  ,  4  ,  0  , -4  ,  2,
										  0  ,  0  ,  0  ,  0  ,  0,
										  1  , -2  ,  0  ,  2  , -1},
										 
										 //W5*E5,
										 
										 { 1  ,  2  ,  0  , -2  , -1,
										 -2  , -4  ,  0  ,  4  ,  2,
										  0  ,  0  ,  0  ,  0  ,  0,
										  2  ,  4  ,  0  , -4  , -2,
										 -1  , -2  ,  0  ,  2  ,  1},
										 
										// W5*S5,
										 
										 { 1  ,  0  , -2  ,  0  ,  1,
										 -2  ,  0  ,  4  ,  0  , -2,
										  0  ,  0  ,  0  ,  0  ,  0,
										  2  ,  0  , -4  ,  0  ,  2,
										 -1  ,  0  ,  2  ,  0  , -1}
																		};




/*
vector <vector <double> > filter	=			{
												   {  1  ,  2 ,   0  , -2  , -1 ,
													 2  ,  4 ,   0  , -4  , -2,
													 0  ,  0 ,   0  ,  0  ,  0,
													-2  , -4 ,   0  ,  4  ,  2,
													-1  , -2 ,   0  ,  2  ,  1},


												   {  1  ,  0 ,  -2  ,  0  ,  1,
													 2  ,  0 ,  -4  ,  0  ,  2,
													 0  ,  0 ,   0  ,  0  ,  0,
													-2  ,  0 ,   4  ,  0  , -2,
													-1  ,  0 ,   2  ,  0  , -1},


													{ 1  , -2 ,   0  ,  2  , -1,
													 2  , -4 ,   0  ,  4  , -2,
													 0  ,  0 ,   0  ,  0  ,  0,
													-2  ,  4 ,   0  , -4  ,  2,
													-1  ,  2 ,   0  , -2  ,  1},


												   { -1  ,  4 ,  -6  ,  4  , -1,
													-2  ,  8 , -12  ,  8  , -2,
													 0  ,  0 ,   0  ,  0  ,  0,
													 2  , -8 ,  12  , -8  ,  2,
													 1  , -4 ,   6  , -4  ,  1},


												   {  1  ,  2 ,   0  , -2  , -1,
													 0  ,  0 ,   0  ,  0  ,  0,
													-2  , -4 ,   0  ,  4  ,  2,
													 0  ,  0 ,   0  ,  0  ,  0,
													 1  ,  2 ,   0  , -2  , -1},



												   {  1  ,  0 ,  -2  ,  0  ,  1,
													 0  ,  0 ,   0  ,  0  ,  0,
													-2  ,  0 ,   4  ,  0  , -2,
													 0  ,  0 ,   0  ,  0  ,  0,
													 1  ,  0 ,  -2  ,  0  ,  1},



												   {  1  , -2 ,   0  ,  2  , -1,
													 0  ,  0 ,   0  ,  0  ,  0,
													-2  ,  4 ,   0  , -4  ,  2,
													 0  ,  0 ,   0  ,  0  ,  0,
													 1  , -2 ,   0  ,  2  , -1},




												   {  1  ,  2 ,   0  , -2  , -1,
													-2  , -4 ,   0  ,  4  ,  2,
													 0  ,  0 ,   0  ,  0  ,  0,
													 2  ,  4 ,   0  , -4  , -2,
													-1  , -2 ,   0  ,  2  ,  1},



												  {   1  ,  0 ,  -2  ,  0  ,  1,
													-2  ,  0 ,   4  ,  0  , -2,
													 0  ,  0 ,   0  ,  0  ,  0,
													 2  ,  0 ,  -4  ,  0  ,  2,
													-1  ,  0 ,   2  ,  0  , -1},




												   {  1  , -2 ,   0  ,  2  , -1,
													-2  ,  4 ,   0  , -4  ,  2,
													 0  ,  0 ,   0  ,  0  ,  0,
													 2  , -4 ,   0  ,  4  , -2,
													-1  ,  2 ,   0  , -2  ,  1},




												   { -1  ,  4 ,  -6  ,  4  , -1,
													 2  , -8 ,  12  , -8  ,  2,
													 0  ,  0 ,   0  ,  0  ,  0,
													-2  ,  8 , -12  ,  8  , -2,
													 1  , -4 ,   6  , -4  ,  1},




												   { -1  , -2 ,   0  ,  2  ,  1,
													 4  ,  8 ,   0  , -8  , -4,
													-6  ,-12 ,   0  , 12  ,  6,
													 4  ,  8 ,   0  , -8  , -4,
													-1  , -2 ,   0  ,  2  ,  1},



												   { -1  ,  0 ,   2  ,  0  , -1,
													 4  ,  0 ,  -8  ,  0  ,  4,
													-6  ,  0 ,  12  ,  0  , -6,
													 4  ,  0 ,  -8  ,  0  ,  4,
													-1  ,  0 ,   2  ,  0  , -1},



												   { -1  ,  2 ,   0  , -2  ,  1,
													 4  , -8 ,   0  ,  8  , -4,
													-6  , 12 ,   0  ,-12  ,  6,
													 4  , -8 ,   0  ,  8  , -4,
													-1  ,  2 ,   0  , -2  ,  1},




												   {  1  , -4 ,   6  , -4  ,  1,
													-4  , 16 , -24  , 16  , -4,
													 6  ,-24 ,  36  ,-24  ,  6,
													-4  , 16 , -24  , 16  , -4,
													 1  , -4 ,   6  , -4  ,  1}
																				   };
*/


double* getpixel(double* Image , int i , int j , int width , int height , int bpp)
{
	return (Image +((i*width +j)*bpp));
}

vector<double> feat_ext_avg(unsigned char* Img, int width, int height, int bpp)
{
	double* Buffer = new double[width*height*bpp];
	double* Zero_Mean_Img = new double[width*height*bpp];
	
	vector<double> features;
	double mean=0.0;
	
	for(int imgrow=0 ; imgrow < height ; imgrow++)
	{
		for(int imgcol=0 ; imgcol < width ; imgcol++)
		{
			mean += *(Img + (imgrow*width + imgcol) );
		}
	}
	
	mean = mean/(width*height);
	
	for(int imgrow=0 ; imgrow <height ; imgrow++)
	{
		for(int imgcol=0 ; imgcol < width ; imgcol++)
		{
			 *(Zero_Mean_Img + (imgrow*width + imgcol) ) =  ( (*(Img + (imgrow*width + imgcol) ) - mean) ) ;
		}
	}
		
	for(int i=0 ; i < filter.size() ; i++)
	{
	    convolution(Zero_Mean_Img,Buffer,filter[i],width,height,bpp);
	    
	    double sum = 0;
	    double avg = 0;
	    
	    for(int imgrow = 0 ; imgrow < height ; imgrow++)
	    {
			for(int imgcol = 0 ; imgcol < width ; imgcol++)
			{
				sum = sum + fabs(*(Buffer + (imgrow*width + imgcol) ));
			}
		}
		
		avg = (sum)/(width*height);
	
	    features.push_back(avg);
    }	
    
    delete[] Buffer;
    delete[] Zero_Mean_Img;
    return features;
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
										
										sum += (*(temp)*filter[t]);
										t++;
						}	
					}
						
						*(Buffer + (i*width + j) ) = sum; 
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
				//print_results(clusters);
				 for(int i=0 ; i < K ; i++)
				 {
					 clusters[i].cluster_points.clear();
					 clusters[i].feature_ID.clear();
				 }
				
				for(int i = 0; i < feature_vector.size(); i++)
				{
					for(int j=0 ; j < clusters.size() ; j++)
					{
						dist.push_back( calc_distance(clusters[j].centroid , feature_vector[i]) );
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
	
    int first_centroid_index = rand() % 12;
    cout<<"####################  K-means++ Intialization  ######################"<<endl;
    cout<<endl;
    cout<<endl;
    cout<<"centroid index 1: " << first_centroid_index+1<<endl;
     
    clusters.push_back( {1, feature_vector[first_centroid_index]  });
    
    vector <double> L2_distance;
    vector <double> min_dist;
    
    while( clusters.size() < K )
    {
		for (int i = 0; i < feature_vector.size(); i++)
        {
		  for( int  j = 0 ; j < clusters.size() ; j++ ) 
		  {
			  L2_distance.push_back( calc_distance(clusters[j].centroid, feature_vector[i]) );
		  }
		
		  min_dist.push_back( *min_element(L2_distance.begin(),L2_distance.end()) );
		  L2_distance.clear();
	    }
	  
	  int max_Element_Index = distance( min_dist.begin() , max_element( min_dist.begin(),min_dist.end() ) );
	  cout<<"centroid index "<<clusters.size()+1<<": "<<max_Element_Index+1<<endl;
	  int cluster_ID = clusters.size()+1;
	  clusters.push_back( { cluster_ID , feature_vector[max_Element_Index] } );
	  min_dist.clear();
    }	
    cout<<endl;
    cout<<endl;
    cout<<"######################################################################"<<endl;
    cout<<endl;
    cout<<endl;
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
	cout<<"################## Texture Classification  ######################"<<endl;
	for(int i=0 ; i < clusters.size() ; i++ )
	{
		cout<<endl;
		cout<<endl;
		cout<<" Cluster-Group ID:" << clusters[i].ID << endl;
		cout<<endl;
		cout<<" Feature ID:" << endl;
		cout<<endl;
		for(int j = 0 ; j < clusters[i].feature_ID.size() ; j++ )
		{
			cout<<" "<<clusters[i].feature_ID[j]+1<<"  ";
		}
		cout<<endl;
		cout<<endl;
	}	
	cout<<"##################################################################"<<endl;
}											
	                                    
	                                    
