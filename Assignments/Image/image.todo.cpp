#include "image.h"
#include <stdlib.h>
#include <math.h>
#include "../Util/exceptions.h"
#include <iostream>
#include <cmath>
#include <vector>
#include <numeric>
#include <random>

using std::iota;
using std::round;
using std::pow;
using std::cout;
using std::endl;
using std::vector;
using std::floor;
using std::ceil;
////////////////////////////
// Image processing stuff //
////////////////////////////
Pixel::Pixel( const Pixel32& p )
{
	Util::Throw( "Pixel::Pixel undefined" );
}
Pixel32::Pixel32( const Pixel& p )
{
	Util::Throw( "Pixel32::Pixel32 undefined" );
}

Image32 Image32::addRandomNoise( float noise ) const
{
	//Util::Throw( "Image32::addRandomNoise undefined" );

    int r = (*this).width();
    int c = (*this).height();
    Image32* img = new Image32();
    (*img).setSize(r, c);

    float randomNoise = 0;
    float range = 2 * noise;
    double red = 0;
    double green = 0;
    double blue = 0;
    int pixelAdd = 0;

    for (int i = 0; i < r; i++) {
       for (int j = 0; j < c; j++) {
          
          randomNoise = rand()*range-noise;

          pixelAdd = rand();

          if (pixelAdd % 4 == 0) {
              red = (float)(*this)(i,j).r * (float)randomNoise;
              blue = (float)(*this)(i,j).b * (float)randomNoise;
              green = (float)(*this)(i,j).g * (float)randomNoise;
          }
          else {
              red = (double)(*this)(i,j).r;
              blue = (double)(*this)(i,j).b;
              green = (double)(*this)(i,j).g;
          }

          (*img)(i,j).r = (unsigned char)red;
          (*img)(i,j).g = (unsigned char)green;
          (*img)(i,j).b = (unsigned char)blue;

       }
    }


	return (*img);
}

//helper function for brighten
double boundary(double rgb) {
    if (rgb < 0) {
        rgb = 0;
    }
    if (rgb > 255) {
        rgb = 255;
    }
    return rgb;
}

double boundary2(double rgb) {
    if (rgb < 0) {
        rgb = 0;
    }
    if (rgb > 1) {
        rgb = 1;
    }
    return rgb;
}


Image32 Image32::brighten( float brightness ) const

{
	//Util::Throw( "Image32::brightness undefined" );
    int r = (*this).width();
    int c = (*this).height();
    Image32* img = new Image32();
    (*img).setSize(r, c);
    
    double red = 0;
    double green = 0;
    double blue = 0;

    for (int i = 0; i < r; i++) {
       for (int j = 0; j < c; j++) {
          

          red = boundary((double)(*this)(i,j).r * brightness);
          green = boundary((double)(*this)(i,j).g * brightness);
          blue = boundary((double)(*this)(i,j).b * brightness);

          (*img)(i,j).r = (unsigned char)red;
          (*img)(i,j).g = (unsigned char)green;
          (*img)(i,j).b = (unsigned char)blue;

       }
    }
	return (*img);
}

Image32 Image32::luminance( void ) const
{
	//Util::Throw( "Image32::luminance undefined" );
    int r = (*this).width();
    int c = (*this).height();
    Image32* img = new Image32();
    (*img).setSize(r, c);
    unsigned char intensity = 0;
    for (int i = 0; i < r; i++ ) {
        for (int j = 0; j < c; j++) {
           //get the intensity value
           intensity = (unsigned char)
               (((double)(*this)(i,j).r*0.30) 
                + ((double)(*this)(i,j).g*0.59) 
                + ((double)(*this)(i,j).b*0.11));
           (*img)(i,j).r = intensity;
           (*img)(i,j).g = intensity;
           (*img)(i,j).b = intensity;
           //make intensity the rgb values
           //fix all the below problems 
        }    
        cout << (*img).width() << endl;
        cout << (*img).height() << endl;
    }
	return (*img);
}


/////////////////////////////////////////////

