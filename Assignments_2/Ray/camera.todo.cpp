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
    Point3D p1 = p0 + distance * towards - distance * tan(angle_v/2) * up;
    Point3D p2 = p0 + distance * towards + distance * tan(angle_v/2) * up;
    Point3D pi = p1 + ((double)(i + 0.5) / height) * (p2 - p1);


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
    Point3D P1 = p0 + distance * towards - distance * tan(angle_h / 2) * right; 
    Point3D P2 = p0 + distance * towards + distance * tan(angle_h / 2) * right; 
    Point3D Pj = P1 + ((double)(j + 0.5) / width) * (P2 - P1);

    //add these two 
    Point3D Pij = pi + Pj;

    Ray3D *ray = new Ray3D(p0, Pij);

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
