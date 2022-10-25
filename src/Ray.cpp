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

bool Ray::ifRefract(Vec3 v, Vec3 n, double refrateOut, Vec3 &refracted)
{
    Vec3 UnitV = v;
    UnitV.Normalize();
    n.Normalize();
    double cosIn = n.Dot(UnitV);
    if (refrate > refrateOut)
    {
        if (sqrt((1 - cosIn * cosIn)) > (refrateOut / refrate)) // no refract
        {
            refracted = Ray().GetReflectRay(v, -n);
            return false;
        }
    }

    // refracted = (Ray().GetReflectRay(v, n));
    // refracted = (refrate / refrateOut) * UnitV - (n / refrateOut) * (refrate * cosIn + sqrt(refrateOut * refrateOut - refrate * refrate * (1 - cosIn * cosIn)));
    refracted = v;

    return true;
}