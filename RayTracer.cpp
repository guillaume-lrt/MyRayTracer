
#include "RayTracer.hpp"

bool RayTracer::rayTrace(const Scene &scene, const Ray &ray, 
            size_t &meshIndex, size_t &triangleIndex,
            float &u, float &v, float &d){
    const auto& meshes = scene.meshes();
    float min_distance = inf;
    bool is_intersection = false;
    for (size_t mIndex = 0; mIndex < meshes.size(); mIndex++){
        const auto& P = meshes[mIndex].vertexPositions();
        const auto& T = meshes[mIndex].indexedTriangles();
        for (size_t tIndex =0; tIndex < T.size(); tIndex++){
            const Vec3i& triangle = T[tIndex];
            float u_temp, v_temp, d_temp;
            if (ray.Triangle_Intersection(P[triangle[0]], P[triangle[1]], P[triangle[2]], u_temp, v_temp, d_temp))
                if (d_temp < min_distance){
                    min_distance = d_temp;
                    is_intersection = true;
                    u = u_temp;
                    v = v_temp;
                    d = d_temp;
                    meshIndex = mIndex;
                    triangleIndex = tIndex;
                }
        }
    }
    return is_intersection;
}

inline Vec3f RayTracer::evaluateColorResponse(const Vec3f &normal, const Vec3f & wi) {
    Vec3f f = {1.f,1.f,1.f};
    return f*dot(normal,wi);
}

Vec3f RayTracer::shade (const Scene &scene, const size_t &meshIndex, const size_t &triangleIndex, const float u, const float v){
    const auto& mesh = scene.meshes()[meshIndex];
    const auto& P = mesh.vertexPositions();
    const auto& N = mesh.vertexNormals();
    const Vec3i triangle = mesh.indexedTriangles()[triangleIndex];
    const auto w = 1.f - u - v;
    Vec3f hitNormal = normalize(w*N[triangle[0]] + u*N[triangle[1]] + v*N[triangle[2]]);

    Vec3f hitPoint = (1.f - u - v) * P[triangle[0]] + u * P[triangle[1]] + v * P[triangle[2]];

    hitPoint += epsilon*hitNormal;

    // No shading so far, only normal visualization
    std::cout << "shade?" << std::endl;
    return Vec3f(0.5f, 0.5f, 0.5f) + hitNormal / 2.f;
    const Light light = scene.light();
    const Vec3f light_ori = light.position();
    Vec3f direction = light_ori - hitPoint;
    Ray ray(hitPoint, direction);

    size_t meshIndex_temp, triangleIndex_temp;      // don't really care
    float u_t,v_t,d_t;

    if (!rayTrace(scene, ray, meshIndex_temp, triangleIndex_temp, u_t, v_t, d_t))       // if not intersection => the point is visible from the light source
        return evaluateColorResponse(hitNormal, -direction);
    return Vec3f(0.f,0.f,0.f);
}

void RayTracer::render (Scene &scene, Image &image){
    const Camera& camera = scene.camera();
    size_t H = image.height();
    size_t W = image.width();
    #pragma omp parallel for
    for (int y = 0; y < H; y++){
        #pragma omp parallel for
        for (int x = 0; x < W; x++){
            Ray ray = camera.rayAt (float (x) / W, 1.f - float (y) / H);
            // std::cout << y << ", " << x << ", " << ray.direction() << std::endl;
            size_t meshIndex, triangleIndex;
            float u,v,d;
            if (rayTrace(scene, ray, meshIndex, triangleIndex, u, v, d))
                image(x,y) = shade(scene, meshIndex, triangleIndex, u, v);
        }
    }
}