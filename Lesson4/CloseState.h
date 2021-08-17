#pragma once
#include<iostream>
#include "State.h"
#include "StateContext.h"
#include "OpenState.h"
#include "LockState.h"
class CloseState :
    public State
{
    void start() override;
    void handleInput() override;
};

