#include "BaseObject.h"

BaseObject::BaseObject(int id, const char* name, std::pair <int, int> position = std::pair <int, int> (0,0))
{
	this->id = id;
	this->name = std::string(name);
	this->position = position;
}

BaseObject::~BaseObject()
{
	this->name.clear();
}

int BaseObject::getId()
{
	return this->id;
}

void BaseObject::setId(int id)
{
	this->id = id;
}

std::string BaseObject::getName()
{
	return this->name;
}

void BaseObject::setName(std::string name)
{
	this->name = name;
}

std::pair <int, int> BaseObject::getPosition()
{
	return this->position;
}

void BaseObject::printPosition()
{
	std::cout <<"(" << this->getPosition().first << ", " << this->getPosition().second << ")" << std::endl;
}

void BaseObject::setPosition(std::pair <int, int> position)
{
	this->position = position;
}
