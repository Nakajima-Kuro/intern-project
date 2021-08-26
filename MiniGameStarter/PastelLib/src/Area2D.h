#pragma once
#include "ISubject.h"
#include "IObserver.h"
#include "Point2D.h"
#include <memory>
class Area2D :
	public ISubject
{
private:
	std::string name;
	Point2D position;
	int sizeX;
	int sizeY;
public:
	Area2D(Point2D position, int sizeX, int sizeY, std::string name);
	std::list<std::shared_ptr<Area2D>> listOverlapArea;
	void checkCollision(std::list<std::shared_ptr<Area2D>> listArea2D);
	Point2D GetPosition();
	int GetSizeX();
	int GetSizeY();
};

