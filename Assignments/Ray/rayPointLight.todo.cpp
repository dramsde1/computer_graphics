#include <math.h>
#include <stdlib.h>
#include <GL/glew.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else // !__APPLE__
#include <GL/glut.h>
#endif // __APPLE__
#include <Util/exceptions.h>
#include "rayPointLight.h"
#include "rayScene.h"

////////////////////////
//  Ray-tracing stuff //
////////////////////////
Point3D RayPointLight::getAmbient( Point3D cameraPosition , RayIntersectionInfo& iInfo )
{
	Util::Throw( "RayPointLight::getAmbient undefined" );
	return Point3D();
}
Point3D RayPointLight::getDiffuse( Point3D cameraPosition , RayIntersectionInfo& iInfo )
{
	Util::Throw( "RayPointLight::getDiffuse undefined" );
	return Point3D();
}
Point3D RayPointLight::getSpecular( Point3D cameraPosition , RayIntersectionInfo& iInfo )
{
	Util::Throw( "RayPointLight::getSpecular undefined" );
	return Point3D();
}
bool RayPointLight::isInShadow( RayIntersectionInfo& iInfo , RayShape* shape )
{
	Util::Throw( "RayPointLight::isInShadow undefined" );
	return false;
}
Point3D RayPointLight::transparency( RayIntersectionInfo& iInfo , RayShape* shape , Point3D cLimit )
{
	Util::Throw( "RayPointLight::transparency undefined" );
	return Point3D(1,1,1);
}


//////////////////
// OpenGL stuff //
//////////////////
void RayPointLight::drawOpenGL( int index , GLSLProgram * glslProgram )
{
	Util::Throw( "RayPointLight::drawOpenGL undefined" );
}