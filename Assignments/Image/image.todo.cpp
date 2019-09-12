#include "image.h"
#include <stdlib.h>
#include <math.h>
#include "../Util/exceptions.h"
#include <iostream>
using std::cout;
using std::endl;
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
	Util::Throw( "Image32::addRandomNoise undefined" );
    //(*this)(0,0).
	return Image32();
}

//helper function for brighten
unsigned char boundary(unsigned char rgb) {
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
    unsigned char red = 0;
    unsigned char green = 0;
    unsigned char blue = 0;
    for (int i = 0; i < r; i++) {
       for (int j = 0; j < c; j++) {
           red = boundary((*this)(i,j).r + brightness);
           green = boundary((*this)(i,j).g + brightness);
           blue = boundary((*this)(i,j).b + brightness);
           //replace these vals with the pixel vals of the image
       }
    }

	return Image32();
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

////contrast help function///
void Image32::getContrast(float factor, Pixel32& pixel) const
{
    //change the range from 0-255 to -0.5-0.5 
    double red = ((pixel.r * 1.0)/255 - 0.5) * factor;
    double green = ((pixel.g * 1.0)/255 - 0.5) * factor;
    double blue = ((pixel.b * 1.0)/255 - 0.5) * factor;
    
    //keep pixel values inside boundary
    if (red > 0.5) {
        red = 0.5;
    }
    else if (red < -0.5) {
        red = -0.5;
    }

    if (green > 0.5) { 
        green = 0.5;
    }
    else if (green < -0.5){ 
        green = -0.5;
    }

    if (blue > 0.5) { 
        blue = 0.5;
    }
    else if (blue < -0.5) { 
        blue = -0.5;
    }

    //convert the vals from -0.5-0.5 to 0-255
    pixel.r = (red + 0.5) * 255;
    pixel.g = (green + 0.5) * 255;
    pixel.b = (blue + 0.5) * 255;
}

/////////////////////////////////////////////

Image32 Image32::contrast( float contrast ) const
{
	//Util::Throw( "Image32::contrast undefined" );
    ////fix how this works
    Image32* img = new Image32();
    int r = (*this).width();
    int c = (*this).height();

    for (int i = 0; i < r; i++) {
       for (int j = 0; j < c; j++) {
          (*img)(i,j) = (*this)(i,j);
          getContrast(contrast, (*img)(i,j));
       }
    }
	return (*img);
}

Image32 Image32::saturate( float saturation ) const
{
	Util::Throw( "Image32::saturation undefined" );
	return Image32();
}

Image32 Image32::quantize( int bits ) const
{
	Util::Throw( "Image32::quantize undefined" );
	return Image32();
}

Image32 Image32::randomDither( int bits ) const
{
	Util::Throw( "Image32::randomDither undefined" );
	return Image32();
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
	Util::Throw( "Image32::crop undefined" );
	return Image32();
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
