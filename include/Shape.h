#ifndef SHAPE_H
#define SHAPE_H

#include <Eigen/Dense>

namespace Raytracer148 {
struct Ray {
  Eigen::Vector3d origin, direction;
};

class Shape;

struct HitRecord {
  Eigen::Vector3d position, normal;
  double t;
};

class Shape {
public:
    virtual ~Shape(){}
    virtual HitRecord intersect(const Ray &ray) = 0;
    virtual void setColor(Eigen::Vector3d c){
        color = c;
    }
    virtual bool isReflective(){
        return reflective;
    }
    bool reflective;
    Eigen::Vector3d color;
};
}
#endif
