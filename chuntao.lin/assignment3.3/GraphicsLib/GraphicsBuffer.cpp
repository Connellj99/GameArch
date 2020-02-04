#include "GraphicsBuffer.h"
#include "Sprites.h"

//Graphics Buffer Functions -------------------------------------------------------------------------------------/
GraphicsBuffer::GraphicsBuffer()
{
	mBuffHeight = 0;
	mBuffWidth = 0;
	//mBufferSprite =  al_load_bitmap((ASSET_PATH + STEPS_FILENAME).c_str());
}

GraphicsBuffer::GraphicsBuffer(Colors color, float xSize, float ySize)
{
	//initialize the allegro addons
	if (!al_init())
	{
		std::cout << "error initting Allegro\n";
		system("pause");
		return;
	}
	if (!al_init_image_addon())
	{
		std::cout << "error initting image add-on\n";
		system("pause");
		return;
	}
	if (!al_install_audio())
	{
		std::cout << "error initting audio\n";
		system("pause");
		return;
	}
	if (!al_reserve_samples(1))
	{
		std::cout << "error initting audio\n";
		system("pause");
		return;
	}
	if (!al_init_font_addon())
	{
		std::cout << "error initting font\n";
		system("pause");
		return;
	}
	if (!al_init_ttf_addon())
	{
		std::cout << "error initting font\n";
		system("pause");
		return;
	}
	if (!al_init_acodec_addon())
	{
		std::cout << "error initting acodec\n";
		system("pause");
		return;
	}
	if (!al_init_primitives_addon())
	{
		std::cout << "error initting primitives\n";
		system("pause");
		return;
	}
	
	//sets the mBuffer to a bitmap of dimensions
	mpBuffer = al_create_bitmap(xSize, ySize);

	//then retarget to the newly created mBuffer
	al_set_target_bitmap(mpBuffer);
	
	//set it to red
	al_clear_to_color(color.RED);
}

GraphicsBuffer::GraphicsBuffer(std::string filePath)
{
	mpBuffer = al_load_bitmap(filePath.c_str());
	assert(mpBuffer);
}

GraphicsBuffer::~GraphicsBuffer()
{
	/*if (mBuffer == NULL)
	{
		al_destroy_bitmap(mBuffer);
	}
	if (mBufferSprite == NULL)
	{
		al_destroy_bitmap(mBufferSprite);
	}*/
	
}

float GraphicsBuffer::getBufferHeight()
{
	return mBuffHeight;
}

float GraphicsBuffer::getBufferWidth()
{
	return mBuffWidth;
}

void GraphicsBuffer::setBuffer(ALLEGRO_BITMAP*& bitmap)
{	
	mBuffHeight = al_get_bitmap_height(bitmap);//gets the mBuffer and retrieves then set those dimensions to the appropriate member variables
	mBuffWidth =  al_get_bitmap_width(bitmap);
}

//passes pointer by reference the buffer, then sets that buffers bitmap to the mBuffer that is in GraphicsBuffer
/*void GraphicsBuffer::getBuffer(ALLEGRO_BITMAP& buffer)
{
	mBuffer = buffer;//graphicBuffObject//&buffer;
}*/

//passes pointer by reference the buffer, then sets that buffers bitmap to the mBuffer that is in GraphicsBuffer
void GraphicsBuffer::getBuffer(GraphicsBuffer& buffer)
{
	//mBufferSprite = buffer;
	mpBuffer = buffer.mpBuffer;//graphicBuffObject//&buffer;
}


//returns the mBuffer
ALLEGRO_BITMAP* GraphicsBuffer::returnBuff()
{
	return mpBuffer;
}
