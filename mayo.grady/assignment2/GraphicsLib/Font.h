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

using namespace std;

class Font : public Trackable
{
	friend class GrphicsSystem;
private:
	ALLEGRO_FONT * mpFont;
	int mFontSize;

public:
	//constructor
	Font(int size, string filename);

	//destructor
	~Font();

	//accessors
	int getFontSize() { return mFontSize; };
	ALLEGRO_FONT* getFont() { return mpFont; };
};