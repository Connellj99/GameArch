#include "GraphicsSystem.h"

GraphicsSystem::GraphicsSystem(int bufferHeight, int bufferWidth)
{
	initGraphicsSystem(bufferHeight, bufferWidth);
}

GraphicsSystem::~GraphicsSystem()
{
	cleanUpGraphics();
}

void GraphicsSystem::initGraphicsSystem(int bufferHeight, int bufferWidth)
{
	if (!al_init())
	{
		std::cout << "error initting Allegro\n";
		system("pause");
		return ;
	}
	if (!al_init_image_addon())
	{
		std::cout << "error initting image add-on\n";
		system("pause");
		return ;
	}

	if (!al_init_primitives_addon())
	{
		std::cout << "error initting image add-on\n";
		system("pause");
		return ;
	}

	if (!al_init_font_addon())
	{
		std::cout << "error initting image add-on\n";
		system("pause");
		return ;
	}

	if (!al_init_ttf_addon())
	{
		std::cout << "error initting image add-on\n";
		system("pause");
		return ;
	}

	if (!al_init_acodec_addon())
	{
		std::cout << "error initting image add-on\n";
		system("pause");
		return ;
	}

	if (!al_install_audio())
	{
		std::cout << "error initting image add-on\n";
		system("pause");
		return ;
	}

	if (!al_reserve_samples(1))
	{
		fprintf(stderr, "Failed to reserve samples\n");
		system("pause");
		return ;
	}
	//mpGraphicsBuffer = new GraphicsBuffer(al_get_target_bitmap(),false);

	ALLEGRO_DISPLAY* display = al_create_display(bufferWidth, bufferHeight);
	mpGraphicsBuffer = new GraphicsBuffer(al_get_target_bitmap(), false);
	assert(display);
	mpDisplay = display;
}

void GraphicsSystem::cleanUpGraphics()
{
	al_destroy_display(mpDisplay);
	delete mpGraphicsBuffer;
}

void GraphicsSystem::flip_Display()
{
	al_flip_display();
}

void GraphicsSystem::WriteText(ALLEGRO_FONT* font, ALLEGRO_COLOR color, std::string message, float x, float y)
{
	al_draw_text(font, color, x, y, 0, message.c_str());
}

void GraphicsSystem::WriteTextF(Font* font, Color color, std::string message, float x, float y)
{
	al_draw_text(font->getFont(), color.getColor(), x, y, 0, message.c_str());
}

void GraphicsSystem::WriteTextF1(Font* font, ALLEGRO_COLOR color, std::string message, float x, float y)
{
	al_draw_text(font->getFont(), color = al_map_rgb(255,0,0), x, y, 0, message.c_str());
}



/*
ALLEGRO_FONT* textFont = al_load_ttf_font((ASSET_PATH + FONT_FILENAME).c_str(), FONT_SIZE, 0);
al_draw_text(textFont, WHITE, LOC1_X, LOC1_Y, ALLEGRO_ALIGN_CENTRE, MESSAGE_TEXT.c_str());
*/
void GraphicsSystem::WriteText(GraphicsBuffer* targetBuffer,Font* font, Color color, std::string message, float x, float y)
{
	ALLEGRO_BITMAP* temp = al_get_target_bitmap();
	al_set_target_bitmap(targetBuffer->getBitmap());
	ALLEGRO_COLOR tempColor = al_map_rgb(color.getColor().r, color.getColor().g, color.getColor().b);
	al_draw_text(font->getFont(), tempColor, x, y, 0, message.c_str());
	al_set_target_bitmap(temp);
}

void GraphicsSystem::SaveBuffer(std::string filename)
{
	al_save_bitmap(filename.c_str(), mpGraphicsBuffer->getBitmap());
}

void GraphicsSystem::SaveBuffer(std::string filename, GraphicsBuffer* targetBuffer)
{
	al_save_bitmap(filename.c_str(), targetBuffer->getBitmap());
}

void GraphicsSystem::draw(float x, float y, Sprites* sprite, float scale)
{
	//ALLEGRO_BITMAP* temp = al_create_sub_bitmap(sprite->getBuffer()->getBitmap(),x,y, sprite->getWidth(), sprite->getHeight());
	al_draw_scaled_bitmap(sprite->getBuffer()->getBitmap(),sprite->getLocX(),sprite->getLocY(),sprite->getWidth(),sprite->getHeight(),x,y,(sprite->getWidth()*scale),(sprite->getHeight()*scale),0);
}

void GraphicsSystem::draw(float x, float y, Sprites* sprite, float scale, GraphicsBuffer* targetBuffer)
{
	ALLEGRO_BITMAP* temp = al_get_target_bitmap();
	al_set_target_bitmap(targetBuffer->getBitmap());
	al_draw_scaled_bitmap(sprite->getBuffer()->getBitmap(), sprite->getLocX(), sprite->getLocY(), sprite->getWidth(), sprite->getHeight(), x, y, sprite->getWidth()*scale, sprite->getHeight()*scale, 0);
	al_set_target_bitmap(temp);
}
void GraphicsSystem::draw(GraphicsBuffer *targetBuffer , GraphicsBuffer *bitmap, float locX, float locY, float scale)
{
	ALLEGRO_BITMAP* temp = al_get_target_bitmap();
	al_set_target_bitmap(targetBuffer->getBitmap());
	al_draw_scaled_bitmap(bitmap->getBitmap(), 0, 0, bitmap->getWidth(), bitmap->getHeight(), locX, locY, bitmap->getWidth() * scale, bitmap->getHeight() * scale, 0);
	al_set_target_bitmap(temp);
}

void GraphicsSystem::draw(GraphicsBuffer *bitmap, float locX, float locY, float scale)
{
	al_draw_scaled_bitmap(bitmap->getBitmap(), 0, 0, bitmap->getWidth(), bitmap->getHeight(), locX, locY, bitmap->getWidth() * scale, bitmap->getHeight() * scale, 0);
}

void GraphicsSystem::move(GraphicsBuffer* bitmap, float locX, float locY, float scale)
{
	al_draw_scaled_bitmap(bitmap->getBitmap(), 0, 0, bitmap->getWidth(), bitmap->getHeight(), locX, locY, bitmap->getWidth() * scale, bitmap->getHeight() * scale, 0);
}

void GraphicsSystem::draw(GraphicsBuffer* bitmap, int x, int y)
{
	al_draw_bitmap(bitmap->getBitmap(), x, y, 0);
}

