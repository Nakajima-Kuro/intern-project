#include "Car.h"

Car::Car(int id, const char* name, std::pair <int, int> position):DynamicObject(id, name, position)
{
	this->setName(this->getName().insert(0, "Car: "));
}

void Car::move(std::pair<int, int> velocity)
{
	//Car move x2 faster
	DynamicObject::move(std::pair<int, int>(velocity.first * 2, velocity.second * 2));
	return;
}
