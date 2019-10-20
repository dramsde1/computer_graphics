#define GL_SILENCE_DEPRECATION
#include <cmath>
#include "../Util/exceptions.h"
#include "camera.h"
#include "shape.h"
#include <stdio.h>

using namespace Ray;
using namespace Util;

////////////
// Camera //
////////////

Ray3D Camera::getRay( int i , int j , int width , int height ) const
{
	/////////////////////////////////////////////////
	// Get the ray through the (i,j)-th pixel here //
	/////////////////////////////////////////////////
    //First view plane
    //double distance = 1;
    Point3D towards = (*this).forward;
    double angle_v = (*this).heightAngle;
    Point3D up = (*this).up;
    Point3D p0 = (*this).position;
    std::cout << p0 << std::endl;
    double ar = (double)height / (double)width;
    double scale = tan(angle_v * 0.5);
 //   std::cout << "scale";
 //   std::cout << scale << std::endl;
    //std::cout << "scal ";
    //std::cout << scale << std::endl;
    double x = (2 * (i + 0.5) / (double)width - 1) * ar * scale;
  //  std::cout << "x";
  //  std::cout << x << std::endl;
    double y = (1 - 2 * (j + 0.5) / (double)height) * scale; 
   // std::cout << "y";
   // std::cout << y << std::endl;
    Point3D target = Point3D(x, y, -1.0); 
    Point3D dir;
    dir = target - p0;
    dir = dir.unit();
    Ray3D *ray = new Ray3D(p0, dir);


    //std::cout << "x ";
    //std::cout << i << std::endl;
    //std::cout << "y ";
    //std::cout << j << std::endl;
    

    
    //normalized device coordinates
   // double x_NDC = ((double)i + 0.5) / width;
   // double y_NDC = ((double)j + 0.5) / height;
   // double x_screen = 2.0 * x_NDC - 1.0;
   // double y_screen = 2.0 * y_NDC - 1.0;
   // y_screen = 1.0 - 2.0 * y_NDC;
   // double x_camera = (2.0 * x_screen - 1.0) * ar;
   // double y_camera = (1.0 - 2.0 * y_screen);
   // x_camera = (2.0 * x_screen - 1.0) * ar * tan(angle_v / 2.0);
   // y_camera = (1.0 - 2.0 * y_screen) * tan(angle_v / 2.0);
   // Point3D target = Point3D(x_camera, y_camera, -1.0); //camera space
   // Point3D dir = target - p0;
   // dir = dir.unit();
   // Ray3D *ray = new Ray3D(p0, dir);

    //std::cout << (*ray).direction << std::endl;


//
//    //up is right 
//    //up becomes right
    //sin(theta_h / 2) = sin(theta_v / 2) / ar 
//    double angle_h = sin(angle_v / 2) / ar;
//    //theta_h / 2 = arcsin(sin(theta_v / 2) / ar) 
//    angle_h = asin(angle_h);
//    //theta_h = arcsin(sin(theta_v / 2) / ar) * 2 
//    angle_h = angle_h * 2;
//    Point3D right = (*this).right;
//
//    //combine the above two steps
//    //down and to the left
//    Point3D pBottomLeft = p0 + distance * towards - distance * tan(angle_v/2) * up - distance * tan(angle_h / 2) * right;
//    //down and to the right
//    Point3D pBottomRight = p0 + distance * towards - distance * tan(angle_v/2) * up + distance * tan(angle_h / 2) * right;
//    //up and to the left
//    Point3D pTopLeft = p0 + distance * towards + distance * tan(angle_v/2) * up - distance * tan(angle_h / 2) * right;
//    //up and to the right
//    Point3D pTopRight = p0 + distance * towards + distance * tan(angle_v/2) * up + distance * tan(angle_h / 2) * right;
//    //try using right or up 
//    Point3D target = pTopLeft + ((j + 0.5) / width) * (pTopRight - pTopLeft) + ((i + 0.5) / height) * (pTopRight - pBottomRight);
//    target = target.unit();
//
//
//    Ray3D *ray = new Ray3D(p0, target);
//
    return *ray;
}

void Camera::drawOpenGL( void ) const
{
	//////////////////////////////
	// Do OpenGL rendering here //
	//////////////////////////////
	THROW( "method undefined" );

	// Sanity check to make sure that OpenGL state is good
	ASSERT_OPEN_GL_STATE();	
}

void Camera::rotateUp( Point3D center , float angle )
{
	///////////////////////////////////////////////////
	// Rotate the camera about the up direction here //
	///////////////////////////////////////////////////
	THROW( "method undefined" );
}

void Camera::rotateRight( Point3D center , float angle )
{
	//////////////////////////////////////////////////////
	// Rotate the camera about the right direction here //
	//////////////////////////////////////////////////////
	THROW( "method undefined" );
}

void Camera::moveForward( float dist )
{
	//////////////////////////////////
	// Move the camera forward here //
	//////////////////////////////////
	THROW( "method undefined" );
}

void Camera::moveRight( float dist )
{
	///////////////////////////////////////
	// Move the camera to the right here //
	///////////////////////////////////////
	THROW( "method undefined" );
}

void Camera::moveUp( float dist )
{
	/////////////////////////////
	// Move the camera up here //
	/////////////////////////////
	THROW( "method undefined" );
}
