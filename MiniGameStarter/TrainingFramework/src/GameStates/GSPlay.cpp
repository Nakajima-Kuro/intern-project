#include "GSPlay.h"
#include "Shader.h"
#include "Texture.h"
#include "Model.h"
#include "Camera.h"
#include "Font.h"
#include "Sprite2D.h"
#include "Area2D.h"
#include "Text.h"
#include "GameButton.h"
#include "ArrowButton.h"
#include "Note.h"
#include "NotePool.h"
#include "Song.h"
#include "Conductor.h"

GSPlay::GSPlay()
	:GameStateBase(StateType::STATE_PLAY), m_song(nullptr), m_conductor(nullptr), m_currentMapPosition(0), m_notePool(nullptr),
	m_score(0), m_perfect(0), m_good(0), m_okay(0), m_miss(0), m_combo(0), m_maxCombo(0)
{

}


GSPlay::~GSPlay()
{
	delete m_conductor;
	delete m_notePool;
	m_listNoteArea.clear();
	m_listArrowButton.clear();
}


void GSPlay::Init()
{
	//Reset score for new play session
	SharedVariableManager::GetInstance()->ResetScore();

	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");

	// background
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg_play_1.tga");
	m_background = std::make_shared<Sprite2D>(model, shader, texture);
	m_background->Set2DPosition((GLint)Globals::screenWidth / 2, (GLint)Globals::screenHeight / 2);
	m_background->SetSize(Globals::screenWidth, Globals::screenHeight);

	// button pause
	texture = ResourceManagers::GetInstance()->GetTexture("btn_pause_symbol.tga");
	m_backButton = std::make_shared<GameButton>(model, shader, texture);
	m_backButton->Set2DPosition(Globals::screenWidth - 50, 50);
	m_backButton->SetSize(50, 50);
	m_backButton->SetClickSfx("click");
	m_backButton->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_PAUSE);
		});

	//LeftArrow
	shader = ResourceManagers::GetInstance()->GetShader("AnimationShader");
	texture = ResourceManagers::GetInstance()->GetTexture("Arrow/spr_arrow_button_left.tga");
	auto button = std::make_shared<ArrowButton>("arrow", model, shader, texture, VK_LEFT);
	button->Set2DPosition(Globals::screenWidth / 2 - 120, m_arrowButtonY);
	button->SetSize(96, 96);
	button->Attach(this);
	m_listArrowButton.push_back(button);

	//UpArrow
	texture = ResourceManagers::GetInstance()->GetTexture("Arrow/spr_arrow_button_up.tga");
	button = std::make_shared<ArrowButton>("arrow", model, shader, texture, VK_UP);
	button->Set2DPosition(Globals::screenWidth / 2, m_arrowButtonY);
	button->SetSize(96, 96);
	button->Attach(this);
	m_listArrowButton.push_back(button);

	//RightArrow
	texture = ResourceManagers::GetInstance()->GetTexture("Arrow/spr_arrow_button_right.tga");
	button = std::make_shared<ArrowButton>("arrow", model, shader, texture, VK_RIGHT);
	button->Set2DPosition(Globals::screenWidth / 2 + 120, m_arrowButtonY);
	button->SetSize(96, 96);
	button->Attach(this);
	m_listArrowButton.push_back(button);

	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("HeartbitXX.ttf");
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	// score text
	m_textScore = std::make_shared<Text>(shader, font, "Score: 0", TextColor::YELLOW, 2);
	m_textScore->Set2DPosition(Vector2(20, 40));

	// combo text
	m_textCombo = std::make_shared<Text>(shader, font, "", TextColor::YELLOW, 3);
	m_textCombo->Set2DPosition(Globals::screenWidth - 220, Globals::screenHeight / 2 - 20);

	// combo value text
	m_textComboValue = std::make_shared<Text>(shader, font, "", TextColor::YELLOW, 3);
	m_textComboValue->Set2DPosition(Globals::screenWidth - 190, Globals::screenHeight / 2 + 30);

	//Get the song info
	m_song = ResourceManagers::GetInstance()->GetSong(SharedVariableManager::GetInstance()->songName);
	m_beatMap = m_song->GetBeatMap();

	//Init the conductor
	m_conductor = new Conductor(m_song->GetBpm(), m_song->GetMeasures(), m_song->GetPath() + ".wav");
	m_conductor->Attach(this);

	//Init the NotePool
	m_notePool = new NotePool(15, m_song->GetBpm(), m_song->GetDifficulty());
	for (auto const& i : m_notePool->GetListNote()) {
		m_listNoteArea.push_back(i);
	}

	//Play the song
	m_conductor->PlayWithBeatOffset(m_song->GetBeatOffset());
	/*m_conductor->PlayFromBeat(360, m_song->GetBeatOffset());
	getCurrentMapPosition(360);*/
}

void GSPlay::Exit()
{
	m_conductor->Detach(this);
}


void GSPlay::Pause()
{
	m_conductor->Pause();
}

void GSPlay::Resume()
{
	m_conductor->Resume();
}


void GSPlay::HandleEvents()
{
}

