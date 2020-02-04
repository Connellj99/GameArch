/*
Author: Steven Pershyn
Class: EGP-310-01
Assignment: Assignment 3
Certification of Authenticity: I certify that this assignment is my own work, except where I referenced classmates' work and mentioned where relevant.
*/
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
private:
	ALLEGRO_DISPLAY* display;
	GraphicsBuffer* mpBackBuffer;
	int dispWidth = 0;
	int dispHeight = 0;
	bool mInit;
public:
	GraphicsSystem();
	~GraphicsSystem();
	void Init(int height, int width);
	void Cleanup();
	void Flip();
	void Rest(float sleepTime);
	int getHeight() { return dispHeight; };
	int getWidth() { return dispWidth; };
	void draw(int x, int y, Sprite* sprite, float scale = 1.0);
	void draw(GraphicsBuffer* targetBuffer);
	void draw(GraphicsBuffer* targetGraphicsBuffer, int x, int y, Sprite* sprite, float scale);
	void draw(int x, int y, GraphicsBuffer* backBuffer, int scale);
	void draw(GraphicsBuffer* targetGraphicsBuffer, int x, int y, GraphicsBuffer* backBuffer, float scale);
	void writeText(int X, int Y, Font* font, Color color, string text);
	void writeText(GraphicsBuffer* targetBuffer, int X, int Y, Font* font, Color color, std::string text);
	void saveBackBuffer(string filename);
	void saveBuffer(GraphicsBuffer* targetBuffer, string filename);



};