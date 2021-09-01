#include "GSLibrary.h"

GSLibrary::GSLibrary()
	: GameStateBase(StateType::STATE_LIBRARY), m_position(0)
{
}

GSLibrary::~GSLibrary()
{
}

void GSLibrary::Init()
{
	//Load the library
	m_library = ResourceManagers::GetInstance()->GetLibrary();
	

	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");

	// background
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg_main_menu.tga");
	m_background = std::make_shared<Sprite2D>(model, shader, texture);
	m_background->Set2DPosition((GLint)Globals::screenWidth / 2, (GLint)Globals::screenHeight / 2);
	m_background->SetSize(Globals::screenWidth, Globals::screenHeight);


}

void GSLibrary::Exit()
{
}

void GSLibrary::Pause()
{
}

void GSLibrary::Resume()
{
}

void GSLibrary::HandleEvents()
{
}

void GSLibrary::HandleKeyEvents(int key, bool bIsPressed)
{
}

void GSLibrary::HandleTouchEvents(int x, int y, bool bIsPressed)
{
}

void GSLibrary::HandleMouseMoveEvents(int x, int y)
{
}

void GSLibrary::Update(float deltaTime)
{
}

void GSLibrary::Draw()
{
}
