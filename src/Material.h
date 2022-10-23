#pragma once
#include "Hitable.h"
class Material
{
public:
    virtual bool Scatter(Ray &ray, HitRecord &record, Vec3 &atteuation, Ray &scattered) const = 0;
};

class Lambertain : public Material
{
public:
    Vec3 albedo;

public:
    Lambertain(Vec3 _albedo) { albedo = _albedo; }
    virtual bool Scatter(Ray &ray, HitRecord &record, Vec3 &atteuation, Ray &scattered) const;
};

class Metal : public Material
{
public:
    Vec3 albedo;
    double diffuse;

public:
    Metal(Vec3 _albedo, double _diffuse)
    {
        albedo = _albedo;
        diffuse = _diffuse;
    }
    virtual bool Scatter(Ray &ray, HitRecord &record, Vec3 &atteuation, Ray &scattered) const;
};