Image32 Image32::contrast( float contrast ) const
{
	//Util::Throw( "Image32::contrast undefined" );
    ////fix how this works
    int r = (*this).width();
    int c = (*this).height();
    double n = r * c;
    double total = 0;
    Image32* img = new Image32();
    (*img).setSize(r, c);

    double red = 0;
    double green = 0;
    double blue = 0;

    for (int i = 0; i < r; i++) {
       for (int j = 0; j < c; j++) {
           total += ((double)(*this)(i,j).r*0.30 + (double)(*this)(i,j).g*0.59 + (double)(*this)(i,j).b*0.11);
       }
    }
    double mean = total / n;
    for (int i = 0; i < r; i++) {
       for (int j = 0; j < c; j++) {
           red = boundary(((double)(*this)(i,j).r - mean)*contrast + mean);
           green = boundary(((double)(*this)(i,j).g - mean)*contrast + mean);
           blue = boundary(((double)(*this)(i,j).b - mean)*contrast + mean);

           (*img)(i,j).r = (unsigned char)red;
           (*img)(i,j).g = (unsigned char)green;
           (*img)(i,j).b = (unsigned char)blue;
       }
    }

	return (*img);
}

Image32 Image32::saturate( float saturation ) const
{
	//Util::Throw( "Image32::saturation undefined" );

    int r = (*this).width();
    int c = (*this).height();
    double luminance = 0;
    double red = 0;
    double green = 0;
    double blue = 0;
    Image32* img = new Image32();
    (*img).setSize(r, c);
    for (int i = 0; i < r; i++ ) {
        for (int j = 0; j < c; j++) {
            luminance = ((double)(*this)(i,j).r*0.30 + (double)(*this)(i,j).g*0.59 + (double)(*this)(i,j).b*0.11);
            red = boundary(((double)(*this)(i,j).r - luminance)*saturation + luminance);
            green = boundary(((double)(*this)(i,j).g - luminance)*saturation + luminance);
            blue = boundary(((double)(*this)(i,j).b - luminance)*saturation + luminance);
            (*img)(i,j).r = (unsigned char)red;
            (*img)(i,j).g = (unsigned char)green;
            (*img)(i,j).b = (unsigned char)blue;
        }    
    }

	return (*img);
}


Image32 Image32::quantize( int bits ) const

{
	//Util::Throw( "Image32::quantize undefined" );

    int r = (*this).width();
    int c = (*this).height();
    double red = 0;
    double green = 0;
    double blue = 0;

        
    Image32* img = new Image32();
    (*img).setSize(r, c);

    for (int i = 0; i < r; i++ ) {
        for (int j = 0; j < c; j++) {

            red = (double)(*this)(i,j).r;
            green = (double)(*this)(i,j).g;
            blue = (double)(*this)(i,j).b;

            red = red / 255;
            blue = blue / 255;
            green = green / 255;

            red = (double)floor(red * pow(2, bits));
            blue = (double)floor(blue * pow(2, bits));
            green = (double)floor(green * pow(2, bits));

            red = (double)(red / (pow(2, bits) - 1));
            blue = (double)(blue / (pow(2, bits) - 1));
            green = (double)(green / (pow(2, bits) - 1));

            red = boundary(red * 255);
            blue = boundary(blue * 255);
            green = boundary(green * 255);


            (*img)(i,j).r = (unsigned char)red;
            (*img)(i,j).g = (unsigned char)green;
            (*img)(i,j).b = (unsigned char)blue;
        }        
    }

	return (*img);
}

Image32 Image32::randomDither( int bits ) const

{
	//Util::Throw( "Image32::randomDither undefined" );

    int r = (*this).width();
    int c = (*this).height();
    double red = 0;
    double green = 0;
    double blue = 0;
    double randomNoise = 0;
    double addedNoise = 0;
    Image32* img = new Image32();
    (*img).setSize(r, c);
    for (int i = 0; i < r; i++ ) {
        for (int j = 0; j < c; j++) {

            red = (double)(*this)(i,j).r;
            green = (double)(*this)(i,j).g;
            blue = (double)(*this)(i,j).b;

            red = red / 255;
            blue = blue / 255;
            green = green / 255;

            std::random_device rd; // get random # from hardware
            std::mt19937 eng(rd()); // seed the generator
            std::uniform_real_distribution<> distr(0, pow(2, bits)); //get range
            randomNoise = (double)distr(eng);
            addedNoise = (double)(randomNoise / pow(2, bits));

            red = (double)floor(red * pow(2, bits));
            red += addedNoise;
            blue = (double)floor(blue * pow(2, bits));
            blue += addedNoise;
            green = (double)floor(green * pow(2, bits));
            green += addedNoise;

            red = (double)(red / (pow(2, bits) - 1));
            blue = (double)(blue / (pow(2, bits) - 1));
            green = (double)(green / (pow(2, bits) - 1));

            red = boundary(red * 255);
            blue = boundary(blue * 255);
            green = boundary(green * 255);

            (*img)(i,j).r = (unsigned char)red;
            (*img)(i,j).g = (unsigned char)green;
            (*img)(i,j).b = (unsigned char)blue;
        }    
    }
	return (*img);
}

