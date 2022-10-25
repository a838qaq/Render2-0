#include "Camera.h"
#include "Vec3.h"
Camera::Camera() {}
Camera::~Camera() {}

Camera::Camera(Vec3 _position, Vec3 _direction, Vec3 _head)
{
    position = _position;
    direction = _direction;
    head = _head;
}

void Camera::Reset()
{
    height.y = 2;
    width.x = 4;
    position = Vec3(0, 0, 0);
    direction = Vec3(0, 0, -1);
    head = Vec3(0, 1, 0);
    Vec3 w = -direction;
    w.Normalize();
    Vec3 u = head.Cross(w);
    u.Normalize();
    Vec3 v = w.Cross(u);
    v.Normalize();
    camLowLeft = (position - (width.x * 0.5) * u * n - (height.y * 0.5) * v * n - w);
    // camLowLeft.z *= -1;
    // camLowLeft = -camLowLeft;
    // std::cout << camLowLeft.x << " " << camLowLeft.y << " " << camLowLeft.z << std::endl;
}

Ray Camera::GetRay(double u, double v)
{
    return Ray(position, camLowLeft + u * width + v * height, 1);
}