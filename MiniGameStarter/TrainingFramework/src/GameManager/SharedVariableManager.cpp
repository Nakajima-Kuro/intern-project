#include "SharedVariableManager.h"

SharedVariableManager::SharedVariableManager()
	:score(0), perfect(0), good(0), okay(0), maxCombo(0)
{
}

SharedVariableManager::~SharedVariableManager()
{
}

void SharedVariableManager::ResetScore()
{
	score = 0;
	perfect = 0;
	good = 0;
	okay = 0;
	maxCombo = 0;
}
