#pragma once
#ifndef KEY_EVENT_H
#define KEY_EVENT_H

#include "Event.h"

enum KeyType { INVALID_KEY_TYPE = -1, W_KEY, A_KEY, S_KEY, D_KEY, ENTER_KEY, F_KEY, ESCAPE_KEY, SPACE_KEY, NUM_KEY_TYPES };

class KeyEvent :public Event 
{
private:
	KeyType mbType;

public:


	KeyEvent(const KeyType& mb);
	~KeyEvent();

	KeyType getButtonType() const { return mbType; }
};

#endif