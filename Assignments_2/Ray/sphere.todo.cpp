#include <cmath>
#include "../Util/exceptions.h"
#include "scene.h"
#include "sphere.h"

using namespace Ray;
using namespace Util;

////////////
// Sphere //
////////////

void Sphere::init( const LocalSceneData &data )
{
	// Set the material pointer
	if( _materialIndex<0 ) THROW( "negative material index: %d" , _materialIndex );
	else if( _materialIndex>=data.materials.size() ) THROW( "material index out of bounds: %d <= %d" , _materialIndex , (int)data.materials.size() );
	else _material = &data.materials[ _materialIndex ];

	///////////////////////////////////
	// Do any additional set-up here //
	///////////////////////////////////
	WARN_ONCE( "method undefined" );
}
void Sphere::updateBoundingBox( void )
{
	///////////////////////////////
	// Set the _bBox object here //
	///////////////////////////////
	THROW( "method undefined" );
}
void Sphere::initOpenGL( void )
{
	///////////////////////////
	// Do OpenGL set-up here //
	///////////////////////////
	WARN_ONCE( "method undefined" );

	// Sanity check to make sure that OpenGL state is good
	ASSERT_OPEN_GL_STATE();	
}

bool quadraticEq(double &a, double &b, double &c, double &t0, double &t1) {
    double delta = b * b - 4 * a * c;
    //if less than zero no intersection
    if (delta < 0) {
        return false;
    }
    //one solution if delta is 0
    else if (delta == 0) {
        t0 = -0.5 * b / a;
        t1 = t0;
    }
    //otherwise there is two solutions
    else {
        t0 = (-b - sqrt(delta)) / (2 * a);
        t1 = (-b + sqrt(delta)) / (2 * a);
    }
    if (t0 > t1) {
        std::swap(t0, t1);
    }
    return true;
}


double Sphere::intersect( Ray3D ray , RayShapeIntersectionInfo &iInfo , BoundingBox1D range , std::function< bool (double) > validityLambda ) const
{
	//////////////////////////////////////////////////////////////
	// Compute the intersection of the sphere with the ray here //
	//////////////////////////////////////////////////////////////
    double t0, t1 = 0;
    Point3D rayOrigin = ray.position;
    Point3D rayDirection = ray.direction;
    double r2 = (*this).radius * (*this).radius;
    Point3D sphereCenter = (*this).center;

    Point3D diff = rayOrigin - sphereCenter;
    double a = rayDirection.dot(rayDirection);
    double b = 2 * rayDirection.dot(diff);
    double c = diff.dot(diff) - r2;
    if (!quadraticEq(a, b, c, t0, t1)) {
        return Infinity;
    }
    if (t0 < 0) {
        //negative values are invalid
        t0 = t1; 
        if (t0 < 0) {
            //both are negative
            return Infinity;
        }
    }
    //return first interection point
	return t0;
}

bool Sphere::isInside( Point3D p ) const
{
	//////////////////////////////////////////////////////
	// Determine if the point is inside the sphere here //
	//////////////////////////////////////////////////////
	THROW( "method undefined" );
	return false;
}

void Sphere::drawOpenGL( GLSLProgram * glslProgram ) const
{
	//////////////////////////////
	// Do OpenGL rendering here //
	//////////////////////////////
	THROW( "method undefined" );

	// Sanity check to make sure that OpenGL state is good
	ASSERT_OPEN_GL_STATE();	
}
