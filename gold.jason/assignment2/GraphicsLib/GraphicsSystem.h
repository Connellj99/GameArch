#pragma once

#include "GraphicsLib.h"
#include "GraphicsBuffer.h"
#include "Sprite.h"
#include "Font.h"
#include "Color.h"

class GraphicsSystem : public Trackable
{
private:

	ALLEGRO_DISPLAY* display;

public:

	//getters
	int getWidth();
	int getHeight();

	//constructor
	GraphicsSystem();

	//initilization
	void initGraphicsSystem(int width, int height);

	//flip display to show back buffer
	void flipDisplay();

	//functions to draw text
	void writeText(int, int, Font, Color, string);
	void writeText(GraphicsBuffer*, int, int, Font, Color, string);

	//functions to draw sprites
	void draw(int, int, Sprite, float);
	void draw(GraphicsBuffer*, int, int, Sprite, float);

	//destructor
	~GraphicsSystem();
};