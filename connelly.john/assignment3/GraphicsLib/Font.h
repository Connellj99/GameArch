/*********************************************************************
**		Author:														**
**		Class: 310 <Section 0>										**
**		Assignment: pa 2											**
**		Certification of Authenticity:								**
**		I certify that this assignment is entirely my own work.	    **
**		Assingment 2 Author: Nick DaCosta							**
*********************************************************************/
#pragma once

// TODO: Remove allegro libraries when leaky abstraction is fixed.
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include <iostream>

#include "Trackable.h"

/// <summary>
/// 
/// </summary>
/// <seealso cref="PerformanceTracker" />
/// TODO Edit XML Comment Template for Font
class Font :
	public Trackable
{
public:
	// Load a font with a specified size from a file.
	Font(std::string _readPath, std::string _fileName, int _size);

	// Clean up the font instance.
	~Font();

	// Initialize the required components.
	void initialize();

	// Get the font size.
	int getSize();
	
	// TODO: Leaky abstraction. Don't return anything allegro.
	// Get the font.
	const ALLEGRO_FONT* getFont() const;

private:
	// Allegro font.
	ALLEGRO_FONT* mpFont;

	// Font size.
	int mSize = 0;
};