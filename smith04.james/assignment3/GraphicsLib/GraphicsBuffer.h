#pragma once

#include <Trackable.h>
#include <allegro5\allegro_image.h>
#include "Color.h"
#include <allegro5\allegro_primitives.h>


#include <iostream>
#include <cassert>
#include <string>
#include <Trackable.h>


class GraphicsBuffer : public Trackable
{
private:
	ALLEGRO_BITMAP* mpBitmap;

	ALLEGRO_BITMAP* getBitMap();

	friend class GraphicsSystem;
	friend class Sprite;
public:
	GraphicsBuffer();
	GraphicsBuffer(const char* assetPath);
	GraphicsBuffer(ALLEGRO_BITMAP* bitmap);
	~GraphicsBuffer();

	void draw(float x, float y);

	void clearColor(Color c);

	float getHeight();
	float getWidth();

	void drawScaled(float x, float y, float s);
};