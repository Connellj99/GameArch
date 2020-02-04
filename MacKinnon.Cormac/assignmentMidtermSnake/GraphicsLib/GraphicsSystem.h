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
#include <stdlib.h>

#include <PerformanceTracker.h>
#include <MemoryTracker.h>
#include <Vector2D.h>

#include "Font.h"
#include "Color.h"
#include "Sprite.h"
#include "GraphicsBuffer.h"

class GraphicsSystem : public Trackable
{
public:
	//friend class System;
	//constructors
	GraphicsSystem();
	~GraphicsSystem();

	//functions
	void init(int width, int height);
	void cleanup();

	int getHeight();
	int getWidth();
	
	void rest(double sleepTime);
	void flipDisplay();

	void draw(float targetLocX, float targetLocY, Sprite* pSprite, float scale); //draw to current backbuffer
	void draw(GraphicsBuffer* targetBuffer, Vector2D location, Sprite* pSprite, float scale); //draw to given GraphicsBuffer
	void draw(float targetLocX, float targetLocY, GraphicsBuffer* pBackBuffer, float scale);
	void draw(GraphicsBuffer* pTargetBuffer, float targetLocX, float targetLocY, GraphicsBuffer* pBackBuffer, float scale);

	void writeText(float targetLocX, float targetLocY, Font* font, Color &color, std::string text); //write to current backbuffer
	void writeText(GraphicsBuffer* targetBuffer, float targetLocX, float targetLocY, Font* font, Color &color, std::string text); //write to given GraphicsBuffer

	void saveBackBuffer(std::string fileName);
	void saveBuffer(GraphicsBuffer *pTargetBuffer, std::string fileName);

	
	//need backbuffer getter
	//possibly add enum based text alignment aspect
	//fix cleanup

private:
	int mWidth;
	int mHeight;

	GraphicsBuffer* getBackBuffer();

	ALLEGRO_DISPLAY *mpDisplayWindow;
	GraphicsBuffer* mpBackBuffer;
};

