#pragma once


#include <allegro5\allegro.h>
#include <allegro5\allegro_acodec.h>
#include <allegro5\allegro_audio.h>
#include <allegro5\allegro_primitives.h>

#include <iostream>
#include <cassert>
#include <string>
#include <Trackable.h>


#include "../GraphicsBuffer.h"
#include "Sprite.h"
#include "Font.h"
#include "Color.h"

class GraphicsSystem : public Trackable
{
private:
	ALLEGRO_DISPLAY* mpDisplay;

	const float dispHeight = 600;
	const float dispWidth = 800;

	GraphicsBuffer* mpBackBuffer;

public:
	GraphicsSystem();
	~GraphicsSystem();

	int init();
	void cleanup();

	float getHeight();
	float getWidth();
	GraphicsBuffer* getBack();

	void flip();
	void draw(float x, float y, Sprite* spr, float s = 1.0);
	void draw(GraphicsBuffer* target, float x, float y, Sprite* spr, float s = 1.0);
	void writeText(float x, float y, Font* f, Color c, const char* text);
	void writeText(GraphicsBuffer* target, float x, float y, Font* f, Color c, const char* text);
	void saveBuffer(GraphicsBuffer* target, char* text);
};