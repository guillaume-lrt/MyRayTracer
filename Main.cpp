#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_write.h"

#include <chrono>
#include <iostream>
#include <cmath>

#include "Vec3.h"
#include "Image.hpp"
#include "Scene.hpp"
#include "RayTracer.hpp"

using namespace std;
// using namespace std::chrono;


int main()
{
    auto start = chrono::high_resolution_clock::now();

    // Initialization

    const size_t W = 480;
    const size_t H = 270; 

    Image image = Image(W,H);
    Scene scene;

    Camera camera(Vec3f(0.f, 0.f, 2.f),
				  Vec3f(),
				  Vec3f(0.f, 1.f, 0.f),
				  60.f,
				  float(W)/H);
    Light light(Vec3f(2.f,2.f,2.f), Vec3f(1.f,0.f,0.f), float(pow(10,1)));
    scene.camera() = camera;
    scene.light() = light;

    // Loading a mesh

	Mesh mesh;
	try {
		mesh.loadOFF("mesh_library/example.off");
	}
	catch (const std::exception & e) {
		std::cerr << e.what() << std::endl;
		exit(1);
	}
    // std::vector<Vec3f> newTriangle = {{-1.f,-1.f,-1.f},{1.f,-1.f,-1.f},{1.f,-1.f,1.f}};
    // std::vector<Vec3f> newTriangleNormals = {{0.f,1.f,0.f},{0.f,1.f,0.f},{0.f,1.f,0.f}};

    mesh.addTriangle(newTriangle,newTriangleNormals);

	scene.meshes ().push_back (mesh);

	// Rendering

    RayTracer rayTracer;
    image.fillBackground();
    std::cout << "Ray tracing starts\n";
    rayTracer.render(scene,image);
    std::cout << "Finished\n";
    image.savePPM("image.ppm");
    // image.saveJPG("image.jpg");
    
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    duration = duration / 1000000;
    cout << "Time taken: " << duration.count() << " seconds" << endl;
    return 0;
}