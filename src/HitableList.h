#pragma once

#include "Hitable.h"
class HitableList : public Hitable
{
private:
    Hitable **list;
    int listSize;

public:
    HitableList();
    HitableList(Hitable **_list, int _listSize);
    ~HitableList();
    virtual bool Hit(Ray ray, double tMin, double tMax, HitRecord &record) const;
};
