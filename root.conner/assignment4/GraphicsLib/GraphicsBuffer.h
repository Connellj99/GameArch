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
	string mFilename = "";

public:
	// Constructor
	GraphicsBuffer();
	GraphicsBuffer(ALLEGRO_BITMAP* bitmap);
	GraphicsBuffer(const string&);
	GraphicsBuffer(int, int, Color);

	// Cleanup
	void cleanup();

	// Accessors
	int getWidth();
	int getHeight();
	string getFileName();
	ALLEGRO_BITMAP* getBitmap();

	// Destructor
	~GraphicsBuffer();
};