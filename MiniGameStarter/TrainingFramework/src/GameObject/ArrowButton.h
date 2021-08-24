#pragma once
#include "Sprite2D.h"
class ArrowButton :
    public Sprite2D
{
public:
    ArrowButton() : Sprite2D() {}
    std::list<std::shared_ptr<Sprite2D>>m_listButtonSprite;
    int input;
    int handle_input(int key);
private:
    
};

