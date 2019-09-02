#include <math.h>
#include <stdlib.h>
#include <GL/glew.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else // !__APPLE__
#include <GL/glut.h>
#endif // __APPLE__
#include <Util/exceptions.h>
#include "rayScene.h"
#include "raySphere.h"

////////////////////////
//  Ray-tracing stuff //
////////////////////////
double RaySphere::intersect( Ray3D ray , RayIntersectionInfo& iInfo , double mx )
{
	Util::Throw( "RaySphere::intersect undefined" );
	return -1;
}

BoundingBox3D RaySphere::setBoundingBox( void )
{
	Util::Throw( "RaySphere::setBoundingBox undefined" );
	return bBox;
}

//////////////////
// OpenGL stuff //
//////////////////
void RaySphere::setUpOpenGL( int cplx , bool setBufferObjects )
{
	openGLComplexity = cplx;
	_vertexArrayID = _elementBufferID = _vertexBufferID = 0;
	Util::Throw( "RaySphere::setUpOpenGL undefined" );
}

int RaySphere::drawOpenGL( int materialIndex , GLSLProgram * glslProgram )
{
	Util::Throw( "RaySphere::drawOpenGL undefined" );
	return -1;
}
