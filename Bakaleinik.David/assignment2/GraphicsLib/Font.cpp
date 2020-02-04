#include "Font.h"


Font ::~Font()
{
	al_destroy_font(cour_font);
	
}

Font::Font(string path, string fontName, int fontSize)
{
	
	mFontName = fontName;
	mFontSize = fontSize;
	cour_font = al_load_ttf_font((path + mFontName).c_str(), mFontSize, 0);
}

Font::Font()
{

}

int Font::getFontSize()
{
	return mFontSize;
}