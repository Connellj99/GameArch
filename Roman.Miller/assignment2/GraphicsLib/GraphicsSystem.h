#ifndef GRAPHICS_SYSTEM_H
#define GRAPHICS_SYSTEM_H

#include "Trackable.h"
#include "Sprite.h"
#include "Font.h"
#include "Color.h"
#include "GraphicsBuffer.h"
#include <Vector2D.h>



class GraphicsSystem : public Trackable
{
public:

	//constuctors and acessors
	GraphicsSystem();
	~GraphicsSystem();
	void cleanUp();
	void init();
	void flip();
	int getWidth();
	int getHeight();
	ALLEGRO_DISPLAY *getBuffer();
	void draw(Vector2D vec, Sprite &sprite, float scale=1);
	void draw(GraphicsBuffer &buffer, Vector2D loc, Sprite &sprite, float scale=1);
	//void draw( Vector2D loc, Sprite &sprite, float scale = 1);
	void writeText(int locX, int locY, Font &font, Color color, string text);
	void writeText(GraphicsBuffer &buffer,int locX, int locY, Font &font, Color color, string text);
	bool saveBuffer(GraphicsBuffer &buffer, string filename);
	bool saveBuffer(string filename);
	void rest(float restTime);

private:

	// allegro display with W and H
	ALLEGRO_DISPLAY* mpDisplay;
	int mHeight = 600;
	int mWidth = 800;

};
#endif