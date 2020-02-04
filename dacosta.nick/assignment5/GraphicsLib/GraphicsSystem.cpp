/*********************************************************************
**		Author:	Nick DaCosta										**
**		Class: 310 <Section 01>										**
**		Assignment: pa 5											**
**		Certification of Authenticity:								**
**		I certify that this assignment is entirely my own work.	    **
*********************************************************************/

#include <iostream>

#include "Trackable.h"

#include "BufferFlags.h"
#include "FontFlags.h"

#include "Color.h"
#include "Font.h"
#include "GraphicsBuffer.h"
#include "Sprite.h"
#include "GraphicsSystem.h"

// Default constructor.
GraphicsSystem::GraphicsSystem()
{
	return;
}

// Destructor.
GraphicsSystem::~GraphicsSystem()
{
	// Clean up the system.
	cleanUp();
	return;
}

// Initialize a display.
void GraphicsSystem::initialize(int _width, int _height)
{
	// Check for prior initialization.
	if (!mIsInitialized)
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

		// We have just initialized.
		mIsInitialized = true;
	}
	else
	{
		// Clean the old display.
		cleanUp();
	}

	// Create a new display with the given dimensions.
	mpDisplay = al_create_display(_width, _height);
	assert(mpDisplay);

	return;
}

// Clean up the object.
void GraphicsSystem::cleanUp()
{
	// Check for null pointer before double cleanup.
	if (mpDisplay != nullptr)
	{
		// Destroy the Allegro display pointer.
		al_destroy_display(mpDisplay);
	}

	// Set the display to null to free up memory.
	mpDisplay = nullptr;
	
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
void GraphicsSystem::update()
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

// Draw a buffer to a target buffer.
void GraphicsSystem::draw(GraphicsBuffer& _drawBuffer, GraphicsBuffer& _targetBuffer, int _flag /*  BUFFER_TOP_LEFT*/, float _scale /* = 1.0f*/)
{
	// Store the back buffer temporarily.
	ALLEGRO_BITMAP* pBackBuffer = al_get_target_bitmap();

	// Set the target buffer as the current buffer.
	al_set_target_bitmap(_targetBuffer.mpBitmap);

	// Get the width of the buffer to draw.
	int drawBufferWidth = _drawBuffer.getWidth();
	// Get the height of the buffer to draw.
	int drawBufferHeight = _drawBuffer.getHeight();

	// Set the scaled width of the buffer to draw.
	float scaledWidth = drawBufferWidth * _scale;
	// Set the scaled height of the buffer to draw.
	float scaledHeight = drawBufferHeight * _scale;

	// Draw location of the x position.
	float destinationX = 0.0f;
	// Draw location of the y position.
	float destinationY = 0.0f;

	// Set the x and y draw position based on the flag.
	setDrawPosition(destinationX, destinationY, scaledWidth, scaledHeight, _flag);

	// Draw a scaled bitmap to the target buffer.
	al_draw_scaled_bitmap(_drawBuffer.mpBitmap, 0.0f, 0.0f, drawBufferWidth, drawBufferHeight, destinationX, destinationY, scaledWidth, scaledHeight, 0);

	// Reset the back buffer.
	al_set_target_bitmap(pBackBuffer);

	return;
}

// Draw directly to the back buffer.
void GraphicsSystem::draw(GraphicsBuffer& _drawBuffer, int _flag /* = BUFFER_TOP_LEFT */, float _scale /* = 1.0f */)
{
	// Get the width of the buffer to draw.
	int drawBufferWidth = _drawBuffer.getWidth();
	// Get the height of the buffer to draw.
	int drawBufferHeight = _drawBuffer.getHeight();

	// Set the scaled width of the buffer to draw.
	float scaledWidth = drawBufferWidth * _scale;
	// Set the scaled height of the buffer to draw.
	float scaledHeight = drawBufferHeight * _scale;

	// Draw location of the x position.
	float destinationX = 0.0f;
	// Draw location of the y position.
	float destinationY = 0.0f;

	// Set the x and y draw position based on the flag.
	setDrawPosition(destinationX, destinationY, scaledWidth, scaledHeight, _flag);

	// Draw a scaled bitmap to the target buffer.
	al_draw_scaled_bitmap(_drawBuffer.mpBitmap, 0.0f, 0.0f, drawBufferWidth, drawBufferHeight, destinationX, destinationY, scaledWidth, scaledHeight, 0);

	return;
}

// Write text to the current buffer.
void GraphicsSystem::writeText(float _destinationX, float _destinationY, Font& _font, Color _color, std::string _text, int _flag /* = FONT_ALIGN_LEFT */)
{
	// Draw text to the current buffer.
	al_draw_text(_font.mpFont, getColor(_color), _destinationX, _destinationY, _flag, _text.c_str());
	return;
}

// Write text to the given buffer.
void GraphicsSystem::writeText(GraphicsBuffer& _buffer, float _destinationX, float _destinationY, Font& _font, Color _color, std::string _text, int _flag /* = FONT_ALIGN_LEFT */)
{
	// Store the current back buffer.
	ALLEGRO_BITMAP* pBackBuffer = al_get_target_bitmap();

	// Set the target drawing buffer.
	al_set_target_bitmap(_buffer.mpBitmap);
	
	// Draw the text to the buffer.
	al_draw_text(_font.mpFont, getColor(_color), _destinationX, _destinationY, _flag, _text.c_str());

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

// Set the buffer as a color.
void GraphicsSystem::setBufferColor(GraphicsBuffer& _buffer, Color _color)
{
	// Hold the old back buffer to reassign after drawing.
	ALLEGRO_BITMAP* pOldBackBuffer = al_get_target_bitmap();

	// Set the bitmap to draw on as the given bitmap.
	al_set_target_bitmap(_buffer.mpBitmap);

	// Make the entire bitmap a given color.
	al_clear_to_color(getColor(_color));

	// Reassign the old back buffer.
	al_set_target_bitmap(pOldBackBuffer);

	return;
}

// Set the drawing position based on the flag.
void GraphicsSystem::setDrawPosition(float& _positionX, float& _positionY, float _drawWidth, float _drawHeight, int _flag)
{
	// Get the back buffer for calculations.
	ALLEGRO_BITMAP* pBackBuffer = al_get_target_bitmap();

	// Get the back buffer width.
	int backBufferWidth = al_get_bitmap_width(pBackBuffer);
	// Get the back buffer height.
	int backBufferHeight = al_get_bitmap_height(pBackBuffer);

	// Difference in width between the back buffer and the draw buffer.
	float differenceWidth = backBufferWidth - _drawWidth;
	// Difference in height between the back buffer and the draw buffer.
	float differenceHeight = backBufferHeight - _drawHeight;

	// Set the x and y position for drawing.
	switch (_flag)
	{
		case BUFFER_TOP_LEFT:
			_positionX = 0.0f;
			_positionY = 0.0f;
			break;

		case BUFFER_TOP:
			_positionX = differenceWidth / 2.0f;
			_positionY = 0.0f;
			break;

		case BUFFER_TOP_RIGHT:
			_positionX = differenceWidth;
			_positionY = 0.0f;
			break;

		case BUFFER_CENTER_LEFT:
			_positionX = 0.0f;
			_positionY = differenceHeight / 2.0f;
			break;

		case BUFFER_CENTER:
			_positionX = differenceWidth / 2.0f;
			_positionY = differenceHeight / 2.0f;
			break;

		case BUFFER_CENTER_RIGHT:
			_positionX = differenceWidth;
			_positionY = differenceHeight / 2.0f;
			break;

		case BUFFER_BOTTOM_LEFT:
			_positionX = 0.0f;
			_positionY = differenceHeight;
			break;

		case BUFFER_BOTTOM:
			_positionX = differenceWidth / 2.0f;
			_positionY = differenceHeight;
			break;

		case BUFFER_BOTTOM_RIGHT:
			_positionX = differenceWidth;
			_positionY = differenceHeight;
			break;
	}

	return;
}

// Get the back buffer.
GraphicsBuffer GraphicsSystem::getBackBuffer()
{
	return GraphicsBuffer(al_get_target_bitmap());
}

// Store the current back buffer of the display.
void GraphicsSystem::setBackBuffer()
{
	mpBackBuffer->mpBitmap = al_get_target_bitmap();
	return;
}

// Set the buffer to draw on.
void GraphicsSystem::setBackBuffer(GraphicsBuffer& _buffer)
{
	al_set_target_bitmap(_buffer.mpBitmap);
	return;
}

// Get an Allegro color.
ALLEGRO_COLOR GraphicsSystem::getColor(Color _color)
{
	return al_map_rgb(_color.getR(), _color.getG(), _color.getB());
}