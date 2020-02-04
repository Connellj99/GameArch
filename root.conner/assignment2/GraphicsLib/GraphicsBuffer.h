/*
Conner Root
EGP 310-01
*/

#pragma once

#include "GraphicsLib.h"
#include "Color.h"

class GraphicsBuffer : public Trackable
{
	friend class GraphicsSystem;

private:
	ALLEGRO_BITMAP * mpBitmap;

public:
	// Constructor
	GraphicsBuffer();
	GraphicsBuffer(ALLEGRO_BITMAP* bitmap);
	GraphicsBuffer(const string&);
	GraphicsBuffer(int, int, Color);

	// Init / Cleanup
	void init();

	// Accessors
	int getWidth();
	int getHeight();
	ALLEGRO_BITMAP* getBitmap();

	// Destructor
	~GraphicsBuffer();
};