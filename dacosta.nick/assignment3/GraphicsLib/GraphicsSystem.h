/*********************************************************************
**		Author:	Nick DaCosta										**
**		Class: 310 <Section 01>										**
**		Assignment: pa 3											**
**		Certification of Authenticity:								**
**		I certify that this assignment is entirely my own work.	    **
*********************************************************************/

#pragma once

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>

/// <summary>
///		Creates and maintains the display.
/// </summary>
/// <seealso cref="Trackable" />
class GraphicsSystem :
	public Trackable
{
public:
	// Create default graphics system.
	GraphicsSystem();

	// Destroy the display pointer.
	~GraphicsSystem();

	// GraphicsSystem initialize (don't call from constructor).
	void initialize(int _width, int _height);
	
	// Clean up the allegro system.
	void cleanUp();

	// Get the width of the display.
	int getWidth();

	// Get the height of the display.
	int getHeight();

	// Bring the back buffer to the main buffer.
	void update();

	// Draw sprites.
	static void draw(Sprite _sprite, float _destinationX, float _destinationY, float _scale = 1.0);
	
	// Draw a buffer to a target buffer.
	static void draw(GraphicsBuffer& _drawBuffer, GraphicsBuffer& _targetBuffer, int _flag = BUFFER_TOP_LEFT, float _scale = 1.0f);

	// Draw directly to the back buffer.
	static void draw(GraphicsBuffer& _drawBuffer, int _justification = BUFFER_TOP_LEFT, float _scale = 1.0f);

	// Write text to the current back buffer.
	static void writeText(float _destinationX, float _destinationY, Font& _font, Color _color, std::string _text, int _flag = FONT_ALIGN_LEFT);

	// Write text to the given buffer.
	static void writeText(GraphicsBuffer& _buffer, float _destinationX, float _destinationY, Font& _font, Color _color, std::string _text, int _flag = FONT_ALIGN_LEFT);

	// Save a buffer.
	static void saveBuffer(GraphicsBuffer& _buffer, std::string _fileName);

	// Set the buffer as a color.
	void setBufferColor(GraphicsBuffer& _buffer, Color _color);

	// Set the drawing position based on the flag.
	static void setDrawPosition(float& _positionX, float& _positionY, float _drawWidth, float _drawHeight, int _flag);

	// Get the back buffer of the display.
	GraphicsBuffer getBackBuffer();

private:
	// Member variable allegro display.
	ALLEGRO_DISPLAY* mpDisplay = nullptr;

	// Member variable to store a back buffer.
	GraphicsBuffer* mpBackBuffer = nullptr;

	// Member variable check for initialization.
	bool mIsInitialized = false;

	// Set the back buffer of the display.
	void setBackBuffer();

	// Set the buffer to draw on.
	void setBackBuffer(GraphicsBuffer& _buffer);

	// Get an Allegro color.
	static ALLEGRO_COLOR getColor(Color _color);
};