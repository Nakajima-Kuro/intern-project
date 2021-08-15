#pragma once
#include "BaseObject.h"
class StaticObject :
    public BaseObject
{
public:
    StaticObject(int id, const char* name, std::pair <int, int> position);
    void move(std::pair <int, int> velocity);
};

