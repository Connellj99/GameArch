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

// Init / Cleanup
void Font::init(string path, int size)
{
	if (!inited)
	{
		mFontSize = size;
		mpFont = al_load_ttf_font(path.c_str(), size, NULL);
		inited = false;
	}
}

void Font::cleanup()
{
	if (inited)
	{
		al_destroy_font(mpFont);
		mpFont = nullptr;
		inited = false;
	}
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
	cleanup();
}