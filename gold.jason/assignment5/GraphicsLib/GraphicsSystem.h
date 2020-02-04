#ifndef GraphicsSystem_h
#define GraphicsSystem_h

#include <Trackable.h>
#include "GraphicsBuffer.h"
#include "Sprites.h"
#include "Font.h"
#include <iostream>
#include <Vector2D.h>
#include <allegro5\allegro.h>
#include <allegro5\allegro_ttf.h>
#include <allegro5\allegro_acodec.h>
#include <allegro5\allegro_image.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_primitives.h>


//dont pass by value
class GraphicsSystem:public Trackable
{
	friend class System;
public:
	GraphicsSystem(int bufferHeight, int bufferWidth);
	~GraphicsSystem();

	void initGraphicsSystem(int bufferHeight, int bufferWidth);

	void cleanUpGraphics();

	int getWidth() 
	{
		return mWidth;
	};

	int getHeight() 
	{
		return mHeight;
	};

	void flip_Display();

	void draw(float x, float y, Sprites* sprite, float scale);
	void draw(float x, float y, Sprites* sprite, float scale, GraphicsBuffer* targetBuffer);
	void draw(GraphicsBuffer* bitmap, int x, int y);
	void draw(GraphicsBuffer* target, GraphicsBuffer* bitmap, float locX, float locY, float scale);
	void draw(GraphicsBuffer *bitmap, float locX, float locY, float scale);
	
	void WriteText(Font* font, Color color, std::string message, float x, float y);
	
	void WriteText(GraphicsBuffer* target, Font* font, Color color, std::string message, float x, float y);
	
	void SaveBuffer(std::string filename);
	void SaveBuffer(std::string filename, GraphicsBuffer* targetBuffer);

	GraphicsBuffer* getBuffer()
	{
		return mpGraphicsBuffer;
	};
private:
	int mWidth;
	int mHeight;
	int mFontSize;
	GraphicsBuffer *mpGraphicsBuffer;
	ALLEGRO_DISPLAY *mpDisplay;
	// display pointer

};
#endif // !GraphicsSystem_h