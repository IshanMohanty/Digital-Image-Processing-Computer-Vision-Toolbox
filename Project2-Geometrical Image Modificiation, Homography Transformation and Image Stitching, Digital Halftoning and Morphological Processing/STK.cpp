#include <vector>
#include <math.h>
#include <algorithm>
#include <iostream>
#include <string.h>
#include <stdio.h>
#include "STK.h"


using namespace std;

vector <window_pos> window_coordinates = { {  0,  1} , 
	                                       {  -1,  1 },{  -1,  0},{  -1, -1}, 
	                                       {  0,  -1}, 
	                                       {  1,  -1}, {  1,  0} , {  1,  1} };




vector <int> shrink_cond_pattern     = {              0x02, 0x08, 0x20, 0x80, // 1
                                                      0x01, 0x04, 0x10, 0x40, // 2
                                                      0x03, 0x06, 0x0C, 0x18, 0x30, 0x60, 0xC0, 0x81, // 3
                                                      0x83, 0x0E, 0x38, 0xE0, // 4
                                                      0x0D, 0x85, 0x16, 0x43, 0x07, 0x1C, 0x70, 0xC1, // 5
                                                      0x8D, 0x36, 0x0F, 0x87, 0x1E, 0x3C, 0x78, 0xF0, 0xE1, 0xC3, // 6
                                                      0x8F, 0x3E, 0xF8, 0xE3, // 7
                                                      0xC7, 0x1F, 0x7C, 0xF1, // 8
                                                      0xCF, 0xE7, 0x3F, 0x9F, 0x7E, 0xFC, 0xF9, 0xF3, // 9
                                                      0xEF, 0xBF, 0xFE, 0xFB // 10
                                                      
                                                      };  



vector <int> thin_cond_pattern     = { 
                                                      0x05, 0x14, 0x50, 0x41, 0x83, 0x0E, 0x38, 0xE0, // 4
                                                      0x0D, 0x85, 0x16, 0x43, 0x07, 0x1C, 0x70, 0xC1, // 5
                                                      0x8D, 0x36, 0x0F, 0x87, 0x1E, 0x3C, 0x78, 0xF0, 0xE1, 0xC3, // 6
                                                      0x8F, 0x3E, 0xF8, 0xE3, // 7
                                                      0xC7, 0x1F, 0x7C, 0xF1, // 8
                                                      0xCF, 0xE7, 0x3F, 0x9F, 0x7E, 0xFC, 0xF9, 0xF3, // 9
                                                      0xEF, 0xBF, 0xFE, 0xFB // 10
                                                      
                                                      };  
                                                      
vector <int> skel_cond_pattern     = { 
                                                      0x05, 0x14, 0x50, 0x41, 0x83, 0x0E, 0x38, 0xE0, // 4
                                                      
                                                      0x0F, 0x87, 0x1E, 0x3C, 0x78, 0xF0, 0xE1, 0xC3, // 6
                                                      0x8F, 0x3E, 0xF8, 0xE3, // 7
                                                      0xC7, 0x1F, 0x7C, 0xF1, // 8
                                                      0xCF, 0xE7, 0x3F, 0x9F, 0x7E, 0xFC, 0xF9, 0xF3, // 9
                                                      0xEF, 0xBF, 0xFE, 0xFB, // 10
                                                      0xDF, 0x7F, 0xFD, 0xF7  // 11
                                                      };  
                                                      
                                                      

