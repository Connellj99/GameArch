#include "Font.h"

Font::Font(int size, string file, const string assetPath)
{
	mSize = size;
	mFont = al_load_ttf_font((assetPath + file).c_str(), size, 0);
	assert(mpFont);
}

//used to clean up memory leaks
Font::~Font()
{
	al_destroy_font(mFont);
	mFont = NULL;
}