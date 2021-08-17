#pragma once
#include<iostream>
#include "State.h"
#include "StateContext.h"
#include "CloseState.h"
class OpenState :
    public State
{
public:
    void start() override;
    void handleInput() override;
};

