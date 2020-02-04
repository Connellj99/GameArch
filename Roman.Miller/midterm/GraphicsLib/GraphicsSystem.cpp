#include "GraphicsSystem.h"
#include <allegro5/allegro_image.h>
using namespace std;
//set display to null
GraphicsSystem::GraphicsSystem()
{
	mpDisplay = NULL;
}

GraphicsSystem::~GraphicsSystem()
{
	cleanUp();

}
//destroy display if not null
void GraphicsSystem::cleanUp()
{
	if (mpDisplay != NULL)
	{

		al_destroy_display(mpDisplay);
		mpDisplay = nullptr;
	}
}
//initialize vaiables
void GraphicsSystem::init()
{
	al_init();
	al_init_image_addon();
	al_init_font_addon();
	al_init_ttf_addon();

	mpDisplay = al_create_display(mWidth, mHeight);
	al_clear_to_color(al_map_rgb(255, 255, 255));
}
//display to screen
void GraphicsSystem::flip()
{
	al_flip_display();
}

int GraphicsSystem::getWidth()
{
	return mWidth;
}

int GraphicsSystem::getHeight()
{
	return mHeight;
}

ALLEGRO_DISPLAY * GraphicsSystem::getBuffer()
{
	return mpDisplay;
}
//draw from location and sprite with scale default 1
void GraphicsSystem::draw(Vector2D vec, Sprite &sprite, float scale)
{
	al_draw_scaled_bitmap(sprite.getGraphicsBuffer()->mpBitmap, sprite.getLocation().getX(), sprite.getLocation().getX(),
		sprite.getDimensions().getX(), sprite.getDimensions().getY(),
		vec.getX(), vec.getY(), sprite.getDimensions().getX()*scale, sprite.getDimensions().getY()*scale, NULL);
}
//draw to buffer and location scale default 1
void GraphicsSystem::draw(GraphicsBuffer &buffer, Vector2D loc, Sprite &sprite, float scale)
{
	const auto initialBitmap = al_get_target_bitmap();
	al_set_target_bitmap(buffer.mpBitmap);

	al_draw_scaled_bitmap(sprite.getGraphicsBuffer()->mpBitmap, sprite.getLocation().getX(), sprite.getLocation().getX(),
		sprite.getDimensions().getX(), sprite.getDimensions().getY(),
		loc.getX(), loc.getY(), sprite.getDimensions().getX()*scale, sprite.getDimensions().getY()*scale, NULL);
	//al_save_bitmap("Temp.jpg", buffer.mpBitmap);
	al_set_target_bitmap(initialBitmap);
}
//write text from string of color
void GraphicsSystem::writeText(int locX, int locY, Font &font, Color color, string text)
{
	al_draw_text(font.getFont(), color.getColor(), locX, locY, ALLEGRO_ALIGN_CENTER, text.c_str());
}
//write text to buffer
void GraphicsSystem::writeText(GraphicsBuffer &buffer, int locX, int locY, Font &font, Color color, string text)
{
	const auto initialBitmap = al_get_target_bitmap();
	al_set_target_bitmap(buffer.mpBitmap);

	al_draw_text(font.getFont(), color.getColor(), locX, locY, ALLEGRO_ALIGN_CENTER, text.c_str());

	al_set_target_bitmap(initialBitmap);
}
//save specifc buffer
bool GraphicsSystem::saveBuffer(GraphicsBuffer &buffer, string filename)
{

	return al_save_bitmap(filename.c_str(), buffer.mpBitmap);
}
//save target to file
bool GraphicsSystem::saveBuffer(string filename)
{
	return al_save_bitmap(filename.c_str(), al_get_backbuffer(mpDisplay));
}
//wait X seconds
void GraphicsSystem::rest(float restTime)
{
	al_rest(restTime*1000);
}


