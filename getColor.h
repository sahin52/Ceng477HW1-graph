#ifndef __GETCOLOR__
#define __GETCOLOR__
#include "rayIntersect.h"
//#include "generateRays.cpp"
using namespace std;
using namespace parser;

Vec3f Irradiance(PointLight light, Vec3f point){
    float length = getDistance(light.position, point);
    //TODO sifirsa napcaz
    return {
        .x = light.intensity.x / length / length,
        .y = light.intensity.y / length / length,
        .z = light.intensity.z / length / length,
    };
}

Vec3f Diffuse(PointLight light, std::vector<Material> materials, int mat_id, RayIntersect ray){

    Vec3f irradiance = Irradiance(light, ray.intersectPoint);
    Vec3f w_i = normalize(Vec3fminus(light.position, ray.intersectPoint));
    Vec3f n = normalize(ray.normal);
    float cos = dotProduct(w_i, n) ;

    return{
        .x =  max(0.0f, materials[mat_id].diffuse.x * cos * irradiance.x ),
        .y =  max(0.0f, materials[mat_id].diffuse.y * cos * irradiance.y ),
        .z =  max(0.0f, materials[mat_id].diffuse.z * cos * irradiance.z ),
    };
};

//Returns whether a point is in shadow from the pointlight
bool golgedemi(Vec3f pointToCheck,Scene scene,PointLight currentLight){
    bool res=false;
    //intersection point ve light arasi ray
    Ray ray;
    ray.yon = Vec3fminus(pointToCheck,currentLight.position);//TODO yon dogru mu
    ray.start = currentLight.position;
    ray.isShading;

    RayIntersect rayIntersect; //uzunluktan gitmek gerek ilk carpma noktasina
    if(rayIntersect.isThereIntersect){
        return true;
    }

    return false;
}
Vec3f addLightFromLightSources(RayIntersect rayIntersect,Scene scene, int cameraId,Ray ray, Vec3f pixelAsFloat){
    int numberOfLights = scene.point_lights.size();

    for(int i=0;i<numberOfLights;i++){
        PointLight currentLight = scene.point_lights[i];
        if(golgedemi(rayIntersect.intersectPoint, scene, currentLight)){ //Golgede kalmis do nothing

        }else{  //isik vuruyor, o isiktan gelen isik degerlerini ekle

        }
    }
    return pixelAsFloat;
}

Vec3f addTheYansimas(RayIntersect rayIntersect,Scene scene, int cameraId,Ray ray, Vec3f pixelAsFloat){
    
    return pixelAsFloat;
}


Vec3i getColorOfTheIntersection(RayIntersect rayIntersect,Scene scene,int cameraId,Ray ray){

    int materialId = 0;
    Vec3f pixelAsFloat;

    if(!rayIntersect.isThereIntersect){
        return scene.background_color;
    }
    
    if(rayIntersect.shape.form == SPHERE){
        materialId = scene.spheres[rayIntersect.shape.id].material_id;
    }
    if(rayIntersect.shape.form == TRIANGLE){
        materialId = scene.triangles[rayIntersect.shape.id].material_id;
    }
    if(rayIntersect.shape.form == MESH){
        materialId = scene.meshes[rayIntersect.shape.id].material_id;
    }
    pixelAsFloat.x = scene.ambient_light.x* scene.materials[materialId].diffuse.x;
    pixelAsFloat.y = scene.ambient_light.y* scene.materials[materialId].diffuse.y;
    pixelAsFloat.z = scene.ambient_light.z* scene.materials[materialId].diffuse.z;
    // if(rayIntersect.isThereIntersect) 
    pixelAsFloat = addLightFromLightSources(rayIntersect, scene, cameraId, ray, pixelAsFloat);
    //Get the light from the light sources,
    pixelAsFloat = addTheYansimas(rayIntersect, scene, cameraId, ray, pixelAsFloat);
    //Get the yansima
    

    //TODO 255

    return {
        .x=(int)(pixelAsFloat.x),
        .y=(int)(pixelAsFloat.y),
        .z=(int)(pixelAsFloat.z)
    };
    //return bisi;
    return{0,0,0};//TODO

}












#endif