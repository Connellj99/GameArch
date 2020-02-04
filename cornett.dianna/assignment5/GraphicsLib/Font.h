/*
Author: Amelia Payne
Class: EGP-310 <2>
Assignment: pa 3
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/

#pragma once
#include <string>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>


#include <PerformanceTracker.h>
#include <MemoryTracker.h>
#include "Color.h"

/*
This class is a Font that can be drawen to the screen using graphics system
*/
class Font : public Trackable
{
private:
	ALLEGRO_FONT * mpAllegroFont;
	int mFontSize;

	ALLEGRO_FONT * getFont() 
	{ 
		return mpAllegroFont; 
	}

public:
	Font(std::string fileName, int fontSize);
	~Font();

	

	int getSize()
	{
		return mFontSize; 
	}

	friend class GraphicsSystem;
};