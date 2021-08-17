#include "Opened.h"

void Opened::close(StateContext* context)
{
	context->changeState(new Opened);
}

void Opened::handleInput(StateContext* context, char* input)
{
	if (strcmp(input, "1") == 0) {
		std::cout << "You closed the door.";
		this->close(context);
	}
	else if (strcmp(input, "2") == 0) {
		std::cout << "You go to the man and said hi to him. Turned out he just dropped his glass and couldn't see anything."<<std::endl
			<<"You helped him looking for his glass and after that he thanked you and walk away."<<std::endl
			<<"The end.";
		context->end();
	}
	else {
		std::cout << "Wrong input.";
	}
}

void Opened::logState()
{
	std::cout << "The door is opened. The street outside is empty except one guy who stand right under the post lamp and staring at you..." << std::endl
		<< "Would you like to:" << std::endl
		<< "1. Close the door." << std::endl
		<< "2. Say hello to the man." << std::endl;
}
