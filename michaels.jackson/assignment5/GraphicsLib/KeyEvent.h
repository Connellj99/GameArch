/*
Author:Jackson Michaels
Class: EGP-310-01
Assignment: Assignment 5
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/
#pragma once

#include "Event.h"
#include "Constants.h"
#include <string>

using namespace std;

class KeyEvent : public Event
{
public:
	KeyEvent(KeyConvert key) : Event(KEYBOARD_EVENT) { mKey = key; }

	~KeyEvent() {}


	KeyConvert const getKey() const { return mKey; }

private:
	KeyConvert mKey;
};