#ifndef __UTILSH_
#define __UTILSH_
#include <iostream>
#include "parser.h"
#include "ppm.h"

using namespace std;
using namespace parser;


Vec3f Vec3fDivision(Vec3f vec, float sayi){
    Vec3f res;
    res.x = vec.x/sayi;
    res.y = vec.y/sayi;
    res.z = vec.z/sayi;
    return res;
}



#endif