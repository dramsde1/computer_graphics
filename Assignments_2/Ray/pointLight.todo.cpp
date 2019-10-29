#include <cmath>
#include <Util/exceptions.h>
#include "pointLight.h"
#include "scene.h"

using namespace Ray;
using namespace Util;

////////////////
// PointLight //
////////////////

Point3D PointLight::getAmbient( Ray3D ray , const RayShapeIntersectionInfo& iInfo ) const
{
	////////////////////////////////////////////////////
	// Get the ambient contribution of the light here //
	////////////////////////////////////////////////////
    Point3D Ka = iInfo.material->ambient;
    double r = _ambient[0] * Ka[0];
    double g = _ambient[1] * Ka[1];
    double b = _ambient[2] * Ka[2];
    Point3D sig = (ray.position - _location).unit();
    double sigma = sig.length();
    double Ired = r / ((double)_constAtten + (double)_linearAtten * sigma + (double)_quadAtten * sig.dot(sig));
    double Igreen = g / ((double)_constAtten + (double)_linearAtten * sigma + (double)_quadAtten * sig.dot(sig));
    double Iblue = b / ((double)_constAtten + (double)_linearAtten * sigma + (double)_quadAtten * sig.dot(sig));
    
	return Point3D(Ired, Igreen, Iblue) ;
}

Point3D PointLight::getDiffuse( Ray3D ray , const RayShapeIntersectionInfo& iInfo ) const
{
	////////////////////////////////////////////////////
	// Get the diffuse contribution of the light here //
	////////////////////////////////////////////////////
	//THROW( "method undefined" );
    Point3D Kd = iInfo.material->diffuse;
    Point3D sig = (ray.position - _location).unit();
    Point3D diffuse = _diffuse;
    double sigma = sig.length();
    double ILred = (double)diffuse[0] / ((double)_constAtten + (double)_linearAtten * sigma + (double)_quadAtten * sig.dot(sig));
    double ILgreen = (double)diffuse[1] / ((double)_constAtten + (double)_linearAtten * sigma + (double)_quadAtten * sig.dot(sig));
    double ILblue = (double)diffuse[2] / ((double)_constAtten + (double)_linearAtten * sigma + (double)_quadAtten * sig.dot(sig));
    Point3D IL = Point3D(ILred, ILgreen, ILblue);
    //Point3D Id = Kd * -iInfo.normal.dot(ray.direction) * IL; //check ray direction
    //Point3D toLight = _direction * -1;
    Point3D toLight = (ray.position - _location).unit() * -1;
    double NL = iInfo.normal.dot(toLight);
    if (NL < 0) {
        NL = 0;
    }
    else if (NL > 1) {
        NL = 1;
    }
    double redFinal = Kd[0] * NL * IL[0]; //check ray direction
    double greenFinal = Kd[1] * NL * IL[1]; //check ray direction
    double blueFinal = Kd[2] * NL * IL[2]; //check ray direction
	return Point3D(redFinal, greenFinal, blueFinal);
}

Point3D PointLight::getSpecular( Ray3D ray , const RayShapeIntersectionInfo& iInfo ) const
{
	/////////////////////////////////////////////////////
	// Get the specular contribution of the light here //
	/////////////////////////////////////////////////////
	//THROW( "method undefined" );
    
    Point3D Ks = iInfo.material->specular;
    double n = iInfo.material->specularFallOff;
    Point3D sig = (ray.position - _location).unit();
    double sigma = sig.length();
    Point3D specular = _specular;
    double ILred = (double)specular[0] / ((double)_constAtten + (double)_linearAtten * sigma + (double)_quadAtten * pow(sigma, 2));
    double ILgreen = (double)specular[1] / ((double)_constAtten + (double)_linearAtten * sigma + (double)_quadAtten * pow(sigma, 2));
    double ILblue = (double)specular[2] / ((double)_constAtten + (double)_linearAtten * sigma + (double)_quadAtten * pow(sigma, 2));
    Point3D normal = iInfo.normal.unit();
    Point3D v = ray.direction * -1;
    Point3D reflect = Scene::Reflect(ray.position - _location, normal);
    double dirreflect = v.dot(reflect);
    if (dirreflect < 0) {
        dirreflect = 0;
    }
    double prod = pow(dirreflect, n);
    if (prod < 0) {
        prod = 0;
    }
    double Isred = Ks[0] * prod * ILred;
    double Isgreen = Ks[1] * prod * ILgreen;
    double Isblue = Ks[2] * prod * ILblue;
    Point3D Is = Point3D(Isred, Isgreen, Isblue);
    return Is;
}

bool PointLight::isInShadow( const RayShapeIntersectionInfo& iInfo , const Shape* shape ) const
{
	//////////////////////////////////////////////
	// Determine if the light is in shadow here //
	//////////////////////////////////////////////
	//THROW( "method undefined" );
    Point3D dir = (iInfo.position - _location).unit();
    Ray3D toLight = Ray3D(iInfo.position + Epsilon * dir * -1, dir * -1);
    RayShapeIntersectionInfo temp = RayShapeIntersectionInfo();
    double t = shape->intersect(toLight, temp);
    if (t != Infinity) {
        return true;
    }
    else {
        return false;
    }
}

Point3D PointLight::transparency( const RayShapeIntersectionInfo &iInfo , const Shape &shape , Point3D cLimit ) const
{
	//////////////////////////////////////////////////////////
	// Compute the transparency along the path to the light //
	//////////////////////////////////////////////////////////
    Point3D dir = (iInfo.position - _location).unit();
    RayShapeIntersectionInfo temp = RayShapeIntersectionInfo();
    Ray3D toLight = Ray3D(iInfo.position + Epsilon * dir * -1, dir * -1);
    double t = shape.intersect(toLight, temp);
    if (t < Infinity && temp.material->transparent.length() > cLimit.length()) {
        return temp.material->transparent * transparency(temp, shape, cLimit/temp.material->transparent);
    }
	return Point3D( 1. , 1. , 1. );
}

void PointLight::drawOpenGL( int index , GLSLProgram * glslProgram ) const
{
	//////////////////////////////
	// Do OpenGL rendering here //
	//////////////////////////////
	THROW( "method undefined" );

	// Sanity check to make sure that OpenGL state is good
	ASSERT_OPEN_GL_STATE();	
}

