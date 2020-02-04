/*
Author:Jackson Michaels
Class: EGP-310-01
Assignment: Assignment 2
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/

#include "GraphicsLib.h"


/*#################################
			GraphicsSystem
#################################*/

GraphicsSystem::GraphicsSystem(int wide, int tall) {
	mDispWidth = wide;
	mDistHeight = tall;
}

GraphicsSystem::~GraphicsSystem() {
	GraphicsSystem::cleanUp();
}

int GraphicsSystem::init() {
	if (!al_init())
	{
		cout << "error initting Allegro\n";
		return 1;
	}
	if (!al_init_image_addon())
	{
		cout << "error - Image Add-on not initted\n";
		return 1;
	}
	if (!al_init_font_addon())
	{
		cout << "error - Font Add-on not initted\n";
		return 1;
	}
	if (!al_init_ttf_addon())
	{
		cout << "error - TTF Add-on not initted\n";
		return 1;
	}
	if (!al_init_primitives_addon())
	{
		cout << "error - primitives Add-on not initted\n";
		return 1;
	}
	if (!al_install_audio())
	{
		cout << "error - Audio Add-on not initted\n";
		//return 1;
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

	mDisplay = al_create_display(mDispWidth, mDistHeight);
	assert(mDisplay);
	al_clear_to_color(WHITE);
	return 0;
}

void GraphicsSystem::flip() {
	al_flip_display();
}

int GraphicsSystem::draw(GraphicsBuffer* buffer, Sprite* sprite, int x, int y, float scale) {
	ALLEGRO_BITMAP* old = al_get_target_bitmap();
	al_set_target_bitmap(buffer->getBitMap());

	this->draw(sprite, x, y, scale);

	al_set_target_bitmap(old);
	return 0;
}

int GraphicsSystem::draw(Sprite* sprite, int x, int y, float scale) {
	al_draw_scaled_bitmap(sprite->getBuffer()->getBitMap(), sprite->getLocX(), sprite->getLocY(), sprite->getWidth(), sprite->getHeight(), x, y, sprite->getWidth()*scale, sprite->getHeight()*scale, 0);
	return 0;
}

int GraphicsSystem::writeText(string text, int x, int y, Font* font, ALLEGRO_COLOR color) {
	al_draw_text(font->getFont(), color, x, y, ALLEGRO_ALIGN_LEFT, text.c_str());
	return 0;
}

int GraphicsSystem::writeText(string text, GraphicsBuffer* buffer, int x, int y, Font* font, ALLEGRO_COLOR color) {
	ALLEGRO_BITMAP* old = al_get_target_bitmap();
	al_set_target_bitmap(buffer->getBitMap());

	this->writeText(text, x, y, font, color);

	al_set_target_bitmap(old);
	return 0;
}

int GraphicsSystem::saveBuffer(string fileName, GraphicsBuffer* buffer) {
	
	ALLEGRO_BITMAP* map;

	if (buffer == NULL) {
		map = al_get_target_bitmap();
	}
	else {
		map = buffer->getBitMap();
	}

	al_save_bitmap(fileName.c_str(), map);
	
	return 0;
}

int GraphicsSystem::cleanUp() {
	al_destroy_display(mDisplay);
	return 0;
}

/*#################################
			Font
#################################*/

Font::Font(string fontName, int size) {
	mSize = size;
	mFont = al_load_ttf_font((ASSET_PATH + fontName).c_str(), size, 0);
	assert(mFont);
}

Font::~Font() {
	al_destroy_font(mFont);
}

/*#################################
			GraphicsBuffer
#################################*/

GraphicsBuffer::GraphicsBuffer(string mapName) {
	mBitmap = al_load_bitmap((ASSET_PATH + mapName).c_str());
	assert(mBitmap);

	mWidth = al_get_bitmap_width(mBitmap);
	mHeight = al_get_bitmap_height(mBitmap);

}
GraphicsBuffer::GraphicsBuffer(int wide, int tall) {
	mBitmap = al_create_bitmap(wide, tall);
	assert(mBitmap);

	mWidth = wide;
	mHeight = tall;
}

GraphicsBuffer::GraphicsBuffer(ALLEGRO_BITMAP* map) {
	mBitmap = map;
	mWidth = al_get_bitmap_width(mBitmap);
	mHeight = al_get_bitmap_height(mBitmap);
}


GraphicsBuffer::~GraphicsBuffer() {
	al_destroy_bitmap(mBitmap);
}

void GraphicsBuffer::setColor(ALLEGRO_COLOR color) {

	ALLEGRO_BITMAP* old = al_get_target_bitmap();
	al_set_target_bitmap(mBitmap);
	al_clear_to_color(color);
	al_draw_bitmap(mBitmap, 0, 0, 0);
	al_set_target_bitmap(old);

}

/*#################################
			Sprite
#################################*/

Sprite::Sprite(GraphicsBuffer* buffer, int x, int y, int width, int height) {
	mBuffer = buffer;
	mLocX = x;
	mLocY = y;
	if (width == NULL) {
		mWidth = mBuffer->getWidth();
		mHeight = mBuffer->getHeight();
	}
	else {
		mWidth = width;
		mHeight = height;
	}

}
