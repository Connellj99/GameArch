#pragma once
/*
Author: Grady Mayo
Class: EGP-310 <Section 01>
Assignment: Assignment 3
Certification of Authenticity: I certify that this assignment is entirely my own work.
*/
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <Trackable.h>

#include "GraphicsBuffer.h"

using namespace std;

class Sprite : public Trackable
{
private:
	GraphicsBuffer* mpGraphicsBuffer;
	int mLocX;
	int mLocY;
	int mSpriteHeight;
	int mSpriteWidth;

public:
	//Constructor
	Sprite( int LocX, int LocY, int width, int height, GraphicsBuffer* pBuffer );

	//Destructor
	~Sprite();

	//Accessors
	int getLocX() { return mLocX; };
	int getLocY() { return mLocY; };
	int getSpriteHeight() { return mSpriteHeight; };
	int getSpriteWidth() { return mSpriteWidth; };
	GraphicsBuffer* getGraphicsBuffer() { return mpGraphicsBuffer; };



};