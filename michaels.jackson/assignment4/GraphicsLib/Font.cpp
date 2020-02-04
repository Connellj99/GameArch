/*
Author:Jackson Michaels
Class: EGP-310-01
Assignment: Assignment 2
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/

#include "Font.h"
/*#################################
			Font
#################################*/

Font::Font(std::string fontName, int size) 
{
	mSize = size;
	mFont = al_load_ttf_font((ASSET_PATH + fontName).c_str(), size, 0);
	assert(mFont);
}

Font::~Font() 
{
	al_destroy_font(mFont);
}