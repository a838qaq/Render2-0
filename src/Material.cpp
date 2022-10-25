#include <iostream>
#include <cmath>
#include "Material.h"
bool Lambertain::Scatter(Ray &ray, HitRecord &record, Vec3 &atteuation, Ray &scattered) const
{
    Vec3 P = 2 * Vec3((rand() % 100000) / 100000.0, (rand() % 1000) / 1000.0, (rand() % 1000) / 1000) - Vec3(1, 1, 1);
    P.Normalize();
    Vec3 target = record.hitPoint + record.norm + P;
    scattered = Ray(record.hitPoint, target - record.hitPoint, ray.refrate);
    atteuation = albedo;
    return true;
}

bool Metal::Scatter(Ray &ray, HitRecord &record, Vec3 &atteuation, Ray &scattered) const
{
    Vec3 P = 2 * Vec3((rand() % 1000) / 1000.0, (rand() % 1000) / 1000.0, (rand() % 1000) / 1000) - Vec3(1, 1, 1);
    P.Normalize();
    Vec3 reflect = Ray().GetReflectRay(ray.direction, record.norm);
    scattered = Ray(record.hitPoint, reflect + diffuse * P, ray.refrate);
    atteuation = albedo;
    return (scattered.direction.Dot(record.norm) > 0); // angle is less than 90
}

bool Glass::Scatter(Ray &ray, HitRecord &record, Vec3 &atteuation, Ray &scattered) const
{
    atteuation = albedo;
    Vec3 outDir;
    Ray inRay(ray);
    Vec3 norm = record.norm;
    norm.Normalize();
    inRay.direction.Normalize();
    double cosIn = norm.Dot(inRay.direction);
    if (record.norm.Dot(inRay.direction) > 0)
    {
        cosIn *= -1;
        if (sqrt(1 - cosIn * cosIn) > (1) / inRay.refrate)
        {
            outDir = inRay.GetReflectRay(inRay.direction, -norm);
            scattered = Ray(record.hitPoint, outDir, inRay.refrate);
            return true;
        }
        else
        {
            outDir = (inRay.refrate) * inRay.direction - (-norm) * (inRay.refrate * cosIn + sqrt(1 - inRay.refrate * inRay.refrate * (1 - cosIn * cosIn)));
            scattered = Ray(record.hitPoint, outDir, 1);
            return true;
        }
    }
    else
    {
        outDir = (inRay.refrate / refrate) * inRay.direction - (norm / refrate) * (inRay.refrate * cosIn + sqrt(refrate * refrate - inRay.refrate * inRay.refrate * (1 - cosIn * cosIn)));
        scattered = Ray(record.hitPoint, outDir, refrate);
        return true;
    }
    /*
        if (Ray(ray).ifRefract(ray.direction, record.norm, refrate, outDir))
        {
            if (record.norm.Dot(ray.direction) > 0)
                scattered = Ray(record.hitPoint, outDir, 1);
            else
                scattered = Ray(record.hitPoint, outDir, refrate);
            // std::cout << "ray" << std::endl;
            return true;
        }
        else
        {
            scattered = Ray(record.hitPoint, outDir, refrate);
        }
        return true; */
}