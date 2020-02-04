#ifndef Font_H

#define Font_H

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


//Font ----------------------------------------------------------------------------------------/
class Font : public Trackable
{
public:

	friend class GraphicsSystem;

	Font();//constructor
	~Font();//destructor

	float getSize();//returns the font size, or mFontSize in this case
	
	Font loadText();//loads in the font to the mFont pointer
	
private:
	//these represent the file to the font file asset
	const std::string ASSET_PATH = "..\\..\\shared\\assets\\";
	const std::string FONT_FILENAME = "cour.ttf";
	const int FONT_SIZE = 24;

	//this is the pointer for the font
	ALLEGRO_FONT * mFont;

	//font size
	float mFontSize;
};
#endif