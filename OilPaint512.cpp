#include <iostream>
#include <fstream>
#include <cmath> 
#include <cstdio>
#include <stdlib.h>


using namespace std;

unsigned char * getpixel(unsigned char* Img , int i , int j , int width , int height , int bpp);

void quantize_512(unsigned char* Img,int width , int height , int bpp, unsigned char * Tempbuff, unsigned char* tempred,unsigned char* tempgreen, unsigned char* tempblue);

void oilpaint(unsigned char* Tempbuff,int width , int height , int bpp, unsigned char* Out, int N);

unsigned char * getpixel(unsigned char* Image , int i , int j , int width , int height , int bpp)
{
	return (Image +((i*width +j)*bpp));
}

void quantize_512(unsigned char* Img,int width , int height , int bpp, unsigned char * Tempbuff, unsigned char* tempred,unsigned char* tempgreen, unsigned char* tempblue)
{
	for(int i = 0 ;i < height ;i++)
	{
		for(int j=0 ; j < width ;j++)
		{
			//red
			tempred = (Img + ((i*width + j)*bpp) + 0);
			
			if( *(tempred) >=0 && *(tempred) <= 31)
			{
				*(Tempbuff + ((i*width + j)*bpp) + 0) = 15;
			}
			else if( *(tempred) > 31 && *(tempred) <= 63)
			{
				*(Tempbuff + ((i*width + j)*bpp) + 0) = 47;
			}
			else if(*(tempred) > 63 && *(tempred) <= 95)
			{
				*(Tempbuff + ((i*width + j)*bpp) + 0) = 79;
			}
			else if(*(tempred) > 95 && *(tempred) <= 127)
			{
				*(Tempbuff + ((i*width + j)*bpp) + 0) = 111;
			}
			else if(*(tempred) > 127 && *(tempred) <= 159)
			{
				*(Tempbuff + ((i*width + j)*bpp) + 0) = 143;
			}
			else if( *(tempred) > 159 && *(tempred) <= 191)
			{
				*(Tempbuff + ((i*width + j)*bpp) + 0) = 175;
			}
			else if(*(tempred) > 191 && *(tempred) <= 223)
			{
				*(Tempbuff + ((i*width + j)*bpp) + 0) = 207;
			}
			else if(*(tempred) > 223 && *(tempred) <= 255)
			{
				*(Tempbuff + ((i*width + j)*bpp) + 0) = 239;
			}
			else
			{
				cout<<"wrong gray level in input pixel"<<endl;
			}
			
			//Green
			
			tempgreen = (Img + ((i*width + j)*bpp) + 1);
			
			if( *(tempgreen) >=0 && *(tempgreen) <= 31)
			{
				*(Tempbuff + ((i*width + j)*bpp) + 1) = 15;
			}
			else if( *(tempgreen) > 31 && *(tempgreen) <= 63)
			{
				*(Tempbuff + ((i*width + j)*bpp) + 1) = 47;
			}
			else if(*(tempgreen) > 63 && *(tempgreen) <= 95)
			{
				*(Tempbuff + ((i*width + j)*bpp) + 1) = 79;
			}
			else if(*(tempgreen) > 95 && *(tempgreen) <= 127)
			{
				*(Tempbuff + ((i*width + j)*bpp) + 1) = 111;
			}
			else if(*(tempgreen) > 127 && *(tempgreen) <= 159)
			{
				*(Tempbuff + ((i*width + j)*bpp) + 1) = 143;
			}
			else if( *(tempgreen) > 159 && *(tempgreen) <= 191)
			{
				*(Tempbuff + ((i*width + j)*bpp) + 1) = 175;
			}
			else if(*(tempgreen) > 191 && *(tempgreen) <= 223)
			{
				*(Tempbuff + ((i*width + j)*bpp) + 1) = 207;
			}
			else if(*(tempgreen) > 223 && *(tempgreen) <= 255)
			{
				*(Tempbuff + ((i*width + j)*bpp) + 1) = 239;
			}
			else
			{
				cout<<"wrong gray level in input pixel"<<endl;
			}
			
			//Blue
			
			tempblue = (Img + ((i*width + j)*bpp) + 2);
			
			if( *(tempblue) >=0 && *(tempblue) <= 31)
			{
				*(Tempbuff + ((i*width + j)*bpp) + 2) = 15;
			}
			else if( *(tempblue) > 31 && *(tempblue) <= 63)
			{
				*(Tempbuff + ((i*width + j)*bpp) + 2) = 47;
			}
			else if(*(tempblue) > 63 && *(tempblue) <= 95)
			{
				*(Tempbuff + ((i*width + j)*bpp) + 2) = 79;
			}
			else if(*(tempblue) > 95 && *(tempblue) <= 127)
			{
				*(Tempbuff + ((i*width + j)*bpp) + 2) = 111;
			}
			else if(*(tempblue) > 127 && *(tempblue) <= 159)
			{
				*(Tempbuff + ((i*width + j)*bpp) + 2) = 143;
			}
			else if( *(tempblue) > 159 && *(tempblue) <= 191)
			{
				*(Tempbuff + ((i*width + j)*bpp) + 2) = 175;
			}
			else if(*(tempblue) > 191 && *(tempblue) <= 223)
			{
				*(Tempbuff + ((i*width + j)*bpp) + 2) = 207;
			}
			else if(*(tempblue) > 223 && *(tempblue) <= 255)
			{
				*(Tempbuff + ((i*width + j)*bpp) + 2) = 239;
			}
			else
			{
				cout<<"wrong gray level in input pixel"<<endl;
			}	
			 
	   }
	}   // end of for loops
}


