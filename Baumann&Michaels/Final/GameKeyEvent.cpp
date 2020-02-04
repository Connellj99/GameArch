#include "GameKeyEvent.h"

GameKeyEvent::GameKeyEvent(const KeyType& kt)
	: Event(GAME_KEY_CHANGED), mbType(kt)
{
}

GameKeyEvent::~GameKeyEvent()
{
}