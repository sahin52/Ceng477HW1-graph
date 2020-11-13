#ifndef __UTILSH_
#define __UTILSH_
#include <iostream>
#include "parser.h"
#include "ppm.h"
#include <math.h>

using namespace std;
using namespace parser;

parser::Vec3f Vec3fminus(parser::Vec3f v1, parser::Vec3f v2){
    parser::Vec3f res;
    res.x = v1.x-v2.x;
    res.y = v1.y-v2.y;
    res.z = v1.z-v2.z;
    return res;
}

Vec3f Vec3fDivision(Vec3f vec, float sayi){
    Vec3f res;
    res.x = vec.x/sayi;
    res.y = vec.y/sayi;
    res.z = vec.z/sayi;
    return res;
}
Vec3f Vec3fMultiply(Vec3f vec, float sayi){
    Vec3f res;
    res.x = vec.x*sayi;
    res.y = vec.y*sayi;
    res.z = vec.z*sayi;
    return res;
}
float getLength(Vec3f v){
   return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}
//Aradaki uzunlugu verir
float getDistance(Vec3f v1, Vec3f v2){
    Vec3f fark = Vec3fminus(v1,v2);
    return getLength(fark);
}
float determinant(Vec3f v0, const Vec3f v1, const Vec3f &v2)
{
    return v0.x * (v1.y*v2.z - v2.y*v1.z)
            + v0.y * (v2.x*v1.z - v1.x*v2.z)
            + v0.z * (v1.x*v2.y - v1.y*v2.x);
}

#endif