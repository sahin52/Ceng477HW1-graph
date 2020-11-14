#ifndef __GETCOLOR__
#define __GETCOLOR__
#include "checkShapes.h"
//#include "generateRays.cpp"
using namespace std;
using namespace parser;

Vec3f Irradiance(PointLight light, Vec3f point){
    float length = getDistance(light.position, point);
    //TODO sifirsa napcaz
    Vec3f res ;
    res.x = light.intensity.x / length / length;
    res.y = light.intensity.y / length / length;
    res.z = light.intensity.z / length / length;
    
    return res;
}

Vec3f Diffuse(PointLight light, std::vector<Material> materials, int mat_id, RayIntersect ray){

    Vec3f irradiance = Irradiance(light, ray.intersectPoint);
    Vec3f w_i = normalize(Vec3fminus(light.position, ray.intersectPoint));
    Vec3f n = normalize(ray.normal);
    float cos = max(0.0f, dotProduct(w_i, n)) ;

    return {
        .x =  materials[mat_id].diffuse.x * cos * irradiance.x ,
        .y =  materials[mat_id].diffuse.y * cos * irradiance.y ,
        .z =  materials[mat_id].diffuse.z * cos * irradiance.z ,
    };
}

Vec3f Specular(PointLight light, RayIntersect rayIntersect, Scene scene, int cam_id, int mat_id,Ray ray){
    
    Vec3f recieved_irr = Irradiance(light, rayIntersect.intersectPoint);
    Vec3f w_i = normalize(Vec3fminus(light.position, rayIntersect.intersectPoint));
    Vec3f w_0 = Vec3fminus(scene.cameras[cam_id].position, rayIntersect.intersectPoint);

    float square_l = dotProduct(Vec3fSum( w_i, w_0), Vec3fSum( w_i, w_0)  );
    Vec3f half_v ;
    half_v.x = (w_i.x + w_0.x) / square_l;
    half_v.y = (w_i.y + w_0.y) / square_l;
    half_v.z = (w_i.z + w_0.z) / square_l;
    half_v = normalize(half_v);

    float cos = max(0.0f, dotProduct(rayIntersect.normal, half_v));
    float phong = scene.materials[mat_id].phong_exponent;

    return {
        .x = scene.materials[mat_id].specular.x * (float)pow(cos, phong) * recieved_irr.x ,
        .y = scene.materials[mat_id].specular.y * (float)pow(cos, phong) * recieved_irr.y ,
        .z = scene.materials[mat_id].specular.z * (float)pow(cos, phong) * recieved_irr.z ,
    };
}

//Returns whether a point is in shadow from the pointlight
bool golgedemi(Vec3f pointToCheck,Scene scene,PointLight currentLight){
    bool res=false;
    //intersection point ve light arasi ray
    Ray ray;
    ray.yon = Vec3fminus(pointToCheck,currentLight.position);//TODO yon dogru mu
    ray.start = currentLight.position;
    ray.isShading;
    RayIntersect sphereIntersect = checkSpheres(ray,scene);
    //RayIntersect rayIntersect; //uzunluktan gitmek gerek ilk carpma noktasina
    if(sphereIntersect.isThereIntersect && sphereIntersect.lengthToTheOrigin<(getDistance(pointToCheck,currentLight.position)+scene.shadow_ray_epsilon*10)){
        return true;
    }
    
    RayIntersect triangleIntersect = checkTriangles(ray,scene);
    if(triangleIntersect.isThereIntersect && triangleIntersect.lengthToTheOrigin<(getDistance(pointToCheck,currentLight.position)+scene.shadow_ray_epsilon*10)){
        return true;
    }
    RayIntersect meshIntersect = checkMeshes(ray,scene,1);
    if(meshIntersect.isThereIntersect && meshIntersect.lengthToTheOrigin<(getDistance(pointToCheck,currentLight.position)+scene.shadow_ray_epsilon*10)){
        return true;
    }

    return false;
};
Vec3f addLightFromLightSources(RayIntersect rayIntersect,Scene scene, int cameraId,Ray ray, Vec3f pixelAsFloat){
    int numberOfLights = scene.point_lights.size();
    int materialId=1;
    if(rayIntersect.shape.form == SPHERE){
        materialId = scene.spheres[rayIntersect.shape.id].material_id;
    }
    if(rayIntersect.shape.form == TRIANGLE){
        materialId = scene.triangles[rayIntersect.shape.id].material_id;
    }
    if(rayIntersect.shape.form == MESH){
        materialId = scene.meshes[rayIntersect.shape.id].material_id;
    }

    for(int i=0;i<numberOfLights;i++){
        PointLight currentLight = scene.point_lights[i];
        // if(golgedemi(rayIntersect.intersectPoint, scene, currentLight)){ //Golgede kalmis do nothing
        //     return {
        //         128.,
        //         128.,
        //         128.,
        //     };
        // }else{  //isik vuruyor, o isiktan gelen isik degerlerini ekle
        pixelAsFloat = Vec3fSum(pixelAsFloat, Diffuse(currentLight, scene.materials, materialId, rayIntersect) );
        pixelAsFloat = Vec3fSum(pixelAsFloat, Specular(currentLight, rayIntersect, scene, cameraId,materialId,ray))       ;
        // }
    }
    return pixelAsFloat;
}

Vec3f addTheYansimas(RayIntersect rayIntersect,Scene scene, int cameraId,Ray ray, Vec3f pixelAsFloat){
    
    return pixelAsFloat;
}


Vec3i getColorOfTheIntersection(RayIntersect rayIntersect,Scene scene,int cameraId,Ray ray){

    int materialId = 0;
    Vec3f pixelAsFloat;
    // if(rayIntersect.isThereIntersect)
    //     return {100,100,100};
    // else
    //     return {200,50,125};
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

    

    pixelAsFloat.x = scene.ambient_light.x* scene.materials[materialId].ambient.x;
    pixelAsFloat.y = scene.ambient_light.y* scene.materials[materialId].ambient.y;
    pixelAsFloat.z = scene.ambient_light.z* scene.materials[materialId].ambient.z;
    if(rayIntersect.isThereIntersect) 
    pixelAsFloat = addLightFromLightSources(rayIntersect, scene, cameraId, ray, pixelAsFloat);
    //Get the light from the light sources,
    //pixelAsFloat = addTheYansimas(rayIntersect, scene, cameraId, ray, pixelAsFloat);
    //Get the yansima
    

    //TODO 255
    Vec3i v ={
        .x=(int)(pixelAsFloat.x),
        .y=(int)(pixelAsFloat.y),
        .z=(int)(pixelAsFloat.z)
    };
    if(v.x > 255) v.x = 255;
    if(v.y > 255) v.y = 255;
    if(v.z > 255) v.z = 255;

    if(v.x<0) v.x = 0;
    if(v.y<0) v.y = 0;
    if(v.z<0) v.z = 0;
    return v;
    //return bisi;
    ///return{0,0,0};//TODO

}












#endif