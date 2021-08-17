#include "Closed.h"

void Closed::lock(StateContext* context)
{
	context->changeState(new Locked());
}

void Closed::open(StateContext* context)
{
	context->changeState(new Opened());
}

void Closed::handleInput(StateContext* context, char* input)
{
	if (strcmp(input, "1") == 0) {
		std::cout << "You locked the door.";
		this->lock(context);
	}
	else if (strcmp(input, "2") == 0) {
		std::cout << "You open the door.";
		this->open(context);
	}
	else {
		std::cout << "Wrong input.";
	}
}

void Closed::logState()
{
	std::cout << "The door is closed. Would you like to:"<<std::endl
		<<"1. Lock the door."<<std::endl
		<<"2. Open the door."<<std::endl;
}
