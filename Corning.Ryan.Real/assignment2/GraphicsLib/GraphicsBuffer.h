#pragma once
#pragma once
#include <allegro5/allegro.h>
#include "Trackable.h"
#include "Vector2D.h"
#include "Color.h"
#include <string>

class GraphicsBuffer : public Trackable
{
	friend class GraphicsSystem;
private:
	ALLEGRO_BITMAP *mBitmap;
public:
	//constructors and destructors
	GraphicsBuffer(Vector2D size, Color color);
	GraphicsBuffer(string filename);
	~GraphicsBuffer();

	//getters
	int getWidth();
	int getHeight();
};