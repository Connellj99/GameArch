/*
Author: Amelia Payne
Class: EGP-310 <2>
Assignment: pa 3
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/

#include "GraphicsSystem.h"
#include <iostream>



//Init and cleanup
bool GraphicsSystem::init(int width, int height)
{
	std::cout << "Calling init on graphics system\n";
	bool isInit = true;
	if (!al_init())
	{
		isInit = false;
		std::cout << "error initting Allegro\n";
	}
	if (!al_init_image_addon())
	{
		isInit = false;
		std::cout << "error - Image Add-on not initted\n";

	}
	if (!al_init_font_addon())
	{
		isInit = false;
		std::cout << "error - Font Add-on not initted\n";

	}
	if (!al_init_ttf_addon())
	{
		isInit = false;
		std::cout << "error - TTF Add-on not initted\n";

	}
	if (!al_init_primitives_addon())
	{
		isInit = false;
		std::cout << "error - primitives Add-on not initted\n";

	}


	//Set the height and width to be positive
	mWidth = abs(width);
	mHeight = abs(height);
	
	//Make the display
	mpDisplay = al_create_display(mWidth, mHeight);

	//make a GraphicsBuffer with the back buffer
	mpBackbuffer = new GraphicsBuffer(al_get_target_bitmap(), true);

	//Make the display
	assert(mpDisplay);

	return isInit;
}




/*DRAW FUNCTIONS*/
void GraphicsSystem::draw(Sprite * image, int x, int y)
{
	al_draw_bitmap_region(image->getGraphicsBuffer()->getBitmap(), image->getSourceX(), image->getSourceY(), image->getWidth(), image->getHeight(), x, y, 0);
}


void GraphicsSystem::draw(Sprite * image, int x, int y, int scale)
{
	ALLEGRO_BITMAP * temp = al_create_sub_bitmap(image->getGraphicsBuffer()->getBitmap(), image->getSourceX(), image->getSourceY(), image->getWidth(), image->getHeight());
	al_draw_scaled_bitmap(temp, 0, 0, image->getWidth(), image->getHeight(), x, y, scale*image->getWidth(), image->getHeight()*scale, 0);
}

void GraphicsSystem::draw(Sprite * image, GraphicsBuffer * graphicsBuffer, int x, int y)
{
	al_set_target_bitmap(graphicsBuffer->getBitmap());
	al_draw_bitmap_region(image->getGraphicsBuffer()->getBitmap(), image->getSourceX(), image->getSourceY(), image->getWidth(), image->getHeight(), x, y, 0);
	al_set_target_bitmap(mpBackbuffer->getBitmap());
}


void GraphicsSystem::draw(Sprite * image, GraphicsBuffer * graphicsBuffer, int x, int y, int scale)
{
	al_set_target_bitmap(graphicsBuffer->getBitmap());
	ALLEGRO_BITMAP * temp = al_create_sub_bitmap(image->getGraphicsBuffer()->getBitmap(), image->getSourceX(), image->getSourceY(), image->getWidth(), image->getHeight());
	al_draw_scaled_bitmap(temp, 0, 0, image->getWidth(), image->getHeight(), x, y, scale*image->getWidth(), image->getHeight()*scale, 0);
	al_set_target_bitmap(mpBackbuffer->getBitmap());
}


/*DRAW GRAPHICS BUFFER*/
void GraphicsSystem::drawGraphicsBuffer(GraphicsBuffer * buffer, int x, int y) 
{
	al_draw_bitmap(buffer->getBitmap(), x, y, 0);

}

void GraphicsSystem::drawGraphicsBuffer(GraphicsBuffer * buffer, int x, int y, float scale)
{
	al_draw_scaled_bitmap(buffer->getBitmap(), 0, 0, buffer->getWidth(), buffer->getHeight(), x, y, buffer->getWidth()*scale, buffer->getHeight()*scale, 0);

}


void GraphicsSystem::drawGraphicsBuffer(GraphicsBuffer * buffer, GraphicsBuffer * background, int x, int y)
{

	al_set_target_bitmap(background->getBitmap());

	al_draw_bitmap(buffer->getBitmap(), 0, 0, 0);

	al_set_target_bitmap(mpBackbuffer->getBitmap());
}

void GraphicsSystem::drawGraphicsBuffer(GraphicsBuffer * buffer, GraphicsBuffer * background, int x, int y, float scale)
{
	al_set_target_bitmap(background->getBitmap());

	al_draw_scaled_bitmap(buffer->getBitmap(), 0, 0, buffer->getWidth(), buffer->getHeight(), x, y, buffer->getWidth()*scale, buffer->getHeight()*scale, 0);

	al_set_target_bitmap(mpBackbuffer->getBitmap());
}


/*TEXT DRAW FUNCTIONS*/
void GraphicsSystem::writeText(Font * font, int x, int y, Color color, std::string message)
{
	al_draw_text(font->getFont(), al_map_rgb(color.r, color.b, color.g), x, y, 0, message.c_str());
}


void GraphicsSystem::writeText(Font * font, GraphicsBuffer * graphicsBuffer, int x, int y, Color color, std::string message)
{

	al_set_target_bitmap(graphicsBuffer->getBitmap());

	auto temp = font->getFont();

	al_draw_text(font->getFont(), al_map_rgb(color.r, color.b, color.g), x, y, 0, message.c_str());

	al_set_target_bitmap(mpBackbuffer->getBitmap());
}


/*SAVE FUNCTIONS*/
void  GraphicsSystem::saveBuffer(GraphicsBuffer * graphicsBuffer, std::string fileName)
{
	al_save_bitmap(fileName.c_str(), graphicsBuffer->getBitmap());
}

void GraphicsSystem::saveBackBuffer(std::string fileName) 
{
	al_save_bitmap(fileName.c_str(), mpBackbuffer->getBitmap());
}


/*UTILITIES**/
void GraphicsSystem::flip()
{
	al_flip_display();
}

void GraphicsSystem::wait(float secounds) 
{
	al_rest(secounds);
}


//Clear the screen to a color
void GraphicsSystem::clearToColor(Color color)
{
	al_clear_to_color(al_map_rgb(color.r, color.b, color.g));
}

//destroy the display and backbuffer
void GraphicsSystem::cleanup()
{
	delete mpBackbuffer;
	al_destroy_display(mpDisplay);
}

GraphicsBuffer * GraphicsSystem::getBackBuffer()
{
	return mpBackbuffer;
}