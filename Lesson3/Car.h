#pragma once
#include "DynamicObject.h"
class Car :
    public DynamicObject
{
public:
    Car(int id, const char* name, std::pair <int, int> position);
    virtual void move(std::pair <int, int> velocity);
};

