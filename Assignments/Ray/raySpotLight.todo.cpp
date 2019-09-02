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
#include "raySpotLight.h"


////////////////////////
//  Ray-tracing stuff //
////////////////////////
Point3D RaySpotLight::getAmbient( Point3D cameraPosition , RayIntersectionInfo& iInfo )
{
	Util::Throw( "RaySpotLight::getAmbient undefined" );
	return Point3D();
}
Point3D RaySpotLight::getDiffuse( Point3D cameraPosition , RayIntersectionInfo& iInfo )
{
	Util::Throw( "RaySpotLight::getDiffuse undefined" );
	return Point3D();
}
Point3D RaySpotLight::getSpecular( Point3D cameraPosition , RayIntersectionInfo& iInfo )
{
	Util::Throw( "RaySpotLight::getSpecular undefined" );
	return Point3D();
}
bool RaySpotLight::isInShadow( RayIntersectionInfo& iInfo , RayShape* shape )
{
	Util::Throw( "RaySpotLight::isInShadow undefined" );
	return false;
}
Point3D RaySpotLight::transparency( RayIntersectionInfo& iInfo , RayShape* shape , Point3D cLimit )
{
	Util::Throw( "RaySpotLight::transparency undefined" );
	return Point3D(1,1,1);
}

//////////////////
// OpenGL stuff //
//////////////////
void RaySpotLight::drawOpenGL( int index , GLSLProgram * glslProgram )
{
	Util::Throw( "RaySpotLight::drawOpenGL undefined" );
}