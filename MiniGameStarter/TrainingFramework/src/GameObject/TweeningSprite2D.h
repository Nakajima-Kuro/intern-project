#pragma once
#include "Sprite2D.h"
class TweeningSprite2D :
    public Sprite2D
{
protected:
	Vector2 m_anchorPosition;
	GLfloat m_tweenX;
	GLfloat m_tweenY;
	int m_directionX;
	int m_directionY;
	GLfloat m_time;
public:
	TweeningSprite2D();
	TweeningSprite2D(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, GLfloat tweenX, GLfloat tweenY, GLfloat time);
	void		Init() override;
	void		Update(GLfloat deltatime) override;
	void		ResetPosition();
	void		Set2DPosition(Vector2 position);
	void		Set2DPosition(GLfloat x, GLfloat y);
};

