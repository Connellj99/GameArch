#include "Font.h"

using namespace std;



Font::Font(string fontFilePath, int fontSize)
{
	mFontSize = fontSize;
	mCurrentFont = al_load_ttf_font(fontFilePath.c_str(), mFontSize, 0);
}


Font::~Font()
{
	al_destroy_font(mCurrentFont);
}

ALLEGRO_FONT* Font::getFont()
{
	return mCurrentFont;
}


int Font::getFontSize()
{
	return mFontSize;
}
