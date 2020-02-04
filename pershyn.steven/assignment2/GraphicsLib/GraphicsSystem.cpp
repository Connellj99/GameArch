#include "GraphicsSystem.h"
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
#include "GraphicsBuffer.h"
#include "Font.h"

#include <PerformanceTracker.h>
#include <MemoryTracker.h>
using namespace std;

GraphicsSystem::GraphicsSystem()
{
	display = NULL;
}

GraphicsSystem::~GraphicsSystem()
{
	Cleanup();
}

int GraphicsSystem::Init(int height, int width)
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
	}
	if (!al_init_acodec_addon())
	{
		cout << "error - Audio Codec Add-on not initted\n";
	}
	if (!al_reserve_samples(1))
	{
		cout << "error - samples not reserved\n";
	}
	mWidth = width;
	mHeight = height;
	display = al_create_display(mWidth, mHeight);
	assert(display);
	mpBackBuffer = new GraphicsBuffer(al_get_target_bitmap(), true);
}

void GraphicsSystem::Cleanup()
{
	delete mpBackBuffer;
	mpBackBuffer = NULL;
	if (display != NULL)
	{
		al_destroy_display(display);
		display = NULL;
	}
}

int GraphicsSystem::getHeight()
{
	return mHeight;
}

int GraphicsSystem::getWidth()
{
	return mWidth;
}

void GraphicsSystem::Flip()
{
	al_flip_display();
}

void GraphicsSystem::Rest(float sleepTime)
{
	al_rest(sleepTime);
}

void GraphicsSystem::draw(int x, int y, Sprite* sprite, int scale)
{
	int sourceWidth = al_get_bitmap_width(sprite->getGraphicsBuffer()->getBitmap());
	int sourceHeight = al_get_bitmap_height(sprite->getGraphicsBuffer()->getBitmap());

	al_draw_scaled_bitmap(sprite->getGraphicsBuffer()->getBitmap(), 0, 0, sourceWidth, sourceHeight, x, y, sourceWidth*scale, sourceHeight*scale, 0);
}
void GraphicsSystem::draw(int x, int y, GraphicsBuffer* backBuffer, int scale)
{
	al_draw_bitmap(backBuffer->getBitmap(), x, y, 0);
}

void GraphicsSystem::draw(GraphicsBuffer * targetGraphicsBuffer, int x, int y, GraphicsBuffer * backBuffer, float scale)
{
	al_set_target_bitmap(targetGraphicsBuffer->getBitmap());
	al_draw_scaled_bitmap(backBuffer->getBitmap(), 0, 0, backBuffer->getWidth(), backBuffer->getHeight(), x, y, backBuffer->getWidth()*scale, backBuffer->getHeight()*scale, 0);
	al_set_target_bitmap(mpBackBuffer->getBitmap());
}

void GraphicsSystem::draw(GraphicsBuffer* targetGraphicsBuffer, int x, int y, Sprite* sprite, float scale)
{
	al_set_target_bitmap(targetGraphicsBuffer->getBitmap());
	al_draw_scaled_bitmap(sprite->getGraphicsBuffer()->getBitmap(), sprite->getX(), sprite->getY(), sprite->getWidth(), sprite->getHeight(), x * scale, y * scale, sprite->getWidth(), sprite->getHeight(), 0);
	al_set_target_bitmap(mpBackBuffer->getBitmap());
}

void GraphicsSystem::writeText(int X, int Y, Font* Font, Color color, string text)
{
	ALLEGRO_COLOR mColor = al_map_rgb(color.getR(), color.getG(), color.getB());
	al_draw_text(Font->getFont(), mColor, X, Y, ALLEGRO_ALIGN_LEFT, text.c_str());
}

void GraphicsSystem::writeText(GraphicsBuffer* targetBuffer, int X, int Y, Font* Font, Color color, std::string text)
{
	al_set_target_bitmap(targetBuffer->getBitmap());
	ALLEGRO_COLOR mColor = al_map_rgb(color.getR(), color.getG(), color.getB());
	al_draw_text(Font->getFont(), mColor, X, Y, ALLEGRO_ALIGN_LEFT, text.c_str());
	al_set_target_bitmap(mpBackBuffer->getBitmap());
}

void GraphicsSystem::saveBuffer(GraphicsBuffer *targetBuffer, string fileName)
{
	al_save_bitmap(fileName.c_str(), targetBuffer->getBitmap());
}

void GraphicsSystem::saveBackBuffer(string fileName)
{
	al_save_bitmap(fileName.c_str(), mpBackBuffer->getBitmap());
}


