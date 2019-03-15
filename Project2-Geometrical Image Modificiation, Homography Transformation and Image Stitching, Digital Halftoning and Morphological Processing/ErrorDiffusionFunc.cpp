#include "ErrorDiffusionFunc.h"
#include <cstring>
#include <math.h>


unsigned char* getpixelpos(unsigned char* Img , int i , int j , int width, const int bpp)
{
	return (Img+((i*width +j)*bpp));	
}

void FloydSteinbergError(unsigned char* Img,int width, int height, const int bpp,unsigned char* Buffer,unsigned char* OutputFloydStein )
{
	// Floyd-Steinberg Error Matrix
    
    unsigned char* PixelPos;
    unsigned char OriginalPixelIntensity, NewPixelIntensity;
    unsigned char Threshold_Factor = 127;
    memcpy(Buffer,Img,(width*height*bpp));
    double diffusion_error;
    
    for(int imgrow =0; imgrow < height; imgrow++)
	{
		for(int imgcol=0 ; imgcol < width ; imgcol++)
		{ 		
			//Serpentine Scanning
			
			if( (imgrow % 2 != 0) )
			{
				PixelPos  = getpixelpos(Buffer,imgrow,width-1-imgcol,width,bpp);
				int revcol = width-1-imgcol;
				OriginalPixelIntensity = *(PixelPos);
				
				if( OriginalPixelIntensity > Threshold_Factor )
				{
					NewPixelIntensity = 255;
				}
				else
				{
					NewPixelIntensity = 0 ;
				}
				
				*(OutputFloydStein + ((imgrow*width) + revcol)*bpp )  = NewPixelIntensity;		 
			    diffusion_error = OriginalPixelIntensity - NewPixelIntensity;
			    
			    	if( revcol-1 >= 0)
			    	{
					 *(Buffer + ((imgrow*width) + (revcol-1)))	         = *(Buffer + ((imgrow*width)     + (revcol-1)))	 + (diffusion_error * 7/16.0) ;
					}
					if( imgrow+1 < height)
					{
					 *(Buffer + (((imgrow+1)*width) + (revcol)) )	     = *(Buffer + (((imgrow+1)*width) + (revcol)))       + (diffusion_error * 5/16.0 ) ;
					  if(revcol+1 < width)
					  {
					    *(Buffer + (((imgrow+1)*width) + (revcol+1)) )	     = *(Buffer + (((imgrow+1)*width) + (revcol+1)))     + (diffusion_error * 3/16.0 ) ;
					  }
					
					  if( revcol-1 >= 0 )
					  {
						*(Buffer + (((imgrow+1)*width) + (revcol-1)) )	     = *(Buffer + (((imgrow+1)*width) + (revcol-1)))     + (diffusion_error * 1/16.0) ;
					  }
			        }
			
				
		    }
		    
		    else
		    {
				PixelPos  = getpixelpos(Buffer,imgrow,imgcol,width,bpp);
				OriginalPixelIntensity = *(PixelPos);
				
				if( OriginalPixelIntensity > Threshold_Factor )
				{
					NewPixelIntensity = 255;
				}
				else
				{
					NewPixelIntensity = 0 ;
				}
				
				*(OutputFloydStein + ((imgrow*width) + imgcol)*bpp )  = NewPixelIntensity;		 
			    diffusion_error = OriginalPixelIntensity - NewPixelIntensity;
			  
			  if( imgcol+1 < width )
			  {				
			   *(Buffer + ((imgrow*width) + (imgcol+1)))	         = *(Buffer + ((imgrow*width)     + (imgcol+1))) + (diffusion_error * 7/16.0) ;
		      }
		      
		      if( imgrow+1 < height )
		      {
			   *(Buffer + (((imgrow+1)*width) + (imgcol)) )	     = *(Buffer + (((imgrow+1)*width) + (imgcol)))   + (diffusion_error * 5/16.0) ;
			   if(imgcol+1 < width)
			   {
			     *(Buffer + (((imgrow+1)*width) + (imgcol+1)) )	 = *(Buffer + (((imgrow+1)*width) + (imgcol+1))) + (diffusion_error * 1/16.0) ;
		       }
		       if( imgcol-1 >= 0 )
		       {
			  *(Buffer + (((imgrow+1)*width) + (imgcol-1)) )	 = *(Buffer + (((imgrow+1)*width) + (imgcol-1))) + (diffusion_error * 3/16.0) ;	
		       }
		      }
		   }	
		   
		}
	}  // End of For Loop
	
}