vector <int> shrink_uncond_pattern = {                       0x02, 0x08, //1
                                                             0x40, 0x01, //2
                                                             0x03, 0x06, 0x0c, 0x18, 0x30, 0x60, 0xc0, 0x81, 0x2a, 
                                                             0xa8, 0x8a, 0xa2, //3
                                                             0x23, 0x8c, 0x62, 0x89, 0x26, 0x98, 0x32, 0xc8, 0x4a, 
                                                             0xaa, 0x29, 0xa4, 0x92, //4
                                                             0x16, 0x0d, 0x85, 0x43, 0x1c, 0x3a, 0x2e, 0x2b, 0x9a, 
                                                             0x8e, 0x8b, 0x6a, 0xca, 0xe8, 0xb8, 0xac, 0xa9, 0xe2, 
                                                             0xb2, 0xa3, 0xa6, 0x25, 0x94, 0x52, 0x49, //5
                                                             0x27, 0x72, 0xc9, 0x9c, 0x3c, 0x1e, 0x15, 0x51, 0x54, 
                                                             0x45, 0x5a, 0x4e, 0x4b, 0xba, 0xae, 0xab, 0xea, 0x69, 
                                                             0x39, 0x2d, 0xe4, 0xb4, 0xa5, 0xd2, 0x96, 0x93, //6
                                                             0x5c, 0xbc, 0x9e, 0x3e, 0x1d, 0x35, 0x95, 0x17, 0xd1, 
                                                             0x53, 0x71, 0x59, 0x56, 0xd4, 0x74, 0xc5, 0x65, 0x4d, 
                                                             0x47, 0x3b, 0x2f, 0x9b, 0x8f, 0x7a, 0x6e, 0xda, 0xce, 
                                                             0xcb, 0xf8, 0xec, 0xe9, 0xb9, 0xad, 0xf2, 0xe3, 0xb3, 
                                                             0xe6, 0xb6, 0xa7, //7
                                                             0xdc, 0x7c, 0x5e, 0xbe, 0x9d, 0x3d, 0x1f, 0x97, 0xd3, 
                                                             0x79, 0xf4, 0xe5, 0x4f, 0x5b, 0xbb, 0xaf, 0xfa, 0xee, 
                                                             0xeb, 0x6d, 0xb5, 0xd6, //8
                                                             0xfc, 0xde, 0x7e, 0x5d, 0xbd, 0x9f, 0x3f, 0x7b, 0x6f, 
                                                             0xdb, 0xcf, 0xf9, 0xed, 0xf3, 0xf6, 0xe7, 0xb7, //9
                                                             
                                                             0xfe, 0xdd, 0x7d, 0x5f, 0xbf, 0xfb, 0xef, 0xf5, 0xd7, //10
                                                            
                                                             0xfd, 0xdf, 0x7f, 0xf7 //11
                                                      };
                                                      

vector <int> thin_uncond_pattern                   = {       0x02, 0x08, //1
                                                             0x40, 0x01, //2
                                                             0x03, 0x06, 0x0c, 0x18, 0x30, 0x60, 0xc0, 0x81, 0x2a, 
                                                             0xa8, 0x8a, 0xa2, //3
                                                             0x23, 0x8c, 0x62, 0x89, 0x26, 0x98, 0x32, 0xc8, 0x4a, 
                                                             0xaa, 0x29, 0xa4, 0x92, //4
                                                             0x16, 0x0d, 0x85, 0x43, 0x1c, 0x3a, 0x2e, 0x2b, 0x9a, 
                                                             0x8e, 0x8b, 0x6a, 0xca, 0xe8, 0xb8, 0xac, 0xa9, 0xe2, 
                                                             0xb2, 0xa3, 0xa6, 0x25, 0x94, 0x52, 0x49, //5
                                                             0x27, 0x72, 0xc9, 0x9c, 0x3c, 0x1e, 0x15, 0x51, 0x54, 
                                                             0x45, 0x5a, 0x4e, 0x4b, 0xba, 0xae, 0xab, 0xea, 0x69, 
                                                             0x39, 0x2d, 0xe4, 0xb4, 0xa5, 0xd2, 0x96, 0x93, //6
                                                             0x5c, 0xbc, 0x9e, 0x3e, 0x1d, 0x35, 0x95, 0x17, 0xd1, 
                                                             0x53, 0x71, 0x59, 0x56, 0xd4, 0x74, 0xc5, 0x65, 0x4d, 
                                                             0x47, 0x3b, 0x2f, 0x9b, 0x8f, 0x7a, 0x6e, 0xda, 0xce, 
                                                             0xcb, 0xf8, 0xec, 0xe9, 0xb9, 0xad, 0xf2, 0xe3, 0xb3, 
                                                             0xe6, 0xb6, 0xa7, //7
                                                             0xdc, 0x7c, 0x5e, 0xbe, 0x9d, 0x3d, 0x1f, 0x97, 0xd3, 
                                                             0x79, 0xf4, 0xe5, 0x4f, 0x5b, 0xbb, 0xaf, 0xfa, 0xee, 
                                                             0xeb, 0x6d, 0xb5, 0xd6, //8
                                                             0xfc, 0xde, 0x7e, 0x5d, 0xbd, 0x9f, 0x3f, 0x7b, 0x6f, 
                                                             0xdb, 0xcf, 0xf9, 0xed, 0xf3, 0xf6, 0xe7, 0xb7, //9
                                                             
                                                             0xfe, 0xdd, 0x7d, 0x5f, 0xbf, 0xfb, 0xef, 0xf5, 0xd7, //10
                                                            
                                                             0xfd, 0xdf, 0x7f, 0xf7 //11
                                                      };                                                      


