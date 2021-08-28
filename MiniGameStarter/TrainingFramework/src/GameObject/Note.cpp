#include "Note.h"
#include "ResourceManagers.h"
#include "AnimationSprite2D.h"

Note::Note()
	: Area2D("note"), m_spawnPosition(Vector2()), m_finishPosition(Vector2()), m_speed(0), m_bpm(0), m_difficulty(4)
{
	Init();
}

Note::Note(Vector2 spawnPosition, Vector2 finishPosition, float bpm, int difficulty)
	: Area2D("note"), m_spawnPosition(spawnPosition), m_finishPosition(finishPosition), m_speed(0), m_bpm(bpm), m_difficulty(difficulty)
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
	m_sprite = new AnimationSprite2D(model, shader, texture, 3, 0.0f);
	m_sprite->SetPlayAnimation(false);
	//Set Position
	Set2DPosition(m_spawnPosition);
	//Caculate speed
	m_speed = float(m_finishPosition.y - m_spawnPosition.y) / (60.0f / m_bpm * m_difficulty);
	Area2D::Init();
}

void Note::Update(float deltaTime)
{
	Set2DPosition(m_position.x, m_position.y + m_speed * deltaTime);
	Area2D::Update(deltaTime);
}

void Note::Draw()
{
	m_sprite->Draw();
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
	//m_sprite->SetVisible(false);
	if (strcmp(status.c_str(), "") != 0) {
		//Being destroy by ArrowButton
		//Emit Particles here
	}
}

void Note::Set2DPosition(Vector2 position)
{
	m_sprite->Set2DPosition(position);
	Area2D::Set2DPosition(position);
}

void Note::Set2DPosition(GLint x, GLint y)
{
	m_sprite->Set2DPosition(x, y);
	Area2D::Set2DPosition(x, y);
}
