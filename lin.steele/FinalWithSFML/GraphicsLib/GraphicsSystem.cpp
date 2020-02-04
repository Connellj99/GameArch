#include "GraphicsSystem.h"


// This function is the default constructor
GraphicsSystem::GraphicsSystem()
{
}





// This function is the destructor
GraphicsSystem::~GraphicsSystem()
{

}





// This function initializes the display window with a 
// given width and height from the user
void GraphicsSystem::init(float width, float height) 
{

		window = new sf::Window;
		window->create(sf::VideoMode(800, 600), "My window");

		// run the program as long as the window is open
		//while (window->isOpen())
		//{
		//	// check all the window's events that were triggered since the last iteration of the loop
		//	sf::Event event;
		//	while (window->pollEvent(event))
		//	{
		//		// "close requested" event: we close the window
		//		if (event.type == sf::Event::Closed)
		//			window->close();
		//	}
		//}


	/*mCurrentDisplay = al_create_display(width, height);
	assert(mCurrentDisplay);

	mBackBuffer = new GraphicsBuffer(al_get_backbuffer(mCurrentDisplay), "Backbuffer");
	al_clear_to_color(al_map_rgb(255, 255, 255));*/
}





// This function cleans up and deletes the display
void GraphicsSystem::cleanup() 
{
	delete mBackBuffer;
	//al_destroy_display(mCurrentDisplay);
}





// This accesor function gets the height
float GraphicsSystem::getHeight() 
{
	return 0.0f;
	//return al_get_display_height(mCurrentDisplay);
}





// This accesor function gets the width
float GraphicsSystem::getWidth() 
{
	return 0.0f;
	//return al_get_display_width(mCurrentDisplay);
}





// This accesor function gets the back buffer
GraphicsBuffer  GraphicsSystem::getBackBuffer() 
{
	return *mBackBuffer;
}





// This function flips the display
void GraphicsSystem::flip() 
{
	window->display();
	//al_flip_display();
}





// This function draws a sprite to the current backbuffer / target bitmap and scales it appropriately
void GraphicsSystem::draw(Vector2 targetLoc, Sprite& sprite, float scale)
{
	//al_set_target_bitmap(mBackBuffer->mStoredBitmap);
	//al_draw_scaled_bitmap(sprite.getGraphicsBuffer()->mStoredBitmap, 0, 0, sprite.getWidth(), sprite.getHeight(), targetLoc.mX, targetLoc.mY, sprite.getWidth()*scale, sprite.getHeight()*scale, 0);
}





// This function draws a sprite to a chosen buffer and scales it appropriately
void GraphicsSystem::draw(GraphicsBuffer& targetGraphicsBuffer, Sprite& sprite, float scale)
{
	// The following code switches target bitmaps to the chosen bitmap to draw the sprite
	// and then switches it back to the previous target bitmap
	//al_set_target_bitmap(targetGraphicsBuffer.mStoredBitmap);
	//al_draw_scaled_bitmap(sprite.getGraphicsBuffer()->mStoredBitmap, 0, 0, sprite.getHeight(), sprite.getWidth(), sprite.getLoc().mX, sprite.getLoc().mY, sprite.getWidth()*scale, sprite.getHeight()*scale, 0);
	//al_set_target_bitmap(mBackBuffer->mStoredBitmap);
}





void GraphicsSystem::drawBackground(GraphicsBuffer& buffer, float scale) 
{
	//al_set_target_bitmap(mBackBuffer->mStoredBitmap);
	//al_draw_scaled_bitmap(buffer.mStoredBitmap, 0, 0, buffer.getWidth(), buffer.getHeight(), 0, 0, buffer.getWidth() * scale, buffer.getHeight() * scale, 0);
}





// This function draws a sprite from a given sprite sheet and places and scales it in a specific location
void GraphicsSystem::drawFromSpriteSheet(Vector2 targetImageLoc, Vector2 targetLoc, Sprite& sprite, Vector2 scale) 
{
	//al_draw_bitmap_region(sprite.getGraphicsBuffer()->mStoredBitmap, targetImageLoc.mX, targetImageLoc.mY, scale.mX, scale.mY, targetLoc.mX, targetLoc.mY,0);
}





// This function draws a sprite from a given sprite sheet and places and scales it in a specific location, 
// it is a static variable such that it can be called from animation to split up the sprite sheet
void GraphicsSystem::drawFromSpriteSheet(GraphicsBuffer& targetGraphicsBuffer, Vector2 targetImageLoc, Vector2 targetLoc, GraphicsBuffer& sprite, Vector2 scale) 
{
	//al_set_target_bitmap(targetGraphicsBuffer.mStoredBitmap);
	//al_draw_bitmap_region(sprite.mStoredBitmap, targetImageLoc.mX, targetImageLoc.mY, scale.mX, scale.mY, targetLoc.mX, targetLoc.mY, 0);
}





// This function draws text to a target location with a font, color, and message to the current graphics buffer / bitmaps
void GraphicsSystem::drawText(Vector2 targetLoc, Font& font, Colors color, string text)
{
	//al_draw_text(font.mCurrentFont, color.mCurrentColor, targetLoc.mX, targetLoc.mY, ALLEGRO_ALIGN_CENTER, text.c_str());
}





// This function draws text to a graphics buffer at a target location a font, color, and message
void GraphicsSystem::drawText(GraphicsBuffer& targetGraphicsBuffer, Vector2 targetLoc, Font& font, Colors color, string text)
{
	// The following code switches target bitmaps to the chosen bitmap to draw the text
	// and then switches it back to the previous target bitmap
	/*al_set_target_bitmap(targetGraphicsBuffer.mStoredBitmap);
	al_draw_text(font.mCurrentFont, color.mCurrentColor, targetLoc.mX, targetLoc.mY, ALLEGRO_ALIGN_CENTER, text.c_str());
	al_set_target_bitmap(mBackBuffer->mStoredBitmap);*/
}





// This function saves a given graphics buffer to as a file, whose name is determined by the user
void GraphicsSystem::saveBuffer(GraphicsBuffer& bufferToSave, string fileName)
{
	//al_save_bitmap(fileName.c_str(), bufferToSave.mStoredBitmap);
}





// This function closes the display window after a certain amount of time,
// which is given by the user
void GraphicsSystem::closeWindow(float secondsDelay) 
{
	//al_rest(secondsDelay);
	cleanup();
}