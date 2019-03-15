#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <cmath>

using namespace std;


//Function Declarations

unsigned char bilinear(unsigned char* Img,double new_image_col , double new_image_row,int width, int bpp, int height, int channel);
double WarpAlgoforX(double X, double Y);
double WarpAlgoforY(double X, double Y);
double DewarpAlgoforX(double coeffx[],double X, double Y);
double DewarpAlgoforY(double coeffx[],double X, double Y);

//Function Definitions

unsigned char bilinear(unsigned char* Img,double new_image_col , double new_image_row, int width , int bpp, int height,int channel)
{
	int refpoint_i =0 , refpoint_j = 0 ;
	refpoint_i = (int)new_image_row;
	refpoint_j = (int)new_image_col;
	double pix_val1, pix_val2;
	double pix_val;
	unsigned char Qref, Qright, Qdown, Qdiag;
	unsigned char pix_value;
	double delta_x = 0.0 , delta_y = 0.0;

	Qref = 0;

	if( refpoint_j < 0)
	{
		refpoint_j = 0;
		new_image_col = 0.0;
	}
	if( refpoint_i < 0)
	{
		refpoint_i = 0;
		new_image_row = 0.0;
	}
	if( refpoint_i >= height)
	{
		refpoint_i = height -1;
		new_image_row = height - 1;
	}
	if( refpoint_j >= width -1 )
	{
		refpoint_j = width -1;
		new_image_col = width-1;
	}

	Qref = *(Img+ ((refpoint_i*width + refpoint_j)*bpp) + channel );
	Qright = Qref;
	Qdown = Qref;
	Qdiag = Qref;

	if( (refpoint_j + 1) <  width)
	{    
		Qright = *(Img+ (((refpoint_i)*width + refpoint_j+1)*bpp ) + channel );
	}
	if( (refpoint_i + 1) < height)
	{
		Qdown = *(Img+ (((refpoint_i + 1)*width + refpoint_j)*bpp) + channel);
	}
	if( (refpoint_j + 1)  < width && (refpoint_i +1) < height )
	{
		Qdiag = *(Img+ (((refpoint_i + 1)*width + refpoint_j + 1 )*bpp) + channel);
	}

	delta_x = new_image_col - refpoint_j;
	delta_y = new_image_row - refpoint_i;

	pix_val1 = Qref*(1-delta_x) + (delta_x*Qright);
	pix_val2 = Qdown*(1-delta_x) + (delta_x*Qdiag);
	pix_val = pix_val1*(1-delta_y) + (delta_y*pix_val2);
	pix_value = (unsigned char)pix_val;

	return pix_value;
}

double WarpAlgoforX(double X, double Y)
{

	if( X < 0 && Y > 0 )
	{
		return (0.998871*X +0.00113*Y + 0.002265*X*Y );
	}
	else if( X >=0 && Y >=0)
	{
		return (0.998871*X + 0.001122*Y + 0.002253*X*Y );
	}
	else if( X > 0 && Y < 0)
	{
		return (1.00112053*X -0.001122*Y - 0.0022410*X*Y  );
	}
	else if( X < 0 && Y < 0)
	{
		return (1.001122*X - 0.001126*Y - 0.002253*X*Y  );
	}
}

double WarpAlgoforY(double X, double Y)
{
	if( X < 0 && Y > 0 )
	{
		return (0.001128*X +0.998869*Y - 0.002265*X*Y);
	}
	else if( X >=0 && Y >=0)
	{
		return (-0.0011289*X + 1.001122*Y + 0.002241*X*Y);
	}
	else if( X > 0 && Y < 0)
	{
		return (-0.0011205*X +1.001122*Y + 0.002241*X*Y);
	}
	else if( X < 0 && Y < 0)
	{
		return (0.00112245*X + 0.998873*Y - 0.002253*X*Y);
	}	
}


double DewarpAlgoforX(double coeffx[], double X , double Y)
{
	if( X < 0 && Y > 0 )
	{
		return (coeffx[0]*X + coeffx[1]*Y + coeffx[2]*X*Y );
	}
	else if( X >=0 && Y >=0)
	{
		return (coeffx[3]*X + coeffx[4]*Y + coeffx[5]*X*Y );
	}
	else if( X > 0 && Y < 0)
	{
		return (coeffx[6]*X +coeffx[7]*Y + coeffx[8]*X*Y  );
	}
	else if( X < 0 && Y < 0)
	{
		return (coeffx[9]*X + coeffx[10]*Y + coeffx[11]*X*Y  );
	}
}

double DewarpAlgoforY(double coeffy[], double X , double Y)
{
	if( X < 0 && Y > 0 )
	{
		return (coeffy[0]*X + coeffy[1]*Y + coeffy[2]*X*Y );
	}
	else if( X >=0 && Y >=0)
	{
		return (coeffy[3]*X + coeffy[4]*Y + coeffy[5]*X*Y );
	}
	else if( X > 0 && Y < 0)
	{
		return (coeffy[6]*X + coeffy[7]*Y + coeffy[8]*X*Y  );
	}
	else if( X < 0 && Y < 0)
	{
		return (coeffy[9]*X + coeffy[10]*Y + coeffy[11]*X*Y  );
	}
}


//Driver Code