vector <int> skel_uncond_pattern                    = {           0x80, 0x20, 0x02, 0x08, //1
                                                                  0x40, 0x01, 0x10, 0x04, //2
                                                                  0x2a, 0x8a, 0xa8, 0xa2, //3
                                                                  0x05, 0x14, 0x41, 0x50, 0x4a, 0xaa, 0x29, 0xa4, 0x92, //4
                                                                   0x1c, 0xc1, 0x3a, 0x2e, 0x2b, 0x9a, 0x8e, 0x8b, 0x6a, 0xca, 
                                                                   0xe8, 0xb8, 0xac, 0xa9, 0xe2, 0xb2, 0xa3, 0xa6, 0x25, 0x94,  
                                                                   0x52, 0x49, //5
                                                                   0x9c, 0x3c, 0x1e, 0xe1, 0xc9, 0xc3, 0x15, 0x54, 0x51, 0x45, 
                                                                   0x5a, 0x4e, 0x4b, 0xba, 0xae, 0xab, 0xea, 0x69, 0x39, 0x2d,  
                                                                   0xe4, 0x93, 0xa5, 0xb4, 0x96, 0xd2,  //6
                                                                   0x5c, 0xbc, 0x9e, 0x3e, 0x1d, 0xd1, 0xe9, 0xc5, 0xe3, 0xcb, 
                                                                   0x95, 0x35, 0x17, 0xd4, 0x74, 0x56, 0x71, 0x59, 0x53, 0x65,  
                                                                   0x4d, 0x47, 0x3b, 0x2f, 0x9b, 0x8f, 0x7a, 0x6e, 0x6b, 0xda, 
                                                                   0xce, 0xf8, 0xb9, 0xec, 0xe6, 0xa7, 0xf2, 0xb3, 0xad, 0xb6,  //7
                                                                   0xdc, 0x7c, 0x5e, 0xbe, 0x9d, 0x3d, 0x1f, 0xf1, 0xd9, 0xe5, 
                                                                   0xcd, 0xd3, 0xeb, 0xc7, 0x55, 0xb5, 0x97, 0x37, 0xf4, 0x76,  
                                                                   0x73, 0x67, 0x5b, 0x4f, 0x79, 0x6d, 0xd6, 0xee, 0xaf, 0xfa, 
                                                                   0xbb, //8
                                                                   0xfc, 0xde, 0x7e, 0x5d, 0xbd, 0x9f, 0x3f, 0xf9, 0xd5, 0xed, 
                                                                   0xf3, 0xdb, 0xe7, 0xcf, 0x75, 0x57, 0xb7, 0xf6, 0x7b, 0x6f,  // 9
                                                                   
                                                                   0xfe, 0xdd, 0x7d, 0x5f, 0xbf, 0xf5, 0xfb, 0xd7, 0xef, 0x77, //10
                                                                   
                                                                   0xfd, 0xdf, 0x7f, 0xf7 //11
                                                              };



                                                


