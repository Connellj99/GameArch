#include "GraphicsSystem.h"

#include "GraphicsBuffer.h"
#include "Sprite.h"
#include "Font.h"


GSystem::~GSystem()
{
	//Call cleanup on this and mpDisplayBuffer
	cleanup();
}

GSystem::GSystem()
{

}

GSystem::GSystem(int height, int width)
{
	mDisplayHeight = height;

	mDisplayWidth = width;

	
}

void GSystem::cleanup()
{
	al_destroy_display(mpDisplay); 
	delete mpDisplayBuffer;
}

void GSystem::initDisplay()
{
	if (!al_init())
	{
		cout << "error initting Allegro\n";
		return;
	}
	if (!al_init_image_addon())
	{
		cout << "error - Image Add-on not initted\n";
		return;
	}
	if (!al_init_font_addon())
	{
		cout << "error - Font Add-on not initted\n";
		return;
	}
	if (!al_init_ttf_addon())
	{
		cout << "error - TTF Add-on not initted\n";
		return;
	}
	if (!al_init_primitives_addon())
	{
		cout << "error - primitives Add-on not initted\n";
		return;
	}
	mpDisplay = al_create_display(mDisplayWidth, mDisplayHeight);

	mpDisplayBuffer = new GBuffer(mpDisplay);

}

void GSystem::draw(int locX, int locY, Sprite* target, float scale)
{
	al_draw_scaled_bitmap(target->getBuffer()->mpBitmap, 0.0, 0.0, al_get_bitmap_width(target->getBuffer()->mpBitmap), al_get_bitmap_height(target->getBuffer()->mpBitmap), locX, locY, al_get_bitmap_width(target->getBuffer()->mpBitmap)*scale, al_get_bitmap_height(target->getBuffer()->mpBitmap)*scale, 0);
}

void GSystem::draw(int locX, int locY, Sprite *target, float scale, int sizeH, int sizeW, int sourceX, int sourceY)
{
	al_draw_scaled_bitmap(target->getBuffer()->mpBitmap, sourceX, sourceY, sizeW, sizeH, locX, locY, sizeW*scale, sizeH*scale, 0);
}

void GSystem::draw(GBuffer *target, int locX, int locY, Sprite* targetSprite, float scale)
{
	ALLEGRO_BITMAP *temp = al_get_target_bitmap();
	al_set_target_bitmap(target->mpBitmap);
	al_draw_scaled_bitmap(targetSprite->getBuffer()->mpBitmap, 0.0, 0.0, al_get_bitmap_width(targetSprite->getBuffer()->mpBitmap), al_get_bitmap_height(targetSprite->getBuffer()->mpBitmap), locX, locY, al_get_bitmap_width(targetSprite->getBuffer()->mpBitmap)*scale, al_get_bitmap_height(targetSprite->getBuffer()->mpBitmap)*scale, 0);
	al_set_target_bitmap(temp);
}

void GSystem::writeText(int locX, int locY, Font* font, int r, int g, int b, string message)
{
	 ALLEGRO_COLOR color = al_map_rgb(r, g, b);

	al_draw_text(font->cour_font, color, locX, locY, 0, message.c_str());
}

void GSystem::writeText(GBuffer *target, int locX, int locY, Font* font, int r, int g, int b, string message)
{
	 ALLEGRO_COLOR color = al_map_rgb(r, g, b);

	ALLEGRO_BITMAP *temp = al_get_target_bitmap();
	al_set_target_bitmap(target->mpBitmap);
	al_draw_text(font->cour_font, color, locX, locY, 0, message.c_str());
	al_set_target_bitmap(temp);
}

void GSystem::saveBuffer(GBuffer target, string filename)
{
	al_save_bitmap(filename.c_str(), target.mpBitmap);

}

ALLEGRO_BITMAP* GSystem::getBackBuffer()
{
	return al_get_backbuffer(this->mpDisplay);
}

int GSystem::getHeight()
{
	return mDisplayHeight;
}

int GSystem::getWidth()
{
	return mDisplayWidth;
}

void GSystem::flipDispaly()
{
	al_flip_display();
}

void GSystem::waitForSeconds(double seconds)
{
	al_rest(seconds);
}