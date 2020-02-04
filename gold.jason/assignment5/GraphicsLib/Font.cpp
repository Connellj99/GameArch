#include "Font.h"

Font::Font(std::string fontFileName, int fontSize)
{
	mFontFile = fontFileName;
	mFontSize = fontSize;
	mFont = al_load_ttf_font(mFontFile.c_str(), mFontSize, 0);
}

Font::~Font()
{
	al_destroy_font(mFont);
	mFont = NULL;
}