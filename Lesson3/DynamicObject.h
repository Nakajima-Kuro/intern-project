#pragma once
#include "BaseObject.h"
class DynamicObject :
    public BaseObject
{
public:
    DynamicObject(int id, const char* name, std::pair <int, int> position);
    void move(std::pair <int, int> velocity) override;
};