void JJN(unsigned char* Img,int width, int height, const int bpp,unsigned char* Buffer,unsigned char* OutputJJN )
{
	// Jarvis, Judice & Ninke Matrix
	
	                 
    unsigned char* PixelPos;
    unsigned char OriginalPixelIntensity, NewPixelIntensity;
    unsigned char Threshold_Factor = 127;
    memcpy(Buffer,Img,(width*height*bpp));
    double diffusion_error;
    
    for(int imgrow =0; imgrow < height; imgrow++)
	{
		for(int imgcol=0 ; imgcol < width ; imgcol++)
		{ 		
			//Serpentine Scanning
			
			if( (imgrow % 2 != 0) )
			{
				PixelPos  = getpixelpos(Buffer,imgrow,width-1-imgcol,width,bpp);
				int revcol = width-1-imgcol;
				OriginalPixelIntensity = *(PixelPos);
				
				if( OriginalPixelIntensity > Threshold_Factor )
				{
					NewPixelIntensity = 255;
				}
				else
				{
					NewPixelIntensity = 0 ;
				}
				
				*(OutputJJN + ((imgrow*width) + revcol)*bpp )  = NewPixelIntensity;		 
			    diffusion_error = OriginalPixelIntensity - NewPixelIntensity;
			        
			        if(revcol-1 >= 0 )
			        {
			        *(Buffer+ ((imgrow*width)  + (revcol-1)) )		+=  (diffusion_error * 7/48.0) ;
				    }
				    if(revcol-2 >= 0 )
			        {
					*(Buffer+ ( (imgrow*width) + (revcol-2))  ) 	+=  (diffusion_error * 5/48.0) ;
				    }
				    
				    if( imgrow+1 < height)
				    {
						if(revcol-1 >= 0)
						{
					       *(Buffer+ ((imgrow+1)*width + (revcol-1)) ) 	+=  (diffusion_error * 5/48.0) ;
					    }
					    if(revcol-2 >= 0)
						{
					    
					         *(Buffer+ ((imgrow+1)*width + (revcol-2)) )	    +=  (diffusion_error * 3/48.0) ;
					    }
					    
					    *(Buffer+ ((imgrow+1)*width + (revcol)) ) 	    +=  (diffusion_error * 7/48.0) ;
					
						if( revcol+1 < width)
						{
						*(Buffer+ ((imgrow+1)*width + (revcol+1)) )	    +=  (diffusion_error * 5/48.0) ;
						}
						if( revcol+2 < width)
						{
						  *(Buffer+ ((imgrow+1)*width + (revcol+2)) )	    +=  (diffusion_error * 3/48.0) ;
						}
					}
					
					if( imgrow+2 < height)
				    {
					
					  *(Buffer+ ((imgrow+2)*width + (revcol)) )	    +=  (diffusion_error * 5/48.0) ;
					
					  if(revcol-1 >= 0 )
			          {
						*(Buffer+ ((imgrow+2)*width + (revcol-1)) ) 	+=  (diffusion_error * 3/48.0) ;
					  }
					  
					   if(revcol-2 >= 0 )
			           {
						*(Buffer+ ((imgrow+2)*width + (revcol-2)) ) 	+=  (diffusion_error * 1/48.0) ;
					   }
					   
					   if(  revcol+1 < width)
					   {
					      *(Buffer+ ((imgrow+2)*width + (revcol+1)) )	    +=  (diffusion_error * 3/48.0) ;
					   }
					   
					   if(  revcol+2 < width )
					   {
					       *(Buffer+ ((imgrow+2)*width + (revcol+2)) ) 	+=  (diffusion_error * 1/48.0) ;
					   }
					}
		
		     }
		
		      else
		      {
	
					PixelPos  = getpixelpos(Buffer,imgrow,imgcol,width,bpp);
					OriginalPixelIntensity = *(PixelPos);
					
					if( OriginalPixelIntensity > Threshold_Factor )
					{
						NewPixelIntensity = 255;
					}
					else
					{
						NewPixelIntensity = 0 ;
					}
					
					*(OutputJJN + ((imgrow*width) + imgcol)*bpp )  = NewPixelIntensity;		 
					diffusion_error = OriginalPixelIntensity - NewPixelIntensity;
							
							
					if( imgcol+1 < width)
					{		
						*(Buffer+ ((imgrow*width)  + (imgcol+1)) )		+=  (diffusion_error * 7/48.0) ;
				    }
				    
				    if( imgcol+2 < width)
					{	
					    *(Buffer+ ( (imgrow*width) + (imgcol+2))  ) 	+=  (diffusion_error * 5/48.0) ;
					}
					
					if( imgrow+1 < height )
					{
						 if( imgcol-1 >= 0)
						 {
							*(Buffer+ ((imgrow+1)*width + (imgcol-1)) ) 	+=  (diffusion_error * 5/48.0) ;
						 }
						 if( imgcol-2 >= 0 )
						 {
							*(Buffer+ ((imgrow+1)*width + (imgcol-2)) )	    +=  (diffusion_error * 3/48.0) ;
						 }
						 
						 
						 *(Buffer+ ((imgrow+1)*width + (imgcol)) ) 	    +=  (diffusion_error * 7/48.0) ;
						 
						 if( imgcol+1 < width )
						 {
						   *(Buffer+ ((imgrow+1)*width + (imgcol+1)) )	    +=  (diffusion_error * 5/48.0) ;
						 }
						 if( imgcol+1 < width )
						 {
							*(Buffer+ ((imgrow+1)*width + (imgcol+2)) )	    +=  (diffusion_error * 3/48.0) ;
						 }
				     }
				     
				     if( imgrow+2 < height )
				     {
					
						*(Buffer+ ((imgrow+2)*width + (imgcol)) )	    +=  (diffusion_error * 5/48.0) ;
						
						if( imgcol-1 >=0 )
						{
								*(Buffer+ ((imgrow+2)*width + (imgcol-1)) ) 	+=  (diffusion_error * 3/48.0) ;
						}
					    if( imgcol-2 >=0 )
						{
							*(Buffer+ ((imgrow+2)*width + (imgcol-2)) ) 	+=  (diffusion_error * 1/48.0) ;
						}
						if( imgcol+1 < width )
						{
							*(Buffer+ ((imgrow+2)*width + (imgcol+1)) )	    +=  (diffusion_error * 3/48.0) ;
						}
						if( imgcol+2 < width )
						{
							*(Buffer+ ((imgrow+2)*width + (imgcol+2)) ) 	+=  (diffusion_error * 1/48.0) ;
						}
					}			
			  }				
			
		   }	
		   
		}// End of For Loop
} 
				
