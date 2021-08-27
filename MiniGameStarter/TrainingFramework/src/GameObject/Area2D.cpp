#include "Area2D.h"
#include "GameManager/ResourceManagers.h"
#include "Sprite2D.h"

Area2D::Area2D(std::string name = "")
	: m_sizeX(0), m_sizeY(0), m_name(name), m_background(nullptr)
{
	Init();
}

Area2D::~Area2D()
{
	m_listOverlapArea.clear();
	delete m_background;
}

void Area2D::Init()
{
	//Setup area hitbox display
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	auto texture = ResourceManagers::GetInstance()->GetTexture("spr_hitbox.tga");
	m_background = new Sprite2D(model, shader, texture);
	//m_background->SetVisible(false);
}

void Area2D::Draw()
{
	m_background->Draw();
}

void Area2D::Update(GLfloat deltatime)
{
}

void Area2D::checkCollision(std::list<std::shared_ptr<Area2D>> listArea2D)
{
	for (auto const& area : listArea2D) {

		Vector2 l1 = Vector2(m_position.x - m_sizeX, m_position.y - m_sizeY);
		Vector2 r1 = Vector2(m_position.x + m_sizeX, m_position.y + m_sizeY);
		Vector2 l2 = Vector2(area->GetPosition().x - area->GetSizeX(), area->GetPosition().y - area->GetSizeY());
		Vector2 r2 = Vector2(area->GetPosition().x + area->GetSizeX(), area->GetPosition().y + area->GetSizeY());
		//Check if 2 area overlap
		bool overlap = true;
		if (l1.x == r1.x || l1.y == r1.y || l2.x == r2.x
			|| l2.y == r2.y) {
			// the line cannot have positive overlap
			overlap = false;
		}

		// If one rectangle is on left side of other
		if (l1.x >= r2.x || l2.x >= r1.x)
			overlap = false;

		// If one rectangle is above other
		if (r1.y >= l2.y || r2.y >= l1.y)
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

Vector2 Area2D::Get2DPosition()
{
	return Vector2(m_position.x, m_position.y);
}

void Area2D::Set2DPosition(Vector2 position)
{
	m_position = Vector3(position.x, position.y, 0.0f);
	m_background->Set2DPosition(position);
	CalculateWorldMatrix();
}

void Area2D::Set2DPosition(GLint x, GLint y)
{
	m_position = Vector3(x, y, 0.0f);
	m_background->Set2DPosition(x, y);
	CalculateWorldMatrix();
}

void Area2D::SetSize(GLint sizeX, GLint sizeY)
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
