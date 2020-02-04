#include "Font.h"

Font::Font()
{
	al_init_font_addon();
	al_init_ttf_addon();


	setFontFile("Assets/cour.ttf");
	setFontSize(16);
	mFont = al_load_ttf_font(mFontFile.c_str(), mFontSize, 0);
}



Font::Font(std::string fontFileName, int fontSize)
{
	al_init_font_addon();
	al_init_ttf_addon();

	mFontFile = fontFileName;
	mFontSize = fontSize;
	mFont = al_load_ttf_font(mFontFile.c_str(), mFontSize, 0);
}

Font::Font(int fontSize)
{
	al_init_font_addon();
	al_init_ttf_addon();

	mFontSize = fontSize;
	mFontFile = "Assets\\cour.ttf";
	mFont = al_load_ttf_font(mFontFile.c_str(), mFontSize, 0);
}

Font::~Font()
{
	al_destroy_font(mFont);
	mFont = NULL;
}

void Font::setFontFile(std::string fileName)
{
	mFontFile = fileName.c_str();
}

void Font::setFontSize(int size)
{
	mFontSize = size;
}
