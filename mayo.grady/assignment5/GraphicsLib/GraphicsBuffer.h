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

#include "Color.h"

using namespace std;

class GraphicsBuffer : public Trackable
{
	friend class GraphicsSystem;
private:
	ALLEGRO_BITMAP * mpBitmap;
	bool mOwnsBitmap;
	ALLEGRO_COLOR mColor;

	//Constructor for back buffer
	GraphicsBuffer(ALLEGRO_BITMAP* bitmap);

	ALLEGRO_BITMAP* getBitmap() { return mpBitmap; };

public:
	//constructor with filename
	GraphicsBuffer( string filename );

	//constructor with size and color
	GraphicsBuffer( int width, int height, Color& color );

	//Destructor
	~GraphicsBuffer();

	//Accessors
	int getBitmapHeight() { return al_get_bitmap_height(mpBitmap); };
	int getBitmapWidth() { return al_get_bitmap_width(mpBitmap); };
	
};