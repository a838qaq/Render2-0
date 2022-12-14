#pragma once
#include "Vec3.h"

class Ray
{
public:
    Vec3 origin;
    Vec3 direction;
    double refrate;

public:
    Ray();
    Ray(Vec3 _origin, Vec3 _direction, double _refrate);
    Vec3 GetEnd(double t);
    Vec3 GetReflectRay(Vec3 v, Vec3 n);
    ~Ray();
};