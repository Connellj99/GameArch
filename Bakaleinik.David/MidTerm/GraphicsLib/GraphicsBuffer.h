#pragma once
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

#include "Trackable.h"

using namespace std;

class GBuffer : public Trackable
{
public:
	friend class GSystem;
	//friend class Sprite;

	GBuffer(string path, string filename);
	GBuffer(int height, int width, int r, int g, int b);
	GBuffer(ALLEGRO_DISPLAY* pDisplay);
	GBuffer();
	
	~GBuffer();

	void cleanup();

	int getHeight();
	int getWidth();


private:
	
	string mFilename;
	bool check = false;
	int mHeight;
	int mWidth;

	ALLEGRO_BITMAP *mpBitmap;
	
	ALLEGRO_COLOR mBackgroundColor;
};