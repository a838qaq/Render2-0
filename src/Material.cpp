#include "Material.h"
bool Lambertain::Scatter(Ray &ray, HitRecord &record, Vec3 &atteuation, Ray &scattered) const
{
    Vec3 P = 2 * Vec3((rand() % 1000) / 1000.0, (rand() % 1000) / 1000.0, (rand() % 1000) / 1000) - Vec3(1, 1, 1);
    P.Normalize();
    Vec3 target = record.hitPoint + record.norm + P;
    scattered = Ray(record.hitPoint, target - record.hitPoint);
    atteuation = albedo;
    return true;
}

bool Metal::Scatter(Ray &ray, HitRecord &record, Vec3 &atteuation, Ray &scattered) const
{
    Vec3 P = 2 * Vec3((rand() % 1000) / 1000.0, (rand() % 1000) / 1000.0, (rand() % 1000) / 1000) - Vec3(1, 1, 1);
    P.Normalize();
    Vec3 reflect = Ray().GetReflectRay(ray.direction, record.norm);
    scattered = Ray(record.hitPoint, reflect + diffuse * P);
    atteuation = albedo;
    return (scattered.direction.Dot(record.norm)); // angle is less than 90
}