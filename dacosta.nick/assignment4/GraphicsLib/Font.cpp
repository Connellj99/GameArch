/*********************************************************************
**		Author:	Nick DaCosta										**
**		Class: 310 <Section 01>										**
**		Assignment: pa 4											**
**		Certification of Authenticity:								**
**		I certify that this assignment is entirely my own work.	    **
*********************************************************************/

#include <iostream>

#include "Trackable.h"

#include "FontFlags.h"

#include "Font.h"

// Load a font with a specified size from a file.
Font::Font(std::string _readPath, std::string _fileName, int _size)
{
	// Initialize the required components.
	initialize();

	// Store the size value.
	mSize = _size;

	// Load the font.
	mpFont = al_load_ttf_font((_readPath + _fileName).c_str(), mSize, 0);
	assert(mpFont);

	return;
}

// Clean up the font instance.
Font::~Font()
{
	al_destroy_font(mpFont);
	return;
}

// Initialize the required components.
void Font::initialize()
{

	// Initialize the Allegro font addon.
	if (!al_init_font_addon())
	{
		std::cout << "Error initializing the Allegro font addon!" << std::endl;
		return;
	}

	// Initialize the Allegro ttf addon.
	if (!al_init_ttf_addon())
	{
		std::cout << "Error initializing the Allegro ttf addon!" << std::endl;
		return;
	}

	return;
}

// Get the font size.
int Font::getSize()
{
	return mSize;
}