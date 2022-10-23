#pragma once
#include "Ray.h"

struct HitRecord
{
    double t;
    Vec3 hitPoint;
    Vec3 norm;
};

class Hitable
{
public:
    virtual bool Hit(Ray ray, double tMin, double tMax, HitRecord &record) const = 0;
};
