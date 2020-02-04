/*********************************************************************
**		Author:														**
**		Class: 310 <Section 0>										**
**		Assignment: pa 2											**
**		Certification of Authenticity:								**
**		I certify that this assignment is entirely my own work.	    **
**		Assingment 2 Author: Nick DaCosta							**
*********************************************************************/
#pragma once

// TODO: Add all allegro libraries here. Only call them here and GraphicsBuffer.
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include <iostream>

#include "Font.h"
#include "Color.h"
#include "GraphicsBuffer.h"
#include "Sprite.h"

/// <summary>
///		Creates and maintains the display.
/// </summary>
/// <seealso cref="PerformanceTracker" />
class GraphicsSystem :
	public Trackable
{
public:
	// Create default graphics system.
	GraphicsSystem();

	// TODO: Call cleanup here.
	// NOTE: Not working because object doesn't go out of scope. Change object to a pointer?
	// Destroy the display pointer.
	~GraphicsSystem();

	// GraphicsSystem initialize (don't call from constructor).
	void initialize(int _width, int _height);
	
	// TODO: Call from destructor.
	// NOTE: Not working from destructor because object doesn't go out of scope. Change object to a pointer?
	// Clean up the allegro system.
	void cleanUp();

	// Get the width of the display.
	int getWidth();

	// Get the height of the display.
	int getHeight();

	// Bring the back buffer to the main buffer.
	void updateDisplay();

	// Draw sprites.
	static void draw(Sprite _sprite, float _destinationX, float _destinationY, float _scale = 1.0);
	
	// TODO: Include target buffer to draw to. Don't draw directly to back buffer.
	// Draw a centered buffer in the taget buffer.
	static void draw(GraphicsBuffer& _buffer, float _scale = 1.0f);

	// Write text to the current back buffer.
	static void writeText(float _destinationX, float _destinationY, Font& _font, Color _color, std::string _text);

	// Write text to the given buffer.
	static void writeText(GraphicsBuffer& _buffer, float _destinationX, float _destinationY, Font& _font, Color _color, std::string _text);

	// Save the buffer as a jpg.
	static void saveBuffer(GraphicsBuffer& _buffer, std::string _fileName);

	// Get the back buffer of the display.
	GraphicsBuffer getBackBuffer();

private:
	// Member variable allegro display.
	ALLEGRO_DISPLAY* mpDisplay;
};