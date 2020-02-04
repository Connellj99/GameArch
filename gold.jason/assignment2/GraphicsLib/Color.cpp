#include "Color.h"

//constructors
Color::Color(){
	mColor = al_map_rgb(0, 0, 0);
}
Color::Color(int red, int green, int blue){
	mColor = al_map_rgb(red, green, blue);
}
Color::Color(int red, int green, int blue, int alpha){
	mColor = al_map_rgba(red, green, blue, alpha);
}

//getters
ALLEGRO_COLOR Color::getColor(){
	return mColor;
}

//destructor
Color::~Color(){
	//delete mColor;
}