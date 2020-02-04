#pragma once


#include <allegro5\allegro.h>
#include <allegro5\allegro_acodec.h>
#include <allegro5\allegro_audio.h>
#include <allegro5\allegro_primitives.h>

#include <iostream>
#include <cassert>
#include <string>
#include <Trackable.h>


#include "GraphicsBuffer.h"
#include "Sprite.h"
#include "Font.h"
#include "Color.h"

class GraphicsSystem : public Trackable
{
private:
	ALLEGRO_DISPLAY* mpDisplay;

	float dispWidth;
	float dispHeight;

	GraphicsBuffer* mpBackBuffer;

public:
	GraphicsSystem(float w, float h);
	~GraphicsSystem();

	int init(float w, float h);
	void cleanup();

	float getHeight();
	float getWidth();
	GraphicsBuffer* getBack();

	void flip();
	void draw(float x, float y, Sprite* spr, float s = 1.0);
	void draw(GraphicsBuffer* target, float x, float y, Sprite* spr, float s = 1.0);
	void writeText(float x, float y, Font* f, Color c, std::string text);
	void writeText(GraphicsBuffer* target, float x, float y, Font* f, Color c, std::string text);
	void saveBuffer(GraphicsBuffer* target, char* text);
};