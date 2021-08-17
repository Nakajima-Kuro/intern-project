#include "CloseState.h"

void CloseState::start()
{
	clrscr();
	std::cout << " __________" << std::endl
		<< "|  __  __  |" << std::endl
		<< "| |  ||  | |" << std::endl
		<< "| |  ||  | |" << std::endl
		<< "| |__||__| |" << std::endl
		<< "|  __  __()|" << std::endl
		<< "| |  ||  | |" << std::endl
		<< "| |  ||  | |" << std::endl
		<< "| |  ||  | |" << std::endl
		<< "| |  ||  | |" << std::endl
		<< "| |__||__| |" << std::endl
		<< "|__________|" << std::endl
		<< "The door is unlocked but still closed. Would you like to:" << std::endl
		<< "1. Lock the door." << std::endl
		<< "2. Open the door." << std::endl;
	handleInput();
}

void CloseState::handleInput()
{
	std::string input;
	while (true) {
		std::cin >> input;
		if (input.compare("1") == 0) {
			std::cout << "You locked the door.";
			m_context->changeState(new LockState);
			break;
		}
		else if (input.compare("2") == 0) {
			std::cout << "You open the door.";
			m_context->changeState(new OpenState);
			break;
		}
		else {
			std::cout << "Wrong input.";
		}
	}
	
}
