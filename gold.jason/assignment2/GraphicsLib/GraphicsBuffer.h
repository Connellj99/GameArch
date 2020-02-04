#pragma once

#include "GraphicsLib.h"
#include "Color.h"

class GraphicsBuffer : public Trackable{
private:

	//create a pointer to the bitmap
	ALLEGRO_BITMAP *mBitmap;

public:

	//constructors
	GraphicsBuffer();
	GraphicsBuffer(string);
	GraphicsBuffer(int, int, Color);

	//getters
	int getHeight();
	int getWidth();
	ALLEGRO_BITMAP* getBitmap();

	//destructor
	~GraphicsBuffer();
};