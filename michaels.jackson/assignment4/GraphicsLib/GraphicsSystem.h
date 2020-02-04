/*
Author:Jackson Michaels
Class: EGP-310-01
Assignment: Assignment 3
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/

#pragma once
#include <allegro5/allegro.h>
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

#include "Constants.h"
#include "GraphicsBuffer.h"
#include "Font.h"
#include "Sprite.h"
#include "Color.h"

using namespace std;
class GraphicsSystem : public Trackable 
{
private:
	int mDispWidth = 0;
	int mDistHeight = 0;
	ALLEGRO_DISPLAY* mDisplay;
	bool mInit = false;
public:
	GraphicsSystem();
	~GraphicsSystem();
	int init(int = 100, int = 100);
	int cleanUp();
	static void flip();
	int getWindowWidth() { return mDispWidth; };
	int getWindowHeight() { return mDistHeight; };

	int draw(Sprite*, int, int,  float scale = 1.0);
	int draw(GraphicsBuffer*, Sprite*, int, int,  float scale = 1.0);
	int writeText(string, int, int, Font*, Color*);
	int writeText(string, GraphicsBuffer*, int, int, Font*, Color*);
	int saveBuffer(string, GraphicsBuffer* = NULL);
	GraphicsBuffer* getBackBuffer() { return new GraphicsBuffer(al_get_target_bitmap()); }
};
