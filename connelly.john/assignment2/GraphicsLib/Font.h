#ifndef FONT_H
#define FONT_H

#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include <iostream>
#include <cassert>
#include <string>
#include <stdlib.h>

#include <PerformanceTracker.h>
#include <MemoryTracker.h>

using namespace std;


class Font : public Trackable
{
public:

	friend class GraphicsSystem;

	Font();

	~Font();

	int getSize();


private:
	ALLEGRO_FONT* mCurrentFont;
	int mFontSize;
};

#endif