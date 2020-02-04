/*
Author: Grady Mayo
Class: EGP-310 <Section 01>
Assignment: Assignment 3
Certification of Authenticity: I certify that this assignment is entirely my own work.
*/

#include "Font.h"

Font::Font( int size, string filename )
{
	this->mFontSize = size;
	mpFont = al_load_ttf_font( filename.c_str(), size, 0 );
}

Font::~Font()
{
	al_destroy_font(mpFont);
	mpFont = NULL;
}
