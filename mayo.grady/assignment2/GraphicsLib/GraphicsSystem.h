#pragma once
/*
Author: Grady Mayo
Class: EGP-310 <Section 01>
Assignment: Assignment 2
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
#include "Sprite.h"
#include "Font.h"
#include "Color.h"

using namespace std;

class GraphicsSystem : public Trackable
{
private:
	ALLEGRO_DISPLAY * mpDisplay;
	GraphicsBuffer* mpBackBuffer;

public:
	//Constructor
	GraphicsSystem();

	//Destructor
	~GraphicsSystem();

	//Init
	void init( int width, int height );

	//Cleanup
	void cleanup();

	//Accessors
	int getDisplayHeight() { return al_get_display_height( mpDisplay ); };
	int getDisplayWidth() { return al_get_display_width( mpDisplay ); };

	//Flip
	void flip();

	//Draw to back buffer with sprite
	void draw( int targetLocX, int targetLocY, Sprite sprite, float scale );

	//Overloaded Draw target buffer with sprite
	void draw( GraphicsBuffer* pBuffer, int targetLocX, int targetLocY, Sprite* sprite, float scale );

	//Draw to back buffer
	void draw( GraphicsBuffer* pBuffer, int targetLocX, int targetLocY );

	//Draw buffer to back buffer
	void draw( GraphicsBuffer* pBuffer, int targetLocX, int targetLocY, float scale, GraphicsBuffer* pColorBuffer );

	//Write Text
	void writeText( int targetLocX, int targetLocY, Font* pFont, Color& color, string text );

	//Overloaded Write Text
	void writeText( GraphicsBuffer* pBuffer, int targetLocX, int targetLocY, Font* pFont, Color& color, string text );

	//Save Buffer
	void saveBuffer( GraphicsBuffer* pBuffer, string filename );

	//Save BackBuffer
	void saveBackBuffer(string filename);

	//rest
	void rest(double time);

};