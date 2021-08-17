#include "Locked.h"

void Locked::unlock(StateContext* context)
{
	context->changeState(new Closed());
}

void Locked::handleInput(StateContext* context, char* input)
{
	if (strcmp(input, "1") == 0) {
		std::cout << "You unlocked the door.";
		this->unlock(context);
	}
	else {
		std::cout << "Wrong input.";
	}
}

void Locked::logState()
{
	std::cout << "The door is locked tight. Would you like to:"<<std::endl
		<<"1. Unlock the door.";
}
