﻿/*
Conner Root
EGP 310-01
*/

#pragma once

#include "GraphicsLib.h"

class Font : public Trackable
{
	friend class GraphicsSystem;

private:
	ALLEGRO_FONT* mpFont;
	int mFontSize;
	
	ALLEGRO_FONT* getFont();

public:
	// Constructor
	Font();
	Font(string, int);

	// Accessors
	int getSize();

	// Destructor
	~Font();
};