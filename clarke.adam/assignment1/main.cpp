/*
 * Adam Clarke
 * EGP-310-01
 * Assignment 1
 * I certify that this assignment is entirely my own work.*/
 /*
 References:
 http://wiki.allegro.cc/index.php?title=Windows,_Visual_Studio_2010_and_Allegro_5
 http://wiki.allegro.cc/index.php?title=Allegro_5_Tutorial/Addons/Audio
 http://wiki.allegro.cc/index.php?title=Allegro_5_Tutorial/Bitmaps
 */

 /*
	 please note that the installation of Allegro we are using doesn't include the monolith libs described in the references.
	 You must refer to the allegro.lib and each lib for each add-on separately!!
 */

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

#include <PerformanceTracker.h>
#include <MemoryTracker.h>

using namespace std;

int main()
{
	PerformanceTracker* pPerformanceTracker = new PerformanceTracker;//leave this alone

	const string INIT_TRACKER_NAME = "init";
	const string DRAW_TRACKER_NAME = "draw";
	const string WAIT_TRACKER_NAME = "wait";

	pPerformanceTracker->startTracking(INIT_TRACKER_NAME);//leave this alone

	// used to reserve samples at start
	const int NUM_CONCURRENT_SAMPLES = 1;

	if (!al_init())
	{
		cout << "error initting Allegro\n";
		system("pause");
		return 1;
	}
	//init the various add-ons - you will need image, font, ttf, primitives, audio, and acodec
	if (!al_init_image_addon())
	{
		cout << "error initting image add-on\n";
		system("pause");
		return 1;
	}

	if (!al_init_font_addon())
	{
		cout << "error initting font addd-on\n";
		system("pause");
		return 1;
	}
	if (!al_init_ttf_addon())
	{
		cout << "error initting TrueType font add-on\n";
		system("pause");
		return 1;
	}
	if (!al_init_primitives_addon())
	{
		cout << "error initting primitives add-on\n";
		system("pause");
		return 1;
	}
	if (!al_install_audio())
	{
		cout << "error installing audio add-on\n";
		system("pause");
		return 1;
	}
	if (!al_init_acodec_addon())
	{
		cout << "error initting audio codec add-on\n";
		system("pause");
		return 1;
	}
	if (!al_reserve_samples(NUM_CONCURRENT_SAMPLES))
	{
		cout << "error reserving audio samples\n";
		system("pause");
		return 1;
	}

	//various constants that you should use for asset loading and locating things to be drawn
	const int DISP_WIDTH = 800;
	const int DISP_HEIGHT = 600;

	const string ASSET_PATH = "..\\..\\shared\\assets\\";
	const string BACKGROUND_FILENAME = "axamer-lizum.png";
	const string QUIMBY_FILENAME = "mayor_quimby.png";
	const string FONT_FILENAME = "cour.ttf";
	const int FONT_SIZE = 24;
	const string SAMPLE_FILENAME = "clapping.wav";
	const double SLEEP_TIME_IN_SECONDS = 5.0;

	//create the display
	ALLEGRO_DISPLAY* display = al_create_display(DISP_WIDTH, DISP_HEIGHT);
	assert(display);

	// load background bitmap
	ALLEGRO_BITMAP* backgroundBitmap = al_load_bitmap((ASSET_PATH + BACKGROUND_FILENAME).c_str());
	assert(backgroundBitmap);

	// load quimby bitmap
	ALLEGRO_BITMAP* quimbyBitmap = al_load_bitmap((ASSET_PATH + QUIMBY_FILENAME).c_str());
	assert(quimbyBitmap);

	// load courrier font
	ALLEGRO_FONT* courFont = al_load_ttf_font((ASSET_PATH + FONT_FILENAME).c_str(), FONT_SIZE, NULL);
	assert(courFont);

	// load clapping sample
	ALLEGRO_SAMPLE* clappingSample = al_load_sample((ASSET_PATH + SAMPLE_FILENAME).c_str());
	assert(clappingSample);

	// play clapping sample
	al_play_sample(clappingSample, 1, 0, 1, ALLEGRO_PLAYMODE_LOOP, nullptr);

	//some colors
	const ALLEGRO_COLOR WHITE = al_map_rgb(255, 255, 255);
	const ALLEGRO_COLOR BLACK = al_map_rgb(0, 0, 0);
	const ALLEGRO_COLOR BLACK_TRANSPARENT = al_map_rgba(0, 0, 0, 200);
	const ALLEGRO_COLOR PURPLE = al_map_rgb(128, 64, 212);

	pPerformanceTracker->stopTracking(INIT_TRACKER_NAME);//leave this alone

	pPerformanceTracker->startTracking(DRAW_TRACKER_NAME);//leave this alone

	const int CIRCLE_RADIUS = 150;
	const string MESSAGE_TEXT = "Welcome to Allegro!";

	//used for circle one - circle black and text white
	const int LOC1_X = 400;
	const int LOC1_Y = 300;

	//used for circle two - circle transparent black and text purple
	const int LOC2_X = 200;
	const int LOC2_Y = 500;

	//used for quimby
	const int LOC3_X = 500;
	const int LOC3_Y = 400;
	const float SCALE_FACTOR = 0.75f;
	const float QUIMBY_WIDTH = al_get_bitmap_width(quimbyBitmap);
	const float QUIMBY_HEIGHT = al_get_bitmap_height(quimbyBitmap);

	// clear screen to WHITE
	al_clear_to_color(WHITE);

	// draw the axamer-lizum background image
	al_draw_bitmap(backgroundBitmap, 0, 0, 0);

	// draw circle 1 with message
	al_draw_filled_circle(LOC1_X, LOC1_Y, CIRCLE_RADIUS, BLACK);
	al_draw_text(courFont, WHITE, LOC1_X, LOC1_Y, ALLEGRO_ALIGN_CENTER, MESSAGE_TEXT.c_str());

	// draw circle 2 with message
	al_draw_filled_circle(LOC2_X, LOC2_Y, CIRCLE_RADIUS, BLACK_TRANSPARENT);
	al_draw_text(courFont, PURPLE, LOC2_X, LOC2_Y, ALLEGRO_ALIGN_CENTER, MESSAGE_TEXT.c_str());

	// draw quimby image scaled appropriately
	al_draw_scaled_bitmap(quimbyBitmap, 0, 0, QUIMBY_WIDTH, QUIMBY_HEIGHT,
		LOC3_X, LOC3_Y, QUIMBY_HEIGHT * SCALE_FACTOR, QUIMBY_HEIGHT * SCALE_FACTOR, NULL);

	// flip the display
	al_flip_display();

	pPerformanceTracker->stopTracking(DRAW_TRACKER_NAME);//leave this alone

	pPerformanceTracker->startTracking(WAIT_TRACKER_NAME);//leave this alone

	//al_rest(SLEEP_TIME_IN_SECONDS); - leave this alone for now
	Timer* pTimer = new Timer;
	pTimer->start();
	pTimer->sleepUntilElapsed(SLEEP_TIME_IN_SECONDS*1000.0);

	pPerformanceTracker->stopTracking(WAIT_TRACKER_NAME);//leave this alone

	// free allocated memory
	al_destroy_display(display);
	al_destroy_bitmap(backgroundBitmap);
	al_destroy_bitmap(quimbyBitmap);
	al_destroy_font(courFont);
	al_destroy_sample(clappingSample);

	al_uninstall_audio();
	al_shutdown_primitives_addon();
	al_shutdown_ttf_addon();
	al_shutdown_font_addon();
	al_shutdown_image_addon();
	al_uninstall_system();

	//report elapsed times - leave this alone
	cout << endl << "Time to Init:" << pPerformanceTracker->getElapsedTime(INIT_TRACKER_NAME) << " ms" << endl;
	cout << endl << "Time to Draw:" << pPerformanceTracker->getElapsedTime(DRAW_TRACKER_NAME) << " ms" << endl;
	cout << endl << "Time spent waiting:" << pPerformanceTracker->getElapsedTime(WAIT_TRACKER_NAME) << " ms" << endl;

	MemoryTracker::getInstance()->reportAllocations(cout);//leave this alone - will report memory leaks - don't worry about this for now

	system("pause");
	return 0;
}