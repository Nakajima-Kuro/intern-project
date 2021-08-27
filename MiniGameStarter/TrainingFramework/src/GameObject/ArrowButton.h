#pragma once
#include "AnimationSprite2D.h"
#include "Area2D.h"
#include "IObserver.h"
class ArrowButton :
	public AnimationSprite2D, public IObserver
{
public:
	ArrowButton() : AnimationSprite2D(), m_input(-1) {}
	ArrowButton(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, int input);
	int HandleKeyEvents(int key, bool bIsPressed);

	//Signal Incoming!!!
	void Update(const std::string& message_from_subject) override;

	//Override AnimationSprite2D
	void Update(float deltaTime) override;
	void Draw() override;
private:
	int m_input;
	//All hitbox
	std::shared_ptr<Area2D> m_areaPerfect;
	std::shared_ptr<Area2D> m_areaGood;
	std::shared_ptr<Area2D> m_areaOkay;
};

