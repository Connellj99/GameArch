/*********************************************************************
**		Author:	Nick DaCosta										**
**		Class: 310 <Section 01>										**
**		Assignment: pa 3											**
**		Certification of Authenticity:								**
**		I certify that this assignment is entirely my own work.	    **
*********************************************************************/

#pragma once

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

/// <summary>
///		Holds a chunk of memory to display something.
/// </summary>
/// <seealso cref="Trackable" />
class GraphicsBuffer : 
	public Trackable
{
public:
	// Basic buffer constructor.
	GraphicsBuffer();

	// Constructor taking in an allegro bitmap.
	GraphicsBuffer(ALLEGRO_BITMAP* _pBitmap);

	// Load a buffer from a file.
	GraphicsBuffer(std::string _readPath, std::string fileName);
	
	// Create a buffer with a given dimension.
	GraphicsBuffer(int _width, int _height);

	// Clean up the instance of the buffer.
	~GraphicsBuffer();

	// Initialize the required components.
	void initialize();

	// Get the height of the buffer.
	int getHeight();

	// Get the width of the buffer.
	int getWidth();

	// Allow GraphicsSystem to use private members.
	friend class GraphicsSystem;

private:
	// Allegro bitmap.
	ALLEGRO_BITMAP* mpBitmap = nullptr;

	// Does this object own the bitmap.
	bool mOwnsBitmap = false;

	// TODO: Invalidate copy constructor and assignment operator=
};