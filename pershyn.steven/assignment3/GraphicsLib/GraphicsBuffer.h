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
#include "Color.h"

using namespace std;

class GraphicsBuffer : public Trackable
{
	friend class GraphicsSystem;
public:
	GraphicsBuffer();
	GraphicsBuffer(string bitmapName);
	GraphicsBuffer(string filePath, string fileName);
	GraphicsBuffer(int width, int height, Color colorofScreen);
	GraphicsBuffer(ALLEGRO_BITMAP* newBitmap, bool backBuffer);
	~GraphicsBuffer();
	int getHeight() { return mWidth; };
	int getWidth() { return mHeight; };
	
	void init();

private:
	ALLEGRO_BITMAP *mpBitmap;
	ALLEGRO_BITMAP *getBitmap() { return mpBitmap; };
	int mWidth, mHeight;
	bool mBackBuffer = false;
	bool ownBitmap = false;
};