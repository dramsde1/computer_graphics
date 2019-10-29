#include <cmath>
#include "../Util/exceptions.h"
#include "scene.h"

using namespace Ray;
using namespace Util;

///////////
// Scene //
///////////
Point3D Scene::Reflect( Point3D v , Point3D n )
{
	//////////////////
	// Reflect here //
	//////////////////
	return v - (2 * n.dot(v)* n);
}

bool Scene::Refract( Point3D v , Point3D n , double ir , Point3D& refract )
{
	//////////////////
	// Refract here //
	//////////////////
    double angle_i, angle_r;
    v = v * -1;
    //perpendicular
    if (v.dot(n) > 0.0) {
        ir = 1.0 / ir;
    }
    else {
        n = n * -1;
    }
    angle_i = acos(v.dot(n));
    angle_r = sin(angle_i) * ir;
    if (angle_r > 1.0) {
        return false;
    }
    else {
        angle_r = asin(angle_r);
    }
    refract = (ir * cos(angle_i) - cos(angle_r)) * n - ir * v;
	return true;
}

Point3D Scene::getColor( Ray3D ray , int rDepth , Point3D cLimit )
{
	////////////////////////////////////////////////
	// Get the color associated with the ray here //
	////////////////////////////////////////////////
	//THROW( "method undefined" );
    //get temp variable that 
    RayShapeIntersectionInfo iInfo = RayShapeIntersectionInfo();
    //run for each color channel
    Point3D b = Point3D(0.0, 0.0, 0.0);
    Point3D pixel;
    Ray3D reflect, refract;
    Point3D r;
    bool rbool;
    double t = (*this).intersect(ray, iInfo);
    if (t == Infinity) {
        return b;
    }
    //update iInfo
    Point3D emissive = iInfo.material->emissive;
    pixel += emissive;
    for (int i = 0; i < _globalData.lights.size(); i++) {
        auto light = _globalData.lights[i];
        Point3D ambient = light->getAmbient(ray, iInfo);
        Point3D diffuse = light->getDiffuse(ray, iInfo);
        Point3D specular = light->getSpecular(ray, iInfo);
        Point3D trans = light->transparency(iInfo, *this, cLimit);
       // bool shadow = light->isInShadow(iInfo, this);
       // double isInShadow = 0;
       // if (shadow) {
       //     isInShadow = 0;
       // }
       // else {
       //     isInShadow = 1;
       // }
        //reflect
        pixel += ambient + (diffuse + specular) * trans;
        //pixel += ambient + (diffuse + specular) * isInShadow;
        reflect.direction = Reflect(ray.direction, iInfo.normal);
        reflect.position = iInfo.position + reflect.direction * Epsilon;
        double prod = iInfo.normal.dot(ray.direction);
        if (rDepth > 0 && iInfo.material->specular[0] > cLimit[0] && prod < 0) {
            pixel += getColor(reflect, rDepth - 1, cLimit/iInfo.material->specular) * iInfo.material->specular;
        }

        //refract
        rbool = Refract(ray.direction, iInfo.normal, iInfo.material->ir, r);
        if (rDepth > 0 && iInfo.material->transparent[0] > cLimit[0] && rbool) {
            refract.direction = r;
            refract.position = iInfo.position + r * Epsilon;
            pixel += getColor(refract, rDepth - 1, cLimit/iInfo.material->transparent) * iInfo.material->transparent;
        }

    }
    if (t < Infinity) {
        return Point3D( std::min< double >( 1. , std::max< double >( 0. , pixel[0])) , std::min< double >( 1. , std::max< double >( 0. , pixel[1])) , std::min< double >( 1. , std::max< double >( 0. , pixel[2] ) ) );
        return pixel;
    }
    else {
        return b;
    }
}

//////////////
// Material //
//////////////
void Material::drawOpenGL( GLSLProgram * glslProgram ) const
{
	//////////////////////////////
	// Do OpenGL rendering here //
	//////////////////////////////
	THROW( "method undefined" );

	// Sanity check to make sure that OpenGL state is good
	ASSERT_OPEN_GL_STATE();	
}

/////////////
// Texture //
/////////////
void Texture::initOpenGL( void )
{
	///////////////////////////////////
	// Do OpenGL texture set-up here //
	///////////////////////////////////
	THROW( "method undefined" );

	// Sanity check to make sure that OpenGL state is good
	ASSERT_OPEN_GL_STATE();	
}