double roundDecide(double e, double roundVal, double c) {
    if (e > roundVal) {
        return ceil(c);
    }
    else {
        return floor(c);
    }
}

Image32 Image32::orderedDither2X2( int bits ) const
{
	//Util::Throw( "Image32::orderedDither2x2 undefined" );

    int r = (*this).width();
    int c = (*this).height();
    double red = 0;
    double green = 0;
    double blue = 0;
    double redE = 0;
    double greenE = 0;
    double blueE = 0;
    double d2[2][2] = {{1,3}, {4,2}};
    int x = 0;
    int y = 0;
    double roundVal;


    Image32* img = new Image32();
    (*img).setSize(r, c);

    for (int i = 0; i < r; i++ ) {
        for (int j = 0; j < c; j++) {

            x = i % 2; //x is MATRIX index
            y = j % 2; //y is MATRIX index

            red = (double)(*this)(i,j).r;
            green = (double)(*this)(i,j).g;
            blue = (double)(*this)(i,j).b;

            red = red / 255;
            blue = blue / 255;
            green = green / 255;
            // do all the math stuff after
            

            red = (double)(red * (pow(2, bits) - 1)); //c
            redE = (double)(red - floor(red)); //e
            green = (double)(green * (pow(2, bits) - 1)); //c
            greenE = (double)(green - floor(green)); //e
            blue = (double)(blue * (pow(2, bits) - 1)); //c
            blueE = (double)(blue - floor(blue)); //e

            //right side of the inequality
            roundVal = (double)(d2[x][y] / 5);

            //round up or down
            red = roundDecide(redE, roundVal, red);
            green = roundDecide(greenE, roundVal, green);
            blue = roundDecide(blueE, roundVal, blue);


            //do all the math stuff above
            red = (double)(red / (pow(2, bits) - 1));
            blue = (double)(blue / (pow(2, bits) - 1));
            green = (double)(green / (pow(2, bits) - 1));

            red = boundary(red * 255);
            blue = boundary(blue * 255);
            green = boundary(green * 255);


            (*img)(i,j).r = (unsigned char)red;
            (*img)(i,j).g = (unsigned char)green;
            (*img)(i,j).b = (unsigned char)blue;
        }        
    }

	return (*img);
}


double floydQuantize(double pixelVal, int bits) {
    pixelVal = pixelVal / 255;
    pixelVal = (double)floor(pixelVal * pow(2, bits));
    return (double)(pixelVal / (pow(2, bits) - 1));
}

