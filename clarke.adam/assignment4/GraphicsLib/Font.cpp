#include "Font.h"

Font::Font(std::string filePath, int size)
	:mSize(size)
{
	mpFont = al_load_ttf_font(filePath.c_str(), size, NULL);
	assert(mpFont);
}

Font::~Font()
{
	al_destroy_font(mpFont);
}
