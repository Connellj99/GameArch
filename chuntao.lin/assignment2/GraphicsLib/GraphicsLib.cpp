#include "GraphicsLib.h"

//GraphicsSystem Functions--------------------------------------------------------------------------/
GraphicsSystem::GraphicsSystem()
{
	//stub
	mWidth = 0;
	mHeight = 0;

}

GraphicsSystem::~GraphicsSystem()
{
	//stub
	cleanGraphicSys();
}

int GraphicsSystem::initGraphicSys()
{
	//stub
	if (!al_init())
	{
		cout << "error initting Allegro\n";
		return 1;
	}
	
	mDisplay = al_create_display(mWidth,mHeight);
	assert(mDisplay);
	return 1;
}

void GraphicsSystem::cleanGraphicSys()
{
	//stub
	al_destroy_display(mDisplay);
	//delete mDisplay;
}

float GraphicsSystem::getGraphicSysHeight()
{
	//stub
	if (mHeight == 0)
	{
		mHeight = 600;
	}
	else
	{
		return mHeight;
	}
	return 0;
}

float GraphicsSystem::getGraphicSysWidth()
{
	//stub
	if (mWidth == 0)
	{
		mWidth = 800;
	}
	else
	{
		return mWidth;
	}
	return 0;
}

void GraphicsSystem::getBackBuffer()
{
	//stub

}

void GraphicsSystem::flipDisplay()
{
	//stub
}

void GraphicsSystem:: drawBackBuffer(float xPos, float yPos, ALLEGRO_BITMAP* sprite, float scale)
{
	//stub
}

void GraphicsSystem::drawToGivenBuffer(ALLEGRO_DISPLAY* targetBuffer, float xPos, float yPos, ALLEGRO_BITMAP* sprite, float scale)
{

}

void GraphicsSystem::writeTextBackBuffer(float xPos, float yPos, ALLEGRO_FONT* font, ALLEGRO_COLOR * color, string theText)
{
	//stub
}

/*void GraphicsSystem::writeTextGraphicBuffer(ALLEGRO_BITMAP * graphicBuffer, float xPos, float yPos, ALLEGRO_FONT * font, ALLEGRO_COLOR * color, string theText)
{
	//stub
}*/

/*void GraphicsSystem::saveBuffer(ALLEGRO_BITMAP * graphicBuffer, string outputFile)
{
	//stub
}*/

//Graphics Buffer Functions -------------------------------------------------------------------------------------/
GraphicsBuffer::GraphicsBuffer()
{
	mBuffHeight = 0;
	mBuffWidth = 0;
}

GraphicsBuffer::~GraphicsBuffer()
{
	al_destroy_bitmap(mBuffer);
}

void GraphicsBuffer::getBufferHeight()
{

	//stub
}

void GraphicsBuffer::getBufferWidth()
{
	//stub
}

//Sprite Functions -----------------------------------------------------------------------------------/
Sprite::Sprite()
{
	locX = 0;
	locY = 0;

	spriteWidth = 0;
	spriteHeight = 0;
}

Sprite::~Sprite()
{
	al_destroy_bitmap(graphicBufferBitmap);
	//stub
}

void Sprite::getSpriteLocation()
{
	locX = 800;
	locY = 600;
}

void Sprite::getSpriteHeight()
{
	
	//stub
}

void Sprite::getSpriteWidth()
{
	//stub
}

void Sprite::getGraphicBuffer()
{
	//stub
}

//Font Functions -------------------------------------------------------------------------------------/

Font::Font()
{
	//stub
}

Font::~Font()
{
	//stub
}

void Font::getSize()
{
	//stub
}
