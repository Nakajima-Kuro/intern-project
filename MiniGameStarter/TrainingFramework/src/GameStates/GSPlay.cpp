#include "GSPlay.h"
#include "Shader.h"
#include "Texture.h"
#include "Model.h"
#include "Camera.h"
#include "Font.h"
#include "Sprite2D.h"
#include "Sprite3D.h"
#include "Text.h"
#include "GameButton.h"

GSPlay::GSPlay()
{
	this->conductor = new Conductor(150, 4, "Myths You Forgot (feat. Toby Fox).wav");
}


GSPlay::~GSPlay()
{
	delete conductor;
}


void GSPlay::Init()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");

	// background
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg_play_1.tga");
	m_background = std::make_shared<Sprite2D>(model, shader, texture);
	m_background->Set2DPosition((GLint)Globals::screenWidth / 2, (GLint)Globals::screenHeight / 2);
	m_background->SetSize(Globals::screenWidth, Globals::screenHeight);

	// button close
	texture = ResourceManagers::GetInstance()->GetTexture("btn_back_symbol.tga");
	m_backButton = std::make_shared<GameButton>(model, shader, texture);
	m_backButton->Set2DPosition(Globals::screenWidth - 50, 50);
	m_backButton->SetSize(50, 50);
	m_backButton->SetOnClick([]() {
		GameStateMachine::GetInstance()->PopState();
		});

	//LeftArrow
	std::pair<std::shared_ptr<Texture>, std::shared_ptr<Texture>> texturePair
		= { ResourceManagers::GetInstance()->GetTexture("Arrow/Left/arrow_button_left_1.tga"), ResourceManagers::GetInstance()->GetTexture("Arrow/Left/arrow_button_left_2.tga") };
	auto button = std::make_shared<ArrowButton>(model, shader, texturePair, VK_LEFT);
	button->Set2DPosition(Globals::screenWidth / 2 - 120, m_arrowButtonY);
	button->SetSize(96, 96);
	m_listArrowButton.push_back(button);

	//UpArrow
	texturePair
		= { ResourceManagers::GetInstance()->GetTexture("Arrow/Up/arrow_button_up_1.tga"), ResourceManagers::GetInstance()->GetTexture("Arrow/Up/arrow_button_up_2.tga") };
	button = std::make_shared<ArrowButton>(model, shader, texturePair, VK_UP);
	button->Set2DPosition(Globals::screenWidth / 2, m_arrowButtonY);
	button->SetSize(96, 96);
	m_listArrowButton.push_back(button);

	//RightArrow
	texturePair
		= { ResourceManagers::GetInstance()->GetTexture("Arrow/Right/arrow_button_right_1.tga"), ResourceManagers::GetInstance()->GetTexture("Arrow/Right/arrow_button_right_2.tga") };
	button = std::make_shared<ArrowButton>(model, shader, texturePair, VK_RIGHT);
	button->Set2DPosition(Globals::screenWidth / 2 + 120, m_arrowButtonY);
	button->SetSize(96, 96);
	m_listArrowButton.push_back(button);

	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("HeartbitXX.ttf");
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	// score title
	m_scoreTitle = std::make_shared< Text>(shader, font, "Score:", TextColor::YELLOW, 2);
	m_scoreTitle->Set2DPosition(Vector2(20, 40));

	// score
	m_score = std::make_shared< Text>(shader, font, "0", TextColor::YELLOW, 2);
	m_score->Set2DPosition(Vector2(130, 40));

	// score title
	m_comboTitle = std::make_shared< Text>(shader, font, "Combo:", TextColor::YELLOW, 2);
	m_comboTitle->Set2DPosition(Vector2(20, 75));

	// score
	m_combo = std::make_shared< Text>(shader, font, "0", TextColor::YELLOW, 2);
	m_combo->Set2DPosition(Vector2(130, 75));

	this->conductor->Attach(this);
	this->conductor->PlayWithBeatOffset(2);
}

void GSPlay::Exit()
{
}


void GSPlay::Pause()
{
}

void GSPlay::Resume()
{
}


void GSPlay::HandleEvents()
{
}

void GSPlay::HandleKeyEvents(int key, bool bIsPressed)
{
	for (auto button : m_listArrowButton) {
		button->HandleKeyEvents(key, bIsPressed);
	}
}

void GSPlay::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	m_backButton->HandleTouchEvents(x, y, bIsPressed);
}

void GSPlay::HandleMouseMoveEvents(int x, int y)
{
}

void GSPlay::Update(float deltaTime)
{
	m_backButton->Update(deltaTime);
	for (auto it : m_listArrowButton)
	{
		it->Update(deltaTime);
	}
	conductor->Update(deltaTime);
}

void GSPlay::Draw()
{
	m_background->Draw();
	m_score->Draw();
	m_scoreTitle->Draw();
	m_combo->Draw();
	m_comboTitle->Draw();
	m_backButton->Draw();
	for (auto it : m_listArrowButton)
	{
		it->Draw();
	}
}

void GSPlay::Update(const std::string& message_from_subject)
{
	//Trigger every beat
	if (strcmp(message_from_subject.c_str(), "beat") == 0) {
		//std::cout << conductor->GetBeat();
	}
	//Trigger every beat in loop of measures
	if (strcmp(message_from_subject.c_str(), "measure") == 0) {
		//std::cout << conductor->GetMeasure();
	}
}
