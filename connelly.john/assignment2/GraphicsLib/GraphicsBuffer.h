#ifndef GRAPHICSBUFFER_H
#define GRAPHICSBUFFER_H


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
#include <stdlib.h>

#include <PerformanceTracker.h>
#include <MemoryTracker.h>
#include "Color.h"

using namespace std;


class GraphicsBuffer : public Trackable
{
public:

	friend class GraphicsSystem;
	friend class Sprite;

	GraphicsBuffer();
	GraphicsBuffer( string bitmapFilePath );
	GraphicsBuffer( ALLEGRO_BITMAP * newBitmap );
	GraphicsBuffer( int length , int height , Color colorOfScreen );

	~GraphicsBuffer();

	int getHeight();
	int getWidth();


private:
	ALLEGRO_BITMAP *mStoredBitmap;
};

#endif