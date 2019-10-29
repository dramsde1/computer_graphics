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
    Point3D towards = (*this).forward.unit();
    double distance = 1;
    double angle_v = (*this).heightAngle;
    Point3D up = (*this).up;
    Point3D p0 = (*this).position;
    double ar = height / (double)width;
    double angle_h = asin(sin(angle_v / 2) / ar) * 2;
    Point3D right = (*this).right;
    //Point3D P1 = p0 + distance * towards - distance * tan(angle_h / 2) * right; 
    //Point3D P2 = p0 + distance * towards + distance * tan(angle_h / 2) * right; 
    //Point3D p1 = p0 + distance * towards - distance * tan(angle_v/2) * up;
    //Point3D p2 = p0 + distance * towards + distance * tan(angle_v/2) * up;
    Point3D view = p0 + distance * towards;
    Point3D vert = distance * tan(angle_v/2) * up;
    Point3D hor = distance * tan(angle_h / 2) * right;
    Point3D p1 = view - vert;
    Point3D p2 = view + vert;
    Point3D P1 = view - hor;
    Point3D P2 = view + hor;

    //calculate i
    Point3D pi = P1 + ((i + 0.5) / (double)height) * (P2 - P1);
    //calculate j
    Point3D pj = p1 + ((j + 0.5) / (double)width) * (p2 - p1);

    Point3D target = pi + pj - view;
    target = (target - this->position).unit();
    return Ray3D(p0, target);
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
