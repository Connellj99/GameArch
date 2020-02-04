#pragma once
#include <allegro5/allegro.h>

#include "Trackable.h"

using namespace std;

class GBuffer;
class Sprite;
class Font;

class GSystem : public Trackable 
{
public:
	
	GSystem(int height, int width);
	GSystem();
	~GSystem();
	void cleanup();

	void initDisplay();
	void flipDispaly();
	
	void draw(int locX, int locY, Sprite *target, float scale); 
	void draw(GBuffer* target, int locX, int locY, Sprite *targetSprite, float scale);
	void draw(int locX, int locY, Sprite *target, float scale, int sizeH, int sizeW, int sourceX, int sourceY);

	void writeText(int locX, int locY, Font* font, int r, int g, int b, string message);
	void writeText(GBuffer* target, int locX, int locY, Font* font, int r, int g, int b, string message);

	void saveBuffer(GBuffer target, string fliemane);

	int getHeight();
	int getWidth();
	void waitForSeconds(double time);
	
	ALLEGRO_BITMAP* getBackBuffer();

private:

	int mDisplayHeight;
	int mDisplayWidth;
	

	ALLEGRO_DISPLAY* mpDisplay;
	GBuffer* mpDisplayBuffer = NULL;

};