Image32 Image32::floydSteinbergDither( int bits ) const
{
	//Util::Throw( "Image32::floydSteinbergDither undefined" );

    int r = (*this).width();
    int c = (*this).height();
    double red = 0;
    double green = 0;
    double blue = 0;

    double _alpha = .4375;
    double _beta = .1875;
    double _gamma = .3125;
    double _delta = .0625;

    double r_error = 0;
    double g_error = 0;
    double b_error = 0;

    Image32* img = new Image32();
    (*img).setSize(r, c);

    for (int i = 0; i < r; i++ ) {
        for (int j = 0; j < c; j++) {

            //these are your dests  
            red = floydQuantize((double)(*this)(i,j).r, bits);
            green = floydQuantize((double)(*this)(i,j).g, bits);
            blue = floydQuantize((double)(*this)(i,j).b, bits);

            //sourece - dest
            r_error = (double)(*this)(i,j).r - red;
            g_error = (double)(*this)(i,j).g - green;
            b_error = (double)(*this)(i,j).b - blue;

            //alpha error
            if (j + 1 < c) {
                cout << "here" << endl;
                (*img)(i, j + 1).r = (unsigned char)boundary(((*img)(i, j + 1).r + (_alpha * r_error)));
                (*img)(i, j + 1).g = (unsigned char)boundary(((*img)(i, j + 1).g + (_alpha * g_error)));
                (*img)(i, j + 1).b = (unsigned char)boundary(((*img)(i, j + 1).b + (_alpha * b_error)));
            }

            //beta error
            if (i + 1 < r && j - 1 > 0) {
                cout << "here1" << endl;
                (*img)(i + 1, j - 1).r = (unsigned char)boundary(((*img)(i + 1, j - 1).r + (_beta * r_error)));
                (*img)(i + 1, j - 1).g = (unsigned char)boundary(((*img)(i + 1, j - 1).g + (_beta * g_error)));
                (*img)(i + 1, j - 1).b = (unsigned char)boundary(((*img)(i + 1, j - 1).b + (_beta * b_error)));
            }

            //gamma error
            if (i + 1 < r) {
                cout << "here2" << endl;
                (*img)(i + 1, j).r = (unsigned char)boundary(((*img)(i + 1, j).r + (_gamma * r_error)));
                (*img)(i + 1, j).g = (unsigned char)boundary(((*img)(i + 1, j).g + (_gamma * g_error)));
                (*img)(i + 1, j).b = (unsigned char)boundary(((*img)(i + 1, j).b + (_gamma * b_error)));
            }

            //delta error
            if (i + 1 < r && j + 1 < c) {
                cout << "here3" << endl;
                (*img)(i + 1, j + 1).r = (unsigned char)boundary(((*img)(i + 1, j + 1).r + (_delta * r_error)));
                (*img)(i + 1, j + 1).g = (unsigned char)boundary(((*img)(i + 1, j + 1).g + (_delta * g_error)));
                (*img)(i + 1, j + 1).b = (unsigned char)boundary(((*img)(i + 1, j + 1).b + (_delta * b_error)));
            }

        }        
    }

	return (*img);
}

//create a filter first 

double getGaussianVal(double sig, int di, int dj) {
    double pi = 3.14159265358979323846264;
    double gVal = (1.0 / (double)(2.0 * PI * pow(sig, 2))) * ((double)exp((-((double)pow(di, 2) + (double)pow(dj, 2))) / (double)(2.0 * pow(sig, 2))));
    return gVal;
}


void getMask(double sig, int n, double **arr){
    int di = 0;
    int dj = 0;
    int middle = (n - 1) / 2;
    for (int i = 0; i < n; i++){
        di = middle - i;
        for (int j = 0; j < n; j++) {
            dj = middle - j;
            double gVal = getGaussianVal(sig,di,dj);
            arr[i][j] = gVal;
        }
    }
}

void  multiply(int size, const Image32 * img, double **mask, int i, int j, Image32 * converted, int rows, int cols) {
    int inbounds_x = i - (size/2);
    int inbounds_y = j - (size/2);
    double redTotal = 0;
    double greenTotal = 0;
    double blueTotal = 0;
    double total = 0;       
    for (int r  = 0; r < size; r++){
        for (int c = 0; c < size; c++) {
            if(r+inbounds_x >= 0 && r+inbounds_x < rows && c+inbounds_y >= 0 && c+inbounds_y < cols){
                redTotal += (*img)((r+inbounds_x), (c+inbounds_y)).r * mask[r][c];
                greenTotal += (*img)((r+inbounds_x), (c+inbounds_y)).g * mask[r][c];
                blueTotal += (*img)((r+inbounds_x), (c+inbounds_y)).b * mask[r][c];
                total += mask[r][c];
            } 
        }
    }

    //dont forget to normalize everything
    (*converted)(i, j).r = redTotal / total;
    (*converted)(i, j).g = greenTotal / total;
    (*converted)(i, j).b = blueTotal / total;
}

