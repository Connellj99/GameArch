#ifndef FONT_H
#define FONT_H

#include "Trackable.h"
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
using namespace std;

class Font : public Trackable
{
public:
	//constructor and acessors
	Font(const string assetPath, const string filename, int size);
	~Font();
	int getSize();
	ALLEGRO_FONT* getFont();

private:
	//Allegro Font
	ALLEGRO_FONT* mpFont;
	//Font Size
	int mSize;
};
#endif

