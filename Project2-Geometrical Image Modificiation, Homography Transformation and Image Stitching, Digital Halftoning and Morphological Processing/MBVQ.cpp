#include <cstring>
#include <math.h>
#include <iostream>

#include "MBVQ.h"

using namespace std;

unsigned char* getpixelpos(unsigned char* Img , int i , int j , int width, const int bpp)
{
	return (Img+((i*width +j)*bpp));	
}

void MBVQ(unsigned char* Img,int width, int height, const int bpp,unsigned char* Buffer,unsigned char* Out )
{
   memcpy(Buffer,Img,(width*height*bpp));
   
   unsigned char* LocalBuffer = new unsigned char[width*height*bpp];  
   		
   
   unsigned char CMYW[4][3] = {
									 {0,255,0}, // Cyan
									 {255,0,0}, // Magenta
									 {0,0,255}, //yellow
									 {0,0,0} // white
								   };
					
								   
	unsigned char MYGC[4][3] = { 
									
									 {255,0,0}, // Magenta
									 {0,0,255}, //yellow
									 {0,255,255}, //Green
									  {0,255,0} // Cyan
									 
								   };


	unsigned char RGMY[4][3] = { 
	                    
									 {255,0,255}, // Red
									 {0,255,255}, //Green
									  {255,0,0}, // Magenta
									  {0,0,255} //yellow
						 
								   };	
								   
								   
								   
	  unsigned char KRGB[4][3] = { 
	                                 
									 {255,255,255}, // Black
									 {255,0,255}, // Red
									 {0,255,255}, //Green
									 {255,255,0}  //Blue
									 
									 
								   };	
					
								   
     unsigned char RGBM[4][3] = { 
	                           
									 
									 {255,0,255}, // Red
									 {0,255,255}, //Green
									 {255,255,0},  //Blue
									 {255,0,0} // Magenta
									 
								   };	
				
								   
     unsigned char CMGB[4][3] = { 
	                                 
									 {0,255,0}, // Cyan
									 {255,0,0}, // Magenta
									 {0,255,255}, //Green
									 {255,255,0}  //Blue
									
									 
								   };													   												   													
								   
   unsigned char red , green , blue , cyan , magenta , yellow;
   
     //CMY Represtantion
     
   for(int imgrow = 0; imgrow < height ; imgrow++)
   {
		for(int imgcol =0 ; imgcol < width ; imgcol++)
		{
			red = *( Img + ( imgrow*width + imgcol)*bpp + 0 );
			green = *( Img + ( imgrow*width + imgcol)*bpp + 1 );
			blue = *( Img + ( imgrow*width + imgcol)*bpp + 2 );
			
			cyan    = 255 - red;
            magenta = 255 - green;
            yellow  = 255 - blue;
            
            *( Buffer + ( imgrow*width + imgcol)*bpp + 0 ) = cyan;
			*( Buffer + ( imgrow*width + imgcol)*bpp + 1 ) = magenta;
			*( Buffer + ( imgrow*width + imgcol)*bpp + 2 ) = yellow;
		}
   }
   
   // Floyd-Steinberg Error Matrix
    
    unsigned char* PixelPos;
    unsigned char OriginalCyanPixelIntensity, OriginalMagentaPixelIntensity, OriginalYellowPixelIntensity;  
    unsigned char NewCyanPixelIntensity , NewMagentaPixelIntensity , NewYellowPixelIntensity;
    double diffusion_error_cyan = 0, diffusion_error_magenta = 0 , diffusion_error_yellow = 0 ;
    int buffervalue =0;
    
    
    for(int imgrow =0; imgrow < height; imgrow++)
	{
		for(int imgcol=0 ; imgcol < width ; imgcol++)
		{ 		
			//Serpentine Scanning
		
			int vertex_min = -1;
			
			if( (imgrow % 2 != 0) )
			{
				PixelPos  = getpixelpos(Buffer,imgrow,width-1-imgcol,width,bpp);
				int revcol = width-1-imgcol;
				
				for(int H = 0 ; H < 3 ; H++ )
				{
					if( *(PixelPos + H ) < 0 )
					{
						*(PixelPos + H ) = 0;
					}
					if( *(PixelPos + H) > 255 )
					{
						*(PixelPos + H ) = 255;
					}
			    }
				
					OriginalCyanPixelIntensity    = *(PixelPos + 0 );
					OriginalMagentaPixelIntensity = *(PixelPos + 1 );
					OriginalYellowPixelIntensity  = *(PixelPos + 2 );
			  
			    
			    //MVBQ Type
			    
			    int MBVQ_TYPE = Get_MBVQ_Type(Img,imgrow,revcol,bpp,width);
			    
			    
			    //Threshold Pixel Intensity Based on MVBQ Type
			    
			    switch(MBVQ_TYPE)
			    {
					case 1:   
					          vertex_min = getminvertex(Buffer,imgrow,revcol,bpp,CMYW,width);
					          NewCyanPixelIntensity    = CMYW[vertex_min][0];
							  NewMagentaPixelIntensity = CMYW[vertex_min][1];
							  NewYellowPixelIntensity  = CMYW[vertex_min][2];
					          break;
					          
					case 2:   
					          vertex_min = getminvertex(Buffer,imgrow,revcol,bpp,MYGC,width);
					          NewCyanPixelIntensity    = MYGC[vertex_min][0];
							  NewMagentaPixelIntensity = MYGC[vertex_min][1];
							  NewYellowPixelIntensity  = MYGC[vertex_min][2];	          
					          break;
					
					case 3:   
					          vertex_min = getminvertex(Buffer,imgrow,revcol,bpp,RGMY,width);
					          NewCyanPixelIntensity    = RGMY[vertex_min][0];
							  NewMagentaPixelIntensity = RGMY[vertex_min][1];
							  NewYellowPixelIntensity  = RGMY[vertex_min][2];	   
					          break;
					
					case 4:   
					          vertex_min = getminvertex(Buffer,imgrow,revcol,bpp,KRGB,width);
					          NewCyanPixelIntensity    = KRGB[vertex_min][0];
							  NewMagentaPixelIntensity = KRGB[vertex_min][1];
							  NewYellowPixelIntensity  = KRGB[vertex_min][2];	   
					          break;
					
					case 5:   vertex_min = getminvertex(Buffer,imgrow,revcol,bpp,RGBM,width);
					          NewCyanPixelIntensity    = RGBM[vertex_min][0];
							  NewMagentaPixelIntensity = RGBM[vertex_min][1];
							  NewYellowPixelIntensity  = RGBM[vertex_min][2];	
					          break;
					
					case 6:   vertex_min = getminvertex(Buffer,imgrow,revcol,bpp,CMGB,width);
					          NewCyanPixelIntensity    = CMGB[vertex_min][0];
							  NewMagentaPixelIntensity = CMGB[vertex_min][1];
							  NewYellowPixelIntensity  = CMGB[vertex_min][2];	   
					          break;
					          
					default:  
					          cout << " MBVQ type not among the six mentioned " << endl;
					          break;
			    }			
			    
				  
					*(LocalBuffer + ((imgrow*width) + revcol)*bpp + 0 )  = NewCyanPixelIntensity;
					*(LocalBuffer + ((imgrow*width) + revcol)*bpp + 1 )  = NewMagentaPixelIntensity;	
					*(LocalBuffer + ((imgrow*width) + revcol)*bpp + 2 )  = NewYellowPixelIntensity;	
							 
					diffusion_error_cyan = OriginalCyanPixelIntensity - NewCyanPixelIntensity;
					diffusion_error_magenta = OriginalMagentaPixelIntensity - NewMagentaPixelIntensity;
					diffusion_error_yellow = OriginalYellowPixelIntensity - NewYellowPixelIntensity;
					
				if( revcol-1 >= 0)
				{
				 buffervalue = *(Buffer + ((imgrow*width)  + (revcol-1))*bpp + 0) + (diffusion_error_cyan * 7/16.0) ;
				 if(buffervalue > 255) buffervalue = 255;
				 else if(buffervalue < 0) buffervalue = 0;
				 *(Buffer + ((imgrow*width) + (revcol-1))*bpp + 0)= buffervalue;
				  buffervalue = *(Buffer + ((imgrow*width)  + (revcol-1))*bpp + 1) + (diffusion_error_magenta * 7/16.0) ;
				  if(buffervalue > 255) buffervalue = 255;
				  else if(buffervalue < 0) buffervalue = 0;
				  *(Buffer + ((imgrow*width) + (revcol-1))*bpp + 1)= buffervalue;
				   buffervalue = *(Buffer + ((imgrow*width)  + (revcol-1))*bpp + 2) + (diffusion_error_yellow * 7/16.0) ;
				   if(buffervalue > 255) buffervalue = 255;
				   else if(buffervalue < 0) buffervalue = 0;
				   *(Buffer + ((imgrow*width) + (revcol-1))*bpp + 2)= buffervalue;
				}
				if( imgrow+1 < height)
				{
				 buffervalue = *(Buffer + (((imgrow+1)*width) + (revcol))*bpp + 0)  + (diffusion_error_cyan * 5/16.0 ) ;
				 if(buffervalue > 255) buffervalue = 255;
				 else if(buffervalue < 0) buffervalue = 0;
				 *(Buffer + (((imgrow+1)*width) + (revcol))*bpp + 0)= buffervalue;
				 buffervalue = *(Buffer + (((imgrow+1)*width) + (revcol))*bpp + 1)  + (diffusion_error_magenta * 5/16.0 ) ;
				 if(buffervalue > 255) buffervalue = 255;
				 else if(buffervalue < 0) buffervalue = 0;
				 *(Buffer + (((imgrow+1)*width) + (revcol))*bpp + 1 )= buffervalue;
				 buffervalue = *(Buffer + (((imgrow+1)*width) + (revcol))*bpp + 2)  + (diffusion_error_yellow * 5/16.0 ) ;
				 if(buffervalue > 255) buffervalue = 255;
				 else if(buffervalue < 0) buffervalue = 0;
				 *(Buffer + (((imgrow+1)*width) + (revcol))*bpp + 2)= buffervalue;
				 
				  if(revcol+1 < width)
				  {
					buffervalue	= *(Buffer + (((imgrow+1)*width) + (revcol+1))*bpp + 0) + (diffusion_error_cyan * 3/16.0 ) ;
					if(buffervalue > 255) buffervalue = 255;
					else if(buffervalue < 0) buffervalue = 0;
					*(Buffer + (((imgrow+1)*width) + (revcol+1))*bpp + 0)= buffervalue;
					buffervalue	= *(Buffer + (((imgrow+1)*width) + (revcol+1))*bpp + 1) + (diffusion_error_magenta * 3/16.0 ) ;
					if(buffervalue > 255) buffervalue = 255;
					else if(buffervalue < 0) buffervalue = 0;
					*(Buffer + (((imgrow+1)*width) + (revcol+1))*bpp + 1)= buffervalue;
					buffervalue	= *(Buffer + (((imgrow+1)*width) + (revcol+1))*bpp + 2) + (diffusion_error_yellow * 3/16.0 ) ;
					if(buffervalue > 255) buffervalue = 255;
					else if(buffervalue < 0) buffervalue = 0;
					*(Buffer + (((imgrow+1)*width) + (revcol+1))*bpp + 2)= buffervalue;
				  }
				
				  if( revcol-1 >= 0 )
				  {
					buffervalue = *(Buffer + (((imgrow+1)*width) + (revcol-1))*bpp + 0) + (diffusion_error_cyan * 1/16.0) ;
					if(buffervalue > 255) buffervalue = 255;
					else if(buffervalue < 0) buffervalue = 0;
					*(Buffer + (((imgrow+1)*width) + (revcol-1))*bpp + 0 ) = buffervalue;
					buffervalue = *(Buffer + (((imgrow+1)*width) + (revcol-1))*bpp + 1) + (diffusion_error_magenta * 1/16.0) ;
					if(buffervalue > 255) buffervalue = 255;
					else if(buffervalue < 0) buffervalue = 0;
					*(Buffer + (((imgrow+1)*width) + (revcol-1))*bpp + 1 ) = buffervalue;
					buffervalue = *(Buffer + (((imgrow+1)*width) + (revcol-1))*bpp + 2 ) + (diffusion_error_yellow * 1/16.0) ;
					if(buffervalue > 255) buffervalue = 255;
					else if(buffervalue < 0) buffervalue = 0;
					*(Buffer + (((imgrow+1)*width) + (revcol-1))*bpp + 2) = buffervalue;
				  }
				}
			
				
		    } // end of IF
		    
		    else
		    {
				PixelPos  = getpixelpos(Buffer,imgrow,imgcol,width,bpp);
				
				
					OriginalCyanPixelIntensity    = *(PixelPos + 0 );
					OriginalMagentaPixelIntensity = *(PixelPos + 1 );
					OriginalYellowPixelIntensity  = *(PixelPos + 2 );
			    
			     //MVBQ Type
			    
			    int MBVQ_TYPE = Get_MBVQ_Type(Img,imgrow,imgcol,bpp,width);
			    
			  //Threshold Pixel Intensity Based on MVBQ Type
			    
			    switch(MBVQ_TYPE)
			    {
					case 1:   
					          vertex_min = getminvertex(Buffer,imgrow,imgcol,bpp,CMYW,width);
					          NewCyanPixelIntensity    = CMYW[vertex_min][0];
							  NewMagentaPixelIntensity = CMYW[vertex_min][1];
							  NewYellowPixelIntensity  = CMYW[vertex_min][2];
					          break;
					          
					case 2:   
					          vertex_min = getminvertex(Buffer,imgrow,imgcol,bpp,MYGC,width);
					          NewCyanPixelIntensity    = MYGC[vertex_min][0];
							  NewMagentaPixelIntensity = MYGC[vertex_min][1];
							  NewYellowPixelIntensity  = MYGC[vertex_min][2];	          
					          break;
					
					case 3:   
					          vertex_min = getminvertex(Buffer,imgrow,imgcol,bpp,RGMY,width);
					          NewCyanPixelIntensity    = RGMY[vertex_min][0];
							  NewMagentaPixelIntensity = RGMY[vertex_min][1];
							  NewYellowPixelIntensity  = RGMY[vertex_min][2];	   
					          break;
					
					case 4:   
					          vertex_min = getminvertex(Buffer,imgrow,imgcol,bpp,KRGB,width);
					          NewCyanPixelIntensity    = KRGB[vertex_min][0];
							  NewMagentaPixelIntensity = KRGB[vertex_min][1];
							  NewYellowPixelIntensity  = KRGB[vertex_min][2];	   
					          break;
					
					case 5:   vertex_min = getminvertex(Buffer,imgrow,imgcol,bpp,RGBM,width);
					          NewCyanPixelIntensity    = RGBM[vertex_min][0];
							  NewMagentaPixelIntensity = RGBM[vertex_min][1];
							  NewYellowPixelIntensity  = RGBM[vertex_min][2];	
					          break;
					
					case 6:   vertex_min = getminvertex(Buffer,imgrow,imgcol,bpp,CMGB,width);
					          NewCyanPixelIntensity    = CMGB[vertex_min][0];
							  NewMagentaPixelIntensity = CMGB[vertex_min][1];
							  NewYellowPixelIntensity  = CMGB[vertex_min][2];	   
					          break;
					          
					default:  
					          cout << " MBVQ type not among the six mentioned " << endl;
					          break;
			    }			
			      
			      
				  
					*(LocalBuffer + ((imgrow*width) + imgcol)*bpp + 0 )  = NewCyanPixelIntensity;
					*(LocalBuffer + ((imgrow*width) + imgcol)*bpp + 1 )  = NewMagentaPixelIntensity;	
					*(LocalBuffer + ((imgrow*width) + imgcol)*bpp + 2 )  = NewYellowPixelIntensity;	
					
					diffusion_error_cyan = OriginalCyanPixelIntensity - NewCyanPixelIntensity;
					diffusion_error_magenta = OriginalMagentaPixelIntensity - NewMagentaPixelIntensity;
					diffusion_error_yellow = OriginalYellowPixelIntensity - NewYellowPixelIntensity;
			
			  if( imgcol+1 < width )
			  {				
			   buffervalue = *(Buffer + ((imgrow*width) + (imgcol+1))*bpp + 0) + (diffusion_error_cyan * 7/16.0) ;
			   if(buffervalue > 255) buffervalue = 255;
			   else if(buffervalue < 0) buffervalue = 0;
			   *(Buffer + ((imgrow*width) + (imgcol+1))*bpp + 0 )= buffervalue;
			   buffervalue = *(Buffer + ((imgrow*width) + (imgcol+1))*bpp + 1) + (diffusion_error_magenta * 7/16.0) ;
			   if(buffervalue > 255) buffervalue = 255;
			   else if(buffervalue < 0) buffervalue = 0;
			   *(Buffer + ((imgrow*width) + (imgcol+1))*bpp + 1 )= buffervalue;
			   buffervalue = *(Buffer + ((imgrow*width) + (imgcol+1))*bpp + 2) + (diffusion_error_yellow * 7/16.0) ;
			   if(buffervalue > 255) buffervalue = 255;
			   else if(buffervalue < 0) buffervalue = 0;
			   *(Buffer + ((imgrow*width) + (imgcol+1))*bpp + 2 )= buffervalue;
		      }
		      
		      if( imgrow+1 < height )
		      {
				   buffervalue = *(Buffer + (((imgrow+1)*width) + (imgcol))*bpp + 0) + (diffusion_error_cyan * 5/16.0) ;
				   if(buffervalue > 255) buffervalue = 255;
				   else if(buffervalue < 0) buffervalue = 0;
				   *(Buffer + (((imgrow+1)*width) + (imgcol))*bpp + 0 )	    = buffervalue;
				   buffervalue = *(Buffer + (((imgrow+1)*width) + (imgcol))*bpp + 1) + (diffusion_error_magenta * 5/16.0) ;
				   if(buffervalue > 255) buffervalue = 255;
				   else if(buffervalue < 0) buffervalue = 0;
				   *(Buffer + (((imgrow+1)*width) + (imgcol))*bpp + 1 )	    = buffervalue;
				   buffervalue = *(Buffer + (((imgrow+1)*width) + (imgcol))*bpp + 2) + (diffusion_error_yellow * 5/16.0) ;
				   if(buffervalue > 255) buffervalue = 255;
				   else if(buffervalue < 0) buffervalue = 0;
				   *(Buffer + (((imgrow+1)*width) + (imgcol))*bpp + 2 )	    = buffervalue;
				   
				   
				   if(imgcol+1 < width)
				   {
					 buffervalue = *(Buffer + (((imgrow+1)*width) + (imgcol+1))*bpp + 0) + (diffusion_error_cyan * 1/16.0) ;
					 if(buffervalue > 255) buffervalue = 255;
					 else if(buffervalue < 0) buffervalue = 0;
					 *(Buffer + (((imgrow+1)*width) + (imgcol+1))*bpp + 0 )	= buffervalue;
					 buffervalue = *(Buffer + (((imgrow+1)*width) + (imgcol+1))*bpp + 1) + (diffusion_error_magenta * 1/16.0) ;
					 if(buffervalue > 255) buffervalue = 255;
					 else if(buffervalue < 0) buffervalue = 0;
					 *(Buffer + (((imgrow+1)*width) + (imgcol+1))*bpp + 1 )	= buffervalue;
					 buffervalue = *(Buffer + (((imgrow+1)*width) + (imgcol+1))*bpp + 2) + (diffusion_error_yellow * 1/16.0) ;
					 if(buffervalue > 255) buffervalue = 255;
					 else if(buffervalue < 0) buffervalue = 0;
					 *(Buffer + (((imgrow+1)*width) + (imgcol+1))*bpp + 2 )	= buffervalue;
				   }
				   if( imgcol-1 >= 0 )
				   {
					buffervalue = *(Buffer + (((imgrow+1)*width) + (imgcol-1))*bpp + 0) + (diffusion_error_cyan * 3/16.0) ;	
					if(buffervalue > 255) buffervalue = 255;
					else if(buffervalue < 0) buffervalue = 0;
					*(Buffer + (((imgrow+1)*width) + (imgcol-1))*bpp + 0 )= buffervalue;
					buffervalue = *(Buffer + (((imgrow+1)*width) + (imgcol-1))*bpp + 1) + (diffusion_error_magenta * 3/16.0) ;	
					if(buffervalue > 255) buffervalue = 255;
					else if(buffervalue < 0) buffervalue = 0;
					*(Buffer + (((imgrow+1)*width) + (imgcol-1))*bpp + 1 )= buffervalue;
					buffervalue = *(Buffer + (((imgrow+1)*width) + (imgcol-1))*bpp + 2) + (diffusion_error_yellow * 3/16.0) ;	
					if(buffervalue > 255) buffervalue = 255;
					else if(buffervalue < 0) buffervalue = 0;
					*(Buffer + (((imgrow+1)*width) + (imgcol-1))*bpp + 2 )= buffervalue;
				   }
		      }
		   }	// end of else
		   
		}
	}  // End of For Loop
	
	
	// RGB Representation
	
   for(int imgrow = 0; imgrow < height ; imgrow++)
   {
		for(int imgcol =0 ; imgcol < width ; imgcol++)
		{
			cyan = *( LocalBuffer + ( imgrow*width + imgcol)*bpp + 0 );
			magenta = *( LocalBuffer + ( imgrow*width + imgcol)*bpp + 1 );
			yellow = *( LocalBuffer + ( imgrow*width + imgcol)*bpp + 2 );
			
			red    = 255 - cyan;
            green = 255 - magenta;
            blue  = 255 - yellow;
            
            *( Out + ( imgrow*width + imgcol)*bpp + 0 ) = red;
			*( Out + ( imgrow*width + imgcol)*bpp + 1 ) = green;
			*( Out + ( imgrow*width + imgcol)*bpp + 2 ) = blue;
		}
   }
}


