#include "Tree.h"

Tree::Tree(int id, const char* name, std::pair <int, int> position):StaticObject(id, name, position)
{
	this->setName(this->getName().insert(0, "Tree: "));
}
