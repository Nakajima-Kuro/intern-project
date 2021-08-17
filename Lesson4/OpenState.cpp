#include "OpenState.h"

void OpenState::start()
{
	clrscr();
	std::cout << "   /|" << std::endl
		<< "  / |" << std::endl
		<< " /__|______" << std::endl
		<< "|  __  __  |" << std::endl
		<< "| |  ||  | |" << std::endl
		<< "| |  ||  | |                              ____" << std::endl
		<< "| |__||__| |                             /  __|" << std::endl
		<< "|  __  __()|                                ) )" << std::endl
		<< "| |  ||  | +`                                ||" << std::endl
		<< "| |  ||  | |                            O    ||" << std::endl
		<< "| |  ||  | |                          ==||   ||" << std::endl
		<< "| |__||__| |                            //   ||" << std::endl
		<< "|__________|                           _\\    ||" << std::endl
		<< "The door is opened. " << std::endl 
		<< "The street outside is empty except one guy who stand right under the post lamp and staring at you..." << std::endl
		<< "Would you like to:" << std::endl
		<< "1. Close the door." << std::endl
		<< "2. Say hello to the man." << std::endl;
	handleInput();
}

void OpenState::handleInput()
{
	std::string input;
	while (true) {
		std::cin >> input;
		if (input.compare("1") == 0) {
			std::cout << "You closed the door.";
			m_context->changeState(new CloseState);
		}
		else if (input.compare("2") == 0) {
			clrscr();
			std::cout << "  ,-------------." << std::endl
				<< " /               )  " << std::endl
				<< "(    Thank you!  ) " << std::endl
				<< " |               /  ,-." << std::endl
				<< "  `------------+/ /___|" << std::endl
				<< "                | |o,o|   ,S" << std::endl
				<< "                 ,-|-/-. / '" << std::endl
				<< "                / ,   . V /" << std::endl
				<< "You went to the man and said hi to him. Turned out he just dropped his glasses and couldn't see anything." << std::endl
				<< "You helped him looking for his glasses and after that he thanked you and walk away." << std::endl
				<< "The end." << std::endl;
			break;
		}
		else {
			std::cout << "Wrong input.";
		}
	}
}
