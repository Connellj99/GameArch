#include "Sprites.h"
#include "Colors.h"


//Sprite Functions -----------------------------------------------------------------------------------/
Sprite::Sprite()
{
	mLocX = 0;
	mLocY = 0;

	mSpriteWidth = 0;
	mSpriteHeight = 0;
}

Sprite::~Sprite()
{
	//stub, supposed to check if the bitmap is in use, if so, do nothing, but if it isn't then destroy...
	if (mBitMapInUse == true)
	{

	}
	else
	{
		al_destroy_bitmap(graphicSpriteBitmap);
	}
}

void Sprite::setSpriteSteps(GraphicsBuffer& buffer)
{
	//initialize the allegro addons
	if (!al_init())
	{
		std::cout << "error initting Allegro\n";
		system("pause");
		return;
	}
	if (!al_init_image_addon())
	{
		std::cout << "error initting image add-on\n";
		system("pause");
		return;
	}
	if (!al_install_audio())
	{
		std::cout << "error initting audio\n";
		system("pause");
		return;
	}
	if (!al_reserve_samples(1))
	{
		std::cout << "error initting audio\n";
		system("pause");
		return;
	}
	if (!al_init_font_addon())
	{
		std::cout << "error initting font\n";
		system("pause");
		return;
	}
	if (!al_init_ttf_addon())
	{
		std::cout << "error initting font\n";
		system("pause");
		return;
	}
	if (!al_init_acodec_addon())
	{
		std::cout<< "error initting acodec\n";
		system("pause");
		return;
	}
	if (!al_init_primitives_addon())
	{
		std::cout << "error initting primitives\n";
		system("pause");
		return;
	}

	//set the graphicSpriteBitmap pointer to the loaded bitmap of the steps
	graphicSpriteBitmap = al_load_bitmap((ASSET_PATH + STEPS_FILENAME).c_str());
	buffer.setBuffer(graphicSpriteBitmap);
	buffer.mBufferSprite = graphicSpriteBitmap;

	//check if is valid
	assert(graphicSpriteBitmap);

	return;
}

void Sprite::setSpriteSmurfDean(GraphicsBuffer & buffer)
{
	//initialize the allegro addons
	if (!al_init())
	{
		std::cout << "error initting Allegro\n";
		system("pause");
		return;
	}
	if (!al_init_image_addon())
	{
		std::cout << "error initting image add-on\n";
		system("pause");
		return;
	}
	if (!al_install_audio())
	{
		std::cout << "error initting audio\n";
		system("pause");
		return;
	}
	if (!al_reserve_samples(1))
	{
		std::cout << "error initting audio\n";
		system("pause");
		return;
	}
	if (!al_init_font_addon())
	{
		std::cout << "error initting font\n";
		system("pause");
		return;
	}
	if (!al_init_ttf_addon())
	{
		std::cout << "error initting font\n";
		system("pause");
		return;
	}
	if (!al_init_acodec_addon())
	{
		std::cout << "error initting acodec\n";
		system("pause");
		return;
	}
	if (!al_init_primitives_addon())
	{
		std::cout << "error initting primitives\n";
		system("pause");
		return;
	}

	//set the graphicSpriteBitmap pointer to the loaded bitmap of the steps
	graphicSpriteBitmap = al_load_bitmap((ASSET_PATH + DEAN_FILENAME).c_str());
	buffer.setBuffer(graphicSpriteBitmap);
	buffer.mBufferSprite = graphicSpriteBitmap;

	//check if is valid
	assert(graphicSpriteBitmap);

	return;
}

void Sprite::setSpriteSourceLocation(GraphicsBuffer& buffer)
{
	mLocX = buffer.getBufferWidth()/4;//sets the positions to the sprites member positions
	mLocY = buffer.getBufferHeight()/4;
}

float Sprite::getSpriteSourceLocationX()
{
	return mLocX;
}

float Sprite::getSpriteSourceLocationY()
{
	return mLocY;
}

void Sprite::setSpriteHeight()
{
	//sets the mSpriteHeight variable to the graphicSPriteBitmap's height
	mSpriteHeight = al_get_bitmap_height(graphicSpriteBitmap);
}

void Sprite::setSpriteWidth()
{
	//sets the mSpriteWidth variable to the graphicSPriteBitmap's width
	mSpriteWidth = al_get_bitmap_width(graphicSpriteBitmap);
}

float Sprite::getSpriteHeight()
{
	return mSpriteHeight;
}

float Sprite::getSpriteWidth()
{
	return mSpriteWidth;
}

int Sprite::getNumOfSmurfs()
{
	return mNumSmurfSprites;
}

int Sprite::getNumOfSmurfsX()
{
	return mNumSmurfsX;
}

int Sprite::getNumOfSmurfsY()
{
	return mNumSmurfsY;
}

void Sprite::addNumOfSmurfs()
{
	mNumSmurfSprites++;
}

void Sprite::addNumOfSmurfsX()
{
	mNumSmurfsX++;
}

void Sprite::addNumOfSmurfsY()
{
	mNumSmurfsY++;
}

void Sprite::resetNumOfSmurfsX()
{
	mNumSmurfsX = 0;
}

void Sprite::resetNumOfSmurfsY()
{
	mNumSmurfsY = 0;
}

GraphicsBuffer* Sprite::getGraphicBuffer()
{
	//returns the pointer to the class object
	return &graphicBuffObject;
}