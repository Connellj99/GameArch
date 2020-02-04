#include "Font.h"

//Font Functions -------------------------------------------------------------------------------------/

Font::Font()
{
	//sets the member size to the constant FONT_SIZE
	mFontSize = FONT_SIZE;
}

Font::~Font()
{
	//stub
}

//returns the fontsize
float Font::getSize()
{
	return mFontSize;
}

//Loads to the mFont pointer the ccorrect font with size and flags
Font Font::loadText()
{
	mFont = al_load_font((ASSET_PATH + FONT_FILENAME).c_str(), mFontSize, 0);

	return Font();
}
