#include "House.h"

House::House(int id, const char* name, std::pair<int, int> position) :StaticObject(id, name, position)
{
	this->setName(this->getName().insert(0, "House: "));
}
