#pragma once

#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>

#include <iostream>
#include <cassert>
#include <string>
#include <Trackable.h>


class Font : public Trackable
{
private:
	ALLEGRO_FONT* mpFont;
	int size;

	ALLEGRO_FONT* getFont();

	friend class GraphicsSystem;

public:
	Font();
	Font(const char* font, int s);
	~Font();

	float getSize();
	
};