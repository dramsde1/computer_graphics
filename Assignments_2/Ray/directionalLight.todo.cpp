#include <cmath>
#include <Util/exceptions.h>
#include "directionalLight.h"
#include "scene.h"

using namespace Ray;
using namespace Util;

//////////////////////
// DirectionalLight //
//////////////////////

Point3D DirectionalLight::getAmbient( Ray3D ray , const RayShapeIntersectionInfo& iInfo ) const
{
	////////////////////////////////////////////////////
	// Get the ambient contribution of the light here //
	////////////////////////////////////////////////////
    Point3D Ka = iInfo.material->ambient;
    double red = Ka[0] * _ambient[0];
    double green = Ka[1] * _ambient[1];
    double blue = Ka[2] * _ambient[2];
    Point3D IA = Point3D(red, green, blue);
    
	return IA;
}

Point3D DirectionalLight::getDiffuse( Ray3D ray , const RayShapeIntersectionInfo& iInfo ) const
{
	////////////////////////////////////////////////////
	// Get the diffuse contribution of the light here //
	////////////////////////////////////////////////////
    Point3D Kd = iInfo.material->diffuse;
    Point3D toLight = _direction * -1;
    double prod = iInfo.normal.dot(toLight);
    if (prod < 0) {
        prod = 0;
    }
    else if (prod > 1) {
        prod = 1;
    }
    double red = Kd[0] * prod * _diffuse[0];
    double green = Kd[1] * prod * _diffuse[1];
    double blue = Kd[2] * prod * _diffuse[2];
    return Point3D(red, green, blue);
}

Point3D DirectionalLight::getSpecular( Ray3D ray , const RayShapeIntersectionInfo& iInfo ) const
{
	/////////////////////////////////////////////////////
	// Get the specular contribution of the light here //
	/////////////////////////////////////////////////////
    Point3D Ks = iInfo.material->specular;
    double n = iInfo.material->specularFallOff;
    Point3D normal = iInfo.normal.unit();
    Point3D v = ray.direction * -1;
    Point3D reflect = Scene::Reflect(_direction, normal);
    double dirreflect = v.dot(reflect);
    if (dirreflect < 0) {
        dirreflect = 0;
    }
    double prod = pow(dirreflect, n);
    if (prod < 0) {
        prod = 0;
    }
    double Isred = Ks[0] * prod * _specular[0];
    double Isgreen = Ks[1] * prod * _specular[1];
    double Isblue = Ks[2] * prod * _specular[2];
    Point3D Is = Point3D(Isred, Isgreen, Isblue);
    return Is;
}

bool DirectionalLight::isInShadow( const RayShapeIntersectionInfo& iInfo , const Shape* shape ) const
{
	//////////////////////////////////////////////
	// Determine if the light is in shadow here //
	//////////////////////////////////////////////
    Ray3D toLight = Ray3D(iInfo.position + Epsilon * _direction * -1, _direction * -1);
    RayShapeIntersectionInfo temp = RayShapeIntersectionInfo();
    double t = shape->intersect(toLight, temp);
    if (t != Infinity) {
        return true;
    }
    else {
        return false;
    }
}

Point3D DirectionalLight::transparency( const RayShapeIntersectionInfo &iInfo , const Shape &shape , Point3D cLimit ) const
{
	//////////////////////////////////////////////////////////
	// Compute the transparency along the path to the light //
	//////////////////////////////////////////////////////////
    //Ray3D toLight = Ray3D(iInfo.position + Epsilon * _direction * -1, _direction * -1);
    RayShapeIntersectionInfo temp = RayShapeIntersectionInfo();
    Ray3D toLight = Ray3D(iInfo.position + Epsilon * _direction * -1, _direction * -1);
    double t = shape.intersect(toLight, temp);
    if (t < Infinity && temp.material->transparent.length() > cLimit.length()) {
        return temp.material->transparent * transparency(temp, shape, cLimit/temp.material->transparent);
    }
	return Point3D( 1. , 1. , 1. );
}

void DirectionalLight::drawOpenGL( int index , GLSLProgram * glslProgram ) const
{
	//////////////////////////////
	// Do OpenGL rendering here //
	//////////////////////////////
	THROW( "method undefined" );

	// Sanity check to make sure that OpenGL state is good
	ASSERT_OPEN_GL_STATE();	
}
