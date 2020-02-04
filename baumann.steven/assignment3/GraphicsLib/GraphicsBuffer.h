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
		const string ASSET_PATH = "..\\..\\shared\\assets\\";
	public:
		GraphicsBuffer(string filename);
		GraphicsBuffer(int r, int g, int b);
		GraphicsBuffer(ALLEGRO_BITMAP* bitmap);
		~GraphicsBuffer();
		int GetHeight();
		int GetWidth();

		friend class GraphicsSystem;
		friend class Animation;
		friend class Game;
	
};

#endif