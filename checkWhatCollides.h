#ifndef __CHECKWHATCOLLIDES__
#define __CHECKWHATCOLLIDES__
#include "getColor.h"


RayIntersect getNearestIntersect(RayIntersect sphereInt, RayIntersect triangleInt,RayIntersect meshInt){
    vector<RayIntersect> distances = {};
    
    if(triangleInt.isThereIntersect)
        distances.push_back(triangleInt);
    if(meshInt.isThereIntersect)
        distances.push_back(meshInt);
    if(sphereInt.isThereIntersect)
        distances.push_back(sphereInt);    
    if(distances.size()==0)
    {
        //return empty bg
        return emptyRayIntersect;
    }else{
        //p("intersect at nearest");
    }
    //TODO lengthToTheOrigin hatali birisinde
    RayIntersect nearest = distances[0];
    for(auto i: distances){
        if(i.lengthToTheOrigin < nearest.lengthToTheOrigin){
            nearest = i;
        }
    }
    return nearest;
}

RayIntersect getIntersect(Ray ray,Scene scene,int cameraId){ 
    auto sphereIntersect = checkSpheres(ray,scene);//Returns the touch point,  id and type of the shape
    auto triangleIntersect = checkTriangles(ray, scene); // ucgene degisyosa
    auto meshIntersect = checkMeshes(ray,scene,cameraId);   //meshe degiyosa
    // if(sphereIntersect.isThereIntersect){
    //     p("sphere intersect");
    // }
    // // // // // if(triangleIntersect.isThereIntersect){
    // // // // //     p("triangleIntersect");
    // // // // // }
    // // // // // // if(meshIntersect.isThereIntersect){
    //     p("meshIntersect");
    // }
    auto res = getNearestIntersect(sphereIntersect, triangleIntersect, meshIntersect);
    if(res.isThereIntersect){
        //p("intersect!!!!!");
    }
    return res;
    // lengthToThe.. en kucuk olani alcaz

    //enYakinNoktayiSec();
    
}

//Returns the color of the pixel
Vec3i checkWhatCollides(Ray ray,Scene scene,int cameraId ){
    RayIntersect rayIntersect = getIntersect(ray,scene,cameraId);//idsini verir
    return getColorOfTheIntersection(rayIntersect, scene,cameraId,ray);
    
    //p("123");
    //p(materialId);
    //Vec3i res = getColorOfTheIntersection(rayIntersect, scene,cameraId,ray);

    ///return res;

}



/***
 * 
 * 
 * 
 * 
 * o + t*d 
 * origin
 * t katsayi ***
 * * direction
 */


#endif