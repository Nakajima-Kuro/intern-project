#pragma once
#include<iostream>
#include "StateContext.h"
#include "State.h"

class Locked :
    public State
{
public:
    void unlock(StateContext* context) override;
    void handleInput(StateContext* context, char* input) override;
    void logState() override;
};

class Closed;