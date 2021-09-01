#pragma once
#include "GameManager/Singleton.h"
#include "GameConfig.h"
class SharedVariableManager
	: public CSingleton<SharedVariableManager>
{
public:
	SharedVariableManager();
	~SharedVariableManager();
	void ResetScore();
	//Handle all the score and combo
	unsigned int score;
	int perfect;
	int good;
	int okay;
	int maxCombo;
	//Song name to load
	std::string songName = "";
};

