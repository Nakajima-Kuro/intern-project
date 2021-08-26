#pragma once
#include "ISubject.h"
#include "IObserver.h"
#include "Point2D.h"
#include "Sprite2D.h"
#include <memory>
class Area2D :
	public ISubject
{
private:
	std::string							m_name;
	Point2D								m_position;
	int									m_sizeX;
	int									m_sizeY;

	std::shared_ptr<Sprite2D>			m_background;
	std::list<std::shared_ptr<Area2D>>	m_listOverlapArea;
public:
	Area2D() : m_name(""), m_position(Point2D(0, 0)), m_sizeX(0), m_sizeY(0) {};
	Area2D(Point2D position, int sizeX, int sizeY, std::string name);
	
	//Collision logic
	void checkCollision(std::list<std::shared_ptr<Area2D>> listArea2D);
	std::shared_ptr<Area2D> GetCollidedArea();

	//Draw
	void Draw();
	void Update(float deltaTime);
	
	//get basic info
	Point2D GetPosition();
	void SetPosition(Point2D position);
	void SetPosition(float x, float y);
	void setSize(int sizeX, int sizeY);
	void setVisible(bool isVisible);
	int GetSizeX();
	int GetSizeY();
};

