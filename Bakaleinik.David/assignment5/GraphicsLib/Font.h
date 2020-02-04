#pragma once
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include "Trackable.h"


using namespace std;

class Font : public Trackable
{
public:

	friend class GSystem;

	Font(string path, string fontName, int fontSize);
	Font();
	~Font();

	int getFontSize();

private:

	
	
	string mFontName;
	int mFontSize;
	

	ALLEGRO_FONT *cour_font = NULL;
	

};