Image32 Image32::blur3X3( void ) const
{
	//Util::Throw( "Image32::blur3X3 undefined" );
    int n = 3;
    //n*n mask n/2 = sigma
    double sig = 1.5;
    double **mask = new double*[n];
    for (int i = 0; i < n; i++) {
        mask[i] = new double[n];
    }
    int size = n;
    getMask(sig,n,mask);
    int r = (*this).width();
    int c = (*this).height();
    Image32* img = new Image32();
    (*img).setSize(r, c);

    for (int i = 0; i < r; i++ ) {
        for (int j = 0; j < c; j++) {
            multiply(size, this, mask, i, j, img, r, c);
        }
    }

	return (*img);
}

void  edgeCreater(int size, const Image32 * img, double **mask, int i, int j, Image32 * converted, int rows, int cols) {
    int inbounds_x = i - (size/2);
    int inbounds_y = j - (size/2);
    double redTotal = 0;
    double greenTotal = 0;
    double blueTotal = 0;
    for (int r  = 0; r < size; r++){
        for (int c = 0; c < size; c++) {
            if(r+inbounds_x >= 0 && r+inbounds_x < rows && c+inbounds_y >= 0 && c+inbounds_y < cols){
                redTotal += (*img)((r+inbounds_x), (c+inbounds_y)).r * mask[r][c];
                greenTotal += (*img)((r+inbounds_x), (c+inbounds_y)).g * mask[r][c];
                blueTotal += (*img)((r+inbounds_x), (c+inbounds_y)).b * mask[r][c];
            } 
        }
    }

    (*converted)(i, j).r = boundary(redTotal);
    (*converted)(i, j).g = boundary(greenTotal);
    (*converted)(i, j).b = boundary(blueTotal);
}

Image32 Image32::edgeDetect3X3( void ) const
{
	//Util::Throw( "Image32::edgeDetect3X3 undefined" );
    int n = 3;
    double **mask = new double*[n];
    for (int i = 0; i < n; i++) {
        mask[i] = new double[n];
    }
    //fill the mask
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            mask[i][j] = -1.0;
        }
    }
    //middle value
    mask[1][1] = 8;

    int r = (*this).width();
    int c = (*this).height();

    Image32* img = new Image32();
    (*img).setSize(r, c);

    for (int i = 0; i < r; i++ ) {
        for (int j = 0; j < c; j++) {
            edgeCreater(n, this, mask, i, j, img, r, c);
        }
    }

	return (*img);
}

Image32 Image32::scaleNearest( float scaleFactor ) const
{
	//Util::Throw( "Image32::scaleNearest undefined" );
    int rOg = (*this).width();
    int cOg = (*this).height();
    int r = rOg * scaleFactor;
    int c = cOg * scaleFactor;
    int iu = 0;
    int iv = 0;

    Image32* img = new Image32();
    (*img).setSize(r, c);
    

    for (int i = 0; i < r; i++) {
       for (int j = 0; j < c; j++) {
            iu = floor((float)(i/scaleFactor) + 0.5);
            iv = floor((float)(j/scaleFactor) + 0.5);
            if (iu < rOg && iv < cOg) {
                (*img)(i,j) = nearestSample((float)(i / scaleFactor), (float)(j / scaleFactor));
            }
       }
    }

	return (*img);
}

Image32 Image32::scaleBilinear( float scaleFactor ) const
{
    int rOg = (*this).width();
    int cOg = (*this).height();
    int r = rOg * scaleFactor;
    int c = cOg * scaleFactor;
    double u1 = 0;
    double u2 = 0;
    double v1 = 0;
    double v2 = 0;

    Image32* img = new Image32();
    (*img).setSize(r, c);
    

    for (int i = 0; i < r; i++) {
       for (int j = 0; j < c; j++) {
            u1 = (double)floor((float)(i / scaleFactor));
            u2 = u1 + 1;
            v1 = (double)floor((float)(j / scaleFactor));
            v2 = v1 + 1;
            if (u1 < rOg && v1 < cOg && u2 < rOg && v2 < cOg) {
                (*img)(i,j) = bilinearSample((float)(i / scaleFactor), (float)(j / scaleFactor));
            }
       }
    }

	return (*img);
}

//rotate gaussian use .25

