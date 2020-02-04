#include "GraphicsBuffer.h"

GraphicsBuffer::GraphicsBuffer(string filename) {
	bitmap = al_load_bitmap((ASSET_PATH + filename).c_str());
	assert(bitmap);
}

GraphicsBuffer::GraphicsBuffer(int r, int g, int b) {
	color = al_map_rgb(r, g, b);

	ALLEGRO_BITMAP* tempBmp = al_get_target_bitmap();
	bitmap = al_create_bitmap(800, 600);
	al_set_target_bitmap(bitmap);
	al_clear_to_color(color);
	al_set_target_bitmap(tempBmp);
}

GraphicsBuffer::~GraphicsBuffer() {
	al_destroy_bitmap(bitmap);
}

GraphicsBuffer::GraphicsBuffer(ALLEGRO_BITMAP* bitmap) {
	this->bitmap = bitmap;
}

int GraphicsBuffer::GetHeight() {
	return al_get_bitmap_height(bitmap);
}

int GraphicsBuffer::GetWidth() {
	return al_get_bitmap_width(bitmap);
}