#pragma once
#include "Ray.h"

class Material;
struct HitRecord
{
    double t;
    Vec3 hitPoint;
    Vec3 norm;
    Material *pMar;
};

class Hitable
{
public:
    virtual bool Hit(Ray ray, double tMin, double tMax, HitRecord &record) const = 0;
};
