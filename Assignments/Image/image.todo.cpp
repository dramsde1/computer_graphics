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

            red = red * 255;
            blue = blue * 255;
            green = green * 255;


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

Image32 Image32::orderedDither2X2( int bits ) const
{
	Util::Throw( "Image32::orderedDither2x2 undefined" );
	return Image32();
}

Image32 Image32::floydSteinbergDither( int bits ) const
{
	Util::Throw( "Image32::floydSteinbergDither undefined" );
	return Image32();
}

Image32 Image32::blur3X3( void ) const
{
	//Util::Throw( "Image32::blur3X3 undefined" );
	return Image32();
}

Image32 Image32::edgeDetect3X3( void ) const
{
	Util::Throw( "Image32::edgeDetect3X3 undefined" );
	return Image32();
}
Image32 Image32::scaleNearest( float scaleFactor ) const
{
	Util::Throw( "Image32::scaleNearest undefined" );
	return Image32();
}

Image32 Image32::scaleBilinear( float scaleFactor ) const
{
	Util::Throw( "Image32::scaleBilinear undefined" );
	return Image32();
}

Image32 Image32::scaleGaussian( float scaleFactor ) const
{
	Util::Throw( "Image32::scaleGaussian undefined" );
	return Image32();
}

Image32 Image32::rotateNearest( float angle ) const
{
	Util::Throw( "Image32::rotateNearest undefined" );
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
	Util::Throw( "Image32::setAlpha undefined" );
	return;
}

Image32 Image32::composite( const Image32& overlay ) const
{
	Util::Throw( "Image32::composite undefined" );
	return Image32();
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
	Util::Throw( "Image32::nearestSample undefined" );
	return Pixel32();
}
Pixel32 Image32::bilinearSample( float x , float y ) const
{
	Util::Throw( "Image32::bilinearSample undefined" );
	return Pixel32();
}
Pixel32 Image32::gaussianSample( float x , float y , float variance , float radius ) const
{
	Util::Throw( "Image32::gaussianSample undefined" );
	return Pixel32();
}
