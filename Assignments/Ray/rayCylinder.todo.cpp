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
#include "rayCylinder.h"

////////////////////////
//  Ray-tracing stuff //
////////////////////////
double RayCylinder::intersect( Ray3D ray , RayIntersectionInfo& iInfo , double mx )
{
	Util::Throw( "RayCylinder::intersect undefined" );
	return -1;
}

BoundingBox3D RayCylinder::setBoundingBox( void )
{
	Util::Throw( "RayCylinder::setBoundingBox undefined" );
	return bBox;
}

//////////////////
// OpenGL stuff //
//////////////////
void RayCylinder::setUpOpenGL( int cplx , bool setBufferObjects )
{
	openGLComplexity = cplx;
	_vertexArrayID = _elementBufferID = _vertexBufferID = 0;
	Util::Throw( "RayCylinder::setUpOpenGL undefined" );
}

int RayCylinder::drawOpenGL( int materialIndex , GLSLProgram * glslProgram )
{
	Util::Throw( "RayCylinder::drawOpenGL undefined" );
	return -1;
}
