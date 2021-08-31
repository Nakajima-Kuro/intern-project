#include "Note.h"
#include "ResourceManagers.h"
#include "AnimationSprite2D.h"
#include "Text.h"

Note::Note()
	: Area2D("note"), m_spawnPosition(Vector2()), m_finishPosition(Vector2()), m_speed(0), m_bpm(0), m_difficulty(4), m_isActive(false)
{
	Init();
}

Note::Note(Vector2 spawnPosition, Vector2 finishPosition, float bpm, int difficulty)
	: Area2D("note"), m_spawnPosition(spawnPosition), m_finishPosition(finishPosition), m_speed(0), m_bpm(bpm), m_difficulty(difficulty), m_isActive(false)
{
	Init();
}

Note::~Note()
{
	delete m_sprite;
}

void Note::Init()
{
	//Init 3 arrow sprite
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto shader = ResourceManagers::GetInstance()->GetShader("AnimationShader");
	auto texture = ResourceManagers::GetInstance()->GetTexture("Arrow/spr_note.tga");
	m_sprite = new AnimationSprite2D(model, shader, texture, 4, 0.0f);
	m_sprite->SetPlayAnimation(false);
	auto font = ResourceManagers::GetInstance()->GetFont("HeartbitXX.ttf");
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	m_text = new Text(shader, font, "", TextColor::YELLOW, 2);
	//Set Position
	Set2DPosition(m_spawnPosition);
	CalculateSpeed();
	Area2D::Init();
}

void Note::Update(float deltaTime)
{
	if (m_isActive) {
		Set2DPosition(m_position.x, m_position.y + m_speed * deltaTime);
		if (m_position.y > Globals::screenHeight + 96) {
			Destroy("");
		}
		m_text->Update(deltaTime);
		Area2D::Update(deltaTime);
	}
}

void Note::Draw()
{
	m_sprite->Draw();
	m_text->Draw();
	Area2D::Draw();
}

void Note::SetSize(GLint sizeX, GLint sizeY)
{
	m_sprite->SetSize(sizeX, sizeY);
	Area2D::SetSize(sizeX / 6, sizeY / 6);
}

void Note::SetLane(int lane)
{
	m_sprite->setFrame(lane);
}

void Note::Destroy(std::string status)
{
	if (status.compare("") == 0) {
		//Move offscreen, save resources for object pooling :))
		Set2DPosition(-100, -100);
		SetFinishPosition(-100, -100);
		m_text->SetText("");
		m_isActive = false;
	}
	else {
		//Being destroy by ArrowButton
		//Emit Particles here, or text or whatever effects
		m_sprite->setFrame(3);
		m_text->SetText(status);
		if (status.compare("Perfect") == 0) {
			m_text->SetColor(TextColor::YELLOW);
		}
		else if (status.compare("Good") == 0) {
			m_text->SetColor(TextColor::GREEN);
		}
		else if (status.compare("Okay") == 0) {
			m_text->SetColor(TextColor::RED);
		}
	}
}

void Note::Set2DPosition(Vector2 position)
{
	m_sprite->Set2DPosition(position);
	m_text->Set2DPosition(position.x - 40, position.y);
	Area2D::Set2DPosition(position);
	CalculateSpeed();
}

void Note::Set2DPosition(GLint x, GLint y)
{
	m_sprite->Set2DPosition(x, y);
	m_text->Set2DPosition(x - 40, y);
	Area2D::Set2DPosition(x, y);
	CalculateSpeed();
}

void Note::SetFinishPosition(Vector2 position)
{
	m_finishPosition = position;
	CalculateSpeed();
}

void Note::SetFinishPosition(GLint x, GLint y)
{
	m_finishPosition = Vector2(x, y);
	CalculateSpeed();
}

void Note::CalculateSpeed()
{
	//Caculate speed
	m_speed = float(m_finishPosition.y - m_spawnPosition.y) / (60.0f / m_bpm * m_difficulty);
}

void Note::SetActive(bool isActive)
{
	m_isActive = isActive;
}

bool Note::IsActive()
{
	return m_isActive;
}
