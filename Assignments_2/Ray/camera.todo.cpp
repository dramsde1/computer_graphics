#define GL_SILENCE_DEPRECATION
#include <cmath>
#include "../Util/exceptions.h"
#include "camera.h"
#include "shape.h"

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
    double distance = 5;
    Point3D towards = (*this).forward;
    double angle_v = (*this).heightAngle;
    Point3D up = (*this).up;
    Point3D p0 = (*this).position;

    //up is right 
    //up becomes right
    double ar = height / width;
    //sin(theta_h / 2) = sin(theta_v / 2) / ar 
    double angle_h = sin(angle_v / 2) / ar;
    //theta_h / 2 = arcsin(sin(theta_v / 2) / ar) 
    angle_h = asin(angle_h);
    //theta_h = arcsin(sin(theta_v / 2) / ar) * 2 
    angle_h = angle_h * 2;
    Point3D right = (*this).right;

    //combine the above two steps
    //down and to the left
    Point3D pBottomLeft = p0 + distance * towards - distance * tan(angle_v/2) * up - distance * tan(angle_h / 2) * right;
    //down and to the right
    Point3D pBottomRight = p0 + distance * towards - distance * tan(angle_v/2) * up + distance * tan(angle_h / 2) * right;
    //up and to the left
    Point3D pTopLeft = p0 + distance * towards + distance * tan(angle_v/2) * up - distance * tan(angle_h / 2) * right;
    //up and to the right
    Point3D pTopRight = p0 + distance * towards + distance * tan(angle_v/2) * up + distance * tan(angle_h / 2) * right;
    //try using right or up 
    Point3D target = pTopLeft + ((j + 0.5) / width) * (pTopRight - pTopLeft) + ((i + 0.5) / height) * (pTopRight - pBottomRight);
    target = target.unit();


    Ray3D *ray = new Ray3D(p0, target);

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
