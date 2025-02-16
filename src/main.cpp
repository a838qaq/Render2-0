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
#define MAX_DEPTH 100 // max of tracing depth

using namespace std;

inline Vec3 GetColor(Ray, Hitable *world, int depth);
inline Vec3 GetRandomDirection();
inline double Random();
inline Vec3 GammaCorrect(Vec3 color, double gamma = 2.2);

int main(int argc, char *argv[])
{
    int sampleTimes; // sampletimes per pix
    if (argc == 2)
    {
        sampleTimes = atoi(argv[1]);
    }
    else
    {
        sampleTimes = 10;
    }

    int nx = 1000, ny = 500; // photo's width and height
    int objNumber = 8;
    int ty = 0.01 * ny;
    int count = 1;

    // init for .ppm
    ofstream out;
    out.open("../photo.ppm", ios::out);
    out << "P3" << endl;
    out << nx << " " << ny << endl;
    out << "255" << endl;

    // creat object
    Camera camera;
    camera.Reset();
    Hitable *list[objNumber];

    list[0] = new Sphere(Vec3(0.3, -0.2, -1.7), 0.3, new Lambertain(Vec3(0.0, 0.0, 0.1)));
    // list[8] = new Sphere(Vec3(0.3, 2, -1.5), 1.5, new Light(Vec3(10000, 10000, 10000)));
    list[7] = new Sphere(Vec3(-0.5, 0.1, -2.5), 0.6, new Metal(Vec3(0.3, 0.3, 0.3), 0.1));
    // list[8] = new Sphere(Vec3(-0.8, 0.2, -1), 0.7, new Glass(Vec3(0.6, 0.8, 0.8), 0));
    // list[7] = new Sphere(Vec3(0.7, 0, -0.5), 0.5, new Glass(Vec3(0.8, 0.6, 0.2), 0.2));
    list[1] = new Sphere(Vec3(0, 5.4, -1), 3, new Light(Vec3(500, 500, 500)));
    list[2] = new Sphere(Vec3(0, -100.5, -1), 100, new Lambertain(Vec3(0.8, 0.8, 0.8))); // ground
    list[3] = new Sphere(Vec3(0, 102.5, -1), 100, new Light(Vec3(500, 500, 500)));       // roof
    list[4] = new Sphere(Vec3(0, 1, -103), 100, new Lambertain(Vec3(0.8, 0.8, 0.8)));    // back
    list[5] = new Sphere(Vec3(-101.5, 0, -1), 100, new Lambertain(Vec3(0.6, 0.0, 0.0))); // right
    list[6] = new Sphere(Vec3(101.5, 0, -1), 100, new Lambertain(Vec3(0.0, 0.6, 0.0)));  // left */

    /*  list[0] = new Sphere(Vec3(0, 0, -1), 0.5, new Lambertain((Vec3(0.8, 0.3, 0.3))));
     list[1] = new Sphere(Vec3(0, -100.5, -1), 100, new Lambertain((Vec3(1, 0, 0))));
     list[2] = new Sphere(Vec3(1, 0, -1), 0.5, new Metal(Vec3(0.8, 0.6, 0.2), 0.1));
     list[3] = new Sphere(Vec3(-1, 0, -1), 0.5, new Metal(Vec3(1, 1, 1), 0));
     list[4] = new Sphere(Vec3(0, 0, 2), 0.3, new Light(Vec3(100, 100, 100)));
      */
    Hitable *worldObj = new HitableList(list, objNumber);

    srand(time(NULL));
    for (double y = ny - 1; y >= 0; y--)
    {
        for (double x = 0; x < nx; x++)
        {
            Vec3 color(0, 0, 0);
            for (int i = 0; i < sampleTimes; i++)
            {
                double U = (x + Random()) / nx; // random for AA
                double V = (y + Random()) / ny;
                Ray R = camera.GetRay(U, V);
                Vec3 tClolor = GetColor(R, worldObj, 0);
                tClolor.ColorNormalize();
                color = color + tClolor;
            }
            color = color / sampleTimes;

            color = GammaCorrect(color);

            double r = color.x;
            double g = color.y;
            double b = color.z;
            out << (int)(r * 255) << " " << (int)(g * 255) << " " << (int)(b * 255) << endl;
        }
        if ((long int)y % ty == 0)
        {
            cout << "Rander: " << count++ << "%" << endl;
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
        bool ifLight = false;
        if (depth < MAX_DEPTH && tempRecord.pMar->Scatter(ray, tempRecord, attunuation, scattered, ifLight))
        {
            if (!ifLight)
            {
                return attunuation * GetColor(scattered, world, depth + 1);
            }
            else
            {
                return attunuation;
            }
        }
        else
        {
            return Vec3(1, 1, 1);
        }
    }
    else
    {
        // background color
        // ray.direction.Normalize();
        // double t = 0.5 * (ray.direction.y + 1);
        // return (1 - t) * Vec3(1, 1, 1) + t * Vec3(0.5, 0.7, 1);
        return Vec3(1, 1, 1);
    }
}
inline double Random()
{
    return (rand() % RAND_MAX) / (double)RAND_MAX;
}

inline Vec3 GetRandomDirection()
{
    Vec3 P(0, 0, 0);
    P = 2 * Vec3(Random(), Random(), Random()) - Vec3(1, 1, 1);
    P.Normalize();

    return P;
}

inline Vec3 GammaCorrect(Vec3 color, double gamma)
{
    color.x = pow(color.x, 1.0 / gamma);
    color.y = pow(color.y, 1.0 / gamma);
    color.z = pow(color.z, 1.0 / gamma);
    return color;
}