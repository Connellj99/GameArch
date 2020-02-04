#pragma once

#include "GraphicsLib.h"

class Font : public Trackable
{
private:
	ALLEGRO_FONT *mFont;
	int fontSize;

public:

	//getters
	int getSize();
	ALLEGRO_FONT* getFont();

	//contructors
	Font();
	Font(string, int);

	//destructor
	//~Font();
};