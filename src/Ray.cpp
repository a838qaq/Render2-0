#include "Ray.h"
#include "Vec3.h"
#include <cmath>
Ray::Ray() {}
Ray::~Ray() {}

Ray::Ray(Vec3 _origin, Vec3 _direction, double _refrate)
{
    origin = _origin;
    direction = _direction;
    refrate = _refrate;
}

Vec3 Ray::GetEnd(double t)
{
    direction.Normalize();
    return origin + t * direction;
}

Vec3 Ray::GetReflectRay(Vec3 v, Vec3 n)
{
    return v - 2 * v.Dot(n) * n;
}