Image32 Image32::scaleGaussian( float scaleFactor ) const
{
    int rOg = (*this).width();
    int cOg = (*this).height();
    int r = rOg * scaleFactor;
    int c = cOg * scaleFactor;
    float variance = (float)pow((float)(.5 / scaleFactor), 2);
    float radius = 1 /scaleFactor;
    int iu = 0;
    int iv = 0;

    Image32* img = new Image32();
    (*img).setSize(r, c);

    for (int i = 0; i < r; i++) {
       for (int j = 0; j < c; j++) {
            iu = floor((float)(i/scaleFactor));
            iv = floor((float)(j/scaleFactor));
            if (iu < rOg && iv < cOg) {
                (*img)(i,j) = gaussianSample((float)(i / scaleFactor), (float)(j / scaleFactor), variance, radius);
            }
       }
    }

	return (*img);
}

//track the conrners
Image32 Image32::rotateNearest( float angle ) const
{
	//Util::Throw( "Image32::rotateNearest undefined" );

	return Image32();
}

Image32 Image32::rotateBilinear( float angle ) const
{
	Util::Throw( "Image32::rotateBilinear undefined" );
	return Image32();
}
	
Image32 Image32::rotateGaussian( float angle ) const
{
	Util::Throw( "Image32::rotateGaussian undefined" );
	return Image32();
}

void Image32::setAlpha( const Image32& matte )
{
	//Util::Throw( "Image32::setAlpha undefined" );
    //set alpha to be the blue channel
    int r = matte.width();
    int c = matte.height();
    

    for (int i = 0; i < r; i++) {
       for (int j = 0; j < c; j++) {
           (*this)(i,j).a = matte(i,j).b;
       }
    }
}

Image32 Image32::composite( const Image32& overlay ) const
{
	//Util::Throw( "Image32::composite undefined" );
    int r = (*this).width();
    int c = (*this).height();
    double opacityA = 0;
    double rA = 0;
    double gA = 0;
    double bA = 0;

    
    double rB = 0;
    double gB = 0;
    double bB = 0;

    double opacityB = 0;

    double opacityOver = 0;

    double rOver = 0;
    double gOver = 0;
    double bOver = 0;
    
    Image32* img = new Image32();
    (*img).setSize(r, c);
    (*img).setAlpha(overlay);

    for (int i = 0; i < r; i++) {
       for (int j = 0; j < c; j++) {
           opacityA = overlay(i,j).a;
           rA = overlay(i,j).r * overlay(i,j).a;
           gA = overlay(i,j).g * overlay(i,j).a;
           bA = overlay(i,j).b * overlay(i,j).a;

           opacityB = (1 - overlay(i,j).a) * (*this)(i,j).a;

           rB = (*this)(i,j).r * (1 - overlay(i,j).a) * (*this)(i,j).a;
           gB = (*this)(i,j).g * (1 - overlay(i,j).a) * (*this)(i,j).a;
           bB = (*this)(i,j).b * (1 - overlay(i,j).a) * (*this)(i,j).a;

           opacityOver = overlay(i,j).a + (1 - overlay(i,j).a) * (*this)(i,j).a;

           rOver = (overlay(i,j).r * overlay(i,j).a) + ((*this)(i,j).r * (1 - overlay(i,j).a) * (*this)(i,j).a);
           gOver = (overlay(i,j).g * overlay(i,j).a) + ((*this)(i,j).g * (1 - overlay(i,j).a) * (*this)(i,j).a);
           bOver = (overlay(i,j).b * overlay(i,j).a) + ((*this)(i,j).b * (1 - overlay(i,j).a) * (*this)(i,j).a);

           (*img)(i,j).r = rOver / opacityOver;
           (*img)(i,j).g = gOver / opacityOver;
           (*img)(i,j).b = bOver / opacityOver;
       }
    }
	return (*img);
}

Image32 Image32::CrossDissolve( const Image32& source , const Image32& destination , float blendWeight )
{
	Util::Throw( "Image32::CrossDissolve undefined" );
	return Image32();
}
Image32 Image32::warp( const OrientedLineSegmentPairs& olsp ) const
{
	Util::Throw( "Image32::warp undefined" );
	return Image32();
}

Image32 Image32::funFilter( void ) const
{
	Util::Throw( "Image32::funFilter undefined" );
	return Image32();
}

