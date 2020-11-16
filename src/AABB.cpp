#include "AABB.h"
#include <limits>
using namespace Raytracer148;
using namespace Eigen;
using namespace std;

HitRecord AABB::intersect(const Ray &ray) {
    HitRecord result;
    result.t = -1;

    float xmin = (vmin[0] - ray.origin[0]) / ray.direction[0];
    float xmax = (vmax[0] - ray.origin[0]) / ray.direction[0];
    
    if (xmin > xmax){
        float temp = xmin;
        xmin = xmax;
        xmax = temp;
    }
    
    float ymin = (vmin[1] - ray.origin[1]) / ray.direction[1];
    float ymax = (vmax[1] - ray.origin[1]) / ray.direction[1];
    
    if (ymin > ymax){
        float temp = ymin;
        ymin = ymax;
        ymax = temp;
    }
    
    if (xmin > ymax || ymin > xmax) return result;
    
    if (ymin > xmin) xmin = ymin;
    
    if (ymax < xmax) xmax = ymax;
    
    
    
    float zmin = (vmin[2] - ray.origin[2]) / ray.direction[2];
    float zmax = (vmax[2] - ray.origin[2]) / ray.direction[2];
    
    if (zmin > zmax){
        float temp = zmin;
        zmin = zmax;
        zmax = temp;
    }
    
    if (xmin > zmax || zmin > xmax) return result;
    
    if (zmin > xmin) xmin = zmin;
    
    if (zmax < xmax) xmax = zmax;
    
    float t = xmin;
    if (t < 0){
        t = xmax;
        if (t < 0) return result;
    }
    
    Vector3d normal = -vmax.normalized();
    result.normal = normal;
    result.t = t;
    result.position = ray.origin + ray.direction * t;
    return result;
}

