#pragma once
#include "Vec3.h"
#include "Ray.h"
#include "Hitable.h"
#include "Material.h"

class Sphere : public Hitable
{
public:
    Vec3 center;
    double R;
    Material *pMaterial;

public:
    Sphere();
    Sphere(Vec3 _center, double _R);
    Sphere(Vec3 _center, double _R, Material *_pMaterial);
    ~Sphere();

    virtual bool Hit(Ray ray, double tMin, double tMax, HitRecord &record) const;
};