void GSPlay::HandleKeyEvents(int key, bool bIsPressed)
{
	if (bIsPressed) {
		if (key == VK_ESCAPE) {
			ResourceManagers::GetInstance()->GetSfx("click")->Play();
			GameStateMachine::GetInstance()->ChangeState(StateType::STATE_PAUSE);
		}
	}
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
		it->checkCollision(m_listNoteArea);
	}
	m_conductor->Update(deltaTime);
	m_notePool->Update(deltaTime);
}

void GSPlay::Draw()
{
	m_background->Draw();
	m_textScore->Draw();
	m_textCombo->Draw();
	m_textComboValue->Draw();
	m_backButton->Draw();
	for (auto const& it : m_listArrowButton)
	{
		it->Draw();
	}
	m_notePool->Draw();
}

void GSPlay::Update(const std::string& message_from_subject)
{
	//Trigger every beat
	if (message_from_subject.compare("beat") == 0) {
		//std::cout << "Beat: " << m_conductor->GetBeat() << " / Measure: " << m_conductor->GetMeasure() << std::endl;
		//If the next beat == the next beat in the map, advance counter by 1 to step to next phase in the map
		if (m_beatMap[m_currentMapPosition][0] == 0) {
			//check combo one last time
			if (m_combo > m_maxCombo) {
				m_maxCombo = m_combo;
			}
			//End game and transit to score screen here
			SharedVariableManager::GetInstance()->miss = m_miss;
			SharedVariableManager::GetInstance()->okay = m_okay;
			SharedVariableManager::GetInstance()->good = m_good;
			SharedVariableManager::GetInstance()->perfect = m_perfect;
			SharedVariableManager::GetInstance()->score = m_score;
			SharedVariableManager::GetInstance()->maxCombo = m_maxCombo;
			GameStateMachine::GetInstance()->ChangeState(StateType::STATE_SCORE);
		}
		else if (m_conductor->GetBeat() > m_beatMap[m_currentMapPosition][0] - 1) {
			m_currentMapPosition++;
		}

	}

	//Trigger every beat in loop of measures
	if (message_from_subject.compare("measure") == 0) {
		std::vector<int> spawnedPosition;
		int spawnPosition = rand() % 3; //Get random lane for not spawning (0, 1, 2)
		for (int i = 0; i < m_beatMap[m_currentMapPosition][m_conductor->GetMeasure()]; i++) {
			//Spawn the note base on the current number in the beat map
			while (std::find(spawnedPosition.begin(), spawnedPosition.end(), spawnPosition) != spawnedPosition.end()) {
				//Keep ramdoming until we got a free lane. Dont want 2 note spawned in one lane, huh? :))
				spawnPosition = rand() % 3;
			}
			spawnedPosition.push_back(spawnPosition);
			//Add the note to scene
			auto note = m_notePool->AcquireNote();
			note->SetLane(spawnPosition);
			note->Set2DPosition(GetSpawnPosition(spawnPosition));
			note->SetFinishPosition(m_listArrowButton[spawnPosition]->Get2DPosition());
			note->SetActive(true);
		}
	}
	if (message_from_subject.compare("arrow_perfect") == 0) {
		m_perfect++;
		IncreaseScore(300);
	}
	if (message_from_subject.compare("arrow_good") == 0) {
		m_good++;
		IncreaseScore(200);
	}
	if (message_from_subject.compare("arrow_okay") == 0) {
		m_okay++;
		IncreaseScore(100);
	}
	if (message_from_subject.compare("arrow_miss") == 0) {
		m_miss++;
		IncreaseScore(0);
	}
	if (message_from_subject.compare("arrow") == 0) {
		//Lose combo by pressing the note when it's not there
		if (m_score != 0) {
			IncreaseScore(0);
		}
	}
}

Vector2 GSPlay::GetSpawnPosition(int position)
{
	return Vector2(m_listArrowButton[position]->Get2DPosition().x, 30);
}

void GSPlay::IncreaseScore(int num)
{
	//Handle combo and TextCombo
	if (num == 0) {
		//Miss the note => lose combo
		if (m_maxCombo < m_combo) {
			m_maxCombo = m_combo;
		}
		m_combo = 0;
		m_textCombo->SetText("");
	}
	else {
		//Handle note being hit
		for (auto const& arrow : m_listArrowButton)
		{
			if (arrow->GetHandledNote() != nullptr) {
				auto note = std::static_pointer_cast<Note>(arrow->GetHandledNote());
				switch (num)
				{
				case 0: {
					note->Destroy("Miss");
					break;
				}
				case 100: {
					note->Destroy("Okay");
					break;
				}
				case 200: {
					note->Destroy("Good");
					break;
				}
				case 300: {
					note->Destroy("Perfect");
					break;
				}
				}
			}
		}
		//Increase combo
		m_combo++;
		//Handle the score and TextScore
		m_score += num + (num * (m_combo - 1)) / 25;
		m_textScore->SetText("Score: " + std::to_string(m_score));
		if (m_combo >= 10) {
			m_textCombo->SetText("Combo");
			m_textComboValue->SetText(std::to_string(m_combo));
		}
	}
}

void GSPlay::getCurrentMapPosition(int beat)
{
	for (std::vector<std::vector<int>>::size_type i = 0; i != m_beatMap.size() - 1; i++) {
		if (m_beatMap[i][0] <= beat && m_beatMap[i + 1][0] > beat) {
			m_currentMapPosition = i + 1;
			break;
		}
	}
}


