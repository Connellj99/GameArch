#ifndef GRAPHICSBUFFER_H
#define GRAPHICSBUFFER_H

#include <iostream>
#include <cassert>
#include <string>
#include <stdlib.h>

#include <PerformanceTracker.h>
#include <MemoryTracker.h>
#include "Color.h"

using namespace std;


class GraphicsBuffer : public Trackable
{
public:


	// Friends
	friend class GraphicsSystem;
	friend class Sprite;
	friend class GraphicsBufferManager;

	// Constructors
	GraphicsBuffer();
	GraphicsBuffer( string bitmapFilePath, string name );
//	GraphicsBuffer( ALLEGRO_BITMAP * newBitmap, string name );
	GraphicsBuffer( int length , int height , Colors colorOfScreen, string name );
	GraphicsBuffer( int length, int height, string name );

	// Destructors
	~GraphicsBuffer();

	// Acessor Functions
	int getHeight();
	int getWidth();


private:

	bool mIsBackBuffer;

	string mName;

};

#endif