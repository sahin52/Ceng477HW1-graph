#include <iostream>
#include "parser.h"
#include "ppm.h"
#include "generateRays.cpp"


using namespace std;
using namespace parser;

enum Form
{
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
    Vec3f point;
    bool isThereIntersect;
};

Vec3i aynaGolgeVsEkle(Shape shape, Scene scene,Ray ray, int cameraNum){
    Vec3i res;
    return res;
}
RayIntersect checkSpheres(Ray ray,Scene scene,int cameraId){
    RayIntersect checkOneSphere(Ray ray,Sphere sphere,int cameraId);

    RayIntersect rayIntersect;
    rayIntersect.isThereIntersect = false;
    for(int i = 0;i<scene.spheres.size();i++){
        checkOneSphere(ray, scene.spheres[i],cameraId);
    }
    return rayIntersect;


    /**
     * returns the collision point and; type and id of the shape if a collision happened
     */
    RayIntersect checkOneSphere(Ray ray,Sphere sphere,int cameraId){
        //TODO
        throw "implement";
    }
}


RayIntersect checkTriangles(Ray ray,Scene scene,int cameraId){
    RayIntersect checkOneTriangle(Ray ray,Sphere sphere,int cameraId);

    RayIntersect rayIntersect;
    rayIntersect.isThereIntersect = false;
    

};
RayIntersect checkMeshes(Ray ray,Scene scene,int cameraId){

};
    
Shape getShapeIdThatIntersectsRay(Ray ray,Scene scene,int cameraId){ 
    checkSpheres(ray,scene,cameraId);//Returns the touch point,  id and type of the shape
    checkTriangles(ray, scene,cameraId);
    checkMeshes(ray,scene,cameraId);
    Shape res;
    return res;
}
Vec3i checkWhatCollides(Ray ray,Scene scene,int cameraId ){
    Shape shape = getShapeIdThatIntersectsRay(ray,scene,cameraId);//idsini verir
    Vec3i res = aynaGolgeVsEkle(shape, scene, ray, cameraId);
    return res;

}