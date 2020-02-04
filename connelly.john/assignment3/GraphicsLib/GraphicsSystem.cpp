/*********************************************************************
**		Author:														**
**		Class: 310 <Section 0>										**
**		Assignment: pa 2											**
**		Certification of Authenticity:								**
**		I certify that this assignment is entirely my own work.	    **
**		Assingment 2 Author: Nick DaCosta							**
*********************************************************************/
#include "GraphicsSystem.h"

// Default constructor.
GraphicsSystem::GraphicsSystem()
{
	return;
}

// Destructor.
GraphicsSystem::~GraphicsSystem()
{
	// TODO: Call cleanup here.
	// NOTE: Not working because object doesn't go out of scope. Change object to a pointer?
	return;
}

// Initialize a display.
void GraphicsSystem::initialize(int _width, int _height)
{
	// Initialize Allegro.
	if (!al_init())
	{
		std::cout << "Error initializing Allegro!" << std::endl;
		return;
	}

	// Initialize Allegro ttf addon.
	if (!al_init_ttf_addon())
	{
		std::cout << "Error initializing Allegro ttf addon!" << std::endl;
		return;
	}

	// Initialize Allegro font addon.
	if (!al_init_font_addon())
	{
		std::cout << "Error initializing Allegro font addon!" << std::endl;
		return;
	}

	// Create a new display with the given dimensions.
	mpDisplay = al_create_display(_width, _height);
	assert(mpDisplay);

	return;
}

// TODO: Call from destructor.
// NOTE: Not working from destructor because object doesn't go out of scope. Change object to a pointer?
// Clean up the allegro display pointer.
void GraphicsSystem::cleanUp()
{
	// Destroy the Allegro display pointer.
	al_destroy_display(mpDisplay);
	
	return;
}

// Get the width of the display.
int GraphicsSystem::getWidth()
{
	return al_get_display_width(mpDisplay);
}

// Get the height of the display.
int GraphicsSystem::getHeight()
{
	return al_get_display_height(mpDisplay);
}

// Update the display.
void GraphicsSystem::updateDisplay()
{
	al_flip_display();
	return;
}

// Draw a sprite to the display.
void GraphicsSystem::draw(Sprite _sprite, float _destinationX, float _destinationY, float _scale)
{
	al_draw_bitmap_region(_sprite.getBuffer()->mpBitmap, _sprite.getSourceX(), _sprite.getSourceY(), _sprite.getWidth(), _sprite.getHeight(), _destinationX, _destinationY, 0);

	return;
}

// TODO: Include target buffer to draw to. Don't draw directly to back buffer.
// Draw a centered buffer in the taget buffer.
void GraphicsSystem::draw(GraphicsBuffer& _drawBuffer, float _scale)
{
	// Get the width of the buffer to draw.
	int drawBufferWidth = al_get_bitmap_width(_drawBuffer.mpBitmap);
	// Get the height of the buffer to draw.
	int drawBufferHeight = al_get_bitmap_height(_drawBuffer.mpBitmap);

	// Set the scaled width of the buffer to draw.
	float scaledWidth = drawBufferWidth * _scale;
	// Set the scaled height of the buffer to draw.
	float scaledHeight = drawBufferHeight * _scale;

	// Get the back buffer for calculations.
	ALLEGRO_BITMAP* pBackBuffer = al_get_target_bitmap();

	// Set the drawing x coordinate for horizontal centering.
	float destinationX = (al_get_bitmap_width(pBackBuffer) - scaledWidth) / 2;
	// Set the drawing y coordinate for vertical centering.
	float destinationY = (al_get_bitmap_height(pBackBuffer) - scaledHeight) / 2;

	// Draw a scaled bitmap to the back buffer.
	al_draw_scaled_bitmap(_drawBuffer.mpBitmap, 0, 0, drawBufferWidth, drawBufferHeight, destinationX, destinationY, scaledWidth, scaledHeight, 0);

	return;
}

// Write text to the current buffer.
void GraphicsSystem::writeText(float _destinationX, float _destinationY, Font& _font, Color _color, std::string _text)
{
	// Create an allegro color.
	ALLEGRO_COLOR drawColor = al_map_rgb(_color.getR(), _color.getG(), _color.getB());
	
	// TODO: Leaky abstraction. Don't get allegro font (getFont()).
	// Draw text to the current buffer.
	al_draw_text(_font.getFont(), drawColor, _destinationX, _destinationY, 0, _text.c_str());
	return;
}

// Write text to the given buffer.
void GraphicsSystem::writeText(GraphicsBuffer& _buffer, float _destinationX, float _destinationY, Font& _font, Color _color, std::string _text)
{
	// Store the current back buffer.
	ALLEGRO_BITMAP* pBackBuffer = al_get_target_bitmap();

	// Set the target drawing buffer.
	al_set_target_bitmap(_buffer.mpBitmap);

	ALLEGRO_COLOR drawColor = al_map_rgb(_color.getR(), _color.getG(), _color.getB());

	// Draw the text to the buffer.
	al_draw_text(_font.getFont(), drawColor, _destinationX, _destinationY, 0, _text.c_str());

	// Restore the back buffer.
	al_set_target_bitmap(pBackBuffer);

	return;
}

// Save a buffer.
void GraphicsSystem::saveBuffer(GraphicsBuffer& _buffer, std::string _fileName)
{
	al_save_bitmap(_fileName.c_str(), _buffer.mpBitmap);
	return;
}

// Get the back buffer.
GraphicsBuffer GraphicsSystem::getBackBuffer()
{
	return GraphicsBuffer(al_get_target_bitmap());
}
