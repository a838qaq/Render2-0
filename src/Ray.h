#pragma once
#include "Vec3.h"

class Ray
{
public:
    Vec3 origin;
    Vec3 direction;

public:
    Ray();
    Ray(Vec3 _origin, Vec3 _direction);
    ~Ray();
};