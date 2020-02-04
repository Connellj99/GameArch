/*
Conner Root
EGP 310-01
*/

#include "Font.h"

// Constructor
Font::Font()
{
	mpFont = nullptr;
}
Font::Font(string path, int size)
{
	mFontSize = size;
	mpFont = al_load_ttf_font(path.c_str(), size, NULL);
	assert(mpFont);
}

// Accessors
int Font::getSize()
{
	return mFontSize;
}

ALLEGRO_FONT* Font::getFont()
{
	return mpFont;
}

// Destructor
Font::~Font()
{
	al_destroy_font(mpFont);
	mpFont = nullptr;
}