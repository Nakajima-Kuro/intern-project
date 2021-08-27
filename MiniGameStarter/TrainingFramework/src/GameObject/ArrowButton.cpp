#include "ArrowButton.h"
#include "Area2D.h"

ArrowButton::ArrowButton() 
	: AnimationSprite2D(), m_input(-1), m_areaPerfect(nullptr), m_areaGood(nullptr), m_areaOkay(nullptr)
{
	Init();
};

ArrowButton::ArrowButton(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, int input)
	: AnimationSprite2D(model, shader, texture, 2, 0.0f), m_input(input)
{
	Init();
}

ArrowButton::~ArrowButton()
{
	delete m_areaPerfect;
	delete m_areaGood;
	delete m_areaOkay;
}

void ArrowButton::Init() 
{
	//Set animation playing to false
	this->SetPlayAnimation(false);

	//Setup all area2D for score
	m_areaPerfect = new Area2D("perfect");
	m_areaPerfect->SetSize(16, 16);

	m_areaGood = new Area2D("good");
	m_areaPerfect->SetSize(16, 32);

	m_areaOkay = new Area2D("okay");
	m_areaPerfect->SetSize(16, 48);

	//Asign signal, hail Godot!!!
	m_areaPerfect->Attach(this);
	m_areaGood->Attach(this);
	m_areaOkay->Attach(this);
}

int ArrowButton::HandleKeyEvents(int key, bool bIsPressed)
{
	if (key == m_input) {
		if (bIsPressed)
		{
			// The button is being pressed down
			this->setFrame(1);
		}
		else
		{
			this->setFrame(0);
		}
	}
	return 0;
}

void ArrowButton::checkCollision(std::list<std::shared_ptr<Area2D>> listArea2D)
{
	m_areaOkay->checkCollision(listArea2D);
	m_areaGood->checkCollision(listArea2D);
	m_areaPerfect->checkCollision(listArea2D);
}

void ArrowButton::Update(const std::string& message_from_subject)
{
	//Handle all 6 message here
	if (strcmp(message_from_subject.c_str(), "perfect_area_enter") == 0) {
		m_status = "perfect";
	}
	if (strcmp(message_from_subject.c_str(), "perfect_area_exit") == 0) {
		m_status = "good";
	}
	if (strcmp(message_from_subject.c_str(), "good_area_enter") == 0) {
		m_status = "good";
	}
	if (strcmp(message_from_subject.c_str(), "good_area_exit") == 0) {
		m_status = "okay";
	}
	if (strcmp(message_from_subject.c_str(), "okay_area_enter") == 0) {
		m_status = "okay";
	}
	if (strcmp(message_from_subject.c_str(), "okay_area_exit") == 0) {
		m_status = "";
	}
}

void ArrowButton::Update(float deltaTime)
{
	m_areaPerfect->Update(deltaTime);
	m_areaGood->Update(deltaTime);
	m_areaOkay->Update(deltaTime);
	AnimationSprite2D::Update(deltaTime);
}

void ArrowButton::Draw()
{
	AnimationSprite2D::Draw();
	m_areaGood->Draw();
	m_areaOkay->Draw();
	m_areaPerfect->Draw();
}

void ArrowButton::Set2DPosition(GLint x, GLint y)
{
	AnimationSprite2D::Set2DPosition(x, y);
	m_areaPerfect->Set2DPosition(x, y);
	m_areaGood->Set2DPosition(x, y);
	m_areaOkay->Set2DPosition(x, y);
}

void ArrowButton::Set2DPosition(Vector2 position)
{
	AnimationSprite2D::Set2DPosition(position);
	m_areaPerfect->Set2DPosition(position);
	m_areaGood->Set2DPosition(position);
	m_areaOkay->Set2DPosition(position);
}
