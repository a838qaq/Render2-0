#include <iostream>
#include <fstream>
#include "Vec3.h"
#include "Ray.h"
#include "Camera.h"

Vec3 GetColor(Ray ray)
{
    ray.direction.Normalize();
    double t = 0.5 * (ray.direction.y + 1);
    return (1 - t) * Vec3(1, 1, 1) + t * Vec3(0.5, 0.7, 1);
}

using namespace std;
int main()
{
    int nx = 1000, ny = 500;

    ofstream out;
    out.open("../photo.pmm", ios::out);
    out << "P3" << endl;
    out << nx << " " << ny << endl;
    out << "255" << endl;

    Camera camera;
    camera.Reset();

    for (double y = 0; y < ny; y++)
    {
        for (double x = 0; x < nx; x++)
        {
            double U = x / nx;
            double V = y / ny;
            Ray R = camera.GetRay(U, V);
            // Ray R = Ray(Vec3(0, 0, 0), Vec3(-2, -1, -1) + U * Vec3(4, 0, 0) + V * Vec3(0, 2, 0));
            Vec3 v = GetColor(R);
            double r = v.x;
            double g = v.y;
            double b = v.z;
            out << (int)(r * 255) << " " << (int)(g * 255) << " " << (int)(b * 255) << endl;
        }
    }
    return 0;
}