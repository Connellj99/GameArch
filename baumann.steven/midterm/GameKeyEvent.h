#pragma once
#ifndef GAME_KEY_EVENT_H
#define GAME_KEY_EVENT_H

#include "KeyEvent.h"

class GameKeyEvent :public Event 
{
private:
	KeyType mbType;

public:

	GameKeyEvent(const KeyType& mb);
	~GameKeyEvent();

	KeyType getButtonType() const { return mbType; }
};

#endif