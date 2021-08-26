#include "Area2D.h"
#include<algorithm>

Area2D::Area2D(Point2D position, int sizeX, int sizeY, std::string name = "")
{
	this->position = position;
	this->sizeX = sizeX;
	this->sizeY = sizeY;
	this->name = name;
}

void Area2D::checkCollision(std::list<std::shared_ptr<Area2D>> listArea2D)
{
	for (auto const& area : listArea2D) {

		Point2D l1 = Point2D(this->position.GetX() - this->sizeX, this->position.GetY() - this->sizeY);
		Point2D r1 = Point2D(this->position.GetX() + this->sizeX, this->position.GetY() + this->sizeY);
		Point2D l2 = Point2D(area->GetPosition().GetX() - area->GetSizeX(), area->GetPosition().GetY() - area->GetSizeY());
		Point2D r2 = Point2D(area->GetPosition().GetX() + area->GetSizeX(), area->GetPosition().GetY() + area->GetSizeY());
		//Check if 2 area overlap
		bool overlap = true;
		if (l1.GetX() == r1.GetX() || l1.GetY() == r1.GetY() || l2.GetX() == r2.GetX()
			|| l2.GetY() == r2.GetY()) {
			// the line cannot have positive overlap
			overlap = false;
		}

		// If one rectangle is on left side of other
		if (l1.GetX() >= r2.GetX() || l2.GetX() >= r1.GetX())
			overlap = false;

		// If one rectangle is above other
		if (r1.GetY() >= l2.GetY() || r2.GetY() >= l1.GetY())
			overlap = false;

		if (overlap == true) {
			//One area enter
			listOverlapArea.push_back(area);
			//Notify overlap here
			Notify(this->name.append("area_enter"));
		}
		else {
			if ((std::find(this->listOverlapArea.begin(), this->listOverlapArea.end(), area) != this->listOverlapArea.end())) {
				//Found area in the list. Which mean this area has exited OUR area
				//Notify area exit here
				Notify(this->name.append("area_exit"));
				listOverlapArea.remove(area);
			}
		}
	}
}

Point2D Area2D::GetPosition()
{
	return this->position;
}

int Area2D::GetSizeX()
{
	return this->sizeX;
}

int Area2D::GetSizeY()
{
	return this->sizeY;
}
