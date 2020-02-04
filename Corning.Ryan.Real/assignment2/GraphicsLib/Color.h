#pragma once
#include "Trackable.h"
#include "allegro5/allegro.h"


class Color : public Trackable
{
public:
	Color();
	// (r,g,b,A)
	Color(int, int, int, int);
	ALLEGRO_COLOR getColor();
private:
	//used for axcessing the color so dont have use 4 getters
	ALLEGRO_COLOR mColor;
};
