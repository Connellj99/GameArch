#pragma once
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "Trackable.h"
using namespace std;

class Font : public Trackable
{
	friend class GraphicsSystem;
private:
	ALLEGRO_FONT* mFont;
	int mSize;
public:
	//constructor/destructor
	Font( int size, string file, const string assetPath);
	~Font();
	ALLEGRO_FONT* getAllegroFont() const { return mFont; }
	int getSize() { return mSize; };
};