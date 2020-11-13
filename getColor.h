#ifndef __GETCOLOR__
#define __GETCOLOR__
#include "rayIntersect.h"
//#include "generateRays.cpp"
using namespace std;
using namespace parser;

Vec3i getColorOfTheIntersection(RayIntersect rayIntersect,Scene scene,int cameraId,Ray ray){

    int materialId = 0;

    //Get the light from the light sources,
    //Get the yansima
    
    if(rayIntersect.shape.form == SPHERE){
        materialId = scene.spheres[rayIntersect.shape.id].material_id;
    }
    if(rayIntersect.shape.form == TRIANGLE){
        materialId = scene.triangles[rayIntersect.shape.id].material_id;
    }
    if(rayIntersect.shape.form == MESH){
        materialId = scene.meshes[rayIntersect.shape.id].material_id;
    }
    if(rayIntersect.isThereIntersect) return {
        .x=(int)(scene.ambient_light.x* scene.materials[materialId].diffuse.x ),
        .y=(int)(scene.ambient_light.y* scene.materials[materialId].diffuse.y),
        .z=(int)(scene.ambient_light.z* scene.materials[materialId].diffuse.z)
    };


    if(!rayIntersect.isThereIntersect){
        return scene.background_color;
    }
    //return bisi;
    return{0,0,0};//TODO

}












#endif