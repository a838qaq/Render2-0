#include "HitableList.h"
HitableList::HitableList(/* args */)
{
    list = nullptr;
}

HitableList::~HitableList()
{
    if (!list)
        delete[] list;
}

HitableList::HitableList(Hitable **_list, int _listSize)
{
    list = _list;
    listSize = _listSize;
}

bool HitableList::Hit(Ray ray, double tMin, double tMax, HitRecord &record) const
{
    HitRecord tempRecord;
    bool hited = false;
    double far = tMax;
    for (int i = 0; i < listSize; i++)
    {
        if (list[i]->Hit(ray, tMin, far, tempRecord))
        {
            hited = true;
            far = tempRecord.t;
            record = tempRecord;
        }
    }
    return hited;
}