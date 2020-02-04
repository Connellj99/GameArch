#include "GraphicsBuffer.h"

// This is the default constuctor for the class
GraphicsBuffer::GraphicsBuffer() 
{
	// Intiailize bitmap to a null value
	mIsBackBuffer = false;
	//mStoredBitmap = NULL;
}





// This constuctor takes the stored bitmap based 
// on an asset file path
GraphicsBuffer::GraphicsBuffer(string bitmapFilePath, string name)
{
	mName = name;
	mIsBackBuffer = false;
	//mStoredBitmap = al_load_bitmap(bitmapFilePath.c_str());
}





// This constructor takes the width and height and also the
// color to create a colored bitmap
GraphicsBuffer::GraphicsBuffer(int width, int height, Colors colorOfScreen, string name) 
{
	mName = name;

	mIsBackBuffer = false;
	//mStoredBitmap = al_create_bitmap(width, height);

	//// The following code swaps the target bitmaps to color the 
	//// created bitmap and then destroys the temporary bitmap pointer
	//ALLEGRO_BITMAP * temp = al_get_target_bitmap();
	//al_set_target_bitmap(mStoredBitmap);
	//al_clear_to_color(colorOfScreen.mCurrentColor);
	//al_set_target_bitmap(temp);
	//temp = NULL;
}





// This constructor creates a blank bitmap from only a given
// length and height
GraphicsBuffer::GraphicsBuffer(int length, int height, string name) 
{
	mName = name;
	mIsBackBuffer = false;
	//mStoredBitmap = al_create_bitmap(length, height);

	//ALLEGRO_BITMAP * temp = al_get_target_bitmap();
	//al_set_target_bitmap(mStoredBitmap);
	//al_set_target_bitmap(temp);
	//temp = NULL;
}




//
//// This constructor is exclusively used when the backbuffer
//// is stored from graphics system
//GraphicsBuffer::GraphicsBuffer(ALLEGRO_BITMAP * newBitmap, string name) 
//{
//	mName = name;
//	mIsBackBuffer = true;
//	mStoredBitmap = newBitmap; 
//}
//




// This function gets the height of the stored bitmap
int GraphicsBuffer::getHeight()
{
	return 0;
	//return al_get_bitmap_height(mStoredBitmap);
}





// This function gets the width of the stored bitmap
int GraphicsBuffer::getWidth() 
{
	return 0;
	//return al_get_bitmap_width(mStoredBitmap);
}





// This function destroys the stored allegro bitmap
GraphicsBuffer::~GraphicsBuffer()
{
	if (mIsBackBuffer == false) 
	{
		//al_destroy_bitmap(mStoredBitmap);
	}
}