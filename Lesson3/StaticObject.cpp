#include "StaticObject.h"

StaticObject::StaticObject(int id, const char* name, std::pair<int, int> position):BaseObject(id, name, position)
{
}

void StaticObject::move(std::pair<int, int> velocity)
{
	return;
}
