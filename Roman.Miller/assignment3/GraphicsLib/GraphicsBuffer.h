#ifndef GRAPHICSBUFFER_H
#define GRAPHICSBUFFER_H

#include "Trackable.h"
#include "allegro5/allegro.h"
#include "Vector2D.h"
#include "Color.h"
using namespace std;

class GraphicsBuffer : public Trackable
{
	friend class GraphicsSystem;
public:
	//constuctors and acessors
	GraphicsBuffer(Vector2D size, Color color);
	GraphicsBuffer(string filename);
	~GraphicsBuffer();
	int getWidth();
	int getHeight();

private:
	//referance to a bitmap
	ALLEGRO_BITMAP *mpBitmap;
};
#endif