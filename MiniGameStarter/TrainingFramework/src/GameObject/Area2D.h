#pragma once
#include "BaseObject.h"
#include "ISubject.h"
#include "IObserver.h"
#include "Sprite2D.h"
#include <memory>
class Area2D :
	public BaseObject, public ISubject
{
protected:
	std::string							m_name;
	GLint								m_sizeX;
	GLint								m_sizeY;
	std::list<std::shared_ptr<Area2D>>	m_listOverlapArea;
public:
	Area2D() : m_name(""), m_sizeX(0), m_sizeY(0), m_background(nullptr) {};
	Area2D(std::string name);
	virtual ~Area2D();

	//Game Function
	void	Init() override;
	void	Draw() override;
	void	Update(GLfloat deltatime) override;

	//Collision logic
	void checkCollision(std::list<std::shared_ptr<Area2D>> listArea2D);
	std::shared_ptr<Area2D> GetCollidedArea();

	//get basic info
	Vector2 Get2DPosition();
	void Set2DPosition(Vector2 position);
	void Set2DPosition(GLfloat x, GLfloat y);
	void SetSize(GLint x, GLint y);
	void setVisible(bool isVisible);
	int GetSizeX();
	int GetSizeY();
private:
	Sprite2D* m_background;
};

