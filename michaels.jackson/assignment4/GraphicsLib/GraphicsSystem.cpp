/*
Author:Jackson Michaels
Class: EGP-310-01
Assignment: Assignment 2
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/

#include "GraphicsSystem.h"



/*#################################
			GraphicsSystem
#################################*/

GraphicsSystem::GraphicsSystem() 
{
	
}

GraphicsSystem::~GraphicsSystem() 
{
	GraphicsSystem::cleanUp();
}

int GraphicsSystem::init(int wide, int tall)
{
	
	if (mInit == false) 
	{
		mDispWidth = wide;
		mDistHeight = tall;
		mDisplay = al_create_display(mDispWidth, mDistHeight);
		assert(mDisplay);
		al_clear_to_color(al_map_rgba_f(1.0, 1.0, 1.0, 1.0));

		mInit = true;
	}
	
	return 0;
}

void GraphicsSystem::flip() 
{
	al_flip_display();
}

int GraphicsSystem::draw(GraphicsBuffer* buffer, Sprite* sprite, int x, int y, float scale) 
{
	ALLEGRO_BITMAP* old = al_get_target_bitmap();
	al_set_target_bitmap(buffer->getBitMap());

	this->draw(sprite, x, y, scale);

	al_set_target_bitmap(old);
	return 0;
}

int GraphicsSystem::draw(Sprite* sprite, int x, int y, float scale) 
{
	al_draw_scaled_bitmap(sprite->getBuffer()->getBitMap(), sprite->getLocX(), sprite->getLocY(), sprite->getWidth(), sprite->getHeight(), x, y, sprite->getWidth()*scale, sprite->getHeight()*scale, 0);
	return 0;
}

int GraphicsSystem::writeText(string text, int x, int y, Font* font, Color* color) 
{
	al_draw_text(font->getFont(), color->getAllegroColor(), x, y, ALLEGRO_ALIGN_LEFT, text.c_str());
	return 0;
}

int GraphicsSystem::writeText(string text, GraphicsBuffer* buffer, int x, int y, Font* font, Color* color) 
{
	ALLEGRO_BITMAP* old = al_get_target_bitmap();
	al_set_target_bitmap(buffer->getBitMap());

	this->writeText(text, x, y, font, color);

	al_set_target_bitmap(old);
	return 0;
}

int GraphicsSystem::saveBuffer(string fileName, GraphicsBuffer* buffer) 
{
	
	ALLEGRO_BITMAP* map;

	if (buffer == NULL) 
	{
		map = al_get_target_bitmap();
	}
	else 
	{
		map = buffer->getBitMap();
	}

	al_save_bitmap(fileName.c_str(), map);
	
	return 0;
}


int GraphicsSystem::cleanUp() 
{
	if (mInit)
	{
		al_destroy_display(mDisplay);
		mInit = false;
	}
	return 0;
}


