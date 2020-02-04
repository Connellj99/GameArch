#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include <iostream>

#include "GraphicsSystem.h"

//constuctor call
GraphicsSystem::GraphicsSystem(){
	display = nullptr;
}

//making sure everything is initialized
void GraphicsSystem::initGraphicsSystem(int width, int height){
	if (!al_init()){
		cout << "error initting Allegro\n";
	}
	if (!al_init_image_addon()){
		cout << "error - Image Add-on not initted\n";
	}
	if (!al_init_font_addon()){
		cout << "error - Font Add-on not initted\n";
	}
	if (!al_init_ttf_addon()){
		cout << "error - TTF Add-on not initted\n";
	}
	if (!al_init_primitives_addon()){
		cout << "error - primitives Add-on not initted\n";
	}
	if (!al_install_audio()){
		cout << "error - Audio Add-on not initted\n";
	}
	if (!al_init_acodec_addon()){
		cout << "error - Audio Codec Add-on not initted\n";
	}
	if (!al_reserve_samples(1)){
		cout << "error - samples not reserved\n";
	}

	display = al_create_display(width, height);
	al_clear_to_color(al_map_rgb(255, 0, 0));
}

//getters
int GraphicsSystem::getWidth(){
	return al_get_display_width(display);
}

int GraphicsSystem::getHeight(){
	return al_get_display_height(display);
}

//flip the display to show whats in the back buffer
void GraphicsSystem::flipDisplay(){
	al_flip_display();
}

//draw function to draw to current buffer
void GraphicsSystem::draw(int LOC_X, int LOC_Y, Sprite sprite, float scale = 1.0){
	al_draw_scaled_bitmap(sprite.getBuffer()->getBitmap(), sprite.getLocX(), sprite.getLocY(), sprite.getWidth(), sprite.getHeight(), LOC_X, LOC_Y, sprite.getWidth()*scale, sprite.getHeight()*scale, NULL);
}

//function to write text
void GraphicsSystem::writeText(int LOC_X, int LOC_Y, Font font, Color textCol, string text = "null") {
	al_draw_text(font.getFont(), textCol.getColor(), LOC_X, LOC_Y, NULL, text.c_str());
}

//draw function to draw to specified buffer
void GraphicsSystem::draw(GraphicsBuffer* buff, int LOC_X, int LOC_Y, Sprite sprite, float scale = 1.0){
	
	//create the bitmap
	ALLEGRO_BITMAP* initBitmap = al_get_target_bitmap();

	//set the target bitmap
	al_set_target_bitmap(buff->getBitmap());

	//draw the sprite
	draw(LOC_X, LOC_Y, sprite, scale);

	al_set_target_bitmap(initBitmap);
}

//function to write text to a specified buffer
void GraphicsSystem::writeText(GraphicsBuffer* buff, int LOC_X, int LOC_Y, Font font, Color col, string str = "null"){
	ALLEGRO_BITMAP* initBitmap = al_get_target_bitmap();

	al_set_target_bitmap(buff->getBitmap());

	writeText(LOC_X, LOC_Y, font, col, str);

	al_set_target_bitmap(initBitmap);
}

//destructor
GraphicsSystem::~GraphicsSystem(){
	al_destroy_display(display);
}