/*
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
	bool inited = false;

	ALLEGRO_FONT* getFont();

public:
	// Constructor
	Font();

	// Init / Cleanup
	void init(string, int);
	void cleanup();

	// Accessors
	int getSize();

	// Destructor
	~Font();
};