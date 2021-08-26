#include "Area2D.h"
#include "GameManager/ResourceManagers.h"
#include<algorithm>

Area2D::Area2D(Point2D position, int sizeX, int sizeY, std::string name = "") :m_position(position), m_sizeX(sizeX), m_sizeY(sizeY), m_name(name)
{
	//Setup area hitbox display
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	auto texture = ResourceManagers::GetInstance()->GetTexture("spr_hitbox.tga");
	m_background = std::make_shared<Sprite2D>(model, shader, texture);
	m_background->Set2DPosition(GLint(m_position.GetX()), GLint(m_position.GetY()));
	m_background->SetSize(m_sizeX * 2, m_sizeY * 2);
	//m_background->SetVisible(false);
}

void Area2D::checkCollision(std::list<std::shared_ptr<Area2D>> listArea2D)
{
	for (auto const& area : listArea2D) {

		Point2D l1 = Point2D(m_position.GetX() - m_sizeX, m_position.GetY() - m_sizeY);
		Point2D r1 = Point2D(m_position.GetX() + m_sizeX, m_position.GetY() + m_sizeY);
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
			m_listOverlapArea.push_back(area);
			//Notify overlap here
			Notify(m_name.append("_area_enter"));
		}
		else {
			if ((std::find(m_listOverlapArea.begin(), m_listOverlapArea.end(), area) != m_listOverlapArea.end())) {
				//Found area in the list. Which mean this area has exited OUR area
				//Notify area exit here
				Notify(m_name.append("_area_exit"));
				m_listOverlapArea.remove(area);
			}
		}
	}
}

std::shared_ptr<Area2D> Area2D::GetCollidedArea()
{
	return m_listOverlapArea.front();
}

void Area2D::Draw()
{
	m_background->Draw();
}

void Area2D::Update(float deltaTime)
{
	m_background->Set2DPosition(GLint(m_position.GetX()), GLint(m_position.GetY()));
}

Point2D Area2D::GetPosition()
{
	return m_position;
}

void Area2D::SetPosition(Point2D position)
{
	m_position = position;
}

void Area2D::SetPosition(float x, float y)
{
	m_position = Point2D(x, y);
}

void Area2D::setSize(int sizeX, int sizeY)
{
	m_sizeX = sizeX;
	m_sizeY = sizeY;
	m_background->SetSize(sizeX * 2, sizeY * 2);
}

void Area2D::setVisible(bool isVisible)
{
	m_background->SetVisible(isVisible);
}

int Area2D::GetSizeX()
{
	return m_sizeX;
}

int Area2D::GetSizeY()
{
	return m_sizeY;
}