void oilpaint(unsigned char* Tempbuff,int width , int height , int bpp, unsigned char* Out,int N)
{ 
	  int arrayred_8[8] = {0};
	  int arraygreen_8[8] = {0};
	  int arrayblue_8[8] = {0};
	
	
	int n,m; //relative pixel position	
	
	unsigned char * temp = NULL;
	
	for(int i = 0; i<height ; i++)
	{
		for(int j=0 ; j<width ; j++)
		{
			 
	               for(int k= (-1*(N/2)) ; k <= (N/2) ; k++)
	               {
		                for(int h = (-1*(N/2)) ; h <= (N/2) ; h++)
		                {

					                  n = i + k;
					                  m = j + h;

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
																	 
										temp = getpixel(Tempbuff,n,m,width,height,bpp);
									
									
										//red

										switch( *(temp+0) )
										{
											case 15: arrayred_8[0]++;

												 break;

											case 47: arrayred_8[1]++;
												 break;

											case 79: arrayred_8[2]++;
												  break;

											case 111: arrayred_8[3]++;
												  break; 
											
											case 143: arrayred_8[4]++;
												  break; 
										    
										    case 175: arrayred_8[5]++;
												  break; 
											
											case 207: arrayred_8[6]++;
												  break; 
											
											case 239: arrayred_8[7]++;
												  break; 
										    
											default:  //cout<<"incorrect quantized red value"<<endl;
												  break;
										}
										
										//Green

										switch( *(temp+1) )
										{
											case 15: arraygreen_8[0]++;

												 break;

											case 47: arraygreen_8[1]++;
												 break;

											case 79: arraygreen_8[2]++;
												  break;

											case 111: arraygreen_8[3]++;
										          break; 
											
											case 143: arraygreen_8[4]++;
												  break; 
										    
										    case 175: arraygreen_8[5]++;
												  break; 
											
											case 207: arraygreen_8[6]++;
												  break; 
											
											case 239: arraygreen_8[7]++;
												  break; 
										    
											default:  //cout<<"incorrect quantized green value"<<endl;
												  break;
										}
										
										//Blue

										switch( *(temp+2) )
										{
											case 15: arrayblue_8[0]++;

												 break;

											case 47: arrayblue_8[1]++;
												 break;

											case 79: arrayblue_8[2]++;
												  break;

											case 111: arrayblue_8[3]++;
												  break; 
											
											case 143: arrayblue_8[4]++;
												  break; 
										    
										    case 175: arrayblue_8[5]++;
												  break; 
											
											case 207: arrayblue_8[6]++;
												  break; 
											
											case 239: arrayblue_8[7]++;
												  break; 
										    
											default:  //cout<<"incorrect quantized blue value"<<endl;
												  break;
										}
									
								
				   }
		        } // end of k and h for loop
		        
           
		       //red
		       
		       int maxredindex = 0;
		       
		       for(int l=0; l<8; l++)
		       {
				  if(arrayred_8[maxredindex] <= arrayred_8[l+1])
				  {
					   maxredindex = l+1;
				  }
			   }			   

		       if( maxredindex == 0)
		       {
			       *(Out + ((i*width + j)*bpp) + 0) = 15;
		       }
		       else if( maxredindex == 1)
		       {
			       *(Out + ((i*width + j)*bpp) + 0) = 47;
		       }
		       else if( maxredindex == 2)
		       {
			       *(Out + ((i*width + j)*bpp) + 0) = 79;
		       }
		       else if( maxredindex == 3 )
		       {
			       *(Out + ((i*width + j)*bpp) + 0) = 111;
		       }
		       else if( maxredindex == 4 )
		       {
				   *(Out + ((i*width + j)*bpp) + 0) = 143;
			   }
			   else if( maxredindex == 5 )
		       {
				   *(Out + ((i*width + j)*bpp) + 0) = 175;
			   }
			   else if( maxredindex == 6 )
		       {
				   *(Out + ((i*width + j)*bpp) + 0) = 207;
			   }
			   else if( maxredindex == 7 )
		       {
				   *(Out + ((i*width + j)*bpp) + 0) = 239;
			   }
			  
			  
		       //green
               
               int maxgreenindex = 0;
		       
		       for(int l=0; l<8; l++)
		       {
				  if(arraygreen_8[maxgreenindex] <= arraygreen_8[l+1])
				  {
					   maxgreenindex = l+1;
				  }
			   }

		       if( maxgreenindex == 0)
		       {
			       *(Out + ((i*width + j)*bpp) + 1) = 15;
		       }
		       else if( maxgreenindex == 1)
		       {
			       *(Out + ((i*width + j)*bpp) + 1) = 47;
		       }
		       else if( maxgreenindex == 2)
		       {
			       *(Out + ((i*width + j)*bpp) + 1) = 79;
		       }
		       else if( maxgreenindex == 3 )
		       {
			       *(Out + ((i*width + j)*bpp) + 1) = 111;
		       }
		       else if( maxgreenindex == 4 )
		       {
				   *(Out + ((i*width + j)*bpp) + 1) = 143;
			   }
			   else if( maxgreenindex == 5 )
		       {
				   *(Out + ((i*width + j)*bpp) + 1) = 175;
			   }
			   else if( maxgreenindex == 6 )
		       {
				   *(Out + ((i*width + j)*bpp) + 1) = 207;
			   }
			   else if( maxgreenindex == 7 )
		       {
				   *(Out + ((i*width + j)*bpp) + 1) = 239;
			   }
			   

		       //Blue

		       int maxblueindex=0;
		       for( int l=0 ; l < 8 ; l++)
		       {
			       if(arrayblue_8[maxblueindex] <= arrayblue_8[l+1])
			       {
				       maxblueindex = l+1;
			       }
		       }

		       if( maxblueindex == 0)
		       {
			       *(Out + ((i*width + j)*bpp) + 2) = 15;
		       }
		       else if( maxblueindex == 1)
		       {
			       *(Out + ((i*width + j)*bpp) + 2) = 47;
		       }
		       else if( maxblueindex == 2)
		       {
			       *(Out + ((i*width + j)*bpp) + 2) = 79;
		       }
		       else if( maxblueindex == 3 )
		       {
			       *(Out + ((i*width + j)*bpp) + 2) = 111;
		       }
		       else if( maxblueindex == 4)
		       {
			       *(Out + ((i*width + j)*bpp) + 2) = 143;
		       }
		       else if( maxblueindex == 5)
		       {
			       *(Out + ((i*width + j)*bpp) + 2) = 175;
		       }
		       else if( maxblueindex == 6 )
		       {
			       *(Out + ((i*width + j)*bpp) + 2) = 207;
		       }
		       else if( maxblueindex == 7 )
		       {
			       *(Out + ((i*width + j)*bpp) + 2) = 239;
		       }
		            
		       for(int x=0 ; x < 8 ; x++)
               {
						 arrayred_8[x] = 0;
						 arraygreen_8[x] = 0;
						 arrayblue_8[x] = 0;
			   }
			   
			 			 			   
		}
	}//end of for loops i , j	
}


