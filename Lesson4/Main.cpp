#include<iostream>
#include"StateContext.h"
#include"OpenState.h"
#include <crtdbg.h>
int main() {
	{
		StateContext* context = new StateContext(new LockState);
		context->start();
		delete context;
	}
	_CrtDumpMemoryLeaks();
}