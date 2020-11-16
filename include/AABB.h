#ifndef AABB_H
#define AABB_H

#include "Shape.h"

namespace Raytracer148 {
  class  AABB: public Shape {
  public:
      AABB(Eigen::Vector3d &v1,Eigen::Vector3d &v2) : vmin(v1), vmax(v2) {reflective = false;}
      
      virtual HitRecord intersect(const Ray &ray);
      Eigen::Vector3d vmin;
      Eigen::Vector3d vmax;
  };
}

#endif
