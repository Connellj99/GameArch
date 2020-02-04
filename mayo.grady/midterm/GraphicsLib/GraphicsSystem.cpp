/*
Author: Grady Mayo
Class: EGP-310 <Section 01>
Assignment: Assignment 3
Certification of Authenticity: I certify that this assignment is entirely my own work.
*/

#include "GraphicsSystem.h"

GraphicsSystem::GraphicsSystem()
{
	
}

GraphicsSystem::~GraphicsSystem()
{
	cleanup();
}

void GraphicsSystem::init( int width, int height )
{
	//cout << "graphics system init" << endl;
	mIsInitted = true;
	if (!al_init())
	{
		cout << "error initting Allegro\n";
	}
	if (!al_init_image_addon())
	{
		cout << "error - Image Add-on not initted\n";
	}
	if (!al_init_font_addon())
	{
		cout << "error - Font Add-on not initted\n";
	}
	if (!al_init_ttf_addon())
	{
		cout << "error - TTF Add-on not initted\n";
	}
	if (!al_init_primitives_addon())
	{
		cout << "error - primitives Add-on not initted\n";
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
	mpDisplay = al_create_display( width, height );
	mpBackBuffer = new GraphicsBuffer( al_get_backbuffer( mpDisplay ));
}

void GraphicsSystem::cleanup()
{
	if (mIsInitted)
	{
		delete mpBackBuffer;
		al_destroy_display(mpDisplay);
	}
}

void GraphicsSystem::flip()
{
	al_flip_display();
}

void GraphicsSystem::draw( int targetLocX, int targetLocY, Sprite * sprite, float scale )
{
	int spriteWidth = al_get_bitmap_width(sprite->getGraphicsBuffer()->getBitmap());
	int spriteHeight = al_get_bitmap_height(sprite->getGraphicsBuffer()->getBitmap());
	al_draw_scaled_bitmap( sprite->getGraphicsBuffer()->getBitmap(), 0, 0, spriteWidth, spriteHeight, targetLocX, targetLocY, ( spriteWidth * scale ), ( spriteHeight * scale ), 0 );
}

void GraphicsSystem::draw(int targetLocX, int targetLocY, int spriteWidth, int spriteHeight, Sprite * sprite, float scale)
{
	al_draw_scaled_bitmap(sprite->getGraphicsBuffer()->getBitmap(), sprite->getLocX(), sprite->getLocY(), spriteWidth, spriteHeight, targetLocX, targetLocY, (spriteWidth * scale), (spriteHeight * scale), 0);
}

void GraphicsSystem::draw( GraphicsBuffer* pBuffer, int targetLocX, int targetLocY, Sprite* sprite, float scale )
{
	al_set_target_bitmap( pBuffer->getBitmap() );
	al_draw_scaled_bitmap( sprite->getGraphicsBuffer()->getBitmap(), sprite->getLocX(), sprite->getLocY(), sprite->getSpriteWidth(), sprite->getSpriteHeight(), targetLocX, targetLocY, ( sprite->getSpriteWidth() * scale ), ( sprite->getSpriteHeight() * scale ), 0 );
	al_set_target_bitmap( mpBackBuffer->getBitmap() );
}

void GraphicsSystem::draw( GraphicsBuffer* pBuffer, int targetLocX, int targetLocY )
{
	al_draw_bitmap(pBuffer->getBitmap(), targetLocX, targetLocY, 0);
}

void GraphicsSystem::draw( GraphicsBuffer* pBuffer, int targetLocX, int targetLocY, float scale)//, GraphicsBuffer* pColorBuffer)
{
	//al_set_target_bitmap(pColorBuffer->getBitmap());
	al_draw_scaled_bitmap(pBuffer->getBitmap(), 0, 0, pBuffer->getBitmapWidth(), pBuffer->getBitmapHeight(), targetLocX, targetLocY, (pBuffer->getBitmapWidth() * scale), (pBuffer->getBitmapHeight() * scale),  0);
	//al_set_target_bitmap(mpBackBuffer->getBitmap());
}

void GraphicsSystem::writeText( int targetLocX, int targetLocY, Font* pFont, Color& color, string text )
{
	ALLEGRO_COLOR textColor = al_map_rgb( color.getRValue(), color.getGValue(), color.getBValue() );
	al_draw_text( pFont->getFont(), textColor, targetLocX, targetLocY, ALLEGRO_ALIGN_LEFT, text.c_str() );
}

void GraphicsSystem::writeText( GraphicsBuffer* pBuffer, int targetLocX, int targetLocY, Font* pFont, Color& color, string text )
{
	al_set_target_bitmap( pBuffer->getBitmap() );
	ALLEGRO_COLOR textColor = al_map_rgb( color.getRValue(), color.getGValue(), color.getBValue() );
	al_draw_text( pFont->getFont(), textColor, targetLocX, targetLocY, ALLEGRO_ALIGN_LEFT, text.c_str() );
	al_set_target_bitmap(mpBackBuffer->getBitmap() );
}

void GraphicsSystem::saveBuffer( GraphicsBuffer* pBuffer, string filename )
{
	al_save_bitmap( filename.c_str(), pBuffer->getBitmap() );
}

void GraphicsSystem::saveBackBuffer(string filename)
{
	al_save_bitmap(filename.c_str(), mpBackBuffer->getBitmap());
}

void GraphicsSystem::rest(double time)
{
	al_rest(time);
}