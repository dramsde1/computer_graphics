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
    printf("method undefined");
}
void Sphere::initOpenGL( void )
{
	///////////////////////////
	///////////////////////////
	WARN_ONCE( "method undefined" );

	// Sanity check to make sure that OpenGL state is good
	ASSERT_OPEN_GL_STATE();	
}


double Sphere::intersect( Ray3D ray , RayShapeIntersectionInfo &iInfo , BoundingBox1D range , std::function< bool (double) > validityLambda ) const
{
	//////////////////////////////////////////////////////////////
	// Compute the intersection of the sphere with the ray here //
	//////////////////////////////////////////////////////////////
    double t0, t1 = 0;
    Point3D rayOrigin = ray.position;
    Point3D rayDirection = ray.direction.unit();
    double r2 = (*this).radius * (*this).radius;
    Point3D sphereCenter = (*this).center;

    Point3D diff = rayOrigin - sphereCenter;
    double a = 1;
    double b = 2 * rayDirection.dot(diff);
    double c = diff.dot(diff) - r2;
    Polynomial1D<2> p = Polynomial1D<2>();
    p.coefficient(2) = 1; //2 is the degree of x and 1 is the value of the coefficient
    p.coefficient(1) = b;
    p.coefficient(0) = c;
    double * arr = new double[2]; //dont forget to free
    double numRoots = p.roots(arr);
    if (numRoots > 0) {
        return 1;
    }
    //return first interection point
	return Infinity;
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
