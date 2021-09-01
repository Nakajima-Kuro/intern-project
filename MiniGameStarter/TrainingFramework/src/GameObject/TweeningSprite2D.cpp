#include "TweeningSprite2D.h"
#include "Shader.h"
#include "Model.h"
#include "Camera.h"
#include "Texture.h"
#include "Application.h"

TweeningSprite2D::TweeningSprite2D()
	:Sprite2D(), m_anchorPosition(Vector2(0, 0)), m_tweenX(0), m_tweenY(0), m_directionX(1), m_directionY(1), m_time(0)
{
}

TweeningSprite2D::TweeningSprite2D(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, GLfloat tweenX, GLfloat tweenY, GLfloat time)
	: Sprite2D(model, shader, texture), m_anchorPosition(Vector2(0, 0)), m_tweenX(tweenX), m_tweenY(tweenY), m_directionX(1), m_directionY(1), m_time(time)
{
}

void TweeningSprite2D::Init()
{
	SetCamera(Application::GetInstance()->GetCamera());
	CalculateWorldMatrix();
}

void TweeningSprite2D::Update(GLfloat deltatime)
{
	int offsetX = Get2DPosition().x - m_anchorPosition.x;
	int offsetY = Get2DPosition().y - m_anchorPosition.y;
	if (offsetX >= m_tweenX) {
		m_directionX = -1;
	}
	if (offsetX <= 0) {
		m_directionX = 1;
	}
	if (offsetY >= m_tweenY) {
		m_directionY = -1;
	}
	if (offsetY <= 0) {
		m_directionY = 1;
	}
	Sprite2D::Set2DPosition(
		Get2DPosition().x + round(m_directionX * (m_tweenX * (deltatime / m_time))),
		Get2DPosition().y + round(m_directionY * (m_tweenY * (deltatime / m_time)))
	);
}

void TweeningSprite2D::Set2DPosition(Vector2 position)
{
	m_anchorPosition = position;
	Sprite2D::Set2DPosition(position);
}

void TweeningSprite2D::Set2DPosition(GLfloat x, GLfloat y)
{
	Set2DPosition(Vector2(x, y));
}
