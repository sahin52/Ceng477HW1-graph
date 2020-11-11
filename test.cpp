

// #include <iostream>
// #include "parser.h"
// #include "ppm.h"
// #include <cmath>

// using namespace parser;
// using namespace std;

// Ray generateRay(const Camera &camera, int i, int j)
// {
//     float left = camera.near_plane.x;
//     float right = camera.near_plane.y;
//     float bottom = camera.near_plane.z;
//     float top = camera.near_plane.w;

//     Vec3f gaze = normalizeVector(camera.gaze);

//     float su = (right - left)*(j + 0.5)/camera.image_width;
//     float sv = (top - bottom)*(i + 0.5)/camera.image_height;

//     Vec3f m, q, u, v;
//     m.x = camera.position.x + (gaze.x * camera.near_distance);
//     m.y = camera.position.y + (gaze.y * camera.near_distance);
//     m.z = camera.position.z + (gaze.z * camera.near_distance);

//     u = crossProduct(gaze, camera.up);
//     u = normalizeVector(u);

//     v = crossProduct(u, gaze);

//     q.x = m.x + (u.x*left) + (v.x*top);
//     q.y = m.y + (u.y*left) + (v.y*top);
//     q.z = m.z + (u.z*left) + (v.z*top);

//     Vec3f s;
//     s.x = q.x + (u.x*su) - (v.x * sv);
//     s.y = q.y + (u.y*su) - (v.y * sv);
//     s.z = q.z + (u.z*su) - (v.z * sv);

//     Ray ray;
//     ray.origin = camera.position;
//     ray.direction = subtract(s, camera.position);
//     ray.direction = normalizeVector(ray.direction);
//     ray.shadowRay = false;

//     return ray;
// }

// int main(){
//     return 0;
// }
