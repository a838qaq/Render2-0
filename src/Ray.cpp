#include "Ray.h"
#include "Vec3.h"
Ray::Ray() {}
Ray::~Ray() {}

Ray::Ray(Vec3 _origin, Vec3 _direction)
{
    origin = _origin;
    direction = _direction;
}