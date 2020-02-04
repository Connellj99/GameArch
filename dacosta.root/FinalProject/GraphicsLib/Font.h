/*********************************************************************
**		Author:	Nick DaCosta										**
**		Class: 310 <Section 01>										**
**		Assignment: pa 5											**
**		Certification of Authenticity:								**
**		I certify that this assignment is entirely my own work.	    **
*********************************************************************/

#pragma once

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

class GraphicsSystem;

/// <summary>
///		A font.
/// </summary>
/// <seealso cref="Trackable" />
class Font :
	public Trackable
{
public:
	// Allow graphics system to access member items.
	friend GraphicsSystem;

	// Load a font with a specified size from a file.
	Font(std::string _readPath, std::string _fileName, int _size);

	// Clean up the font instance.
	~Font();

	// Initialize the required components.
	void initialize();

	// Get the font size.
	int getSize();

private:
	// Allegro font.
	ALLEGRO_FONT* mpFont;

	// Font size.
	int mSize = 0;
};