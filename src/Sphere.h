#pragma once
#include "Vec3.h"
#include "Ray.h"
#include "Hitable.h"
class Sphere : public Hitable
{
public:
    Vec3 center;
    double R;

public:
    Sphere();
    Sphere(Vec3 _center, double _R);
    ~Sphere();

    virtual bool Hit(Ray ray, double tMin, double tMax, HitRecord &record) const;
};
