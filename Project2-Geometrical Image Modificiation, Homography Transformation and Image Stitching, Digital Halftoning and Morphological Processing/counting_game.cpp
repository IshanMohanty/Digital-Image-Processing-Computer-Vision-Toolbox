#include "counting_game.h"
#include <vector>
#include <iostream>

using namespace std;

int counting(unsigned char* Img, unsigned char* LabelImg, int width, int height)
{
	int Connect_Comp = 0;
	int Label_Comp = 0;
	
	for(int imgrow = 0 ; imgrow < height ; imgrow++)
	{
		for(int imgcol = 0 ; imgcol < width ; imgcol++)
		{
			unsigned char in_pixval = *(Img + (imgrow*width + imgcol));
			unsigned char label_pixval = *(LabelImg + (imgrow*width + imgcol));
		
			if( in_pixval == 0 && label_pixval == 255 )
			{
				Connect_Comp = Connect_Comp + 1;
				Label_Comp = Connect_Comp;
				
				FindCompDFS(Img,LabelImg,imgrow,imgcol,Label_Comp,width);
				
			}
		}
	}
			
   return Connect_Comp; 
}


void FindCompDFS(unsigned char* Img, unsigned char* LabelImg, int imgrow, int imgcol, int Label_Comp,int width)
{ 
	vector <window_pos_count> window_coordinates = { {  0,  1} , 
	                                       {  -1,  1 },{  -1,  0},{  -1, -1}, 
	                                       {  0,  -1}, 
	                                       {  1,  -1}, {  1,  0} , {  1,  1} };
	vector <window_pos_count> stack;
	
	stack.clear();
	
	stack.push_back({imgrow , imgcol });

	while( !(stack.empty()) )
	{		
		window_pos_count t = stack.back();
	    stack.pop_back();
	    *(LabelImg + (t.row*width + t.col) ) = Label_Comp;
	    
	    for(int k = 7 ; k >= 0 ; k-- )
		{
						
			if( *(Img + ( ( t.row + window_coordinates[k].row)*width) + (t.col + window_coordinates[k].col) ) == 0 &&
			      *(LabelImg + ( ( t.row + window_coordinates[k].row)*width) + (t.col + window_coordinates[k].col) ) == 255 )
			{
				
	              *(LabelImg + ( ( t.row + window_coordinates[k].row)*width) + (t.col + window_coordinates[k].col) ) = 0;
	              stack.push_back({ t.row + window_coordinates[k].row , t.col + window_coordinates[k].col });
	         }
	    }
	}
	

}
	
	
