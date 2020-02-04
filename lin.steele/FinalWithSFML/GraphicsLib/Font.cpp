#include "Font.h"



// This functions is the default constructor
Font::Font() 
{
	// Initialize everything to default values
	mFontSize = 0;
	mFilePath = "";
	//mCurrentFont = NULL;
}





// This constructor takes in the font file path and the file size
Font::Font( string fontFilePath, int fontSize ) 
{

	mFontSize = fontSize;
	mFilePath = fontFilePath;
	//mCurrentFont = al_load_ttf_font(fontFilePath.c_str(), mFontSize, 0);
}





// This constructor takes in the font file
Font::Font( string fontFilePath ) 
{
	mFontSize = 0;
	mFilePath = fontFilePath;
	//mCurrentFont = al_load_ttf_font(fontFilePath.c_str(), mFontSize, 0);
}





// This is the destructor
Font::~Font()
{
	//al_destroy_font(mCurrentFont);	
}





// This function gets the size member variable
int Font::getSize() 
{
	return mFontSize;
}





// This function changes the font size and loads the new version of the font
void Font::setSize(int newSize) 
{
	mFontSize = newSize;
	//mCurrentFont = al_load_ttf_font(mFilePath.c_str(), mFontSize, 0);
}