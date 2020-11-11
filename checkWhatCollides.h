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
Shape emptyshape;
Vec3f emptyPoint;
const RayIntersect emptyRayIntersect = {
    .shape= emptyshape,
    .lengthToTheOrigin=-1.,
    .isThereIntersect = false,
    .intersectPoint = emptyPoint,
};
parser::Vec3f Vec3fminus(parser::Vec3f v1, parser::Vec3f v2){
    parser::Vec3f res;
    res.x = v1.x-v2.x;
    res.y = v1.y-v2.y;
    res.z = v1.z-v2.z;
    return res;
}

float dotProduct(Vec3f v1,Vec3f v2){
    return v1.x*v2.x   +   v1.y*v2.y   +   v1.z*v2.z;
}



Vec3i aynaGolgeVsEkle(Shape shape, Scene scene,Ray ray, int cameraNum){///bunsuz paint olur
    Vec3i res;
    return res;
}
/**
 * returns the collision point and; type and id of the shape if a collision happens
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
        // string anan = "No hit to the sphere " + to_string(radius) + " by the ray: "+ to_string(ray.start.x) 
        // +" "+ to_string(ray.start.y)  +" "+ to_string(ray.start.z)  +" "+ to_string(ray.yon.x)  +" "+ to_string(ray.yon.y)  +" "+ to_string(ray.yon.z)
        //  ;
        //p(anan);
        RayIntersect rayIntersect;
        rayIntersect.isThereIntersect = false;
        return rayIntersect;
    }else{
        //p("intersected!!");
        auto t1 = (-b-sqrt(discriminant))/(2.0*a);
        auto t2 = (-b+sqrt(discriminant))/(2.0*a);

        if(t1<0){
            //p("empty Ray Intersect bc of wrong side");
            return emptyRayIntersect;
        }
        if(t1<t2){
            RayIntersect res;
            res.isThereIntersect = true;
            res.lengthToTheOrigin = t1;
            Shape shape;
            shape.id = shapeId;
            shape.form = SPHERE;
            res.shape = shape;
            //res.intersectPoint  ;//Find intersection point t1 TODO
            return res;
        }else{
            RayIntersect res;
            res.isThereIntersect = true;
            res.lengthToTheOrigin = t2;
            Shape shape;
            shape.id = shapeId;
            shape.form = SPHERE;
            res.shape = shape;
            //res.intersectPoint = 0.0 ;//Find intersection point t2 TODO
            return res;
        }
    }

    
    
}
/** Checks all spheres and returns the nearest RayIntersect To the camera
 * 
*/
RayIntersect checkSpheres(Ray ray,Scene scene,int cameraId){

    RayIntersect rayIntersect = emptyRayIntersect;
    vector<RayIntersect> intersects = {};
    for(int i = 0;i<scene.spheres.size();i++){
        rayIntersect = checkOneSphere(ray, scene.spheres[i],i,cameraId,scene);
    }
    return rayIntersect; // t => mesafe katsayisi


    
}


