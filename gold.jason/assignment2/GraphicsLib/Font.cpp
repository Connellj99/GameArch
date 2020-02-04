#include "Font.h"

//constructors to make a font
Font::Font() {
	mFont = nullptr;
}
Font::Font(string path, int size){
	fontSize = size;
	mFont = al_load_ttf_font(path.c_str(), size, NULL);
	assert(mFont);
}

//getters to get the size and actual font
int Font::getSize(){
	return fontSize;
}

ALLEGRO_FONT* Font::getFont(){
	return mFont;
}

//destructor
/*
Font::~Font(){
	al_destroy_font(mFont);
}; */