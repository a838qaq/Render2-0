#include <iostream>
#include <cmath>
#include "Material.h"
bool Lambertain::Scatter(Ray &ray, HitRecord &record, Vec3 &atteuation, Ray &scattered, bool &ifLight) const
{
    Vec3 P = 2 * Vec3((rand() % RAND_MAX) / (double)RAND_MAX, (rand() % RAND_MAX) / (double)RAND_MAX, (rand() % RAND_MAX) / (double)RAND_MAX) - Vec3(1, 1, 1);
    P.Normalize();
    Vec3 target = record.hitPoint + record.norm + P;
    scattered = Ray(record.hitPoint, target - record.hitPoint, ray.refrate);
    atteuation = albedo;
    return true;
}

bool Metal::Scatter(Ray &ray, HitRecord &record, Vec3 &atteuation, Ray &scattered, bool &ifLight) const
{
    Vec3 P = 2 * Vec3((rand() % RAND_MAX) / (double)RAND_MAX, (rand() % RAND_MAX) / (double)RAND_MAX, (rand() % RAND_MAX) / (double)RAND_MAX) - Vec3(1, 1, 1);
    P.Normalize();
    Vec3 reflect = Ray().GetReflectRay(ray.direction, record.norm);
    scattered = Ray(record.hitPoint, reflect + diffuse * P, ray.refrate); // get some diffuse
    atteuation = albedo;
    return (scattered.direction.Dot(record.norm) > 0); // angle is less than 90
}

bool Glass::Scatter(Ray &ray, HitRecord &record, Vec3 &atteuation, Ray &scattered, bool &ifLight) const
{
    atteuation = albedo;
    Vec3 outDir;
    Ray inRay(ray);
    Vec3 norm = record.norm;
    norm.Normalize();
    inRay.direction.Normalize();
    double cosIn = norm.Dot(inRay.direction);
    if (record.norm.Dot(inRay.direction) > 0) // out shoot light
    {
        cosIn *= -1;
        if (sqrt(1 - cosIn * cosIn) > (1 / inRay.refrate))
        {
            // reflect
            outDir = inRay.GetReflectRay(inRay.direction, -norm);
            outDir.Normalize();
            scattered = Ray(record.hitPoint + 0.01 * outDir, outDir, refrate);
            return true;
        }
        else
        {
            // refract
            outDir = (inRay.refrate) * inRay.direction - (-norm) * (inRay.refrate * cosIn + sqrt(1 - inRay.refrate * inRay.refrate * (1 - cosIn * cosIn)));
            outDir.Normalize();
            scattered = Ray(record.hitPoint + 0.01 * outDir, outDir, 1);
            return true;
        }

        /*  outDir = inRay.direction;
         scattered = Ray(record.hitPoint + 0.01 * outDir, outDir, 1); */
        return true;
    }
    else // in shoot light
    {
        outDir = (inRay.refrate / refrate) * inRay.direction - (norm / refrate) * (inRay.refrate * cosIn + sqrt(refrate * refrate - inRay.refrate * inRay.refrate * (1 - cosIn * cosIn)));
        // outDir = inRay.direction;
        outDir.Normalize();
        scattered = Ray(record.hitPoint + 0.01 * outDir, outDir, refrate);
        return true;
    }
}

bool Light::Scatter(Ray &ray, HitRecord &record, Vec3 &atteuation, Ray &scattered, bool &ifLight) const
{
    atteuation = intensity;
    ifLight = true;
    return true;
}