//*******************************************///
RayIntersect checkOneTriangle(Ray ray,Scene scene,int cameraId, int TriangleId){
    //TODO
    RayIntersect res;
    res.isThereIntersect = false;

    Vec3f v0 = scene.vertex_data[scene.triangles[TriangleId].indices.v0_id];
    Vec3f v1 = scene.vertex_data[scene.triangles[TriangleId].indices.v1_id];
    Vec3f v2 = scene.vertex_data[scene.triangles[TriangleId].indices.v2_id];

    Vec3f v1_v0 = Vec3fminus(v1,v0);
    Vec3f v2_v0 = Vec3fminus(v2,v0);
    Vec3f normalv = cross(v1_v0, v2_v0);

    //checking if direction of ray and normal are parallel
    float checkparallel = dotProduct(normalv, ray.yon);
    if (fabs(checkparallel) == 0)
    {
        res.isThereIntersect =false;
        return res;
    }      /* TODO       epsilon olacak  */

    // d is in the plane equation ---- Ax + By + Cz + d = 0 
    float d = dotProduct(normalv, v0);

    // t is in the ray equation ---- ray = start + t*yon
    float t = (dotProduct(normalv,ray.start) + d) / checkparallel ;
    
    //finding if intersected point inside of triangle
    Vec3f point;
    point.x = ray.start.x + t*ray.yon.x ;
    point.y = ray.start.y + t*ray.yon.y ;
    point.z = ray.start.z + t*ray.yon.z ;

    //point should be inside 3 edges
    Vec3f edge0, edge1, edge2;
    edge0 = Vec3fminus(v1,v0);
    edge1 = Vec3fminus(v2,v1);
    edge2 = Vec3fminus(v0,v1);

    // dot product of "cross_of_point" and "normalv" is positive means
    // that point is in the correct side of edge
    Vec3f cross_of_point = cross(edge0, (Vec3fminus(point,v0)) );       /*  for edge0  */
    if( dotProduct(normalv,cross_of_point)<0 ) return res;      /* erken bitirilebilir */
    cross_of_point = cross(edge1, (Vec3fminus(point,v1)) );       /*  for edge1  */
    if( dotProduct(normalv,cross_of_point)<0 ) return res;      /* erken bitirilebilir */
    cross_of_point = cross(edge2, (Vec3fminus(point,v2)) );       /*  for edge2  */
    if( dotProduct(normalv,cross_of_point)<0 ) return res;      /* erken bitirilebilir */

    // if none of the ifs above true than point is inside triangle
    res.isThereIntersect = true;
    res.intersectPoint = point;
    res.shape.form=TRIANGLE;
    res.shape.id = TriangleId;
    
    return res;
}
RayIntersect checkTriangles(Ray ray,Scene scene,int cameraId){
    // RayIntersect checkOneTriangle(Ray ray,Triangle triangle,int cameraId);

    RayIntersect rayIntersect;
    rayIntersect.isThereIntersect = false;

    for(int i=0;i<scene.triangles.size();i++){
        rayIntersect = checkOneTriangle(ray,scene,cameraId, i);
    }
    return rayIntersect;
};
//*******************************************///

//////?????????????????????????/////////// MESH START
RayIntersect checkOneMesh(Ray ray,Mesh mesh,int meshId,int cameraId){
    //mesh ucgenlerden olusur, mesh icerisindeki tum faceleri bir ucgen haline getirip checkonetriangle'da kullanabiliriz
    RayIntersect res = emptyRayIntersect;
    for(auto i: mesh.faces){
        
    }
    //throw("implement\n");

    return res;
}

RayIntersect checkMeshes(Ray ray,Scene scene,int cameraId){
    RayIntersect res = emptyRayIntersect;
    for(int i=0;i<scene.meshes.size();i++){
        checkOneMesh(ray,scene.meshes[i],i,cameraId);
    }
    return res;
    
    // RayIntersect rayIntersect;
    // rayIntersect.isThereIntersect = false;
};
//////?????????????????????????/////////// MESH END


RayIntersect getNearestIntersect(RayIntersect sphereInt, RayIntersect triangleInt,RayIntersect meshInt){
    vector<RayIntersect> distances = {};
    if(sphereInt.isThereIntersect)
        distances.push_back(sphereInt);
    if(triangleInt.isThereIntersect)
        distances.push_back(triangleInt);
    if(meshInt.isThereIntersect)
        distances.push_back(meshInt);
    if(distances.size()==0)
    {
        //return empty bg
        return emptyRayIntersect;
    }else{
        //p("intersect at nearest");
    }
    RayIntersect nearest = distances[0];
    for(auto i: distances){
        if(i.lengthToTheOrigin<nearest.lengthToTheOrigin){
            nearest = i;
        }
    }
    return nearest;
}

RayIntersect getIntersect(Ray ray,Scene scene,int cameraId){ 
    auto sphereIntersect = checkSpheres(ray,scene,cameraId);//Returns the touch point,  id and type of the shape
    auto triangleIntersect = checkTriangles(ray, scene,cameraId); // ucgene degisyosa
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


Vec3i checkWhatCollides(Ray ray,Scene scene,int cameraId ){
    RayIntersect rayIntersect = getIntersect(ray,scene,cameraId);//idsini verir
    //return getColorOfTheIntersection(rayIntersect, scene);
    Vec3i dolu = {
        .x=200,
        .y=0,
        .z=200
    };
    Vec3i bos = {
        .x=0,
        .y=200,
        .z=100
    };

    if(rayIntersect.isThereIntersect){
        return dolu;
    }else{
        return bos;
    }
    //res = aynaGolgeVsEkle(shape, scene, ray, cameraId);
    //return res;

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