/*
Conner Root
EGP 310-01
*/

#include "GraphicsSystem.h"

// Constructor
GraphicsSystem::GraphicsSystem()
{
	mpDisplay = nullptr;
	mpBackBuff = nullptr;
}

// Init / Cleanup
void GraphicsSystem::initGraphicsSystem(int w, int h)
{
	if (!mInited)
	{
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

	mpDisplay = al_create_display(w, h);
	mpBackBuff = new GraphicsBuffer();
	mInited = true;
	}
}

void GraphicsSystem::cleanup()
{
	if (mInited)
	{
		delete mpBackBuff;
		al_destroy_display(mpDisplay);

		mpDisplay = nullptr;
		mpBackBuff = nullptr;

		mInited = false;
	}
}

// Accessors
int GraphicsSystem::getWidth()
{
	return al_get_display_width(mpDisplay);
}
int GraphicsSystem::getHeight()
{
	return al_get_display_height(mpDisplay);
}

// Flip the display
void GraphicsSystem::flipDisplay()
{
	al_flip_display();
}

// Draw functions
void GraphicsSystem::draw(int xPos, int yPos, Sprite* sprite, float scale = 1.0)
{
	al_draw_scaled_bitmap(sprite->getBuffer()->getBitmap(), sprite->getXPos(), sprite->getYPos(), sprite->getWidth(), sprite->getHeight(), xPos, yPos, sprite->getWidth()*scale, sprite->getHeight()*scale, 0);
}
void GraphicsSystem::draw(int xPos, int yPos, Sprite* sprite, GraphicsBuffer* graphBuff, float scale = 1.0)
{
	ALLEGRO_BITMAP* initBitmap = al_get_target_bitmap();

	al_set_target_bitmap(graphBuff->getBitmap());

	draw(xPos, yPos, sprite, scale);

	al_set_target_bitmap(initBitmap);
}

// Write functions
void GraphicsSystem::writeText(int xPos, int yPos, Font* font, Color col, string str = "null")
{
	al_draw_text(font->getFont(), col.getColor(), xPos, yPos, 0, str.c_str());
}
void GraphicsSystem::writeText(int xPos, int yPos, Font* font, Color col, GraphicsBuffer* graphBuff, string str = "null")
{
	ALLEGRO_BITMAP* initBitmap = al_get_target_bitmap();

	al_set_target_bitmap(graphBuff->getBitmap());

	writeText(xPos, yPos, font, col, str);

	al_set_target_bitmap(initBitmap);
}

// Wait function
void GraphicsSystem::wait(float time)
{
	al_rest(time);
}

// Save Function
void GraphicsSystem::saveBuffer(GraphicsBuffer* pGraphBuff, string fileName)
{
}

// Destructor
GraphicsSystem::~GraphicsSystem()
{
	cleanup();
}
