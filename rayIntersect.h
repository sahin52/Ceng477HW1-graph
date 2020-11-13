#ifndef __RAYINTERSECT__
#define __RAYINTERSECT__
#include <iostream>
#include "parser.h"
#include "ppm.h"
#include "generateRays.h"
//#include "generateRays.cpp"


using namespace std;
using namespace parser;

enum Form{
    MESH,
    TRIANGLE,
	SPHERE    
};

struct Shape{
    Form form;
    int id;
};

struct RayIntersect{
    Shape shape;
    float lengthToTheOrigin;//This can be the length to the origin
    bool isThereIntersect;//false ise bg
    Vec3f intersectPoint;
    Vec3f normal;
};
Shape emptyshape;
Vec3f emptyPoint;
const RayIntersect emptyRayIntersect = {
    .shape= emptyshape,
    .lengthToTheOrigin=-1.,
    .isThereIntersect = false,
    .intersectPoint = emptyPoint,
};

float dotProduct(Vec3f v1,Vec3f v2){
    return v1.x*v2.x   +   v1.y*v2.y   +   v1.z*v2.z;
}


#endif