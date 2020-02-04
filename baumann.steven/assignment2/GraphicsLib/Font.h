#pragma once

#ifndef FONT_H
#define FONT_H

#include <string>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

using namespace std;

class Font {
private:
	ALLEGRO_FONT *cour_font;
	const string ASSET_PATH = "..\\..\\shared\\assets\\";
	const string FONT_FILENAME = "cour.ttf";
	int fontSize;
public:
	Font(int size);
	~Font();

	int GetSize();
	void SetSize(int size);

	friend class GraphicsSystem;

};

#endif