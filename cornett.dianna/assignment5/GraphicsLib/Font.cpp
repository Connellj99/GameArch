/*
Author: Amelia Payne
Class: EGP-310 <2>
Assignment: pa 3
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/

#include "Font.h"



Font::Font(std::string fileName, int fontSize)
{
	mpAllegroFont = al_load_ttf_font(fileName.c_str(), fontSize, 0);
	mFontSize = fontSize;
}

Font::~Font()
{
	al_destroy_font(mpAllegroFont);
	mpAllegroFont = NULL;
}

