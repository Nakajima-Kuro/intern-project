#include "LockState.h"

void LockState::start()
{
	clrscr();
	std::cout << " __________"<<std::endl
		<< "|  __  __  |" << std::endl
		<< "| |  ||  | |" << std::endl
		<< "| |  ||  | |" << std::endl
		<< "| |__||__| |" << std::endl
		<< "|  __  __ X|" << std::endl
		<< "| |  ||  | |" << std::endl
		<< "| |  ||  | |" << std::endl
		<< "| |  ||  | |" << std::endl
		<< "| |  ||  | |" << std::endl
		<< "| |__||__| |" << std::endl
		<< "|__________|" << std::endl
		<< "The door is locked tight. Would you like to:" << std::endl
		<< "1. Unlock the door." << std::endl;
	handleInput();

}

void LockState::handleInput()
{
	std::string input;
	while (true) {
		std::cin >> input;
		if (input.compare("1") == 0) {
			std::cout << "You unlocked the door.";
			m_context->changeState(new CloseState);
			break;
		}
		else {
			std::cout << "Wrong input.";
		}
	}
}
