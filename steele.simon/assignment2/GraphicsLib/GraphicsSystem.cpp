#include "GraphicsSystem.h"



// This function is the default constructor
GraphicsSystem::GraphicsSystem()
{
	mBackBuffer = new GraphicsBuffer();
}





// This function is the destructor
GraphicsSystem::~GraphicsSystem()
{

}





// This function initializes the display window with a 
// given width and height from the user
void GraphicsSystem::init(float width, float height) 
{
	if (!al_init())
	{
		cout << "error initting Allegro\n";
		//return 1;
	}
	if (!al_init_image_addon())
	{
		cout << "error - Image Add-on not initted\n";
		//return 1;
	}
	if (!al_init_ttf_addon())
	{
		cout << "error - TTF Add-on not initted\n";
		//return 1;
	}
	if (!al_init_primitives_addon())
	{
		cout << "error - primitives Add-on not initted\n";
		//return 1;
	}
	if (!al_install_audio())
	{
		cout << "error - Audio Add-on not initted\n";
		//return 1;
	}
	if (!al_init_font_addon())
	{
		cout << "error - Font Add-on not initted\n";
	}
	if (!al_init_acodec_addon())
	{
		cout << "error - Audio Codec Add-on not initted\n";
		//return 1;
	}
	if (!al_reserve_samples(1))
	{
		cout << "error - samples not reserved\n";
		//return 1;
	}


	mCurrentDisplay = al_create_display(width, height);
	assert(mCurrentDisplay);

	mBackBuffer = new GraphicsBuffer(al_get_backbuffer(mCurrentDisplay));
	al_clear_to_color(al_map_rgb(255, 255, 255));
}





// This function cleans up and deletes the display
void GraphicsSystem::cleanup() 
{
	delete mBackBuffer;
	al_destroy_display(mCurrentDisplay);
}





// This accesor function gets the height
float GraphicsSystem::getHeight() 
{
	return al_get_display_height(mCurrentDisplay);
}





// This accesor function gets the width
float GraphicsSystem::getWidth() 
{
	return al_get_display_width(mCurrentDisplay);
}





// This accesor function gets the back buffer
GraphicsBuffer  GraphicsSystem::getBackBuffer() 
{
	return *mBackBuffer;
}





// This function flips the display
void GraphicsSystem::flip() 
{
	al_flip_display();
}





// This function draws a sprite to the current backbuffer / target bitmap and scales it appropriately
void GraphicsSystem::draw(Vector2 targetLoc, Sprite& sprite, float scale)
{
	al_draw_scaled_bitmap(sprite.getGraphicsBuffer()->mStoredBitmap, 0, 0, sprite.getHeight(), sprite.getWidth(), targetLoc.mX, targetLoc.mY, sprite.getWidth()*scale, sprite.getHeight()*scale, 0);
}





// This function draws a sprite to a chosen buffer and scales it appropriately
void GraphicsSystem::draw(GraphicsBuffer& targetGraphicsBuffer, Sprite& sprite, float scale)
{
	// The following code switches target bitmaps to the chosen bitmap to draw the sprite
	// and then switches it back to the previous target bitmap
	al_set_target_bitmap(targetGraphicsBuffer.mStoredBitmap);
	al_draw_scaled_bitmap(sprite.getGraphicsBuffer()->mStoredBitmap, 0, 0, sprite.getHeight(), sprite.getWidth(), sprite.getLoc().mX, sprite.getLoc().mY, sprite.getWidth()*scale, sprite.getHeight()*scale, 0);
	al_set_target_bitmap(mBackBuffer->mStoredBitmap);
}





// This function draws a sprite from a given sprite sheet and places and scales it in a specific location
void GraphicsSystem::drawFromSpriteSheet(Vector2 targetImageLoc, Vector2 targetLoc, Sprite& sprite, Vector2 scale) 
{
	al_draw_bitmap_region(sprite.getGraphicsBuffer()->mStoredBitmap, targetImageLoc.mX, targetImageLoc.mY, scale.mX, scale.mY, targetLoc.mX, targetLoc.mY,0);
}





// This function draws text to a target location with a font, color, and message to the current graphics buffer / bitmaps
void GraphicsSystem::drawText(Vector2 targetLoc, Font& font, Color color, string text)
{
	al_draw_text(font.mCurrentFont, al_map_rgb(0,0,0), targetLoc.mX, targetLoc.mY, ALLEGRO_ALIGN_LEFT, text.c_str());
}





// This function draws text to a graphics buffer at a target location a font, color, and message
void GraphicsSystem::drawText(GraphicsBuffer& targetGraphicsBuffer, Vector2 targetLoc, Font& font, Color color, string text)
{
	// The following code switches target bitmaps to the chosen bitmap to draw the text
	// and then switches it back to the previous target bitmap
	al_set_target_bitmap(targetGraphicsBuffer.mStoredBitmap);
	al_draw_text(font.mCurrentFont, color.mCurrentColor, targetLoc.mX, targetLoc.mY, ALLEGRO_ALIGN_LEFT, text.c_str());
	al_set_target_bitmap(mBackBuffer->mStoredBitmap);
}





// This function saves a given graphics buffer to as a file, whose name is determined by the user
void GraphicsSystem::saveBuffer(GraphicsBuffer& bufferToSave, string fileName)
{
	al_save_bitmap(fileName.c_str(), bufferToSave.mStoredBitmap);
}





// This function closes the display window after a certain amount of time,
// which is given by the user
void GraphicsSystem::closeWindow(float secondsDelay) 
{
	al_rest(secondsDelay);
	cleanup();
}