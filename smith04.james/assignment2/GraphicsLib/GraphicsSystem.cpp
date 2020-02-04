#include "GraphicsSystem.h"
using namespace std;

GraphicsSystem::GraphicsSystem()
{

}

GraphicsSystem::~GraphicsSystem()
{
	
}

int GraphicsSystem::init()
{
	if (!al_init())
	{
		cout << "error initting Allegro\n";
		return 1;
	}
	if (!al_init_image_addon())
	{
		cout << "error - Image Add-on not initted\n";
		return 1;
	}
	if (!al_init_font_addon())
	{
		cout << "error - Font Add-on not initted\n";
		return 1;
	}
	if (!al_init_ttf_addon())
	{
		cout << "error - TTF Add-on not initted\n";
		return 1;
	}
	if (!al_init_primitives_addon())
	{
		cout << "error - primitives Add-on not initted\n";
		return 1;
	}
	if (!al_install_audio())
	{
		cout << "error - Audio Add-on not initted\n";
		return 1;
	}
	if (!al_init_acodec_addon())
	{
		cout << "error - Audio Codec Add-on not initted\n";
		return 1;
	}
	if (!al_reserve_samples(1))
	{
		cout << "error - samples not reserved\n";
		return 1;
	}

	mpDisplay = al_create_display(dispWidth, dispHeight);
}

void GraphicsSystem::cleanup()
{
	al_destroy_display(mpDisplay);
	delete mpBackBuffer;

	al_shutdown_font_addon();
	al_shutdown_image_addon();
	al_shutdown_primitives_addon();
	al_shutdown_ttf_addon();
	al_uninstall_audio();
	//al_uninstall_system();
}

float GraphicsSystem::getHeight()
{
	return dispHeight;
}

float GraphicsSystem::getWidth()
{
	return dispWidth;
}

GraphicsBuffer* GraphicsSystem::getBack()
{
	mpBackBuffer = new GraphicsBuffer(al_get_backbuffer(mpDisplay));
	return mpBackBuffer;
}

void GraphicsSystem::flip()
{
	al_flip_display();
}

void GraphicsSystem::draw(float x, float y, Sprite* spr, float s)
{
	al_draw_scaled_bitmap(spr->getBuffer()->getBitMap(), spr->getX(), spr->getY(), 
		spr->getBuffer()->getWidth(), spr->getBuffer()->getHeight(), x, y, spr->getBuffer()->getWidth() * s, spr->getBuffer()->getHeight() * s, 0);
}

void GraphicsSystem::draw(GraphicsBuffer* target, float x, float y, Sprite* spr, float s)
{
	ALLEGRO_BITMAP* temp = al_get_target_bitmap();
	al_set_target_bitmap(target->getBitMap());
	draw(x, y, spr, s);
	al_set_target_bitmap(temp);
}

void GraphicsSystem::writeText(float x, float y, Font* f, Color c, const char* text)
{
	al_draw_text(f->getFont(), c.getColor(), x, y, 0, text);
}

void GraphicsSystem::writeText(GraphicsBuffer* target, float x, float y, Font* f, Color c, const char* text)
{
	ALLEGRO_BITMAP* temp = al_get_target_bitmap();
	al_set_target_bitmap(target->getBitMap());
	writeText(x, y, f, c, text);
	al_set_target_bitmap(temp);
}

void GraphicsSystem::saveBuffer(GraphicsBuffer* target, char* text)
{
	al_save_bitmap(text, target->getBitMap());
}