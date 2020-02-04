#ifndef GRAPHICSSYSTEM_H
#define GRAPHICSSYSTEM_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

#include <iostream>
#include <cassert>
#include <string>
#include <stdlib.h>

#include <PerformanceTracker.h>
#include <MemoryTracker.h>

#include "GraphicsBuffer.h"
#include "Font.h"
#include "Color.h"
#include "Sprite.h"

using namespace std;

class GraphicsSystem : public Trackable
{
public:


	// Constructors
	GraphicsSystem();


	// Destructors
	~GraphicsSystem();


	// Initializes / Deinitializers
	void init(float width, float height);
	void cleanup();


	// Acessors
	float getHeight();
	float getWidth();
	GraphicsBuffer getBackBuffer();


	// Display-controller functions
	void closeWindow(float secondsDelay);
	void flip();

	// Drawing functions for sprites
	void draw(Vector2 targetLoc, Sprite& sprite, float scale);
	void drawBackground(GraphicsBuffer& buffer, float scale);
	void draw(GraphicsBuffer& targetGraphicsBuffer, Sprite& sprite, float scale);
	void drawSquares(Vector2 targetLoc,float scale);


	// Drawing functions for sprite sheets
	void drawFromSpriteSheet(Vector2 targetImageLoc, Vector2 targetLoc, Sprite& sprite, Vector2 scale);
	static void drawFromSpriteSheet(GraphicsBuffer& targetGraphicsBuffer, Vector2 targetImageLoc, Vector2 targetLoc, GraphicsBuffer& sprite, Vector2 scale);

	// Drawing functions for text
	void drawText(Vector2 targetLoc, Font& font, Color color, string text);
	void drawText(GraphicsBuffer& targetGraphicsBuffer, Vector2 targetLoc, Font& font, Color color, string text);

	
	// Save/load functions
	void saveBuffer(GraphicsBuffer& bufferToSave, string fileName);


private:

	// Graphics Buffers
	GraphicsBuffer* mBackBuffer;

	// Displays
	ALLEGRO_DISPLAY* mCurrentDisplay;
};

#endif