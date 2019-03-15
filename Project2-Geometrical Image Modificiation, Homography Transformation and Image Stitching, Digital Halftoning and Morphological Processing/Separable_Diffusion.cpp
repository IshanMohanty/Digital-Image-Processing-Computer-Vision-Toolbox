#include <cstring>
#include <math.h>
#include <iostream>

#include "Separable_Diffusion.h"

using namespace std;


unsigned char* getpixelpos(unsigned char* Img , int i , int j , int width, const int bpp)
{
	return (Img+((i*width +j)*bpp));	
}

void separable_diffusion(unsigned char* Img,int width, int height, const int bpp,unsigned char* Buffer,unsigned char* Out )
{
   memcpy(Buffer,Img,(width*height*bpp));
   
   unsigned char* LocalBuffer = new unsigned char[width*height*bpp];  
   
   unsigned char colorcube[8][3] = { 
	                                 {0,0,0}, // white
									 {0,0,255}, //yellow
									 {0,255,0}, // Cyan
									 {255,0,0}, // Magenta
									 {0,255,255}, //Green
									 {255,0,255}, // Red
									 {255,255,0},  //Blue
									 {255,255,255} // Black
									 
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
    int buffervalue = 0;
    
    
    for(int imgrow =0; imgrow < height; imgrow++)
	{
		for(int imgcol=0 ; imgcol < width ; imgcol++)
		{ 		
			//Serpentine Scanning
			
			double squared_dist[8] = {0};
			double euclidean_dist[8] = {0};
			
		
			double least_dist = 1000.0;
			int vertex_min = -1;
			
			if( (imgrow % 2 != 0) )
			{
				PixelPos  = getpixelpos(Buffer,imgrow,width-1-imgcol,width,bpp);
				int revcol = width-1-imgcol;
				
				OriginalCyanPixelIntensity    = *(PixelPos + 0 );
			    OriginalMagentaPixelIntensity = *(PixelPos + 1 );
			    OriginalYellowPixelIntensity  = *(PixelPos + 2 );
			    
			    //Threshold Pixel Intensity Based on the CMY Cube
			      
			      
			      for( int v = 0 ; v < 8 ; v++)
			      {
					
						squared_dist[v] = pow(  ( colorcube[v][0] - *( Buffer + (imgrow*width + revcol)*bpp + 0 ) ) , 2 )  + 
												 pow(  ( colorcube[v][1] - *( Buffer + (imgrow*width + revcol)*bpp + 1 ) ) , 2 )  +
												 pow(  ( colorcube[v][2] - *( Buffer + (imgrow*width + revcol)*bpp + 2 ) ) , 2 );
						
						
						euclidean_dist[v] = pow( squared_dist[v]  , 0.5 ); 
					
						if( least_dist > euclidean_dist[v] )
						{
							least_dist = euclidean_dist[v];
							vertex_min = v;
						}	
				  }
			    
				  NewCyanPixelIntensity    = colorcube[vertex_min][0];
				  NewMagentaPixelIntensity = colorcube[vertex_min][1];
				  NewYellowPixelIntensity  = colorcube[vertex_min][2];
				  
					*(LocalBuffer + ((imgrow*width) + revcol)*bpp + 0 )  = NewCyanPixelIntensity;
					*(LocalBuffer + ((imgrow*width) + revcol)*bpp + 1 )  = NewMagentaPixelIntensity;	
					*(LocalBuffer + ((imgrow*width) + revcol)*bpp + 2 )  = NewYellowPixelIntensity;	
							 
					diffusion_error_cyan = OriginalCyanPixelIntensity - NewCyanPixelIntensity;
					diffusion_error_magenta = OriginalMagentaPixelIntensity - NewMagentaPixelIntensity;
					diffusion_error_yellow = OriginalYellowPixelIntensity - NewYellowPixelIntensity;
					
				if( revcol-1 >= 0)
				{
				 buffervalue = *(Buffer + ((imgrow*width)  + (revcol-1))*bpp + 0) + (diffusion_error_cyan * 7/16.0) ;
				 if(buffervalue > 255) buffervalue=255;
				 else if(buffervalue < 0) buffervalue = 0;
				 *(Buffer + ((imgrow*width) + (revcol-1))*bpp + 0) = buffervalue;
				  buffervalue = *(Buffer + ((imgrow*width)  + (revcol-1))*bpp + 1) + (diffusion_error_magenta * 7/16.0) ;
				  if(buffervalue > 255) buffervalue=255;
				  else if(buffervalue < 0) buffervalue = 0;
				  *(Buffer + ((imgrow*width) + (revcol-1))*bpp + 1) = buffervalue;
				   buffervalue = *(Buffer + ((imgrow*width)  + (revcol-1))*bpp + 2) + (diffusion_error_yellow * 7/16.0) ;
				   if(buffervalue > 255) buffervalue=255;
				   else if(buffervalue < 0) buffervalue = 0;
				   *(Buffer + ((imgrow*width) + (revcol-1))*bpp + 2) = buffervalue;
				}
				if( imgrow+1 < height)
				{
				 buffervalue = *(Buffer + (((imgrow+1)*width) + (revcol))*bpp + 0)  + (diffusion_error_cyan * 5/16.0 ) ;
				 if(buffervalue > 255) buffervalue=255;
				 else if(buffervalue < 0) buffervalue = 0;
				 *(Buffer + (((imgrow+1)*width) + (revcol))*bpp + 0) = buffervalue;
				 buffervalue = *(Buffer + (((imgrow+1)*width) + (revcol))*bpp + 1)  + (diffusion_error_magenta * 5/16.0 ) ;
				 if(buffervalue > 255) buffervalue=255;
				 else if(buffervalue < 0) buffervalue = 0;
				 *(Buffer + (((imgrow+1)*width) + (revcol))*bpp + 1 ) = buffervalue;
				 buffervalue = *(Buffer + (((imgrow+1)*width) + (revcol))*bpp + 2)  + (diffusion_error_yellow * 5/16.0 ) ;
				 if(buffervalue > 255) buffervalue=255;
				 else if(buffervalue < 0) buffervalue = 0;
				 *(Buffer + (((imgrow+1)*width) + (revcol))*bpp + 2) = buffervalue;
				 
				  if(revcol+1 < width)
				  {
					buffervalue = *(Buffer + (((imgrow+1)*width) + (revcol+1))*bpp + 0) + (diffusion_error_cyan * 3/16.0 ) ;
					if(buffervalue > 255) buffervalue=255;
					else if(buffervalue < 0) buffervalue = 0;
					*(Buffer + (((imgrow+1)*width) + (revcol+1))*bpp + 0)	= buffervalue;
					buffervalue = *(Buffer + (((imgrow+1)*width) + (revcol+1))*bpp + 1) + (diffusion_error_magenta * 3/16.0 ) ;
					if(buffervalue > 255) buffervalue=255;
					else if(buffervalue < 0) buffervalue = 0;
					*(Buffer + (((imgrow+1)*width) + (revcol+1))*bpp + 1)	= buffervalue;
					buffervalue = *(Buffer + (((imgrow+1)*width) + (revcol+1))*bpp + 2) + (diffusion_error_yellow * 3/16.0 ) ;
					if(buffervalue > 255) buffervalue=255;
					else if(buffervalue < 0) buffervalue = 0;
					*(Buffer + (((imgrow+1)*width) + (revcol+1))*bpp + 2)	= buffervalue;
				  }
				
				  if( revcol-1 >= 0 )
				  {
					buffervalue = *(Buffer + (((imgrow+1)*width) + (revcol-1))*bpp + 0) + (diffusion_error_cyan * 1/16.0) ;
					if(buffervalue > 255) buffervalue=255;
					else if(buffervalue < 0) buffervalue = 0;
					*(Buffer + (((imgrow+1)*width) + (revcol-1))*bpp + 0 )  = buffervalue;
					buffervalue = *(Buffer + (((imgrow+1)*width) + (revcol-1))*bpp + 1) + (diffusion_error_magenta * 1/16.0) ;
					if(buffervalue > 255) buffervalue=255;
					else if(buffervalue < 0) buffervalue = 0;
					*(Buffer + (((imgrow+1)*width) + (revcol-1))*bpp + 1 )  = buffervalue;
					buffervalue = *(Buffer + (((imgrow+1)*width) + (revcol-1))*bpp + 2 ) + (diffusion_error_yellow * 1/16.0) ;
					if(buffervalue > 255) buffervalue=255;
					else if(buffervalue < 0) buffervalue = 0;
					*(Buffer + (((imgrow+1)*width) + (revcol-1))*bpp + 2)  = buffervalue;
				  }
				}
			
				
		    } // end of IF
		    
		    else
		    {
				PixelPos  = getpixelpos(Buffer,imgrow,imgcol,width,bpp);
				
				OriginalCyanPixelIntensity    = *(PixelPos + 0 );
			    OriginalMagentaPixelIntensity = *(PixelPos + 1 );
			    OriginalYellowPixelIntensity  = *(PixelPos + 2 );
			    
			      //Threshold Pixel Intensity Based on the CMY Cube
			      
			      
			      for( int v = 0 ; v < 8 ; v++)
			      {
					
						squared_dist[v] = pow(  ( colorcube[v][0] - *( Buffer + (imgrow*width + imgcol)*bpp + 0 ) ) , 2 )  + 
												 pow(  ( colorcube[v][1] - *( Buffer + (imgrow*width + imgcol)*bpp + 1 ) ) , 2 )  +
												 pow(  ( colorcube[v][2] - *( Buffer + (imgrow*width + imgcol)*bpp + 2 ) ) , 2 );
						
						
						euclidean_dist[v] = pow( squared_dist[v]  , 0.5 ); 
					
						if( least_dist > euclidean_dist[v] )
						{
							least_dist = euclidean_dist[v];
							vertex_min = v;
						}	
				  }
			    
				  NewCyanPixelIntensity    = colorcube[vertex_min][0];
				  NewMagentaPixelIntensity = colorcube[vertex_min][1];
				  NewYellowPixelIntensity  = colorcube[vertex_min][2];
				  
					*(LocalBuffer + ((imgrow*width) + imgcol)*bpp + 0 )  = NewCyanPixelIntensity;
					*(LocalBuffer + ((imgrow*width) + imgcol)*bpp + 1 )  = NewMagentaPixelIntensity;	
					*(LocalBuffer + ((imgrow*width) + imgcol)*bpp + 2 )  = NewYellowPixelIntensity;	
					
					diffusion_error_cyan = OriginalCyanPixelIntensity - NewCyanPixelIntensity;
					diffusion_error_magenta = OriginalMagentaPixelIntensity - NewMagentaPixelIntensity;
					diffusion_error_yellow = OriginalYellowPixelIntensity - NewYellowPixelIntensity;
			
			  if( imgcol+1 < width )
			  {				
			   buffervalue = *(Buffer + ((imgrow*width) + (imgcol+1))*bpp + 0) + (diffusion_error_cyan * 7/16.0) ;
			   if(buffervalue > 255) buffervalue=255;
			   else if(buffervalue < 0) buffervalue = 0;
			   *(Buffer + ((imgrow*width) + (imgcol+1))*bpp + 0 ) = buffervalue;
			   buffervalue = *(Buffer + ((imgrow*width) + (imgcol+1))*bpp + 1) + (diffusion_error_magenta * 7/16.0) ;
			   if(buffervalue > 255) buffervalue=255;
			   else if(buffervalue < 0) buffervalue = 0;
			   *(Buffer + ((imgrow*width) + (imgcol+1))*bpp + 1 ) = buffervalue;
			   buffervalue = *(Buffer + ((imgrow*width) + (imgcol+1))*bpp + 2) + (diffusion_error_yellow * 7/16.0) ;
			   if(buffervalue > 255) buffervalue=255;
			   else if(buffervalue < 0) buffervalue = 0;
			   *(Buffer + ((imgrow*width) + (imgcol+1))*bpp + 2 ) = buffervalue;
		      }
		      
		      if( imgrow+1 < height )
		      {
				   buffervalue = *(Buffer + (((imgrow+1)*width) + (imgcol))*bpp + 0) + (diffusion_error_cyan * 5/16.0) ;
				   if(buffervalue > 255) buffervalue=255;
				   else if(buffervalue < 0) buffervalue = 0;
				   *(Buffer + (((imgrow+1)*width) + (imgcol))*bpp + 0 )	     = buffervalue;
				   buffervalue = *(Buffer + (((imgrow+1)*width) + (imgcol))*bpp + 1) + (diffusion_error_magenta * 5/16.0) ;
				   if(buffervalue > 255) buffervalue=255;
				   else if(buffervalue < 0) buffervalue = 0;
				   *(Buffer + (((imgrow+1)*width) + (imgcol))*bpp + 1 )	     = buffervalue;
				   buffervalue = *(Buffer + (((imgrow+1)*width) + (imgcol))*bpp + 2) + (diffusion_error_yellow * 5/16.0) ;
				   if(buffervalue > 255) buffervalue=255;
				   else if(buffervalue < 0) buffervalue = 0;
				   *(Buffer + (((imgrow+1)*width) + (imgcol))*bpp + 2 )	     = buffervalue;
				   
				   
				   if(imgcol+1 < width)
				   {
					 buffervalue = *(Buffer + (((imgrow+1)*width) + (imgcol+1))*bpp + 0) + (diffusion_error_cyan * 1/16.0) ;
					 if(buffervalue > 255) buffervalue=255;
					 else if(buffervalue < 0) buffervalue = 0;
					 *(Buffer + (((imgrow+1)*width) + (imgcol+1))*bpp + 0 )	 = buffervalue;
					 buffervalue = *(Buffer + (((imgrow+1)*width) + (imgcol+1))*bpp + 1) + (diffusion_error_magenta * 1/16.0) ;
					 if(buffervalue > 255) buffervalue=255;
					 else if(buffervalue < 0) buffervalue = 0;
					 *(Buffer + (((imgrow+1)*width) + (imgcol+1))*bpp + 1 )	 = buffervalue;
					 buffervalue = *(Buffer + (((imgrow+1)*width) + (imgcol+1))*bpp + 2) + (diffusion_error_yellow * 1/16.0) ;
					 if(buffervalue > 255) buffervalue=255;
					 else if(buffervalue < 0) buffervalue = 0;
					 *(Buffer + (((imgrow+1)*width) + (imgcol+1))*bpp + 2 )	 = buffervalue;
				   }
				   if( imgcol-1 >= 0 )
				   {
					buffervalue = *(Buffer + (((imgrow+1)*width) + (imgcol-1))*bpp + 0) + (diffusion_error_cyan * 3/16.0) ;	
					if(buffervalue > 255) buffervalue=255;
					else if(buffervalue < 0) buffervalue = 0;
					*(Buffer + (((imgrow+1)*width) + (imgcol-1))*bpp + 0 ) = buffervalue;
					buffervalue = *(Buffer + (((imgrow+1)*width) + (imgcol-1))*bpp + 1) + (diffusion_error_magenta * 3/16.0) ;	
					if(buffervalue > 255) buffervalue=255;
					else if(buffervalue < 0) buffervalue = 0;
					*(Buffer + (((imgrow+1)*width) + (imgcol-1))*bpp + 1 ) = buffervalue;
					buffervalue = *(Buffer + (((imgrow+1)*width) + (imgcol-1))*bpp + 2) + (diffusion_error_yellow * 3/16.0) ;	
					if(buffervalue > 255) buffervalue=255;
					else if(buffervalue < 0) buffervalue = 0;
					*(Buffer + (((imgrow+1)*width) + (imgcol-1))*bpp + 2 ) = buffervalue;
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
              
   
