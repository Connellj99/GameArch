/*
Conner Root
EGP 310-01
*/

#pragma once

#include "GraphicsLib.h"
#include "GraphicsBuffer.h"
#include "Sprite.h"
#include "Font.h"
#include "Color.h"

class GraphicsSystem : public Trackable
{
private:
	ALLEGRO_DISPLAY * mpDisplay;
	GraphicsBuffer * mpBackBuff;
	bool mInited = false;

public:
	// Constructor
	GraphicsSystem();

	// Init / Cleanup
	void initGraphicsSystem(int w, int h);
	void cleanup();

	// Accessors
	int getWidth();
	int getHeight();

	// Flip the display
	void flipDisplay();

	// Draw functions
	void draw(int, int, Sprite*, float);
	void draw(int, int, Sprite*, GraphicsBuffer*, float);

	// Write functions
	void writeText(int, int, Font*, Color, string);
	void writeText(int, int, Font*, Color, GraphicsBuffer*, string);

	// Wait function
	void wait(float);

	// Save Function
	void saveBuffer(GraphicsBuffer*, string);

	// Destructor
	~GraphicsSystem();
};