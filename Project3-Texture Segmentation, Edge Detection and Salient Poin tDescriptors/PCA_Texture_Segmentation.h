#ifndef PCA_TEXTURE_SEGMENTATION_H
#define PCA_TEXTURE_SEGMENTATION_H

#include <vector>

using namespace std;

struct cluster
{
	int ID;
	vector <double> centroid;
	vector < vector <double> > cluster_points;
    vector <int> feature_ID;
};

double* getpixel(double* Image , int i , int j , int width , int height , int bpp);
void feat_ext_avg(unsigned char* Img, int width, int height, int bpp, vector<vector<double>> & feature_vector);
void convolution(double* Img, double* Buffer, vector <double> filter, int width, int height, int bpp);
void kmeans(int K, vector <vector <double> > feature_vector, vector <cluster> &clusters, int N );
void initialization( vector<cluster> &clusters , vector <vector <double> > feature_vector , int K);
double calc_distance( vector <double> centroid, vector <double> feature_vector );
void print_results(vector<cluster> & clusters);
double calc_L1_distance(vector <double> centroid, vector <double> feature_vector );
void normalization(vector <vector <double> > & feature_vector,int width,int height,int dimension);
void texture_segment(vector<cluster> & clusters, unsigned char* Out);
vector<vector<double>> read_file();
void post_process(unsigned char* Out, int width, int height, unsigned char* post_Out );


#endif /* PCA_TEXTURE_SEGMENTATION_H */
