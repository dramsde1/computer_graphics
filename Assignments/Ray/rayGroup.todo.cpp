#include <stdlib.h>
#include <stdlib.h>
#include <GL/glew.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else // !__APPLE__
#include <GL/glut.h>
#endif // __APPLE__
#include <Util/exceptions.h>
#include "rayGroup.h"
#include "rayTriangle.h"

////////////////////////
//  Ray-tracing stuff //
////////////////////////
double RayGroup::intersect( Ray3D ray , RayIntersectionInfo& iInfo , double mx )
{
	Util::Throw( "RayGroup::intersect undefined" );
	return -1;
}

BoundingBox3D RayGroup::setBoundingBox( void )
{
	Util::Throw( "RayGroup::setBoundingBox undefined" );
	return bBox;
}

bool StaticRayGroup::set( void )
{
	static bool firstTime = true;
	if( firstTime ) Util::Warn( "StaticRayGroup::set undefined" );
	firstTime = false;
	return true;
}
//////////////////
// OpenGL stuff //
//////////////////
int RayGroup::drawOpenGL( int materialIndex , GLSLProgram * glslProgram )
{
	Util::Throw( "RayGroup::drawOpenGL undefined" );
	return -1;
}

//////////////////////////
// TriangleListRayGroup //
//////////////////////////
////////////////////////
//  Ray-tracing stuff //
////////////////////////
double TriangleListRayGroup::intersect( Ray3D ray , RayIntersectionInfo& iInfo , double mx )
{
	Util::Throw( "TriangleListRayGroup::intersect undefined" );
	return -1;
}

int TriangleListRayGroup::drawOpenGL( int materialIndex , GLSLProgram * glslProgram )
{
	Util::Throw( "TriangleListRayGroup::drawOpenGL undefined" );
	return -1;
}

void TriangleListRayGroup::setUpOpenGL( int cplx , bool setBufferObjects )
{
	_vertexArrayID = _vertexBufferID = _elementBufferID = 0;
	Util::Throw( "TriangleListRayGroup::setUpOpenGL undefined" );
}

/////////////////////
// Animation Stuff //
/////////////////////
Matrix4D ParametrizedEulerAnglesAndTranslation::getMatrix( void )
{
	Util::Throw( "ParametrizedEulerAnglesAndTranslation::getMatrix undefined" );
	return Matrix4D::IdentityMatrix();
}
Matrix4D ParametrizedClosestRotationAndTranslation::getMatrix( void )
{
	Util::Throw( "ParametrizedClosestRotationAndTranslation::getMatrix undefined" );
	return Matrix4D::IdentityMatrix();
}
Matrix4D ParametrizedRotationLogarithmAndTranslation::getMatrix( void )
{
	Util::Throw( "ParametrizedRotationLogarithmAndTranslation::getMatrix undefined" );
	return Matrix4D::IdentityMatrix();
}
Matrix4D ParametrizedQuaternionAndTranslation::getMatrix( void )
{
	Util::Throw( "ParametrizedQuaternionAndTranslation::getMatrix undefined" );
	return Matrix4D::IdentityMatrix();
}
