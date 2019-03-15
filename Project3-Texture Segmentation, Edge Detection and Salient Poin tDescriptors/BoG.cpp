#include "opencv2/xfeatures2d.hpp"
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <stdio.h>
#include "opencv2/imgcodecs.hpp"
#include "opencv2/features2d.hpp"
#include <string>

using namespace cv;
using namespace std;
using namespace xfeatures2d;

void saveDescriptor(string filename, Mat bowDescriptor);

int main()
{
 
    //Step 1 - Obtain the set of bags of features.
      
	Mat features_Unclustered;

   
   //Open and Read Image
   
   //read images

	  Mat Img1_in = imread("/media/sf_ShareDip/HW3/EE569_hw3_images/EE569_hw3_images/bumblebee.jpg",CV_LOAD_IMAGE_COLOR);
	  Mat Img2_in = imread("/media/sf_ShareDip/HW3/EE569_hw3_images/EE569_hw3_images/Optimus_Prime.jpg",CV_LOAD_IMAGE_COLOR);
	  Mat Img3_in = imread("/media/sf_ShareDip/HW3/EE569_hw3_images/EE569_hw3_images/ferrari1.jpg",CV_LOAD_IMAGE_COLOR);
	  Mat Img4_in = imread("/media/sf_ShareDip/HW3/EE569_hw3_images/EE569_hw3_images/ferrari_2.jpg",CV_LOAD_IMAGE_COLOR);
	 
     Ptr<SIFT> feat_2d = SIFT::create();
     
     //-- Step 1: Detect the keypoints:
	  
	  vector<KeyPoint> keypts_1, keypts_2, keypts_3, keypts_4;    
  
	  feat_2d->detect( Img1_in , keypts_1 );
	  feat_2d->detect( Img2_in , keypts_2 );
	  feat_2d->detect( Img3_in , keypts_3 );
	  feat_2d->detect( Img4_in , keypts_4 ); 
	  
	  
	  //-- Step 2: Calculate descriptors (feature vectors) 
     
	  Mat desc_1, desc_2, desc_3, desc_4;
		  
	  feat_2d->compute( Img1_in , keypts_1, desc_1 );
	  feat_2d->compute( Img2_in , keypts_2, desc_2 );
	  feat_2d->compute( Img3_in , keypts_3, desc_3 );
	  feat_2d->compute( Img4_in , keypts_4, desc_4 );

      //Store features
      
      features_Unclustered.push_back(desc_1);
      features_Unclustered.push_back(desc_2);
      features_Unclustered.push_back(desc_3);
      features_Unclustered.push_back(desc_4);
    
		//Construct BOWKMeansTrainer
		
		//the number of bags
		
		int dictionarySize=8;
		
		//define Term Criteria
		
		TermCriteria tc(CV_TERMCRIT_ITER,100,0.001);
		
		//retries number
		
		int retries=1;
		
		//necessary flags
		
		int flags=KMEANS_PP_CENTERS;
		
		//Create the BoW (or BoF) trainer
		
		BOWKMeansTrainer bowTrainer(dictionarySize,tc,retries,flags);
		
		//cluster the feature vectors
		
		Mat dictionary=bowTrainer.cluster(features_Unclustered);   
		 
		//create a nearest neighbor matcher
		
	    Ptr<DescriptorMatcher> matcher = DescriptorMatcher::create( "FlannBased" );
		//create Sift descriptor extractor
		Ptr<DescriptorExtractor> extractor = SIFT::create();    
		//create BoF (or BoW) descriptor extractor
		BOWImgDescriptorExtractor bowDE(extractor,matcher);
		//Set the dictionary with the vocabulary we created in the first step
		bowDE.setVocabulary(dictionary);
		
		
		//To store the BoW (or BoF) representation of the image
		
		Mat bowDescriptor1,bowDescriptor2,bowDescriptor3,bowDescriptor4;    
	
		//extract BoW (or BoF) descriptor from given image
		bowDE.compute(Img1_in,keypts_1,bowDescriptor1);
		bowDE.compute(Img2_in,keypts_2,bowDescriptor2);
		bowDE.compute(Img3_in,keypts_3,bowDescriptor3);
		bowDE.compute(Img4_in,keypts_4,bowDescriptor4);
		
		string desc1 = "descriptor1.yml";
		string desc2 = "descriptor2.yml";
		string desc3 = "descriptor3.yml";
		string desc4 = "descriptor4.yml";
		
	    saveDescriptor(desc1,bowDescriptor1);
	    saveDescriptor(desc2,bowDescriptor2);
	    saveDescriptor(desc3,bowDescriptor3);
	    saveDescriptor(desc4,bowDescriptor4);
      
        return 0;
}

void saveDescriptor(string filename, Mat bowDescriptor)
{
	
		//To store the image tag name - only for save the descriptor in a file
		char * imageTag = new char[10];
 
		//open the file to write the resultant descriptor
		FileStorage fs1(filename, FileStorage::WRITE);   
		 
		//prepare the yml (some what similar to xml) file
		sprintf(imageTag,"img1");            
		
		//write the new BoF descriptor to the file
		fs1 << imageTag << bowDescriptor;        
	 
		//You may use this descriptor for classifying the image.
				
		//release the file storage
		fs1.release();  
}
