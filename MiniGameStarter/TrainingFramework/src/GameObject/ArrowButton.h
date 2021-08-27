#pragma once
#include "AnimationSprite2D.h"
#include "IObserver.h"

class Area2D;
class Note;

class ArrowButton :
	public AnimationSprite2D, public IObserver
{
public:
	ArrowButton();
	ArrowButton(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, int input);
	~ArrowButton();

	void Init();
	int HandleKeyEvents(int key, bool bIsPressed);

	//Check collision
	void checkCollision(std::list<std::shared_ptr<Area2D>> listArea2D);

	//Signal Incoming!!!
	void Update(const std::string& message_from_subject) override;

	//Override AnimationSprite2D
	void Update(float deltaTime) override;
	void Draw() override;
	void Set2DPosition(GLint x, GLint y);
	void Set2DPosition(Vector2 position);
private:
	int m_input;
	std::string m_status;
	std::shared_ptr<Note> m_currentNote;
	//All hitbox
	Area2D* m_areaPerfect;
	Area2D* m_areaGood;
	Area2D* m_areaOkay;
};

