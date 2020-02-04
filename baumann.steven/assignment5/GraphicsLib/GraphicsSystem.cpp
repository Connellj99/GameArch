#include "GraphicsSystem.h"
#include "GraphicsBuffer.h"
#include <iostream>
#include <random>
GraphicsSystem::GraphicsSystem(int newWidth, int newHeight) : width(newWidth), height(newHeight)
{
	this->init();
	display = al_create_display(width, height);
	assert(display);
} 

int GraphicsSystem::init()
{
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
	if (!al_install_mouse()) 
	{
		cout << "error - Mouse not installed\n";
		return 1;
	}
	if (!al_install_keyboard())
	{
		cout << "error - Keyboard not installed\n";
		return 1;
	}
	cout << "Init complete!" << endl;
	return 0;
}

void GraphicsSystem::SetHeight(int height) 
{
	this->height = height;
}
int GraphicsSystem::GetHeight() 
{
	return height;
}

void GraphicsSystem::SetWidth(int width) 
{
	this->width = width;
}
int GraphicsSystem::GetWidth() 
{
	return width;
}

void GraphicsSystem::Flip()
{
	al_flip_display();
}

void GraphicsSystem::Draw(int x, int y, Sprite* picture, double scale) 
{
	GraphicsBuffer* BMPBuffer = picture->getBuffer();
	ALLEGRO_BITMAP* bmp = BMPBuffer->bitmap;
	assert(bmp);
	al_draw_scaled_bitmap(bmp, picture->GetX(), picture->GetY(), picture->GetWidth(), picture->GetHeight(), x, y, picture->GetWidth()*scale, picture->GetHeight()*scale, 0);

}

void GraphicsSystem::Draw(GraphicsBuffer* buffer, int x, int y, Sprite* picture, double scale) 
{
	al_draw_scaled_bitmap(buffer->bitmap, picture->GetX(), picture->GetY(), picture->GetWidth(), picture->GetHeight(), x, y, picture->GetWidth()*scale, picture->GetHeight()*scale, 0);
}

 void GraphicsSystem::WriteText(int x, int y, Font* font, int r, int g, int b, string text) 
 {
	 al_draw_text(font->cour_font, al_map_rgb(r, g, b), x, y, 0, text.c_str());
 }

 void GraphicsSystem::WriteText(GraphicsBuffer* buffer, int x, int y, Font* font, int r, int g, int b, string text) 
 {
	 ALLEGRO_BITMAP* tempBmp = al_get_target_bitmap();
	 al_set_target_bitmap(buffer->bitmap);
	 al_draw_text(font->cour_font, al_map_rgb(r, g, b), x, y, 0, text.c_str());
	 al_set_target_bitmap(tempBmp);
 }

 Animation* GraphicsSystem::Slice(GraphicsBuffer* buffer, vector<GraphicsBuffer*> &targetBuffer, int dimensions) 
 {
	 const int NUM_ROWS = 4;
	 const int NUM_COLS = 4;
	 Animation* playerAnim = new Animation();

	 int currentXCoord = 0;
	 int currentYCoord = 0;
	 for (int i = 0; i < NUM_ROWS; i++) 
	 {
		 currentXCoord = i * dimensions;
		 for (int j = 0; j < NUM_COLS; j++) 
		 {
			 currentYCoord = j * dimensions;

			 //First, we create the new bitmap.
			 ALLEGRO_BITMAP* newBmp = al_create_bitmap(dimensions, dimensions);

			 ALLEGRO_BITMAP* prevBmp = al_get_target_bitmap();
			 al_set_target_bitmap(newBmp);

			 al_draw_bitmap_region(buffer->bitmap, currentYCoord, currentXCoord, dimensions, dimensions, 0, 0, 0); //60, 60

			 al_set_target_bitmap(prevBmp);

			 targetBuffer.push_back(playerAnim->loadFromBitmap(newBmp, dimensions, dimensions, 0, 0));

			 //al_draw_bitmap_region(picture->getBuffer()->bitmap, currentXCoord, currentYCoord, 64, 60, rand() % 800, rand() % 600, 0); used to draw randomly
		 }
	 }
	 
	 return playerAnim;

 }

 void GraphicsSystem::SaveBuffer(string filename) 
 {
	 al_save_bitmap(filename.c_str(), al_get_backbuffer(al_get_current_display()));
 }

 void GraphicsSystem::SaveBuffer(GraphicsBuffer* buffer, string filename) 
 {
	 al_save_bitmap(filename.c_str(), buffer->bitmap);
 }

void GraphicsSystem::ExitApplication() 
{
	al_rest(5.0);
}

GraphicsSystem::~GraphicsSystem() 
{
	al_destroy_display(display);
}