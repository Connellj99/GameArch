/*
Author: Amelia Payne
Class: EGP-310 <2>
Assignment: pa 3
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/

#pragma once
#include <string>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

#include <PerformanceTracker.h>
#include <MemoryTracker.h>
#include "Color.h"

/*
This class holds an Bitmap that the graphics system can draw
*/
class GraphicsBuffer : public Trackable 
{
private:
	ALLEGRO_BITMAP * mpBitmap;
	bool mIsBack = false;

	ALLEGRO_BITMAP * getBitmap()
	{
		return mpBitmap;
	}

	
public:
	friend class GraphicsSystem;
	friend class Unit;
	//Constructor and destructor 
	GraphicsBuffer();

	GraphicsBuffer(std::string fileName);

	GraphicsBuffer(int w, int h);

	GraphicsBuffer(ALLEGRO_BITMAP * bitmap, bool isBack);

	~GraphicsBuffer();

	void clearToColor(Color color);

	//Acessors
	int getHeight() {return al_get_bitmap_height(mpBitmap);};
	int getWidth() {return al_get_bitmap_width(mpBitmap);};

};