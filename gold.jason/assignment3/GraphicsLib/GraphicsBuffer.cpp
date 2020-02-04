/*********************************************************************
**		Author:														**
**		Class: 310 <Section 0>										**
**		Assignment: pa 2											**
**		Certification of Authenticity:								**
**		I certify that this assignment is entirely my own work.	    **
**		Assingment 2 Author: Nick DaCosta							**
*********************************************************************/
#include "GraphicsBuffer.h"

// Basic buffer constructor.
GraphicsBuffer::GraphicsBuffer()
{
	// Initialize the required components.
	initialize();

	// This object owns the bitmap.
	mOwnsBitmap = true;

	return;
}

// Create a buffer from an allegro bitmap.
GraphicsBuffer::GraphicsBuffer(ALLEGRO_BITMAP* _pBitmap)
{
	mpBitmap = _pBitmap;
	return;
}

// Load a buffer from a file.
GraphicsBuffer::GraphicsBuffer(std::string _readPath, std::string _fileName)
{
	// Initialize the required components.
	initialize();

	// Load the bitmap from the file.
	mpBitmap = al_load_bitmap((_readPath + _fileName).c_str());
	assert(mpBitmap);

	// This object owns the bitmap.
	mOwnsBitmap = true;
	
	return;
}

// Create a buffer with a given dimension.
GraphicsBuffer::GraphicsBuffer(int _width, int _height)
{
	// Initialize the required components.
	initialize();

	// Create a bitmap with given dimensions.
	mpBitmap = al_create_bitmap(_width, _height);
	assert(mpBitmap);

	// This object owns the bitmap.
	mOwnsBitmap = true;

	return;
}

// Clean up the instance of the buffer.
GraphicsBuffer::~GraphicsBuffer()
{
	// Check if the pointer belongs to this object.
	// Not owned pointers will throw off the actual owner and break the code.
	if (mOwnsBitmap)
	{
		al_destroy_bitmap(mpBitmap);
	}

	return;
}

// Initialize the required components.
void GraphicsBuffer::initialize()
{
	// Initialize Allegro.
	if (!al_init())
	{
		std::cout << "Error initializing Allegro!" << std::endl;
		return;
	}

	// Initialize Allegro image addon.
	if (!al_init_image_addon())
	{
		std::cout << "Error initializing Allegro image addon!" << std::endl;
		return;
	}	

	return;
}

// Get the height of the buffer.
int GraphicsBuffer::getHeight()
{
	return al_get_bitmap_height(mpBitmap);
}

// Get the width of the buffer.
int GraphicsBuffer::getWidth()
{
	return al_get_bitmap_width(mpBitmap);
}
