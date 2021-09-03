#include "ArrowButton.h"
#include "Area2D.h"

ArrowButton::ArrowButton()
	: AnimationSprite2D(), m_name(""), m_input(-1), m_currentNote(nullptr), m_isInputHandled(false), m_isCurrentNoteHandled(false)
{
	Init();
};

ArrowButton::ArrowButton(std::string name, std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, int input)
	: AnimationSprite2D(model, shader, texture, 2, 0.0f), m_name(name), m_input(input), m_currentNote(nullptr), m_isInputHandled(false), m_isCurrentNoteHandled(false)
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
	m_areaPerfect->SetSize(16, 8);

	m_areaGood = new Area2D("good");
	m_areaGood->SetSize(16, 24);

	m_areaOkay = new Area2D("okay");
	m_areaOkay->SetSize(16, 48);

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
			if (!m_isInputHandled) {
				m_isInputHandled = true;//Make sure input only being handle once
				if (!m_isCurrentNoteHandled && m_currentNote != nullptr) {
					m_isCurrentNoteHandled = true;
					//Emit Signal, Hail Godot!!!
					Notify(m_name + m_status);
				}
				else {
					//Lose combo by pressing when a note is not there
					Notify(m_name);
				}
			}
		}
		else
		{
			m_isInputHandled = false;
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
	if (message_from_subject.compare("perfect_area_enter") == 0) {
		m_status = "_perfect";
	}
	if (message_from_subject.compare("perfect_area_exit") == 0) {
		m_status = "_good";
	}
	if (message_from_subject.compare("good_area_enter") == 0) {
		m_status = "_good";
	}
	if (message_from_subject.compare("good_area_exit") == 0) {
		m_status = "_okay";
	}
	if (message_from_subject.compare("okay_area_enter") == 0) {
		m_status = "_okay";
		m_currentNote = m_areaOkay->GetCollidedArea();
		m_isCurrentNoteHandled = false;
	}
	if (message_from_subject.compare("okay_area_exit") == 0) {
		m_currentNote.reset();
		if (!m_isCurrentNoteHandled) {
			//Miss the note
			m_status = "_miss";
			Notify(m_name + m_status);
		}
		m_status = "";
	}
}

std::shared_ptr<Area2D> ArrowButton::GetHandledNote()
{
	if (m_isInputHandled && m_currentNote != nullptr) {
		return m_currentNote;
	}
	return nullptr;
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
	m_areaOkay->Draw();
	m_areaGood->Draw();
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
