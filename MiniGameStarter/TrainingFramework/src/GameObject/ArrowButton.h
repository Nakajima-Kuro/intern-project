#pragma once
#include "Sprite2D.h"
#include "Area2D.h"
#include "IObserver.h"
class ArrowButton :
	public Sprite2D, public IObserver
{
public:
	ArrowButton() : Sprite2D(), m_listTexture({ NULL, NULL }), m_input(-1) {}
	ArrowButton(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::pair<std::shared_ptr<Texture>, std::shared_ptr<Texture>> textureStatus, int input);
	std::pair<std::shared_ptr<Texture>, std::shared_ptr<Texture>> m_listTexture;
	int HandleKeyEvents(int key, bool bIsPressed);

	//Signal Incoming!!!
	void Update(const std::string& message_from_subject) override;
	void Update(float deltaTime);

	//Override Sprite2D
	void Draw() override;
private:
	int m_input;
	//All hitbox
	std::shared_ptr<Area2D> m_areaPerfect;
	std::shared_ptr<Area2D> m_areaGood;
	std::shared_ptr<Area2D> m_areaOkay;
};