void Stucki(unsigned char* Img,int width, int height, const int bpp,unsigned char* Buffer,unsigned char* OutputStucki )
{
	// Stucki
	
	unsigned char* PixelPos;
    unsigned char OriginalPixelIntensity, NewPixelIntensity;
    unsigned char Threshold_Factor = 127;
    memcpy(Buffer,Img,(width*height*bpp));
    double diffusion_error;
    
    for(int imgrow =0; imgrow < height; imgrow++)
	{
		for(int imgcol=0 ; imgcol < width ; imgcol++)
		{ 		
			//Serpentine Scanning
			
			if( (imgrow % 2 != 0) )
			{
				PixelPos  = getpixelpos(Buffer,imgrow,width-1-imgcol,width,bpp);
				int revcol = width-1-imgcol;
				OriginalPixelIntensity = *(PixelPos);
				
				if( OriginalPixelIntensity > Threshold_Factor )
				{
					NewPixelIntensity = 255;
				}
				else
				{
					NewPixelIntensity = 0 ;
				}
				
				*(OutputStucki + ((imgrow*width) + revcol)*bpp )  = NewPixelIntensity;		 
			    diffusion_error = OriginalPixelIntensity - NewPixelIntensity;
			        
			        if(revcol-1 >= 0 )
			        {
			        *(Buffer+ ((imgrow*width)  + (revcol-1)) )		+=  (diffusion_error * 8/42.0) ;
				    }
				    if(revcol-2 >= 0 )
			        {
					*(Buffer+ ( (imgrow*width) + (revcol-2))  ) 	+=  (diffusion_error * 4/42.0) ;
				    }
				    
				    if( imgrow+1 < height)
				    {
						if(revcol-1 >= 0)
						{
					       *(Buffer+ ((imgrow+1)*width + (revcol-1)) ) 	+=  (diffusion_error * 4/42.0) ;
					    }
					    if(revcol-2 >= 0)
						{
					    
					         *(Buffer+ ((imgrow+1)*width + (revcol-2)) )	    +=  (diffusion_error * 2/42.0) ;
					    }
					    
					    *(Buffer+ ((imgrow+1)*width + (revcol)) ) 	    +=  (diffusion_error * 8/42.0) ;
					
						if( revcol+1 < width)
						{
						*(Buffer+ ((imgrow+1)*width + (revcol+1)) )	    +=  (diffusion_error * 4/42.0) ;
						}
						if( revcol+2 < width)
						{
						  *(Buffer+ ((imgrow+1)*width + (revcol+2)) )	    +=  (diffusion_error * 2/42.0) ;
						}
					}
					
					if( imgrow+2 < height)
				    {
					
					  *(Buffer+ ((imgrow+2)*width + (revcol)) )	    +=  (diffusion_error * 4/42.0) ;
					
					  if(revcol-1 >= 0 )
			          {
						*(Buffer+ ((imgrow+2)*width + (revcol-1)) ) 	+=  (diffusion_error * 2/42.0) ;
					  }
					  
					   if(revcol-2 >= 0 )
			           {
						*(Buffer+ ((imgrow+2)*width + (revcol-2)) ) 	+=  (diffusion_error * 1/42.0) ;
					   }
					   
					   if(  revcol+1 < width)
					   {
					      *(Buffer+ ((imgrow+2)*width + (revcol+1)) )	    +=  (diffusion_error * 2/42.0) ;
					   }
					   
					   if(  revcol+2 < width )
					   {
					       *(Buffer+ ((imgrow+2)*width + (revcol+2)) ) 	+=  (diffusion_error * 1/42.0) ;
					   }
					}
		
		     }
		
		      else
		      {
	
					PixelPos  = getpixelpos(Buffer,imgrow,imgcol,width,bpp);
					OriginalPixelIntensity = *(PixelPos);
					
					if( OriginalPixelIntensity > Threshold_Factor )
					{
						NewPixelIntensity = 255;
					}
					else
					{
						NewPixelIntensity = 0 ;
					}
					
					*(OutputStucki + ((imgrow*width) + imgcol)*bpp )  = NewPixelIntensity;		 
					diffusion_error = OriginalPixelIntensity - NewPixelIntensity;
							
							
					if( imgcol+1 < width)
					{		
						*(Buffer+ ((imgrow*width)  + (imgcol+1)) )		+=  (diffusion_error * 8/42.0) ;
				    }
				    
				    if( imgcol+2 < width)
					{	
					    *(Buffer+ ( (imgrow*width) + (imgcol+2))  ) 	+=  (diffusion_error * 4/42.0) ;
					}
					
					if( imgrow+1 < height )
					{
						 if( imgcol-1 >= 0)
						 {
							*(Buffer+ ((imgrow+1)*width + (imgcol-1)) ) 	+=  (diffusion_error * 4/42.0) ;
						 }
						 if( imgcol-2 >= 0 )
						 {
							*(Buffer+ ((imgrow+1)*width + (imgcol-2)) )	    +=  (diffusion_error * 2/42.0) ;
						 }
						 
						 
						 *(Buffer+ ((imgrow+1)*width + (imgcol)) ) 	    +=  (diffusion_error * 8/42.0) ;
						 
						 if( imgcol+1 < width )
						 {
						   *(Buffer+ ((imgrow+1)*width + (imgcol+1)) )	    +=  (diffusion_error * 4/42.0) ;
						 }
						 if( imgcol+1 < width )
						 {
							*(Buffer+ ((imgrow+1)*width + (imgcol+2)) )	    +=  (diffusion_error * 2/42.0) ;
						 }
				     }
				     
				     if( imgrow+2 < height )
				     {
					
						*(Buffer+ ((imgrow+2)*width + (imgcol)) )	    +=  (diffusion_error * 4/42.0) ;
						
						if( imgcol-1 >=0 )
						{
								*(Buffer+ ((imgrow+2)*width + (imgcol-1)) ) 	+=  (diffusion_error * 2/42.0) ;
						}
					    if( imgcol-2 >=0 )
						{
							*(Buffer+ ((imgrow+2)*width + (imgcol-2)) ) 	+=  (diffusion_error * 1/42.0) ;
						}
						if( imgcol+1 < width )
						{
							*(Buffer+ ((imgrow+2)*width + (imgcol+1)) )	    +=  (diffusion_error * 2/42.0) ;
						}
						if( imgcol+2 < width )
						{
							*(Buffer+ ((imgrow+2)*width + (imgcol+2)) ) 	+=  (diffusion_error * 1/42.0) ;
						}
					}			
			  }				
			
		   }	
		   
		}// End of For Loop
} 		    
		    
