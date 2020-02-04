#pragma once

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

#include <PerformanceTracker.h>
#include <MemoryTracker.h>
#include <Trackable.h>

#include "Font.h"
#include "Color.h"
#include "Sprite.h"
#include "GraphicsBuffer.h"
using namespace std;

class GraphicsSystem : public Trackable
{
public:
	GraphicsSystem();
	~GraphicsSystem();
	int Init(int height, int width);
	void Cleanup();
	void Flip();
	void Rest(float sleepTime);
	int getHeight();
	int getWidth();
	void draw(int x, int y, Sprite* sprite, int scale);
	void draw(GraphicsBuffer* targetGraphicsBuffer, int x, int y, Sprite* sprite, float scale);
	void draw(int x, int y, GraphicsBuffer* backBuffer, int scale);
	void draw(GraphicsBuffer* targetGraphicsBuffer, int x, int y, GraphicsBuffer* backBuffer, float scale);
	void writeText(int X, int Y, Font* font, Color color, string text);
	void writeText(GraphicsBuffer* targetBuffer, int X, int Y, Font* font, Color color, std::string text);
	void saveBackBuffer(string filename);
	void saveBuffer(GraphicsBuffer* targetBuffer, string filename);


private:
	ALLEGRO_DISPLAY* display;
	GraphicsBuffer* mpBackBuffer;
	int mHeight = 600;
	int mWidth = 800;
};