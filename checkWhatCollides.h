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
};

parser::Vec3f Vec3fminus(parser::Vec3f v1, parser::Vec3f v2){
    parser::Vec3f res;
    res.x = v1.x-v2.x;
    res.y = v1.y-v2.y;
    res.z = v1.z-v2.z;
    return res;
}

float dotProduct(Vec3f v1,Vec3f v2){
    return v1.x*v2.x+v1.y*v2.y+v1.z*v2.z;
}



Vec3i aynaGolgeVsEkle(Shape shape, Scene scene,Ray ray, int cameraNum){///bunsuz paint olur
    Vec3i res;
    return res;
}
/**
 * returns the collision point and; type and id of the shape if a collision happened
 */
RayIntersect checkOneSphere(Ray ray,Sphere sphere, int shapeId, int cameraId, Scene scene){
    //TODO
    //P = point on the sphere, C is center, r is radius
    // ∥P−C∥2=r2  //sphere 
    // dot((P−C),(P−C))=r2
    //A ray is p=(O+tD) origin + Direction* a number, this will give us a point on the ray
    //In order to know if the ray and sphere intersect, we must give the point on the 
    //    sphere, the ray equation must be written in the sphere equation.
    //      dot((O+tD−C),(O+tD−C))=r2
    // ... -r2 = 0  iki tane t degeri iki tane gectiyse kucuk olani t degerleri negatifse alma
    // t degerleri pozitifse, kucuk olani aldim
    // O + tD 
    Vec3f center = scene.vertex_data[sphere.center_vertex_id - 1];
    parser::Vec3f ray_origin_to_sp_center = Vec3fminus(ray.start , center);
    auto radius = sphere.radius;

    auto a = dotProduct(ray.yon,ray.yon);
    auto b = 2.0 * dotProduct(ray_origin_to_sp_center, ray.yon);
    auto c = dotProduct(ray_origin_to_sp_center,ray_origin_to_sp_center) - radius*radius;
    float discriminant = b*b - 4.0*a*c;
    if(discriminant<0){
        string anan = "No hit to the sphere " + to_string(radius) + " by the ray: "+ to_string(ray.start.x) 
        +" "+ to_string(ray.start.y)  +" "+ to_string(ray.start.z)  +" "+ to_string(ray.yon.x)  +" "+ to_string(ray.yon.y)  +" "+ to_string(ray.yon.z)
         ;
        p(anan);
        RayIntersect rayIntersect;
        rayIntersect.isThereIntersect = false;
        return rayIntersect;
    }else{
        p("intersected!!");
        auto t1 = (-b-sqrt(discriminant))/(2.0*a);
        auto t2 = (-b+sqrt(discriminant))/(2.0*a);

        if(t1<0){
            RayIntersect res;
            res.isThereIntersect = false;
            return res;
        }
        if(t1<t2){
            RayIntersect res;
            res.isThereIntersect = true;
            res.lengthToTheOrigin = t1;
            Shape shape;
            shape.id = shapeId;
            shape.form = SPHERE;
            res.shape = shape;
            res.intersectPoint ;//Find intersection point t1 TODO
        }else{
            RayIntersect res;
            res.isThereIntersect = true;
            res.lengthToTheOrigin = t2;
            Shape shape;
            shape.id = shapeId;
            shape.form = SPHERE;
            res.shape = shape;
            res.intersectPoint ;//Find intersection point t2 TODO
        }
    }

    
    
}

RayIntersect checkSpheres(Ray ray,Scene scene,int cameraId){

    RayIntersect rayIntersect;
    rayIntersect.isThereIntersect = false;
    for(int i = 0;i<scene.spheres.size();i++){
        checkOneSphere(ray, scene.spheres[i],i,cameraId,scene);
    }
    return rayIntersect; // t => mesafe katsayisi


    
}


//*******************************************///
RayIntersect checkOneTriangle(Ray ray,Scene scene,int cameraId, int TriangleId){
    //TODO
    RayIntersect res;
    res.isThereIntersect = false;

    return res;
}
RayIntersect checkTriangles(Ray ray,Scene scene,int cameraId){
    // RayIntersect checkOneTriangle(Ray ray,Triangle triangle,int cameraId);

    RayIntersect rayIntersect;
    rayIntersect.isThereIntersect = false;

    for(int i=0;i<scene.triangles.size();i++){
        rayIntersect = checkOneTriangle(ray,scene,cameraId, i);
    }
};
//*******************************************///


RayIntersect checkOneMesh(Ray ray,Mesh mesh,int cameraId){
    RayIntersect res;
    throw("implement\n");
    return res;
}

RayIntersect checkMeshes(Ray ray,Scene scene,int cameraId){
    // RayIntersect checkOneMesh(Ray ray,Mesh mesh,int cameraId);

    // RayIntersect rayIntersect;
    // rayIntersect.isThereIntersect = false;
};
    
Shape getShapeIdThatIntersectsRay(Ray ray,Scene scene,int cameraId){ 
    checkSpheres(ray,scene,cameraId);//Returns the touch point,  id and type of the shape
    checkTriangles(ray, scene,cameraId); // ucgene degisyosa
    checkMeshes(ray,scene,cameraId);   //meshe degiyosa

    // lengthToThe.. en kucuk olani alcaz

    //enYakinNoktayiSec();
    Shape res;
    return res;
}


Vec3i checkWhatCollides(Ray ray,Scene scene,int cameraId ){
    //Shape shape = getShapeIdThatIntersectsRay(ray,scene,cameraId);//idsini verir
    Vec3i res;
    //res = aynaGolgeVsEkle(shape, scene, ray, cameraId);
    return res;

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