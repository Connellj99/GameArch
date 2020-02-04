/*

The class which creates and maintains the display
Data
• The display

Functions
• Constructor/Destructor
• Init/Cleanup
• Accessors (height, width, back buffer)
• Flip – call the al_flip function to display what is in the Back Buffer

Could be static or non-static functions (up to you):
• Draw (target loc, Sprite, scale  default to 1.0  ) - draw to current backbuffer
• Draw(target graphics buffer, target loc, Sprite, scale  default to 1.0 ) - draw to given

GraphicsBuffer
• WriteText(target loc, Font, Color, text) – write to current backbuffer
• WriteText(target graphics buffer, target loc, Font, Color, text) – write to given GraphicsBuffer
• SaveBuffer(buffer to save, filename) – save the contents of a GraphicsBuffer to a file

needs backbuffer


make GraphicsSystem a friend of GraphicsBuffer

*/


//al_display
//drawing and writing
/*pseudo
draw()
{

al_draw_bitmap(sprite.getBuffer);

}


*/

#include "GraphicsSystem.h"

GraphicsSystem::GraphicsSystem()
{

	mBackBuffer = new GraphicsBuffer();
}

GraphicsSystem::~GraphicsSystem()
{
}

void GraphicsSystem::cleanup()
{
	delete mBackBuffer;
	al_destroy_display(currentDisplay);
}

//gets height
float GraphicsSystem::getHeight()
{
	return al_get_display_height(currentDisplay);
}

//gets width
float GraphicsSystem::getWidth()
{
	return al_get_display_width(currentDisplay);
}

// gets the back buffer
GraphicsBuffer  GraphicsSystem::getBackBuffer()
{
	return *mBackBuffer;
}

// draw to current backbuffer
void GraphicsSystem::draw(Vector2 targetLoc, Sprite sprite, float scale)
{
	al_draw_scaled_bitmap(sprite.getGraphicsBuffer().mStoredBitmap, 0, 0, sprite.getLength(), sprite.getWidth(), targetLoc.sX, targetLoc.sY, sprite.getWidth()*scale, sprite.getLength()*scale, 0);
}

//- draw to given
void GraphicsSystem::draw(GraphicsBuffer targetGraphicsBuffer, Sprite sprite, float scale)
{
	ALLEGRO_BITMAP * temp = al_get_target_bitmap();
	al_set_target_bitmap(targetGraphicsBuffer.mStoredBitmap);
	al_draw_scaled_bitmap(sprite.getGraphicsBuffer().mStoredBitmap, 0, 0, sprite.getLength(), sprite.getWidth(), sprite.getLoc().sX, sprite.getLoc().sY, sprite.getWidth()*scale, sprite.getLength()*scale, 0);
	al_set_target_bitmap(temp);
}

//write to current backbuffer
void GraphicsSystem::writeText(Vector2 targetLoc, Font font, Color color, string text)
{
	al_draw_text(font.mCurrentFont, al_map_rgb(0, 0, 0), targetLoc.sX, targetLoc.sY, ALLEGRO_ALIGN_LEFT, text.c_str());
}

//write to given GraphicsBuffer
void GraphicsSystem::writeText(GraphicsBuffer targetGraphicsBuffer, Vector2 targetLoc, Font font, Color color, string text)
{
	ALLEGRO_BITMAP * temp = al_get_target_bitmap();
	al_set_target_bitmap(targetGraphicsBuffer.mStoredBitmap);
	al_draw_text(font.mCurrentFont, color.mCurrentColor, targetLoc.sX, targetLoc.sY, ALLEGRO_ALIGN_LEFT, text.c_str());
	al_set_target_bitmap(temp);
}

//save the contents of a GraphicsBuffer to a file
void GraphicsSystem::saveBuffer(GraphicsBuffer bufferToSave, string fileName)
{
	al_save_bitmap(fileName.c_str(), bufferToSave.mStoredBitmap);
}

