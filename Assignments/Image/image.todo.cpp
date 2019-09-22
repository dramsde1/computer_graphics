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


Image32 Image32::floydSteinbergDither( int bits ) const
{
	//Util::Throw( "Image32::floydSteinbergDither undefined" );

    int r = (*this).width();
    int c = (*this).height();
    double red = 0;
    double green = 0;
    double blue = 0;
    double red1 = 0;
    double green1 = 0;
    double blue1 = 0;
    double errorRed = 0;
    double errorBlue = 0;
    double errorGreen = 0;
    double redDest = 0;
    double blueDest = 0;
    double greenDest = 0;
    double alpha = 0.4375;
    double Beta = 0.1875;
    double gamma = 0.3125;
    double delta = 0.0625;
    bool or1 = false;
    bool or2 = false;
    bool or3 = false;
    bool or4 = false;
    double test = 0;

        
    Image32* img = new Image32();
    (*img).setSize(r, c);

    for (int j = 0; j < c; j++ ) {
        for (int i = 0; i < r; i++) {

            //boundary check 1
            try {
                test = (double)(*this)(i, j + 1).r;
            }
            catch(...) {
                or1 = true;
            }
            //boundary check 2

            try {
                test = (double)(*this)(i + 1, j - 1).r;
            }
            catch(...) {
                or2 = true;
            }

            //boundary check 3
            try {
                test = (double)(*this)(i + 1,j).r;
            }
            catch(...) {
                or3 = true;
            }

            //boundary check 4
            try {
                test = (double)(*this)(i + 1, j + 1).r;
            }
            catch(...) {
                or4 = true;
            }

            //end boundary checking
            red = (double)(*this)(i,j).r;
            green = (double)(*this)(i,j).g;
            blue = (double)(*this)(i,j).b;

            red = red / 255;
            blue = blue / 255;
            green = green / 255;


            redDest = boundary2((double)floor(red * pow(2, bits)));
            blueDest = boundary2((double)floor(blue * pow(2, bits)));
            greenDest = boundary2((double)floor(green * pow(2, bits)));

            //redDest = (double)(redDest / (pow(2, bits) - 1));
            //blueDest = (double)(blueDest / (pow(2, bits) - 1));
            //greenDest = (double)(greenDest / (pow(2, bits) - 1));

            //red is source
            errorRed = abs(red - redDest);
            errorGreen = abs(green - greenDest); 
            errorBlue = abs(blue - blueDest); 
            //step one
            if (!or1) {
            
                red1 = (double)(*this)(i,j + 1).r / 255;
                //red1 = (double)(red1 / (pow(2, bits) - 1));
                cout << "alpha" << endl;
                cout << alpha << endl;
                cout << "errorRed" << endl;
                cout << errorRed << endl;
                red1 += (alpha * errorRed);
                cout << "alpha times" << endl;
                cout << alpha * errorRed << endl;
                green1 = (double)(*this)(i,j + 1).g / 255;
                //green1 = (double)(green1 / (pow(2, bits) - 1));
                green1 += (alpha * errorGreen);
                blue1 = (double)(*this)(i,j + 1).b / 255;
                //blue1 = (double)(blue1 / (pow(2, bits) - 1));
                blue1 += (alpha * errorBlue);

                red1 = boundary(red1 * 255);
                green1 = boundary(green1 * 255);
                blue1 = boundary(blue1 * 255);

                cout << "red1" << endl;
                cout << red1 << endl;
                cout<< "og" << endl;
                cout << (double)(*this)(i, j + 1).r << endl;

                (*img)(i, j + 1).r = (unsigned char)red1;
                (*img)(i, j + 1).g = (unsigned char)green1;
                (*img)(i, j + 1).b = (unsigned char)blue1;
            }

            //step two
            if (!or2) {

                red1 = (double)(*this)(i + 1,j - 1).r / 255;
                //red1 = (double)(red1 / (pow(2, bits) - 1));
                red1 += (Beta * errorRed);
                green1 = (double)(*this)(i + 1,j - 1).g / 255;
                //green1 = (double)(green1 / (pow(2, bits) - 1));
                green1 += (Beta * errorGreen);
                blue1 = (double)(*this)(i + 1,j - 1).b / 255;
                //blue1 = (double)(blue1 / (pow(2, bits) - 1));
                blue1 += (Beta * errorBlue);

                red1 = boundary(red1 * 255);
                green1 = boundary(green1 * 255);
                blue1 = boundary(blue1 * 255);

                (*img)(i + 1, j - 1).r = (unsigned char)red1;
                (*img)(i + 1, j - 1).g = (unsigned char)green1;
                (*img)(i + 1, j - 1).b = (unsigned char)blue1;

            }
            //step three
            if (!or3) {


                red1 = (double)(*this)(i + 1,j).r / 255;
                //red1 = (double)(red1 / (pow(2, bits) - 1));
                red1 += (gamma * errorRed);
                green1 = (double)(*this)(i + 1,j).g / 255;
                //green1 = (double)(green1 / (pow(2, bits) - 1));
                green1 += (gamma * errorGreen);
                blue1 = (double)(*this)(i + 1,j).b / 255;
                //blue1 = (double)(blue1 / (pow(2, bits) - 1));
                blue1 += (gamma * errorBlue);


                red1 = boundary(red1 * 255);
                green1 = boundary(green1 * 255);
                blue1 = boundary(blue1 * 255);

                (*img)(i + 1,j).r = (unsigned char)red1;
                (*img)(i + 1,j).g = (unsigned char)green1;
                (*img)(i + 1,j).b = (unsigned char)blue1;

            }
            //step four
            if (!or4) {

                red1 = (double)(*this)(i + 1,j + 1).r / 255;
                //red1 = (double)(red1 / (pow(2, bits) - 1));
                red1 += (delta * errorRed);
                green1 = (double)(*this)(i + 1,j + 1).g / 255;
                //green1 = (double)(green1 / (pow(2, bits) - 1));
                green1 += (delta * errorGreen);
                blue1 = (double)(*this)(i + 1,j + 1).b / 255;
                //blue1 = (double)(blue1 / (pow(2, bits) - 1));
                blue1 += (delta * errorBlue);


                red1 = boundary(red1 * 255);
                green1 = boundary(green1 * 255);
                blue1 = boundary(blue1 * 255);

                (*img)(i + 1,j + 1).r = (unsigned char)red1;
                (*img)(i + 1,j + 1).g = (unsigned char)green1;
                (*img)(i + 1,j + 1).b = (unsigned char)blue1;

            }

            // below is for the pixel your on
            or1 = false;
            or2 = false;
            or3 = false;
            or4 = false;
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

    //dont forget to normalize everything
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
            mask[i][j] = -0.125;
        }
    }
    //middle value
    mask[1][1] = 1.0;

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