int main(int argc, char* argv[])
{

	// Check for proper syntax

	if (argc < 6)
	{
		cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
		cout << argv[0]<<"  input_image.raw output_image.raw dewarped_image.raw width height" << endl;
		return 0;
	}

	FILE* fptr1;
	int bpp    = 3;
	int width  = atoi(argv[4]);
	int height = atoi(argv[5]);
	unsigned char* Img = new unsigned char[width*height*bpp];    
	unsigned char* Out = new unsigned char[width*height*bpp]();
	unsigned char* Dewarped = new unsigned char[width*height*bpp]; 
	const int Offset = 256;
	double cartesian_x = 0.0;
	double cartesian_y = 0.0;
	double polar_radius = 0.0;
	double Output_cartesian_x = 0.0;
	double Output_cartesian_y = 0.0;
	double new_image_col = 0.0;
	double new_image_row = 0.0;
	unsigned char pixelValueRed;
	unsigned char pixelValueGreen;
	unsigned char pixelValueBlue;


	fptr1 = fopen(argv[1],"rb");

	if(!(fptr1 == NULL))
	{     
		fread(Img,sizeof(unsigned char),width*height*bpp,fptr1); //Reading RAW image into 3D image data matrix
		fclose(fptr1);
		cout<<"Image can be read"<<endl;	
                cout<<"Successful!"<<endl;	
	}
	else
	{
		cout<<"Image cannot be read"<<endl;
	}


        /* ################################################################################################ */

        //Code for warping

        //Perform reverse address mapping , from output to input
        //Setup output and grab pixels from input corresponding to pixels in the output

	for(int imgrow =0; imgrow < height; imgrow++)
	{
		for(int imgcol=0 ; imgcol < width ; imgcol++)
		{ 
			cartesian_x = imgcol + 0.5 - Offset;
			cartesian_y = height - 0.5 - imgrow - Offset;

			polar_radius = sqrt((pow(cartesian_x,2))+(pow(cartesian_y,2)));
                        
            //Check in the output image whether radius <= 256.5 , only then proceed to warping 

			if( polar_radius <= 256.5)
			{           
				Output_cartesian_x = WarpAlgoforX(cartesian_x,cartesian_y);
				Output_cartesian_y = WarpAlgoforY(cartesian_x,cartesian_y);

				//Convert Cartesian coordinates to corresponding output image coordinates

				new_image_col     = Output_cartesian_x - 0.5 + Offset;
				new_image_row     = height - Output_cartesian_y - 0.5 - Offset;

				pixelValueRed = bilinear(Img,new_image_col,new_image_row,width,bpp,height,0);
				pixelValueGreen = bilinear(Img,new_image_col,new_image_row,width,bpp,height,1);
				pixelValueBlue = bilinear(Img,new_image_col,new_image_row,width,bpp,height,2);

				*(Out+ ((imgrow*width + imgcol)*bpp) + 0) = pixelValueRed;
				*(Out+ ((imgrow*width + imgcol)*bpp) + 1) = pixelValueGreen;
				*(Out+ ((imgrow*width + imgcol)*bpp) + 2) = pixelValueBlue;
			}          
			else
			{
				*(Out+ ((imgrow*width + imgcol)*bpp) + 0) = 0;
				*(Out+ ((imgrow*width + imgcol)*bpp) + 1) = 0;
				*(Out+ ((imgrow*width + imgcol)*bpp) + 2) = 0; 				 				
			}

		}
	}

	//write

	fptr1 =fopen(argv[2],"wb");
	if(!(fptr1 == NULL))
	{ 
		fwrite(Out,sizeof(unsigned char),width*height*bpp,fptr1);
		fclose(fptr1);
	}


	/*  ##################################################################### */



	//Code for dewarping

	double coeffx[12]   =  { 1.00056776e+00, -5.68880703e-04, -1.13998357e-03,
				1.00056888e+00,-5.65549579e-04,-1.13554790e-03, 
				9.99434446e-01  , 5.66658513e-04  , 1.13110351e-03 , 
				9.99433341e-01 , 5.67767429e-04 , 1.13553921e-03 };

	double coeffy[12]   =  {-5.67763072e-04, 1.00056888e+00, 1.13998357e-03, 
				5.68880703e-04, 9.99434450e-01, -1.13554790e-03,
				5.65553919e-04, 9.99433341e-01, -1.13110351e-03,
				-5.66658513e-04,  1.00056777e+00,  1.13553921e-03}; 

	for(int imgrow =0; imgrow < height; imgrow++)
	{
		for(int imgcol=0 ; imgcol < width ; imgcol++)
		{ 
			cartesian_x = imgcol + 0.5 - Offset;
			cartesian_y = height - 0.5 - imgrow - Offset;

			Output_cartesian_x = DewarpAlgoforX(coeffx,cartesian_x,cartesian_y);
			Output_cartesian_y = DewarpAlgoforY(coeffy,cartesian_x,cartesian_y);

			new_image_col     = Output_cartesian_x - 0.5 + Offset;
			new_image_row     = height - Output_cartesian_y - 0.5 - Offset;

			pixelValueRed = bilinear(Out,new_image_col,new_image_row,width,bpp,height,0);
			pixelValueGreen = bilinear(Out,new_image_col,new_image_row,width,bpp,height,1);
			pixelValueBlue = bilinear(Out,new_image_col,new_image_row,width,bpp,height,2);

			*(Dewarped + ((imgrow*width + imgcol)*bpp) + 0) = pixelValueRed;
			*(Dewarped + ((imgrow*width + imgcol)*bpp) + 1) = pixelValueGreen;
			*(Dewarped + ((imgrow*width + imgcol)*bpp) + 2) = pixelValueBlue;

		}
	}


        //Write Dewarped image

	fptr1 =fopen(argv[3],"wb");
	if(!(fptr1 == NULL))
	{ 
		fwrite(Dewarped,sizeof(unsigned char),width*height*bpp,fptr1);
		fclose(fptr1);
	}

	delete[] Img;
	delete[] Out;	
	delete[] Dewarped;

	return 0;
}

