#pragma once
#ifndef GRAPHICS_SYSTEM
#define GRAPHICS_SYSTEM

#include "Sprite.h"
#include "GraphicsBuffer.h"
#include "Font.h"
#include <iostream>
#include <string>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
using namespace std;

class GraphicsSystem {
	private:
		ALLEGRO_DISPLAY* display;
		int height;
		int width;
	public:
		GraphicsSystem(int width, int height);
		~GraphicsSystem();

		int init(); // returns any error code

		void SetHeight(int height);
		int GetHeight();

		void SetWidth(int width);
		int GetWidth();

		void Flip();

		void Draw(int x, int y, Sprite* picture, double scale = 1.0);
		void Draw(GraphicsBuffer* buffer, int x, int y, Sprite* picture, double scale = 1.0);
		void DrawSmurfs(Sprite* picture); // Will use the Sprite buffer by default

		void WriteText(int x, int y, Font* font, int r, int g, int b, string text);
		void WriteText(GraphicsBuffer* buffer, int x, int y, Font* font, int r, int g, int b, string text);

		void SaveBuffer(string filename); // Saves backbuffer by default
		void SaveBuffer(GraphicsBuffer* buffer, string filename);
		
		static void ExitApplication();

		friend class GraphicsBuffer;

};


#endif