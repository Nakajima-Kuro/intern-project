#include "DynamicObject.h"

DynamicObject::DynamicObject(int id, const char* name, std::pair<int, int> position) :BaseObject(id, name, position)
{
}

void DynamicObject::move(std::pair <int, int> velocity)
{
	this->setPosition(std::pair <int, int>(this->getPosition().first + velocity.first, this->getPosition().second + velocity.second));
	return;
}
