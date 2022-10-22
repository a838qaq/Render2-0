#include <iostream>
#include <fstream>
#include "Vec3.h"

using namespace std;
int main()
{
    int nx = 1000, ny = 500;

    ofstream out;
    out.open("../photo.pmm", ios::out);
    out << "P3" << endl;
    out << nx << " " << ny << endl;
    out << "255" << endl;

    for (double y = 0; y < ny; y++)
    {
        for (double x = 0; x < nx; x++)
        {
            Vec3 v(x / nx, y / ny, 0.2);
            double r = v.x;
            double g = v.y;
            double b = v.z;
            out << (int)(r * 255) << " " << (int)(g * 255) << " " << (int)(b * 255) << endl;
        }
    }
    return 0;
}