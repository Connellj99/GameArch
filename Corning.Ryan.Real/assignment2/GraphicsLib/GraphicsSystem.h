#pragma once
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include "GraphicsBuffer.h"
#include "Sprite.h"
#include "Font.h"
#include <iostream>
#include<string>
using namespace std;

class GraphicsSystem : public Trackable
{
private:
	ALLEGRO_DISPLAY* display;
	GraphicsBuffer* mpBackBuffer;
	int mWidth = 800;
	int mHight = 600;

public:
	GraphicsSystem();
	~GraphicsSystem();
	int Init( int height, int width);
	void Cleanup();//used to make the buld of 
	int getHeight() { return mHight;};
	int getWidth() { return mWidth;};
	ALLEGRO_DISPLAY *getBackBuffer();
	//void draw(int x, int y, Sprite)
};