#include "GraphicsBuffer.h"

//constructors
GraphicsBuffer::GraphicsBuffer(){
	mBitmap = nullptr;
}

GraphicsBuffer::GraphicsBuffer(string fileName){
	mBitmap = al_load_bitmap(fileName.c_str());
	assert(mBitmap);
}

GraphicsBuffer::GraphicsBuffer(int width, int height, Color col){
	mBitmap = al_create_bitmap(width, height);
	assert(mBitmap);

	ALLEGRO_BITMAP* initBitmap = al_get_target_bitmap();

	al_set_target_bitmap(mBitmap);

	al_clear_to_color(col.getColor());

	al_set_target_bitmap(initBitmap);
}

//getters
ALLEGRO_BITMAP* GraphicsBuffer::getBitmap() {
	return mBitmap;
}

int GraphicsBuffer::getWidth(){
	return al_get_bitmap_width(mBitmap);
}

int GraphicsBuffer::getHeight(){
	return al_get_bitmap_height(mBitmap);
}

//destructor
GraphicsBuffer::~GraphicsBuffer(){
	al_destroy_bitmap(mBitmap);
}