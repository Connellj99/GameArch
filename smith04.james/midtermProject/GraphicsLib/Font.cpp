#include "Font.h"

Font::Font()
{
	mpFont = nullptr;
}

Font::Font(const char* font, int s)
{
	mpFont = al_load_ttf_font(font, s, 0);
	size = s;
}

Font::~Font()
{
	al_destroy_font(mpFont);
}

float Font::getSize()
{
	return size;
}

ALLEGRO_FONT* Font::getFont()
{
	return mpFont;
}