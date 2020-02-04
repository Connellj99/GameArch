/*

A class to hold a chunk of memory used to display something
Data
• An Allegro bitmap
Functions
• Constructor(s)/destructor
• Accessors( height, width )



to friend:
friend class GraphicSystem;

needs
GB::GB 
filename
size,color
public al_bitmap that was created already

add a destructor for graphics buffer that
al_destroy_bitmap;

to do a destroy bitmap function
add a bool to each value in the constructors, where onl bitmap is false, then destroy everything that is false


al_set_target
al_get_target
*/


//al_bitmap
//sends pointers for bitmaps to allow sprite to draw

#include "GraphicsBuffer.h"
GraphicsBuffer::GraphicsBuffer()
{
	mStoredBitmap = NULL;
}

GraphicsBuffer::GraphicsBuffer(string bitmapFilePath)
{
	mStoredBitmap = al_load_bitmap(bitmapFilePath.c_str());
}

//create colored bitmap
GraphicsBuffer::GraphicsBuffer(int width, int height, Color colorOfScreen)
{
	mStoredBitmap = al_create_bitmap(width, height);
	ALLEGRO_BITMAP * temp = al_get_target_bitmap();
	al_set_target_bitmap(mStoredBitmap);
	al_clear_to_color(colorOfScreen.mCurrentColor);
	al_set_target_bitmap(temp);
}

//for backbuffer
GraphicsBuffer::GraphicsBuffer(ALLEGRO_BITMAP * newBitmap)
{
	mStoredBitmap = newBitmap;
}

//get the width of bitmap
int GraphicsBuffer::getHeight()
{
	return al_get_bitmap_height(mStoredBitmap);
}

//get the height of bitmap
int GraphicsBuffer::getWidth()
{
	return al_get_bitmap_width(mStoredBitmap);
}