int main(int argc, char *argv[])
{
    FILE* fptr1;
    int width  = atoi(argv[3]);
    int height = atoi(argv[4]);
    int bpp    = 3;
    int N      = atoi(argv[5]);
        
    unsigned char *Img        = new unsigned char[width*height*bpp];
    unsigned char *Tempbuff   = new unsigned char[width*height*bpp];
    unsigned char *Out        = new unsigned char[width*height*bpp];
    unsigned char *tempred    = NULL;
    unsigned char *tempgreen  = NULL;
    unsigned char *tempblue   = NULL;
    
    // Check for proper syntax
	if (argc < 5){
		cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
		cout << argv[0]<<"input_image.raw output_image.raw width height windowsize" << endl;
		return 0;
	}
    
    fptr1 = fopen(argv[1],"rb");
    
	if(!(fptr1 == NULL))
	{       
        fread(Img,sizeof(unsigned char),width*height*bpp,fptr1); //Reading RAW image into 3D image data matrix
	    fclose(fptr1);
		cout<<"Image can be read"<<endl;
		
	}
	else
	{
		cout<<"Image cannot be read"<<endl;
	}
	
	quantize_512(Img,width,height,bpp,Tempbuff,tempred,tempgreen,tempblue);
	
	oilpaint(Tempbuff,width,height,bpp,Out,N);
	
	//write
	fptr1 =fopen(argv[2],"wb");
	if(!(fptr1 == NULL))
    { 
		fwrite(Out,sizeof(unsigned char),width*height*bpp,fptr1);
	    fclose(fptr1);
	}
	
	delete[] Img;
	delete[] Tempbuff;
	delete[] Out;
	
	cout<<"Successfully Done!"<<endl;
	
	return 0;
}	
