#include "opencv2/xfeatures2d.hpp"
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <stdio.h>
#include "opencv2/imgcodecs.hpp"
#include "opencv2/features2d.hpp"
#include <time.h>

using namespace cv;
using namespace std;
using namespace xfeatures2d;

//function declaration
vector <DMatch> matches(Mat descriptors_1, Mat descriptors_2 );

int main()
{ 
	  //Sift Algorithm
	
	  //read images

	  Mat Img1_in = imread("/media/sf_ShareDip/HW3/EE569_hw3_images/EE569_hw3_images/bumblebee.jpg",CV_LOAD_IMAGE_COLOR);
	  Mat Img2_in = imread("/media/sf_ShareDip/HW3/EE569_hw3_images/EE569_hw3_images/Optimus_Prime.jpg",CV_LOAD_IMAGE_COLOR);
	  Mat Img3_in = imread("/media/sf_ShareDip/HW3/EE569_hw3_images/EE569_hw3_images/ferrari1.jpg",CV_LOAD_IMAGE_COLOR);
	  Mat Img4_in = imread("/media/sf_ShareDip/HW3/EE569_hw3_images/EE569_hw3_images/ferrari_2.jpg",CV_LOAD_IMAGE_COLOR);
	 
	  Ptr<Feature2D> feat_2d = SIFT::create(10000);
	  
	  clock_t t;
	  t = clock();
	  
	  //-- Step 1: Detect the keypoints:
	  
	  vector<KeyPoint> keypts_1, keypts_2, keypts_3, keypts_4;    
  
	  feat_2d->detect( Img1_in , keypts_1 );
	  feat_2d->detect( Img2_in , keypts_2 );
	  feat_2d->detect( Img3_in , keypts_3 );
	  feat_2d->detect( Img4_in , keypts_4 );
  
	  cout<<" No of Keypoints Img1 -- Bumblebee : " << keypts_1.size() << endl;
	  cout<<" No of Keypoints Img2 -- Optimus Prime : " << keypts_2.size() << endl;
	  cout<<" No of Keypoints Img1 -- Ferrari 1 : " << keypts_3.size() << endl;
	  cout<<" No of Keypoints Img2 -- Ferrari 2 : " << keypts_4.size() << endl;
	  
      //-- Step 2: Calculate descriptors (feature vectors) 
     
	  Mat desc_1, desc_2, desc_3, desc_4;
		  
	  feat_2d->compute( Img1_in , keypts_1, desc_1 );
	  feat_2d->compute( Img2_in , keypts_2, desc_2 );
	  feat_2d->compute( Img3_in , keypts_3, desc_3 );
	  feat_2d->compute( Img4_in , keypts_4, desc_4 );
	  
	  t = clock() - t;
      cout<<"Sift runs for "<<t<< " clicks " << ((float)t)/CLOCKS_PER_SEC <<" seconds"<< endl;
  
	  // Draw Keypoints in output image
	  
	  Mat Out1, Out2;
	  
	  drawKeypoints(Img1_in , keypts_1 , Out1 , Scalar::all(-1),
					cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
					
	  drawKeypoints(Img2_in , keypts_2 , Out2 , Scalar::all(-1),
					cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
				            
    //Display Output Sift image
   
    imshow( "Display first", Out1 );   
    imshow( "Display second", Out2 );         
	
	//Write Out Image
	
	imwrite("/media/sf_ShareDip/HW3/Report3_images/Bumble_500.jpg",Out1);
	imwrite("/media/sf_ShareDip/HW3/Report3_images/Optimus_500.jpg",Out2);

   
	  //-- Step 3: Matching descriptor vectors 
	  vector< DMatch > good_matches1, good_matches2, good_matches3;
	  
	  good_matches1 = matches(desc_3,desc_1) ;
	  good_matches2 = matches(desc_3,desc_2) ;
	  good_matches3 = matches(desc_3,desc_4) ;
	  
	  //-- Draw only "good" matches
	  
      Mat Out3, Out4, Out5;
      
      drawMatches( Img3_in, keypts_3, Img1_in, keypts_1,
      good_matches1, Out3 , Scalar::all(-1), Scalar::all(-1),
      vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS );
      
      drawMatches( Img3_in, keypts_3, Img2_in, keypts_2,
      good_matches2, Out4 , Scalar::all(-1), Scalar::all(-1),
      vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS );
      
      drawMatches( Img3_in, keypts_3, Img4_in, keypts_4,
      good_matches3, Out5 , Scalar::all(-1), Scalar::all(-1),
      vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS );
      
	  //-- Show detected matches
	  
	  imshow( "Good Matches 3 and 1", Out3 );
	  //~ for( int i = 0; i < (int)good_matches1.size(); i++ )
	  //~ { 
		  //~ printf( "-- Good Match [%d] Keypoint 3: %d  -- Keypoint 1: %d  \n", i, good_matches1[i].queryIdx, good_matches1[i].trainIdx ); 
	  //~ }
	  
	  imshow( "Good Matches 3 and 2", Out4 );
	  //~ for( int i = 0; i < (int)good_matches2.size(); i++ )
	  //~ { 
		  //~ printf( "-- Good Match [%d] Keypoint 3: %d  -- Keypoint 2: %d  \n", i, good_matches2[i].queryIdx, good_matches2[i].trainIdx ); 
	  //~ }
	  
	  imshow( "Good Matches 3 and 4", Out5 );
	  //~ for( int i = 0; i < (int)good_matches3.size(); i++ )
	  //~ { 
		  //~ printf( "-- Good Match [%d] Keypoint 3: %d  -- Keypoint 4: %d  \n", i, good_matches3[i].queryIdx, good_matches3[i].trainIdx ); 
	  //~ }
	  
	  
	  //Write Out Image
	
		imwrite("/media/sf_ShareDip/HW3/Report3_images/Match_ferrari_1_Bumble_500.jpg",Out3);
		imwrite("/media/sf_ShareDip/HW3/Report3_images/Match_ferrari_1_Optimus_500.jpg",Out4);
		imwrite("/media/sf_ShareDip/HW3/Report3_images/Match_ferrari_1_ferrari_2_500.jpg",Out5);
	    
    waitKey(0);
    destroyAllWindows();
    
    
    
    return 0;  
}


vector <DMatch> matches(Mat descriptors_1, Mat descriptors_2 )
{
  Ptr<DescriptorMatcher> matcher = DescriptorMatcher::create( "BruteForce" );
  vector< DMatch > matches;
  matcher->match(descriptors_1, descriptors_2, matches);
  vector< DMatch > great_matches;;
  double max_dist = 0; double min_dist = 100;
  
  //-- calculation of max and min distances between keypoints
  
  for( int i = 0; i < descriptors_1.rows; i++ )
  { double dist = matches[i].distance;
    if( dist < min_dist ) min_dist = dist;
    if( dist > max_dist ) max_dist = dist;
  }
  
  //-- Draw only "good" matches (i.e. whose distance is less than 2*min_dist,
  //-- or a small arbitary value ( 0.02 ) in the event that min_dist is very
  //-- small)
  
  for( int i = 0; i < descriptors_1.rows; i++ )
  { 
	if( matches[i].distance <= max(2*min_dist, 0.02) )
    { 
		great_matches.push_back( matches[i]); 
	}
  }

  cout << "Good Matches : "<< great_matches.size() << endl;
  return great_matches;
}
  


