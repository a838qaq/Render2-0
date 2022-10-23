#include "Sphere.h"
#include <cmath>

Sphere::Sphere() {}
Sphere::~Sphere() {}

Sphere::Sphere(Vec3 _center, double _R)
{
    center = _center;
    R = _R;
}

bool Sphere::Hit(Ray ray, double tMin, double tMax, HitRecord &record) const
{
    Vec3 OC = ray.origin - center;
    double a = ray.direction.Dot(ray.direction);
    double b = 2 * OC.Dot(ray.direction);
    double c = OC.Dot(OC) - R * R;
    double delta = b * b - 4 * a * c;
    if (delta > 0)
    {
        double temp = (-b - sqrt(delta)) / (2 * a);
        if (temp < tMax && temp > tMin)
        {
            record.t = temp;
            record.hitPoint = ray.GetEnd(record.t);
            record.norm = record.hitPoint - center;
            record.norm.Normalize();
            return true;
        }
        temp = (-b + sqrt(delta)) / (2 * a);
        if (temp < tMax && temp > tMin)
        {
            record.t = temp;
            record.hitPoint = ray.GetEnd(record.t);
            record.norm = record.hitPoint - center;
            record.norm.Normalize();
            return true;
        }
    }
    return false;
}