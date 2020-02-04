#pragma once

#ifndef GRAPHICS_BUFFER
#define GRAPHICS_BUFFER

#include "Trackable.h"
#include <string>
#include <allegro5/allegro.h>
using namespace std;

class GraphicsBuffer :public Trackable
{
	private:
		ALLEGRO_BITMAP* bitmap;
		ALLEGRO_COLOR color;
	public:
		GraphicsBuffer(string filename);
		GraphicsBuffer(int r, int g, int b);
		GraphicsBuffer(ALLEGRO_BITMAP* bitmap);
		GraphicsBuffer();
		~GraphicsBuffer();
		void setBitmap(ALLEGRO_BITMAP* newBitmap);
		int GetHeight();
		int GetWidth();

		friend class GraphicsSystem;
		friend class Animation;
		friend class Game;
	
};

#endif