/*
Author:Jackson Michaels
Class: EGP-310-01
Assignment: Assignment 5
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/
#pragma once

#include "Event.h"
#include <string>

using namespace std;

class MouseEvent : public Event
{
public:
	MouseEvent(MouseState state = MouseState()) : Event(MOUSEIN_EVENT) { mState = state; }
	
	~MouseEvent() {}

	 MouseState const getState() const { return mState; }

private:
	MouseState mState;
};