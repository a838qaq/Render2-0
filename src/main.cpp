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

inline Vec3 GetColor(Ray, Hitable *world, int depth);
inline Vec3 GetRandomDirection();
inline double Random();

int main()
{
    int nx = 1000, ny = 500; // photo's width and height
    int sampleTimes = 100;   // sample time per pix
    int objNumber = 4;

    // init for .ppm
    ofstream out;
    out.open("../photo.ppm", ios::out);
    out << "P3" << endl;
    out << nx << " " << ny << endl;
    out << "255" << endl;

    Camera camera;
    camera.Reset();
    Hitable *list[objNumber];
    list[0] = new Sphere(Vec3(0, 0, -1), 0.5, new Lambertain((Vec3(0.8, 0.3, 0.3))));
    list[1] = new Sphere(Vec3(0, -100.5, -1), 100, new Lambertain((Vec3(1, 0, 0))));
    list[2] = new Sphere(Vec3(1, 0, -1), 0.5, new Metal(Vec3(0.8, 0.6, 0.2), 0.1));
    list[3] = new Sphere(Vec3(-1, 0, -1), 0.5, new Metal(Vec3(0.8, 0.8, 0.8), 0.5));
    Hitable *worldObj = new HitableList(list, objNumber);

    srand(time(NULL));
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
                color = color + GetColor(R, worldObj, 0);
            }
            color = color / sampleTimes;
            double r = color.x;
            double g = color.y;
            double b = color.z;
            out << (int)(r * 255) << " " << (int)(g * 255) << " " << (int)(b * 255) << endl;
        }
        int ty = ny * 0.1;
        if ((long int)y % ty == 0)
        {
            cout << "Rander: " << (ny - y) / ny * 100 << "%" << endl;
        }
    }
    return 0;
}

inline Vec3 GetColor(Ray ray, Hitable *world, int depth)
{
    HitRecord tempRecord;
    if (world->Hit(ray, 0, __DBL_MAX__, tempRecord))
    {
        Ray scattered;    // difuse light
        Vec3 attunuation; // fade rate
        if (depth < 50 && tempRecord.pMar->Scatter(ray, tempRecord, attunuation, scattered))
        {
            return attunuation * GetColor(scattered, world, depth + 1);
        }
        else
        {
            return Vec3(0, 0, 0);
        }
    }
    else
    {
        ray.direction.Normalize();
        double t = 0.5 * (ray.direction.y + 1);
        return (1 - t) * Vec3(1, 1, 1) + t * Vec3(0.5, 0.7, 1);
    }
}
inline double Random()
{
    return (rand() % 1000) / 1000.0;
}

inline Vec3 GetRandomDirection()
{
    Vec3 P(0, 0, 0);
    P = 2 * Vec3(Random(), Random(), Random()) - Vec3(1, 1, 1);
    P.Normalize();

    return P;
}