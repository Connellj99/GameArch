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
#include <stdlib.h>

#include <PerformanceTracker.h>
#include <MemoryTracker.h>

class Font :public Trackable
{
public:
	friend class GraphicsSystem;
	//constructors
	Font();
	Font(std::string &fileName, int fontSize);
	~Font();

	//accessors
	int getSize();
	ALLEGRO_FONT* getFont();

private:
	ALLEGRO_FONT* mpFont;
	int mFontSize;

};

