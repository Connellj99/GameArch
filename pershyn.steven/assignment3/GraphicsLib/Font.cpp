/*
Author: Steven Pershyn
Class: EGP-310-01
Assignment: Assignment 3
Certification of Authenticity: I certify that this assignment is my own work, except where I referenced classmates' work and mentioned where relevant.
*/
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
