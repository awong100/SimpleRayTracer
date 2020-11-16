#include <iostream>
#include "Image.h"
#include "Scene.h"
#include "Sphere.h"
#include "Cylinder.h"
#include "AABB.h"
using namespace std;
using namespace Raytracer148;
using namespace Eigen;

int main() {
    Image im(400, 400);

    Scene scene;
    
    Vector3d sphereColor1 = Vector3d(1.0, 0.0, 0.0);
    Vector3d center;
    
    //  Red Sphere
    center[0] = -1.5;
    center[1] = -0.5;
    center[2] = 6.0;
    Sphere *sph1 = new Sphere(center, 2);
    sph1->reflective = false;
    sph1->setColor(sphereColor1);
    scene.addShape(sph1);
    
    //  Green Sphere
    Vector3d sphereColor2 = Vector3d(0.0, 1.0, 0.0);
    center[0] = -2.0;
    center[1] = 0.5;
    center[2] = 4.5;
    Sphere *sph2 = new Sphere(center, .5);
    sph2->reflective = false;
    sph2 -> setColor(sphereColor2);
    scene.addShape(sph2);
    
    //  Blue sphere
    Vector3d sphereColor3 = Vector3d(0.0, 0.0, 1.0);
    center[0] = -1.0;
    center[1] = 0.75;
    center[2] = 4.75;
    Sphere *sph3 = new Sphere(center, .5);
    sph3->reflective = false;
    sph3 -> setColor(sphereColor3);
    scene.addShape(sph3);
    
    //  Purple Cylinder
    Vector3d cylColor = Vector3d(1.0, 0.0, 1.0);
    center = Vector3d(1.0, -1.5, 2.5);
    Vector3d direction = Vector3d(1.0, 0.0, 0.0);
    double radius = 0.2;
    Cylinder *cyl = new Cylinder(center, direction, radius);
    cyl->reflective = false;
    cyl->setColor(cylColor);
    scene.addShape(cyl);
    
    //  Teal Cylinder
    cylColor = Vector3d(0.0, 1.0, 1.0);
    center = Vector3d(0.5, 0, 3.5);
    direction = Vector3d(0.0, 1.0, 0.0);
    Cylinder *cylB = new Cylinder(center, direction, radius);
    cylB->reflective = true;
    cylB->setColor(cylColor);
    scene.addShape(cylB);
    
    
    //  Silver/Metallic Cylinder
    cylColor = Vector3d(.75, .75, .75);
    center = Vector3d(0.0, 0.5, 2.0);
    direction = Vector3d(1.0, 0.0, 0.0);
    radius = 0.15;
    Cylinder *cylC = new Cylinder(center, direction, radius);
    cylC->reflective = true;
    cylC->setColor(cylColor);
    scene.addShape(cylC);
    
    //  Blue Cube
    Vector3d cubeColor = Vector3d(0.0, 0.0, 0.99);
    Vector3d b1 = Vector3d(1.5, 1.5, 2.5);
    Vector3d b2 = Vector3d(0, 0, 3.5);
    AABB *cube = new AABB(b1, b2);
    cube->reflective = false;
    cube->setColor(cubeColor);
    scene.addShape(cube);
    
    //  Gold Square
    cubeColor = Vector3d(1.0,0.84,0.0);
    b1 = Vector3d(-1, 1, 3);
    b2 = Vector3d(-2, 2, 3);
    AABB *cube2 = new AABB(b1, b2);
    cube2->reflective = false;
    cube2->setColor(cubeColor);
    scene.addShape(cube2);
    
    
    
    scene.render(im);
    im.writePNG("test.png");
    return 0;
}
