#pragma once

#include "../Header.h"
#include <allegro5/allegro.h>
#include <Trackable.h>

class Color : public Trackable
{
private:
	ALLEGRO_COLOR mColor;
	int r;
	int g;
	int b;

public:
	Color();
	Color(int red, int green, int blue);

	void setR(int red);
	void setG(int green);
	void setB(int blue);
	ALLEGRO_COLOR getColor();
};