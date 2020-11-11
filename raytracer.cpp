#include "checkWhatCollides.h"

typedef unsigned char RGB[3];
using namespace std;
using namespace parser;



// template <typename T> 
// void p(T const& t) 
// { 
//     cout << "slm\n";
//     cout << t; 
// }




/**
 * Gets the scene and returns the image as a char* 
 * Uses details like width and height 
 * 
 * 
 * 
 */
unsigned char * generateImages(Scene scene){
    for(int cam = 0; cam < scene.cameras.size(); cam++){
        unsigned char * image = new unsigned char[(scene.cameras[cam].image_height*scene.cameras[cam].image_width)* 3];
        int width = scene.cameras[0].image_width;
        int height = scene.cameras[0].image_height;
        for(int i=0;i<height;i++){
            for(int j=0;j<width;j++){
                auto ray  = generateRay(i,j,scene.cameras[cam]);
                if(i<3 && j<3) {
                    std::cout << ray.yon.x << std::endl;
                    std::cout << ray.yon.y << std::endl;
                    std::cout << ray.yon.z << std::endl;
                }
                Vec3i pixel = checkWhatCollides(ray,scene,cam);//bir pixel

                //TODO:
                image[i*width*3+3*j  ] =(unsigned char)  pixel.x; 
                image[i*width*3+3*j+1] =(unsigned char)  pixel.y;
                image[i*width*3+3*j+2] =(unsigned char)  pixel.z;
            }
        }
        p("Generating image: "+scene.cameras[cam].image_name);
        write_ppm(scene.cameras[cam].image_name.c_str(), image, scene.cameras[cam].image_width,scene.cameras[cam].image_height);
    }
    
}



int main(int argc, char* argv[])
{
    // Sample usage for reading an XML scene file
    parser::Scene scene;

    scene.loadFromXml(argv[1]);
    p("background color: ");
    p(scene.background_color);
    p("\n");
    p("shadow ray epsilon: ");
    p(scene.shadow_ray_epsilon);
    p("\nmax_recursion_depth: ");
    p(scene.max_recursion_depth);
    p("\ncameras: ");
    p(scene.cameras);
    p("\nambient_light: ");
    p(scene.ambient_light);
    p("\npoint_lights: ");
    p(scene.point_lights);
    p("\nmaterials: ");
    p(scene.materials);
    p("\nvertex_data: ");
    p(scene.vertex_data);
    p("\nHere are the objects:");
    p("\n meshes: ");
    p(scene.meshes);
    p("\ntriangles: ");
    p(scene.triangles);
    p("\nspheres: ");
    p(scene.spheres);
    p("\n");

    unsigned char* image = generateImages(scene);

    // // The code below creates a test pattern and writes
    // // it to a PPM file to demonstrate the usage of the
    // // ppm_write function.
    // //
    // // Normally, you would be running your ray tracing
    // // code here to produce the desired image.

    // const RGB BAR_COLOR[8] =
    // {
    //     { 255, 255, 255 },  // 100% White
    //     { 255, 255,   0 },  // Yellow
    //     {   0, 255, 255 },  // Cyan
    //     {   0, 255,   0 },  // Green
    //     { 255,   0, 255 },  // Magenta
    //     { 255,   0,   0 },  // Red
    //     {   0,   0, 255 },  // Blue
    //     {   0,   0,   0 },  // Black
    // };

    // int width = 640, height = 480;
    // int columnWidth = width / 8;

    // unsigned char* image = new unsigned char [width * height * 3];

    // int i = 0;
    // for (int y = 0; y < height; ++y)
    // {
    //     for (int x = 0; x < width; ++x)
    //     {
    //         int colIdx = x / columnWidth;
    //         image[i++] = BAR_COLOR[colIdx][0];
    //         image[i++] = BAR_COLOR[colIdx][1];
    //         image[i++] = BAR_COLOR[colIdx][2];
    //     }
    // }

    //write_ppm("test.ppm", image, scene.cameras[0].image_width,scene.cameras[0].image_height);

}
