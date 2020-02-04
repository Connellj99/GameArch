#ifndef COLOR_H
#define COLOR_H

#include "Trackable.h"
#include "allegro5/allegro.h"



class Color : public Trackable
{
public:
	Color();
	Color(int,int,int,int);
	ALLEGRO_COLOR getColor();
private:
	ALLEGRO_COLOR mColor;
	
	

};

#endif


