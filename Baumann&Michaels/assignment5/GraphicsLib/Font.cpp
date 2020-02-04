#include "Font.h"

Font::Font(int size) 
{
	cour_font = al_load_ttf_font((ASSET_PATH + FONT_FILENAME).c_str(), size, 0);
	fontSize = size;
}

Font::~Font() 
{
	al_destroy_font(cour_font);
}

void Font::SetSize(int size) 
{
	fontSize = size;
}

int Font::GetSize() 
{
	return fontSize;
}