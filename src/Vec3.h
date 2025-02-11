#pragma once
#include <iostream>
class Vec3
{
public:
    double x;
    double y;
    double z;

public:
    Vec3();
    Vec3(double _x = 0, double _y = 0, double _z = 0);
    ~Vec3();
    Vec3 operator+() { return *this; };
    Vec3 operator-() { return Vec3(-x, -y, -z); };
    double GetLenth();
    double GetLenth2();
    double Dot(Vec3 v);
    Vec3 Cross(Vec3 v);
    void Normalize();
    void ColorNormalize();
    friend Vec3 operator+(Vec3 v1, Vec3 v2);
    friend Vec3 operator*(Vec3 v1, Vec3 v2);
    friend Vec3 operator-(Vec3 v1, Vec3 v2);
    friend Vec3 operator*(double s, Vec3 v);
    friend Vec3 operator*(Vec3 v, double s);
    friend Vec3 operator/(Vec3 v, double s);
    friend std::istream &operator>>(std::istream, Vec3 v);
    friend std::ostream &operator<<(std::ostream, Vec3 v);
};
