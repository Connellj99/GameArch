#ifndef Colors_H

#define Colors_H

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


//The class for the colors
class Colors : public Trackable
{
public:
	//Friends
	friend class GraphicsSystem;
	friend class GraphicsBuffer;

	Colors(float r,float g, float b);//constructor that must take in a rgb value
	~Colors();//destructor
	
private: 

	ALLEGRO_COLOR* mColor;//pointer of color that will be used to assign colors
		
	//constant allegro color variables set to different rgb maps
	const ALLEGRO_COLOR WHITE = al_map_rgb(255, 255, 255);
	const ALLEGRO_COLOR RED = al_map_rgb(255, 0, 0);
	const ALLEGRO_COLOR BLACK = al_map_rgb(0, 0, 0);
	const ALLEGRO_COLOR BLACK_TRANSPARENT = al_map_rgba(0, 0, 0, 200);
	const ALLEGRO_COLOR PURPLE = al_map_rgb(128, 64, 212);

};
#endif
