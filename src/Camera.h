#pragma once
#include "Vec3.h"
#include "Ray.h"
class Camera
{
public:
    Vec3 position;
    Vec3 direction;
    Vec3 head;

    Vec3 camLowLeft;
    Vec3 height;
    Vec3 width;
    double n = 1;

public:
    Camera();
    Camera(Vec3 _position, Vec3 _direction, Vec3 _head);
    ~Camera();
    void Reset();
    Ray GetRay(double u, double v);
};
