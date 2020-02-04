#include "Font.h"


//default constructor
Font::Font()
{
	mpFont = NULL;
	mFontSize = 0;
}

//constructor for font
Font::Font(std::string &fileName, int fontSize) 
{
	mpFont = al_load_ttf_font(fileName.c_str(), fontSize, 0);

	mFontSize = fontSize;
}

//destructor for font
Font::~Font()
{
	al_destroy_font(mpFont);
	mpFont = NULL;
}

//accessor function
int Font::getSize() 
{
	return mFontSize;
}

ALLEGRO_FONT* Font::getFont() 
{
	return mpFont;
}
