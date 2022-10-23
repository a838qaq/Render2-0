#include <iostream>
#include <fstream>
#include <random>
#include <ctime>
#include "Vec3.h"
#include "Ray.h"
#include "Camera.h"
#include "Sphere.h"
#include "HitableList.h"
#include "Hitable.h"
using namespace std;
inline double Random()
{
    time_t seed = time(nullptr);
    default_random_engine eng(seed);
    uniform_real_distribution<double> number(0, 1);
    return number(eng);
}
inline Vec3 GetColor(Ray ray, Hitable *world)
{
    HitRecord tempRecord;
    if (world->Hit(ray, 0, __DBL_MAX__, tempRecord))
    {
        return 0.5 * Vec3(tempRecord.norm.x + 1, tempRecord.norm.y + 1, tempRecord.norm.z + 1);
    }
    else
    {
        ray.direction.Normalize();
        double t = 0.5 * (ray.direction.y + 1);
        return (1 - t) * Vec3(1, 1, 1) + t * Vec3(0.5, 0.7, 1);
    }
}

int main()
{
    int nx = 1000, ny = 500;
    int sampleTimes = 2;
    int objNumber = 2;

    ofstream out;
    out.open("../photo.pmm", ios::out);
    out << "P3" << endl;
    out << nx << " " << ny << endl;
    out << "255" << endl;

    Camera camera;
    camera.Reset();
    Hitable *list[objNumber];
    list[0] = new Sphere(Vec3(0, 0, -1), 0.5);
    list[1] = new Sphere(Vec3(0, -100.5, -1), 100);
    Hitable *worldObj = new HitableList(list, objNumber);

    for (double y = ny - 1; y >= 0; y--)
    {
        for (double x = 0; x < nx; x++)
        {
            Vec3 color(0, 0, 0);
            for (int i = 0; i < sampleTimes; i++)
            {
                double U = (x + Random()) / nx;
                double V = (y + Random()) / ny;
                Ray R = camera.GetRay(U, V);
                color = color + GetColor(R, worldObj);
            }
            color = color / sampleTimes;
            double r = color.x;
            double g = color.y;
            double b = color.z;
            out << (int)(r * 255) << " " << (int)(g * 255) << " " << (int)(b * 255) << endl;
        }
    }
    return 0;
}