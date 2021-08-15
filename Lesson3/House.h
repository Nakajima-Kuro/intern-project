#pragma once
#include "StaticObject.h"
class House :
    public StaticObject
{
public:
    House(int id, const char* name, std::pair <int, int> position);
};

