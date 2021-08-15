#include "Motorbike.h"

Motorbike::Motorbike(int id, const char* name, std::pair <int, int> position) :DynamicObject(id, name, position)
{
	this->setName(this->getName().insert(0, "Motorbike: "));
}