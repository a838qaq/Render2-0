#include "Vec3.h"
#include <cmath>

Vec3::Vec3() {}

Vec3::Vec3(double _x, double _y, double _z)
{
    this->x = _x;
    this->y = _y;
    this->z = _z;
}

Vec3::~Vec3() {}

double Vec3::Dot(Vec3 v)
{
    return x * v.x + y * v.y + z * v.z;
}

double Vec3::GetLenth()
{
    return (sqrt(x * x + y * y + z * z));
}

double Vec3::GetLenth2()
{
    return x * x + y * y + z * z;
}

Vec3 Vec3::Cross(Vec3 v)
{
    return Vec3(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
}

void Vec3::Normalize()
{
    double l = this->GetLenth();
    x /= l;
    y /= l;
    z /= l;
}

Vec3 operator+(Vec3 v1, Vec3 v2)
{
    return Vec3(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}

Vec3 operator-(Vec3 v1, Vec3 v2)
{
    return Vec3(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}

Vec3 operator*(Vec3 v, double s)
{
    return Vec3(v.x * s, v.y * s, v.z * s);
}

Vec3 operator*(double s, Vec3 v)
{
    return Vec3(v.x * s, v.y * s, v.z * s);
}

Vec3 operator/(Vec3 v, double s)
{
    return Vec3(v.x / s, v.y / s, v.z / s);
}

std::istream &operator>>(std::istream &IS, Vec3 v)
{
    IS >> v.x >> v.y >> v.z;
    return IS;
}

std::ostream &operator<<(std::ostream &OS, Vec3 v)
{
    OS << v.x << " " << v.y << " " << v.z;
    return OS;
}