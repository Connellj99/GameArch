#include "GraphicsSystem.h"



GraphicsSystem::GraphicsSystem()
{

}

GraphicsSystem::~GraphicsSystem()
{
	cleanup();
}
//graphics system initializer, creates display window and initiates add ons
void GraphicsSystem::init(int width, int height)
{
	
	if (!al_init_image_addon())
	{
		std::cout << "error - Image Add-on not initted\n";
	}
	if (!al_init_font_addon())
	{
		std::cout << "error - Font Add-on not initted\n";
	}
	if (!al_init_ttf_addon())
	{
		std::cout << "error - TTF Add-on not initted\n";
	}
	if (!al_init_primitives_addon())
	{
		std::cout << "error - primitives Add-on not initted\n";
	}
	if (!al_install_audio())
	{
		std::cout << "error - Audio Add-on not initted\n";
	}
	if (!al_init_acodec_addon())
	{
		std::cout << "error - Audio Codec Add-on not initted\n";
	}
	if (!al_reserve_samples(1))
	{
		std::cout << "error - samples not reserved\n";
	}

	mWidth = width;
	mHeight = height;

	mpDisplayWindow = al_create_display(mWidth, mHeight);
	mpBackBuffer = new GraphicsBuffer(al_get_backbuffer(mpDisplayWindow));
}

//destroys program properly
void GraphicsSystem::cleanup() 
{
	delete mpBackBuffer;
	al_destroy_display(mpDisplayWindow);
}

//accessors
int GraphicsSystem::getHeight() 
{
	return mHeight;
}

int GraphicsSystem::getWidth() 
{
	return mWidth;
}

GraphicsBuffer* GraphicsSystem::getBackBuffer() 
{
	return mpBackBuffer;
}

//flip display function
void GraphicsSystem::flipDisplay() 
{
	al_flip_display();
}

//draw functions
void GraphicsSystem::draw(float targetLocX, float targetLocY, Sprite* pSprite, float scale)
{ 
	//int sourceWidth = al_get_bitmap_width(pSprite->getGraphicsBuffer()->getBitmap());
	//int sourceHeight = al_get_bitmap_height(pSprite->getGraphicsBuffer()->getBitmap());

	int sourceWidth = pSprite->getWidth();
	int sourceHeight = pSprite->getHeight();

	al_draw_scaled_bitmap(pSprite->getGraphicsBuffer()->getBitmap(), pSprite->getSourceLocX(), pSprite->getSourceLocY(), sourceWidth, sourceHeight, targetLocX, targetLocY, sourceWidth*scale, sourceHeight*scale, 0);
	
}

void GraphicsSystem::draw(GraphicsBuffer* targetBuffer, Vector2D location, Sprite* pSprite, float scale)
{
	al_set_target_bitmap(targetBuffer->getBitmap());

	al_draw_scaled_bitmap(pSprite->getGraphicsBuffer()->getBitmap(), pSprite->getSourceLocX(), pSprite->getSourceLocY(), pSprite->getWidth(), pSprite->getHeight(), location.getX() * scale, location.getY() * scale, pSprite->getWidth(), pSprite->getHeight(), 0);
	al_set_target_bitmap(mpBackBuffer->getBitmap());
}

void GraphicsSystem::draw(float targetLocX, float targetLocY, GraphicsBuffer* pBackBuffer, float scale)
{
	al_draw_bitmap(pBackBuffer->getBitmap(), targetLocX, targetLocY, 0);
}

void GraphicsSystem::draw(GraphicsBuffer* pTargetBuffer, float targetLocX, float targetLocY, GraphicsBuffer* pBackBuffer, float scale)
{
	al_set_target_bitmap(pTargetBuffer->getBitmap());
	al_draw_scaled_bitmap(pBackBuffer->getBitmap(), 0, 0, pBackBuffer->getWidth(), pBackBuffer->getHeight(), targetLocX, targetLocY, pBackBuffer->getWidth()*scale, pBackBuffer->getHeight()*scale, 0);
	al_set_target_bitmap(mpBackBuffer->getBitmap());
}

//create text functions
void GraphicsSystem::writeText(float targetLocX, float targetLocY, Font* pFont, Color &color, std::string text)
{
	ALLEGRO_COLOR mColor = al_map_rgb(color.getR(), color.getG(), color.getB());
	al_draw_text(pFont->getFont(), mColor, targetLocX, targetLocY, ALLEGRO_ALIGN_LEFT, text.c_str());
}

void GraphicsSystem::writeText(GraphicsBuffer* pTargetBuffer, float targetLocX, float targetLocY, Font* pFont, Color &color, std::string text)
{
	al_set_target_bitmap(pTargetBuffer->getBitmap());
	ALLEGRO_COLOR mColor = al_map_rgb(color.getR(), color.getG(), color.getB());
	al_draw_text(pFont->getFont(), mColor, targetLocX, targetLocY, ALLEGRO_ALIGN_LEFT, text.c_str());
	al_set_target_bitmap(mpBackBuffer->getBitmap());
}

//save specified buffer
void GraphicsSystem::saveBuffer(GraphicsBuffer *pTargetBuffer, std::string fileName)
{
	al_save_bitmap(fileName.c_str(), pTargetBuffer->getBitmap());
}

//save back buffer
void GraphicsSystem::saveBackBuffer(std::string fileName) 
{
	al_save_bitmap(fileName.c_str(), mpBackBuffer->getBitmap());
}

//close program after x amount of time
void GraphicsSystem::rest(double sleepTime) 
{
	al_rest(sleepTime);
}