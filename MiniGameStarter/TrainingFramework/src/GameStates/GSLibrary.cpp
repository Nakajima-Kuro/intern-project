#include "GSLibrary.h"
#include "SongButton.h"
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

	//Init 3 button
	shader = ResourceManagers::GetInstance()->GetShader("AnimationShader");
	texture = ResourceManagers::GetInstance()->GetTexture("btn_song.tga");
	//Upper button
	auto button = std::make_shared<SongButton>(model, shader, texture);
	button->SetClickable(false);
	button->SetSize(650, 120);
	button->Set2DPosition(Globals::screenWidth / 2 + 100, Globals::screenHeight / 2 - 200);
	m_listButton.push_back(button);
	//Middle button
	button = std::make_shared<SongButton>(model, shader, texture, m_library[0]);
	button->SetSize(650, 120);
	button->Set2DPosition(Globals::screenWidth / 2 + 50, Globals::screenHeight / 2);
	m_listButton.push_back(button);
	//Lower button
	button = std::make_shared<SongButton>(model, shader, texture, m_library[1]);
	button->SetSize(650, 120);
	button->Set2DPosition(Globals::screenWidth / 2 + 100, Globals::screenHeight / 2 + 200);
	button->SetClickable(false);
	m_listButton.push_back(button);

	//Foreground for upper and lower button
	texture = ResourceManagers::GetInstance()->GetTexture("spr_foreground.tga");
	auto foreground = std::make_shared<Sprite2D>(-1, model, shader, texture);
	foreground->SetSize(650, 120);
	foreground->Set2DPosition(Globals::screenWidth / 2 + 100, Globals::screenHeight / 2 - 200);
	foreground->SetVisible(false);
	m_listForeground.push_back(foreground);

	foreground = std::make_shared<Sprite2D>(-1, model, shader, texture);
	foreground->SetSize(650, 120);
	foreground->Set2DPosition(Globals::screenWidth / 2 + 100, Globals::screenHeight / 2 + 200);
	m_listForeground.push_back(foreground);
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
	if (key == VK_RETURN) {
		//Choose current song
		auto song = m_listButton[1]->GetSong();
		SharedVariableManager::GetInstance()->songName = song->GetName();
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_PLAY);
	}
	if (key == VK_UP) {
		if (m_position > 0) {
			m_position--;
			UpdateButtonInfo();
		}
	}
	if (key == VK_DOWN) {
		if (m_position < int(m_library.size() - 1)) {
			m_position++;
			UpdateButtonInfo();
		}
	}
}

void GSLibrary::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	for (auto const& button : m_listButton) {
		button->HandleTouchEvents(x, y, bIsPressed);
	}
}

void GSLibrary::HandleMouseMoveEvents(int x, int y)
{
}

void GSLibrary::Update(float deltaTime)
{
}

void GSLibrary::Draw()
{
	m_background->Draw();
	for (auto const& button : m_listButton) {
		button->Draw();
	}
	for (auto const& foreground : m_listForeground) {
		foreground->Draw();
	}
}

void GSLibrary::UpdateButtonInfo()
{
	if (m_position > 0) {
		m_listButton[0]->SetSong(m_library[m_position - 1]);
		m_listForeground[0]->SetVisible(true);
	}
	else {
		m_listButton[0]->SetSong(nullptr);
		m_listForeground[0]->SetVisible(false);
	}
	m_listButton[1]->SetSong(m_library[m_position]);
	if (m_position < int(m_library.size() - 1)) {
		m_listButton[2]->SetSong(m_library[m_position + 1]);
		m_listForeground[1]->SetVisible(true);
	}
	else {
		m_listButton[2]->SetSong(nullptr);
		m_listForeground[1]->SetVisible(false);
	}
}
