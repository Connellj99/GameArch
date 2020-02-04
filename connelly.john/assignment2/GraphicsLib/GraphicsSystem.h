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
#include "Sprite.h"
#include "Color.h"


using namespace std;

/* GraphicsSystem Functions
void GraphicsSystem::draw(target loc, Sprite, scale ); // draw to current backbuffer (scale default value is 1)

void GraphicsSystem::draw(target graphics buffer, target loc, Sprite, scale ); // draw to given GraphicsBuffer (scale default value is 1)

void GraphicsSystem::writeText(target loc, Font, Color, text); //write to current backbuffer

void GraphicsSystem::writeText(target graphics buffer, target loc, Font, Color, text); //write to given GraphicsBuffer

void GraphicsSystem::saveBuffer(buffer to save, filename); // save the contents of a GraphicsBuffer to a file
*/


class GraphicsSystem : public Trackable
{
public:
	GraphicsSystem();

	~GraphicsSystem();

	void init(float width, float height);
	void cleanup();

	float getHeight();
	float getWidth();
	GraphicsBuffer getBackBuffer();

	void draw(Vector2 targetLoc, Sprite sprite, float scale);
	void draw(GraphicsBuffer targetGraphicsBuffer, Sprite sprite, float scale);

	void writeText(Vector2 targetLoc, Font font, Color color, string text);
	void writeText(GraphicsBuffer targetGraphicsBuffer, Vector2 targetLoc, Font font, Color color, string text);

	void saveBuffer(GraphicsBuffer bufferToSave, string fileName);


private:
	GraphicsBuffer*mBackBuffer;
	ALLEGRO_DISPLAY* currentDisplay;
};

#endif