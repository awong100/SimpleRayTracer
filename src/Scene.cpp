#include "Scene.h"
#include <cmath>
using namespace Raytracer148;
using namespace std;
using namespace Eigen;

HitRecord Scene::closestHit(const Ray &ray) {
    HitRecord result;
    result.t = -1;
    bool foundSomething = false;

    for (unsigned int i = 0; i < shapes.size(); i++) {
        HitRecord r = shapes[i]->intersect(ray);
        if (r.t > std::numeric_limits<double>::epsilon() && (!foundSomething || r.t < result.t)) {
            result = r;
            foundSomething = true;
        }
    }
    return result;
}

// Returns an RGB color, where R/G/B are each in the range [0,1]
Vector3d Scene::trace(const Ray &ray) {
    // For now we'll have diffuse shading with no shadows, so it's easy!
    HitRecord r = closestHit(ray);
    
    int rayDepth = 0;
    
    Vector3d tempColor = Vector3d(0.0, 0.0, 0.0);// default color
    
    Vector3d result;    //  color
    result[0] = result[1] = result[2] = 0.0; //can be used to change background/"default" color
    
    // Phong Shading components
    Vector3d diffuse, specular, ambient;
    diffuse[0] = diffuse[1] = diffuse[2] = 0;
    specular[0] = specular[1] = specular[2] = 0;
    
    //  ambient light
    float ambientStrength = 0.2;
    ambient = ambientStrength * Vector3d(1.0, 1.0, 1.0);
    
    if (r.t < numeric_limits<double>::epsilon()) return result;

    Vector3d lightDir = (lightPos - r.position).normalized();
    double dot = lightDir.dot(r.normal);
    if (dot < 0) dot = 0;
    
    //  diffuse light
    float diff = max(r.normal.dot(lightDir), 0.0);
    diffuse = diff * Vector3d(1.0, 1.0, 1.0);
    
    //specular light
    Vector3d viewDir = (ray.origin - r.position).normalized();
    Vector3d reflectDir = -lightDir - 2 * (-lightDir.dot(r.normal))
                            * r.normal;
    double specularStrength, spec;
    specularStrength = 0.5;
    spec = pow(max(viewDir.dot(reflectDir), 0.0), 32);
    specular = specularStrength * spec * Vector3d(1.0, 1.0, 1.0);
    
    //  calculate color
    result =  (ambient + diffuse + specular);
    Vector3d R = reflect(ray.direction, r.normal).normalized();
    
    //  assign color to shapes
    for (int i = 0; i < shapes.size(); i++){
        if(r.t == shapes[i]->intersect(ray).t){
            tempColor[0] = shapes[i]->color[0];
            tempColor[1] = shapes[i]->color[1];
            tempColor[2] = shapes[i]->color[2];
            break;
        }
    }
    
    //  phong lighting (no shadow)
    result[0] = result[0] * tempColor[0];
    result[1] = result[1] * tempColor[1];
    result[2] = result[2] * tempColor[2];
    
    //  Calculate reflections components
    //  recursively.
    for(int i = 0; i < shapes.size(); i++){
        rayDepth++;
        Ray reflection;
        reflection.origin = r.normal;
        reflection.direction = R;
        if(r.t == shapes[i]->intersect(ray).t){
            if(shapes[i]->isReflective() == true){
                result -= specular;
                specularStrength = 0.75;
                spec = pow(max(viewDir.dot(reflectDir), 0.0), 64);
                specular = specularStrength * spec * Vector3d(1.0, 1.0,                                                 1.0);
                result += specular;
                result = 0.8 * result + trace(reflection);
                if (rayDepth >= 2) {
                    //rayDepth = 0;
                    break;
                }
            }
        }
//        result = 0.8 * result + trace(reflection);
//        if (rayDepth >= 2) {
//            //rayDepth = 0;
//            break;
//        }
        
    }
    
    //  Shadow components
    Ray shadow;
    shadow.origin[0] = shadow.origin[1] = shadow.origin[2] = 0;
    
    //  calculate shadow parameters
    float bias = 0.01f; //  to fix "shadow acne"
    shadow.origin = r.position + r.normal * bias;
    shadow.direction = (lightDir - shadow.origin);
    HitRecord shadowHit = closestHit(shadow);
    
    //  cast shadows by reducing the color by 85%
    if(shadowHit.t > 0 ){
        result[0] = .15 * tempColor[0];
        result[1] = .15 * tempColor[1];
        result[2] = .15 * tempColor[2];
    }
    //result[0] = result[1] = result[2] = dot;
    return result;
}

//  calculate the direction of the reflection ray
Vector3d Scene::reflect(const Vector3d &I, const Vector3d &N){
    return I - 2 * I.dot(N) * N;
}

void Scene::render(Image &image) {
    // We make the assumption that the camera is located at (0,0,0)
    // and that the image plane happens in the square from (-1,-1,1)
    // to (1,1,1).

    assert(image.getWidth() == image.getHeight());

    int size = image.getWidth();
    double pixelSize = 2. / size;
    for (int x = 0; x < size; x++)
        for (int y = 0; y < size; y++) {
            Ray curRay;
            curRay.origin[0] = curRay.origin[1] = curRay.origin[2] = 0;

            curRay.direction[0] = (x + 0.5) * pixelSize - 1;
            curRay.direction[1] = 1 - (y + 0.5) * pixelSize;
            curRay.direction[2] = 1;

            Vector3d color = trace(curRay);
            image.setColor(x, y, color[0], color[1], color[2]);
            
            
            
        }
}
