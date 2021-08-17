#pragma once
#include<iostream>
#include "State.h"
#include "StateContext.h"
#include "CloseState.h"
class LockState :
    public State
{
    void start() override;
    void handleInput() override;
};

