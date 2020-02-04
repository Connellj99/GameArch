/*
Author:Jackson Michaels
Class: EGP-310-01
Assignment: Assignment 2
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/
#pragma once
#include "Constants.h"
#include <allegro5/allegro.h>

#include <string>
#include <stdlib.h>

#include <PerformanceTracker.h>
#include <MemoryTracker.h>


class Color;

class GraphicsBuffer : public Trackable 
{
	friend class GraphicsSystem;
private:
	ALLEGRO_BITMAP* mBitmap;
	ALLEGRO_BITMAP* getBitMap() { return mBitmap; };
	int mWidth, mHeight;
	bool mOwnsBitmap;
	GraphicsBuffer(ALLEGRO_BITMAP*);
public:
	GraphicsBuffer(std::string);
	GraphicsBuffer(int, int);
	~GraphicsBuffer();
	int getWidth() { return mWidth; };
	int getHeight() { return mHeight; };
	void setColor(Color* color);
};
