#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

#include <iostream>
#include <cassert>
#include <string>
#include <stdlib.h>

#include <PerformanceTracker.h>
#include <MemoryTracker.h>

#include "GraphicsSystem.h"
#include "GraphicsBuffer.h"
#include "Sprite.h"
#include "Font.h"


using namespace std;

const string ASSET_PATH = "..\\..\\shared\\assets\\";
string mMessageText = "Curse you Papa Smurf!";
const int DISP_WIDTH = 800;
const int DISP_HEIGHT = 600;
const int FONT_SIZE = 24;
const string PICTURE_FILENAME = "steps.png";
const string SPRITE_FILENAME = "smurf_sprites.png";

int startUp()
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
	if (!al_init_primitives_addon())
	{
		cout << "error - primitives Add-on not initted\n";
		return 1;
	}

}

void waitForSeconds(double seconds)
{
	al_rest(seconds);
}
