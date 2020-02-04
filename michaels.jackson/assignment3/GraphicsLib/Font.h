/*
Author:Jackson Michaels
Class: EGP-310-01
Assignment: Assignment 2
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/
#pragma once
#include "Constants.h"
#include <PerformanceTracker.h>
#include <MemoryTracker.h>

#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

class Font : public Trackable 
{
	friend class GraphicsSystem;
private:
	ALLEGRO_FONT* mFont;
	ALLEGRO_FONT* getFont() { return mFont; };
	int mSize;
public:
	Font(std::string, int = 24);
	~Font();

	int getSize() { return mSize; };
};