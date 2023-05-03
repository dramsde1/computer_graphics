# Computer Graphics Mini Projects and C++ Practice

## Image Processing (main1/Makefile1)

A simple image processing program, a pared-down version of Adobe Photoshop or The Gimp. The operations that you implement will be mostly filters which take in an input image, process the image, and produce an output image.

The executable runs on the command line. It reads an image from a specified file, processes the image using the filter specified by the command line arguments, and writes the resulting image to the specified file.
The command line parser is set up to read the arguments from the command line that are specified in the following format: First the parameter name is specified by pre-pending with two hyphens, and then the parameter values are enumerated. (Note that the number of arguments associated to each parameter are fixed in main1.cpp and the order in which the parameters are specified is ignored.)
For example, to increase the brightness of the image in.bmp by 10%, and save the result in the image out.bmp, you would type:


% Assignment1 --brighten 1.1 --in in.bmp --out out.bmp


To see the full list of possible arguments, you can simply type:
% ImageProcessing

## Simple Raytracer (main2/Makefile2)

The implementation of a basic raytracer.

The executable takes in to mandatory arguments, the input (.ray) file name and the output image file name (.bmp, .jpeg, or .jpg). Additionally, you can pass in the dimensions of the output image, the recursion depth, and the cut-off value for early termination. It is invoked from the command line with:


% Assignment2 --in <input ray-file name> --out <output image file name>
  
  
Optional arguments (with default values) are:
--width <image width>=640
--height <image height>=480
--rLimit <recursion limit>=5
--cutOff <recursion cut-off threshold>=0.0001
--lSamples <number of light samples>=100

## OpenGL Practicing (main3/Makefile3)

Practice with the OpenGL graphics library. This program generates a room scene which can be navigated in a walk-through fashion. Emphasis is placed both upon the implemention of OpenGL's basic capabilities (e.g. shading. lighting, transparency, materials properties, etc.) and their use in generating more involved effects (e.g. shadows, reflections.)

The executable takes in as a mandatory arguments the input (.ray) .ray file name. Additionally, you can also pass in the dimensions of the viewing window and the complexity of the tesselation for objects like the sphere, the cylinder, and the cone. (Specifically, this specifies the resolution, e.g. the number of angular samples.) It is invoked from the command line with:


% Assignment3 --in in.ray --width w --height h --cplx c

## Keyframe Animation (main4/Makefile4)

In addition to rendering static models, this program allows you to render animated 3D models. The key to doing this is the class DynamicAffineShape (in Ray/shapeList.[h/cpp]). which represents a transformation node in the scene-graph hierarchy whose value is a function of the time elapsed. This object stores a pointer DynamicAffineShape::_matrix to a Matrix4D. At each frame, the transformation DynamicAffineShape::_matrix is changed, and as a result, OpenGL renders a new image.
More specifically, animation is achieved through the use of the template class KeyFrameData (in Ray/keyFrames.h and Ray/keyFrames.inl). This class:

Stores the values of the different transformations associated to the different joints at the different key-frames.
Maintains an array of transformations KeyFrameData::_currentValues corresponding to the values of each joint at the current time-frame. (This is what each DynamicAffineShape::_matrix points to.)
Has a method KeyFrameData::setCurrentValues responsible for updating the transformations in KeyFrameData::_currentValues by interpolating/approximating the transformations prescribed at the different key-frames.
The samples for the values of the transformations are represented by a templated object of type TransformationParameter< RotationParameterType >. The translation component of the transformation is stored in the Point3D member TransformationParameter::translation and the rotation is stored in the RotationParameterType member TransformationParameter::rotationParameter. In this implementation, the template parameter RotationParameterType will be one of the following RotationParameter types:
TrivialRotationParameter which represents a rotation matrix by a (not necessarily rotation) Matrix3D.
EulerRotationParameter which represents a transformation by a Point3D storing the triplet of Euler angles.
MatrixRotationParameter which represents a transformation by a rotation Matrix3D.
SkewSymmetricRotationParameter which represents a transformation by a skew-symmetric Matrix3D.
QuaternionRotationParameter which represents a transformation by a unit Quaternion.
While these classes represent transformations in different ways, they all store data that support addition, subtraction, and (right) scalar multiplication.

The executable takes in as a mandatory arguments the input (.ray) .ray file name. Additionally, you can also pass in the dimensions of the viewing window, the complexity of the tesselation for objects like the sphere, the cylinder, and the cone, the manner in which rotations should be parameterized, and the way transformations should be blended. It is invoked from the command line with:


% Assignment4 --in <input ray file> --width <width> --height <height> --cplx <complexity> --parameter <matrix representation> --interpolant <interpolation type>

  
The --parameter argument specifies how the rotations will be parameterized. Options include
1: Rotations are represented by 3x3 matrices, the matrices are blended, and the blended transformation (not necessarily rotation) is returned.
2: Rotations are represented by 3x3 matrices, the matrices are blended, and the closest rotation to the blended transformation is returned.
3: Rotations are represented by Euler angles, the Euler angles are blended, and the rotation described by the blended Euler angles is returned.
4: Rotations are represented by skew-symmetric matrices, the skey-symmetrice matrices are blended, and the exponential of the blended skew-symmetric matrix is returned.
5: Rotations are represented by quaternions, the quaternions are blended, and the rotation described by the normalized blended quaternion is returned.
The --interpolant argument specifies how transformations should be blended. Options include:
1: Nearest point interpolation
2: Linear interpolation
3: Catmull-Rom interpolation
4: Uniform cubic B-spline approximation
