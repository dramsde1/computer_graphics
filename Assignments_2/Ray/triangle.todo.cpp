#include <cmath>
#include "../Util/exceptions.h"
#include "triangle.h"

using namespace Ray;
using namespace Util;

//////////////
// Triangle //
//////////////

void Triangle::init( const LocalSceneData &data )
{
	// Set the vertex pointers
	for( int i=0 ; i<3 ; i++ )
	{
		if( _vIndices[i]==-1 ) THROW( "negative vertex index: %d" , _vIndices[i] );
		else if( _vIndices[i]>=data.vertices.size() ) THROW( "vertex index out of bounds: %d <= %d" , _vIndices[i] , (int)data.vertices.size() );
		else _v[i] = &data.vertices[ _vIndices[i] ];
	}

	///////////////////////////////////
	// Do any additional set-up here //
	///////////////////////////////////
	WARN_ONCE( "method undefined" );
}
void Triangle::updateBoundingBox( void )
{
	///////////////////////////////
	// Set the _bBox object here //
	///////////////////////////////
	THROW( "method undefined" );
}
void Triangle::initOpenGL( void )
{
	///////////////////////////
	// Do OpenGL set-up here //
	///////////////////////////
	WARN_ONCE( "method undefined" );

	// Sanity check to make sure that OpenGL state is good
	ASSERT_OPEN_GL_STATE();	
}

double Triangle::intersect( Ray3D ray , RayShapeIntersectionInfo& iInfo , BoundingBox1D range , std::function< bool (double) > validityLambda ) const
{
	/////////////////////////////////////////////////////////////
	// Compute the intersection of the shape with the ray here //
	/////////////////////////////////////////////////////////////
	//THROW( "method undefined" );
    Point3D rayOrigin = ray.position;
    Point3D rayDirection = ray.direction;
    Point3D vertexA = (_v[1]->position - _v[0]->position); //first edge 1 - 0
    //Point3D vertexA = (_v[1] - _v[0]); //first edge 1 - 0
    Point3D vertexB = (_v[2]->position - _v[0]->position); //second edge 2 - 0
    //Point3D vertexNormal = vertexA.CrossProduct(vertexB); //triangle normal
    Point3D vertexNormal = Point3D::CrossProduct(vertexA, vertexB);
    vertexNormal = vertexNormal.unit();
    double D = (double)vertexNormal.dot(_v[0]->position);
    RayShapeIntersectionInfo temp = RayShapeIntersectionInfo();
    //get position P
    //first check to see if ray and triangle are parallel
    //dot product of two perp vectors is zero
    if (vertexNormal.dot(rayDirection) == 0) {
        return Infinity;
    }
    //camera oriented on negative z axis
    double t = - (vertexNormal.dot(rayOrigin) + D) / vertexNormal.dot(rayDirection); //was -
    //behind ray
    if (t < 0) {
        return Infinity;
    }
    Point3D P = rayOrigin + t * rayDirection;
    //only have done two
    temp.position = P; 
    temp.normal = vertexNormal;

    Point3D e0 = _v[1]->position - _v[0]->position;
    Point3D e1 = _v[2]->position - _v[1]->position;
    Point3D e2 = _v[0]->position - _v[2]->position;
    Point3D C0 = P - _v[0]->position;
    Point3D C1 = P - _v[1]->position;
    Point3D C2 = P - _v[2]->position;
    //check if point P is inside triangle
    double check1 = vertexNormal.dot(Point3D::CrossProduct(e0, C0));
    //double check1 = vertexNormal.dot(e0.CrossProduct(C0));
    double check2 = vertexNormal.dot(Point3D::CrossProduct(e1, C1));
    //double check2 = vertexNormal.dot(e1.CrossProduct(C1));
    double check3 = vertexNormal.dot(Point3D::CrossProduct(e2, C2));
    //double check3 = vertexNormal.dot(e2.CrossProduct(C2));
    
    if (check1 > 0 && check2 > 0 && check3 > 0) {
        iInfo = temp;
        return t;
    }
    else {
	    return Infinity;
    }

}

void Triangle::drawOpenGL( GLSLProgram * glslProgram ) const
{
	//////////////////////////////
	// Do OpenGL rendering here //
	//////////////////////////////
	THROW( "method undefined" );

	// Sanity check to make sure that OpenGL state is good
	ASSERT_OPEN_GL_STATE();	
}
