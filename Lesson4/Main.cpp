#include<iostream>
#include"StateContext.h"
#include"OpenState.h"
int main() {
	{
		StateContext* context = new StateContext(new LockState);
		context->start();
		delete context;
	}
}