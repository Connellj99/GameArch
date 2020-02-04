#pragma once

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

#include <PerformanceTracker.h>
#include <MemoryTracker.h>
#include <Trackable.h>
using namespace std;

class Color : public Trackable
{
public:
	Color();
	Color(int r, int g, int b);
	~Color();
	int getR();
	int getG();
	int getB();

private:
	int R;
	int G;
	int B;
	
};

