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
    RayShapeIntersectionInfo temp = RayShapeIntersectionInfo();
    double t0, t1, t = 0;
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
    temp.material = (*this)._material;
    if (numRoots > 0) {
        return 1;
    }
    return Infinity;
//    if (numRoots > 0) {
//        if (numRoots == 1) {
//            t0 = arr[0];
//            if (t0 < 0) return Infinity;
//            Point3D P = rayOrigin + rayDirection * t0;
//            temp.position = P;
//            temp.normal = (P - sphereCenter).unit();
//            temp.material = (*this)._material;
//            iInfo = temp;
//            std::cout << t0 << std::endl;
//            return t0;
//        }
//        if (numRoots == 2) {
//            t0 = arr[0];
//            t1 = arr[1];
//            if (t0 > t1) std::swap(t0, t1); 
//            if (t0 < 0) { 
//                t0 = t1; // if t0 is negative, let's use t1 instead 
//                if (t0 < 0) return Infinity; // both t0 and t1 are negative 
//            } 
//            Point3D P = rayOrigin + rayDirection * t0;
//            temp.position = P;
//            temp.normal = (P - sphereCenter).unit();
//            temp.material = (*this)._material;
//            iInfo = temp;
//            std::cout << t0 << std::endl;
//            return t0;
//        }
//    }
//    else {
//        return Infinity;
//    }
    //return first interection point
}
//do iInfo stuff here for sphere 
//do iInfo stuff in TriangleList in TriangleList

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
