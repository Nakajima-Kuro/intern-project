#include "GSPause.h"
#include "Camera.h"
#include "GameButton.h"

GSPause::GSPause() : 
	GameStateBase(StateType::STATE_PAUSE), m_background(nullptr), m_listButton(std::list<std::shared_ptr<GameButton>>{})
{
}


GSPause::~GSPause()
{
}



void GSPause::Init()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg_main_menu.tga");

	// background
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_background = std::make_shared<Sprite2D>(model, shader, texture);
	m_background->Set2DPosition(Globals::screenWidth / 2, Globals::screenHeight / 2);
	m_background->SetSize(Globals::screenWidth, Globals::screenHeight);

	// resume button
	texture = ResourceManagers::GetInstance()->GetTexture("btn_continue_symbol.tga");
	std::shared_ptr<GameButton> button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Globals::screenWidth / 2 - 200, Globals::screenHeight / 2);
	button->SetSize(100, 100);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->PopState();
		});
	m_listButton.push_back(button);

	// retry button
	texture = ResourceManagers::GetInstance()->GetTexture("btn_retry_symbol.tga");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Globals::screenWidth / 2, Globals::screenHeight / 2);
	button->SetSize(100, 100);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->PopAndReloadState();
		});
	m_listButton.push_back(button);

	// exit button
	texture = ResourceManagers::GetInstance()->GetTexture("btn_exit_symbol.tga");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Globals::screenWidth / 2 + 200, Globals::screenHeight / 2);
	button->SetSize(100, 100);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->PopBackToState(StateType::STATE_MENU);
		});
	m_listButton.push_back(button);

	// game pasue text
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("HeartbitXX.ttf");
	m_textTitle = std::make_shared< Text>(shader, font, "Pause", TextColor::YELLOW, 4, TextAlign::CENTER);
	m_textTitle->Set2DPosition(GLfloat(Globals::screenWidth / 2 - 80), 100);
}

void GSPause::Exit()
{
}


void GSPause::Pause()
{
}

void GSPause::Resume()
{
}


void GSPause::HandleEvents()
{
}

void GSPause::HandleKeyEvents(int key, bool bIsPressed)
{
}

void GSPause::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	for (auto button : m_listButton)
	{
		if (button->HandleTouchEvents(x, y, bIsPressed))
		{
			break;
		}
	}
}

void GSPause::HandleMouseMoveEvents(int x, int y)
{
}

void GSPause::Update(float deltaTime)
{
	m_background->Update(deltaTime);
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
}

void GSPause::Draw()
{
	m_background->Draw();
	for (auto it : m_listButton)
	{
		it->Draw();
	}
	m_textTitle->Draw();
}