void STK(unsigned char* Img, unsigned char* MBuffer, unsigned char* Out,int width, int height, int action, int Run_Times, int FG, int BG)
{

    unsigned char* LocalBuffer = new unsigned char[width*height];	
    
	vector <int> cond_mask , uncond_mask;
	cond_mask.clear();
	uncond_mask.clear();
	
	for(int imgrow = 0 ; imgrow <=height-1 ; imgrow++)
	{
		for(int imgcol = 0 ; imgcol <=width-1 ; imgcol++ )
		{
			*(LocalBuffer + (imgrow*width + imgcol) ) = *( Img + (imgrow*width + imgcol) );
		}
	}
			
				
		
	switch(action)
	{
		case 1: 
		    cond_mask.insert(cond_mask.begin(), shrink_cond_pattern.begin() , shrink_cond_pattern.end() );
		    uncond_mask.insert(uncond_mask.begin(), shrink_uncond_pattern.begin() , shrink_uncond_pattern.end() );	
		break;
		
		case 2:
		    cond_mask.insert(cond_mask.begin(), thin_cond_pattern.begin() , thin_cond_pattern.end() );
		    uncond_mask.insert(uncond_mask.begin(), thin_uncond_pattern.begin() , thin_uncond_pattern.end() );
		break;
		
		case 3:
		     cond_mask.insert(cond_mask.begin(), skel_cond_pattern.begin() , skel_cond_pattern.end() );
		     uncond_mask.insert(uncond_mask.begin() , skel_uncond_pattern.begin() , skel_uncond_pattern.end() );		
		break;
	    
	    default:	    
	    cout<<" wrong action  please select: shrink-1 , thin-2, skel-3 "<<endl;
	    break;
	}
	
	
	for(int N = 0 ; N < Run_Times  ; N++ )
	{
		//Conditional Pattern Matching -- First Stage
		
		for(int imgrow = 1 ; imgrow < height-1 ; imgrow++)
		{
			for(int imgcol = 1 ; imgcol < width-1 ; imgcol++ )
			{
				int pix_intensity = (int)(*(LocalBuffer + (imgrow*width + imgcol) ));	
				int window_pattern = 0;
				
				if(pix_intensity == FG )
				{
					
					for(int k = 7 ; k >= 0 ; k-- )
					{
						
						int cond_window = (int)(*(LocalBuffer + ( (imgrow + window_coordinates[k].row)*width) + 
						                   (imgcol + window_coordinates[k].col) ));
						
						if( cond_window == FG )
						{   
							//left shift with 1 and bitwise OR with 1 to get a 8 bit pattern for matching
							window_pattern = ( window_pattern << 1 ) | 1 ;
						}
						
						else
						{
							//left shift with 1 and bitwise OR with 0 to get a 8 bit pattern for matching
							window_pattern = ( window_pattern << 1) | 0 ;
						}
						
					}
					if( find( cond_mask.begin() , cond_mask.end() , window_pattern ) != cond_mask.end() )
					{
					
						*( MBuffer + ( imgrow*width + imgcol) ) = FG ;
					}
					else
					{
					
						*( MBuffer + ( imgrow*width + imgcol) ) = BG;
					}
				}
				
				else
				{
					    *( MBuffer + ( imgrow*width + imgcol) ) = BG;
				}
		     }
		  } // end of for loop
		  
				
	    // Unconditional Pattern Matching -- Stage 2
				
		for(int imgrow = 1 ; imgrow < height-1 ; imgrow++)
		{
			for(int imgcol = 1 ; imgcol < width-1 ; imgcol++ )
			{
				int pix_intensity = (int)(*(MBuffer + (imgrow*width + imgcol) ));	
				int window_pattern = 0;
				
				if(pix_intensity == FG )
				{
					
					for(int k = 7 ; k >= 0 ; k--)
					{
						int uncond_window = (int)(*(MBuffer + ( (imgrow + window_coordinates[k].row)*width) + 
						                   (imgcol + window_coordinates[k].col) ));
						
						if( uncond_window == FG )
						{   
							//left shift with 1 and bitwise OR with 1 to get a 8 bit pattern for matching
							window_pattern = ( window_pattern << 1 ) | 1;
						}
						
						else
						{
							//left shift with 1 and bitwise OR with 0 to get a 8 bit pattern for matching
							window_pattern = ( window_pattern << 1) | 0 ;
						}
						
					}
					
					if( find( uncond_mask.begin() , uncond_mask.end() , window_pattern ) != uncond_mask.end() )
					{
						*( Out + ( imgrow*width + imgcol) ) = *( LocalBuffer + ( imgrow*width + imgcol) );
						
					}
					else
					{
						*( Out + ( imgrow*width + imgcol) ) = BG;
					}
				}
				
				
				else
				{
					    *( Out + ( imgrow*width + imgcol) ) = *( LocalBuffer + ( imgrow*width + imgcol) ) ;
				}
				
		     }
		  } // end of for loop
		  

			  
		  int comparison = memcmp(Out, LocalBuffer , (width*height));
		  
		  if( comparison == 0)
		  {
			  cout<<"Iteration: " << N << endl;
			  break;
		  }
		
		  for(int imgrow = 0; imgrow < height ; imgrow++)
		  {
			for(int imgcol = 0; imgcol < width ; imgcol++)
			{
				*( LocalBuffer + (imgrow*width + imgcol) )  = *( Out + (imgrow*width + imgcol) );
			}
		  }
   
    }// End of loop for Run times	
    
}


