#include "State.h"

void State::setContext(StateContext* context)
{
	m_context = context;
}

void State::clrscr()
{
	std::cout << "\033[2J\033[1;1H";
}
