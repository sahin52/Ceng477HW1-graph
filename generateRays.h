#ifndef __GENERATESRAYS__
#define __GENERATESRAYS__
#include "printer.h"

#include <math.h>


struct Ray
{
    bool isShading;
    Vec3f start;
    Vec3f yon;
};

Vec3f cross(Vec3f v1, Vec3f v2)
{
    float x = v1.y*v2.z - v1.z*v2.y;
    float y = v1.z*v2.x - v1.x*v2.z;
    float z = v1.x*v2.y - v1.y*v2.x;
    Vec3f result;
    result.x = x; result.y = y; result.z = z;
    return result;
}

Vec3f normalize(Vec3f v)
{
    Vec3f result;
    float uzunluk =  sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
    result.x = v.x / uzunluk;
    result.y = v.y / uzunluk;
    result.z = v.z / uzunluk;
    return result;
}

/*
 * Generates A Ray
 * Ray will have an origin which is the poisition of the camera
 * and a direction which is the direction of the given pixel
 * 
 * 
 * 
*/
Ray generateRay(int row, int column, Camera cam)
{
    Vec3f gaze =  normalize(cam.gaze);
    Vec3f vector_u = cross(gaze, cam.up);//Yana dogru
    vector_u = normalize(vector_u);
    Vec3f vector_v  = cross(vector_u, gaze);

    //Planein merkezi
    Vec3f merkez;
    merkez.x = cam.position.x + gaze.x * cam.near_distance;
    merkez.y = cam.position.y + gaze.y * cam.near_distance;
    merkez.z = cam.position.z + gaze.z * cam.near_distance;

    //Planein sol en ustu
    Vec3f sol_en_ust;
    sol_en_ust.x = merkez.x + vector_u.x*cam.near_plane.x + vector_v.x*cam.near_plane.w ;
    sol_en_ust.y = merkez.y + vector_u.y*cam.near_plane.x + vector_v.y*cam.near_plane.w ;
    sol_en_ust.z = merkez.z + vector_u.z*cam.near_plane.x + vector_v.z*cam.near_plane.w ;

    //leftten pixele olan mesafe
    float yatay_pixel_mesafesi = (cam.near_plane.y - cam.near_plane.x) * (column + 0.5) / cam.image_width ;
    //yukaridan pixele olan mesafe
    float dikey_pixel_mesafesi = (cam.near_plane.w - cam.near_plane.z) * (row + 0.5) / cam.image_height ;

    Vec3f hedef_pixel; //gidecegimiz pixel
    hedef_pixel.x = sol_en_ust.x + vector_u.x*yatay_pixel_mesafesi - vector_v.x*dikey_pixel_mesafesi;
    hedef_pixel.y = sol_en_ust.y + vector_u.y*yatay_pixel_mesafesi - vector_v.y*dikey_pixel_mesafesi;
    hedef_pixel.z = sol_en_ust.z + vector_u.z*yatay_pixel_mesafesi - vector_v.z*dikey_pixel_mesafesi;

    Ray ray;
    ray.isShading = false;
    ray.start = cam.position;
    ray.yon.x = hedef_pixel.x - cam.position.x;
    ray.yon.y = hedef_pixel.y - cam.position.y;
    ray.yon.z = hedef_pixel.z - cam.position.z;
    ray.yon = normalize(ray.yon);

    return ray;
}



#endif