//Get MVBQ type

int Get_MBVQ_Type(unsigned char* Img, int i , int j , int bpp, int width)
{
	unsigned char red = *(Img + (i*width + j)*bpp + 0);
	unsigned char green = *(Img + (i*width + j)*bpp + 1);
	unsigned char blue = *(Img + (i*width + j)*bpp + 2);

	if((red+green) > 255) 
	{
		if((green+blue) > 255) 
		{
			if((red+green+blue) > 510) 
			{
				return 1; //CMYW
			} 
			else 
			{
				return 2; //MYGC
			}
		} 
		else 
		{
			return 3; //RGMY
		}
	} 
	
	else 
	{
		if(!((green+blue) > 255)) 
		{
			if(!((red+green+blue) > 255)) 
			{
				return 4; //KRGB
			} 
			else 
			{
				return 5; //RGBM
			}
		} 
		
		else 
		{
			return 6; //CMGB
		}
	}
}


int getminvertex(unsigned char* Buffer,int i , int j , int bpp , unsigned char tetra_color[4][3] , int width )
{
		        double squared_dist[4] = {0};
		    	double euclidean_dist[4] = {0};
		
			    double least_dist = 1000.0;
			    int min_vertex = -1;
	
	             for( int v = 0 ; v < 4 ; v++)
			      {
					
						squared_dist[v] = pow(  ( tetra_color[v][0] - *( Buffer + (i*width + j)*bpp + 0 ) ) , 2 )  + 
												 pow(  ( tetra_color[v][1] - *( Buffer + (i*width + j)*bpp + 1 ) ) , 2 )  +
												 pow(  ( tetra_color[v][2] - *( Buffer + (i*width + j)*bpp + 2 ) ) , 2 );
						
						
						euclidean_dist[v] = pow( squared_dist[v]  , 0.5 ); 
					
						if( least_dist > euclidean_dist[v] )
						{
							least_dist = euclidean_dist[v];
							min_vertex = v;
						}	
				  }
				  
				  return min_vertex;
}
