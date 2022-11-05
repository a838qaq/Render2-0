#pragma once
#include "Hitable.h"
class Material
{
public:
    virtual bool Scatter(Ray &ray, HitRecord &record, Vec3 &atteuation, Ray &scattered, bool &ifLight) const = 0;
};

class Lambertain : public Material
{
public:
    Vec3 albedo;

public:
    Lambertain(Vec3 _albedo) { albedo = _albedo; }
    virtual bool Scatter(Ray &ray, HitRecord &record, Vec3 &atteuation, Ray &scattered, bool &ifLight) const;
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
    virtual bool Scatter(Ray &ray, HitRecord &record, Vec3 &atteuation, Ray &scattered, bool &ifLight) const;
};

// simplification way of refraction
class Glass : public Material
{
public:
    Vec3 albedo;
    double refrate; // rate of refrate

public:
    Glass(Vec3 _albedo, double _refrate)
    {
        albedo = _albedo;
        refrate = _refrate;
    }
    // double curRefrate
    virtual bool Scatter(Ray &ray, HitRecord &record, Vec3 &atteuation, Ray &scattered, bool &ifLight) const;
};

class Light : public Material
{
public:
    Vec3 intensity;

public:
    Light(Vec3 _intensity) { intensity = _intensity; }
    virtual bool Scatter(Ray &ray, HitRecord &record, Vec3 &atteuation, Ray &Scattered, bool &ifLight) const;
};