int counting(unsigned char* Img, unsigned char* LabelImg, int width, int height)
{
	FILE* fptr2;
	int Connect_Comp = 0;
	int Label_Comp = 0;
	int diff_size_star;
	vector <int> starsize;
	
	for(int imgrow = 0 ; imgrow < height ; imgrow++)
	{
		for(int imgcol = 0 ; imgcol < width ; imgcol++)
		{
			unsigned char in_pixval = *(Img + (imgrow*width + imgcol));
			unsigned char label_pixval = *(LabelImg + (imgrow*width + imgcol));
		
			if( in_pixval == 255 && label_pixval == 255 )
			{
				Connect_Comp = Connect_Comp + 1;
				Label_Comp = Connect_Comp;
				
				diff_size_star = FindCompDFS(Img,LabelImg,imgrow,imgcol,Label_Comp,width);
				starsize.push_back(diff_size_star);	
					
			}
		}
	}
      
    fptr2 =fopen("hist.txt","w");
	if(!(fptr2 == NULL))
    { 
		for(int i = 0 ; i< starsize.size(); i++)
		{
			fprintf(fptr2,"%d ",starsize[i]);
		}
	    
	}  			
			
	 fclose(fptr2);		
   return Connect_Comp; 
}


int FindCompDFS(unsigned char* Img, unsigned char* LabelImg, int imgrow, int imgcol, int Label_Comp,int width)
{ 
	vector <window_pos> window_coordinates = { {  0,  1} , 
	                                       {  -1,  1 },{  -1,  0},{  -1, -1}, 
	                                       {  0,  -1}, 
	                                       {  1,  -1}, {  1,  0} , {  1,  1} };
	vector <window_pos> stack;
	
	stack.clear();
	
	stack.push_back({imgrow , imgcol });
	
	int max_stack_size = 0;

	while( !(stack.empty()) )
	{		
		window_pos t = stack.back();
		max_stack_size++;
	    stack.pop_back();
	    *(LabelImg + (t.row*width + t.col) ) = Label_Comp;
	    
	    for(int k = 7 ; k >= 0 ; k-- )
		{
						
			if( *(Img + ( ( t.row + window_coordinates[k].row)*width) + (t.col + window_coordinates[k].col) ) == 255 &&
			      *(LabelImg + ( ( t.row + window_coordinates[k].row)*width) + (t.col + window_coordinates[k].col) ) == 255 )
			{
				
	              *(LabelImg + ( ( t.row + window_coordinates[k].row)*width) + (t.col + window_coordinates[k].col) ) = 0;
	              stack.push_back({ t.row + window_coordinates[k].row , t.col + window_coordinates[k].col });
	         }
	    }
	    
	}
	
	cout << "size :  " << max_stack_size << endl;
	
	return max_stack_size;

}







