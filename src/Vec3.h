#pragma once
#include <iostream>
class Vec3
{
public:
    double x = 0;
    double y = 0;
    double z = 0;

public:
    Vec3();
    Vec3(double _x, double _y, double _z);
    ~Vec3();
    inline Vec3 operator+() { return *this; };
    inline Vec3 operator-() { return Vec3(-x, -y, -z); };
    inline double GetLenth();
    inline double GetLenth2();
    inline double Dot(Vec3 v);
    inline Vec3 Cross(Vec3 v);
    inline void Normalize();
    inline friend Vec3 operator+(Vec3 v1, Vec3 v2);
    inline friend Vec3 operator-(Vec3 v1, Vec3 v2);
    inline friend Vec3 operator*(double s, Vec3 v);
    inline friend Vec3 operator*(Vec3 v, double s);
    inline friend Vec3 operator/(Vec3 v, double s);
    inline friend std::istream &operator>>(std::istream, Vec3 v);
    inline friend std::ostream &operator<<(std::ostream, Vec3 v);
};
