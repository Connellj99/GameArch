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
#include "Color.h"
using namespace std;

class Font : public Trackable
{
public:
	Font(const string filename, int size);
	~Font();
	int getFontSize();
	ALLEGRO_FONT* getFont();

private:
	ALLEGRO_FONT* mCurrentFont;
	int mFontSize;
};