Image32 Image32::crop( int x1 , int y1 , int x2 , int y2 ) const
{
	//Util::Throw( "Image32::crop undefined" );
    int r = x2 - x1;
    int c = y2 - y1;
    double red = 0;
    double green = 0;
    double blue = 0;
    Image32* img = new Image32();
    (*img).setSize(r, c);
    for (int i = 0; i < r; i++ ) {
        for (int j = 0; j < c; j++) {

            red = (double)(*this)(i,j).r;
            blue = (double)(*this)(i,j).b;
            green = (double)(*this)(i,j).g;

            (*img)(i,j).r = (unsigned char)red;
            (*img)(i,j).g = (unsigned char)green;
            (*img)(i,j).b = (unsigned char)blue;
        }    
    }


	return (*img);


}

Pixel32 Image32::nearestSample( float x , float y ) const
{
    //Return the value of the pixel closest to the position (x,y)
    int iu = floor(x + 0.5);
    int iv = floor(y + 0.5);
    return (*this)(iu, iv);
}

Pixel32 Image32::bilinearSample( float x , float y ) const
{
	//Util::Throw( "Image32::bilinearSample undefined" );
    double u1 = 0;
    double u2 = 0;
    double v1 = 0;
    double v2 = 0;
    double du = 0;
    double dv = 0;
    double aR = 0;
    double aG = 0;
    double aB = 0;
    double bR = 0;
    double bG = 0;
    double bB = 0;

    int r = (*this).width();
    int c = (*this).height();

    Pixel32 * pixel = new Pixel32();

    u1 = (double)floor(x);
    u2 = u1 + 1;
    v1 = (double)floor(y);
    v2 = v1 + 1;
    du = x - u1;


    aR = ((*this)((int)u1, (int)v1).r * (1 - du)) + ((*this)((int)u2, (int)v1).r * du);
    aG = ((*this)((int)u1, (int)v1).g * (1 - du)) + ((*this)((int)u2, (int)v1).g * du);
    aB = ((*this)((int)u1, (int)v1).b * (1 - du)) + ((*this)((int)u2, (int)v1).b * du);


    bR = ((*this)((int)u1, (int)v2).r * (1 - du)) + ((*this)((int)u2, (int)v2).r * du);
    bG = ((*this)((int)u1, (int)v2).g * (1 - du)) + ((*this)((int)u2, (int)v2).g * du);
    bB = ((*this)((int)u1, (int)v2).b * (1 - du)) + ((*this)((int)u2, (int)v2).b * du);

    dv = y - v1;

    (*pixel).r = (aR * (1 - dv)) + (bR * dv);
    (*pixel).g = (aG * (1 - dv)) + (bG * dv);
    (*pixel).b = (aB * (1 - dv)) + (bB * dv);

	return (*pixel);
}

double square(double val) {
    return val * val;
}

Pixel32 Image32::gaussianSample( float x , float y , float variance , float radius ) const
{
    int low_x = 0;
    int high_x = 0;
    int low_y = 0; 
    int high_y = 0;
    double red = 0;
    double green = 0;
    double blue = 0;
    double total = 0;
    double dx = 0;
    double dy = 0;
    double len = 0;
    Pixel32 * p = new Pixel32();

    low_x = floor((double)x - (double)radius);
    high_x = ceil((double)x + (double)radius);

    int w = high_x - low_x;

    low_y = floor((double)y - (double)radius);
    high_y = ceil((double)y + (double)radius);

    int h = high_y - low_y;

    //get within the radius
    for (int i = low_x; i < high_x; i++) {
        for (int j = low_y; j < high_y; j++) {
            dx = (double)x - i;
            dy = (double)y - j;
            len = square(dx * dx + dy * dy);
            if (len < (float)radius) {
                float g = exp(double(-1.0 * ((dx * dx) + (dy * dy)) / (2 * ((double)variance * (double)variance))));
                total += g;
                red += (*this)(i,j).r * g;
                green += (*this)(i,j).g * g;
                blue += (*this)(i,j).b * g;
            }
        }
    }

    (*p).r = red / total;
    (*p).g = green / total;
    (*p).b = blue / total;



	return (*p);
}
