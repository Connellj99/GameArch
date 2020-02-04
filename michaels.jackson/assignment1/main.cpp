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
	// Create a performance tracker.
	PerformanceTracker* pPerformanceTracker = new PerformanceTracker;//leave this alone

	/*********************
		Tracker names.
	**********************/
	const string INIT_TRACKER_NAME = "init";
	const string DRAW_TRACKER_NAME = "draw";
	const string WAIT_TRACKER_NAME = "wait";

	// Start tracking the initialization.
	pPerformanceTracker->startTracking(INIT_TRACKER_NAME);//leave this alone


	/*************************************************
		Initialize Allegro components and add-ons.
	**************************************************/

	/***************
		Allegro.
	****************/
	if (!al_init())
	{
		cout << "Error Initializing Allegro!\n";
		system("pause");
		return 1;
	}


	/********************
		Image add-on.
	*********************/
	if (!al_init_image_addon())
	{
		cout << "Error initializing the image add-on!\n";
		system("pause");
		return 1;
	}


	/********************
		Font add-ons.
	*********************/
	if (!al_init_font_addon())
	{
		cout << "Error initializing the font add-on!\n";
		system("pause");
		return 1;
	}
	if (!al_init_ttf_addon())
	{
		cout << "Error initializing the ttf add-on!\n";
		system("pause");
		return 1;
	}


	/*************************
		Primitives add-on.
	**************************/
	if (!al_init_primitives_addon())
	{
		cout << "Error initializing the primitives add-on!\n";
		system("pause");
		return 1;
	}


	/*********************
		Audio add-ons.
	**********************/
	if (!al_install_audio())
	{
		cout << "Error installing audio!\n";
		system("pause");
		return 1;
	}

	if (!al_init_acodec_addon())
	{
		cout << "Error initializing the acodec add-on!\n";
		system("pause");
		return 1;
	}

	if (!al_reserve_samples(1))
	{
		cout << "Error reserving samples!\n";
		return 1;
	}


	/******************************
		Display specifications.
	*******************************/
	const int DISPLAY_WIDTH = 800;
	const int DISPLAY_HEIGHT = 600;


	/****************************
		Asset specifications.
	*****************************/
	const string ASSET_PATH = "..\\..\\shared\\assets\\";
	const string BACKGROUND_FILENAME = "axamer-lizum.png";
	const string QUIMBY_FILENAME = "mayor_quimby.png";
	const string FONT_FILENAME = "cour.ttf";
	const string SAMPLE_FILENAME = "clapping.wav";

	const int FONT_SIZE = 24;

	const double SLEEP_TIME_IN_SECONDS = 5.0;


	// Create the display.
	ALLEGRO_DISPLAY* display = al_create_display(DISPLAY_WIDTH, DISPLAY_HEIGHT);
	assert(display);

	// Create a background bitmap.
	ALLEGRO_BITMAP* backgroundBitmap = al_load_bitmap((ASSET_PATH + BACKGROUND_FILENAME).c_str());
	assert(backgroundBitmap);

	// Create the font.
	ALLEGRO_FONT* courierFont = al_load_font((ASSET_PATH + FONT_FILENAME).c_str(), FONT_SIZE, 0);
	assert(courierFont);

	// Create a quimby bitmap.
	ALLEGRO_BITMAP* quimbyBitmap = al_load_bitmap((ASSET_PATH + QUIMBY_FILENAME).c_str());
	assert(quimbyBitmap);

	// Create a clapping audio sample.
	ALLEGRO_SAMPLE* clappingSample = al_load_sample((ASSET_PATH + SAMPLE_FILENAME).c_str());
	assert(clappingSample);


	/*************
		Colors
	**************/
	const ALLEGRO_COLOR WHITE = al_map_rgb(255, 255, 255);
	const ALLEGRO_COLOR BLACK = al_map_rgb(0, 0, 0);
	const ALLEGRO_COLOR BLACK_TRANSPARENT = al_map_rgba(0, 0, 0, 200);
	const ALLEGRO_COLOR PURPLE = al_map_rgb(128, 64, 212);


	// Stop tracking initialization.
	pPerformanceTracker->stopTracking(INIT_TRACKER_NAME);//leave this alone

	// Start tracking drawing.
	pPerformanceTracker->startTracking(DRAW_TRACKER_NAME);//leave this alone


	/*****************************
		Circle specifications.
	******************************/
	const int CIRCLE_RADIUS = 150;
	const string MESSAGE_TEXT = "Welcome to Allegro!";

	const int LOCATION_1_X = 400;
	const int LOCATION_1_Y = 300;

	const int LOCATION_2_X = 200;
	const int LOCATION_2_Y = 500;


	/*****************************
		Quimby specifications.
	******************************/
	const int LOCATION_3_X = 500;
	const int LOCATION_3_Y = 400;

	const float SCALE_FACTOR = 0.75f;

	int quimbyWidth = al_get_bitmap_width(quimbyBitmap);
	int quimbyHeight = al_get_bitmap_height(quimbyBitmap);


	/***************************
		Draw to the display.
	****************************/

	// Clear the display and make it white.
	al_clear_to_color(WHITE);

	// Draw the background.
	al_draw_bitmap(backgroundBitmap, 0, 0, 0);

	// Draw a black upper circle with white text.
	al_draw_filled_circle(LOCATION_1_X, LOCATION_1_Y, CIRCLE_RADIUS, BLACK);
	al_draw_text(courierFont, WHITE, LOCATION_1_X, LOCATION_1_Y, ALLEGRO_ALIGN_CENTER, MESSAGE_TEXT.c_str());	// Convert the text to a c_str to avoid errors.

	// Draw a semi-transparent black lower circle with purple text.
	al_draw_filled_circle(LOCATION_2_X, LOCATION_2_Y, CIRCLE_RADIUS, BLACK_TRANSPARENT);
	al_draw_text(courierFont, PURPLE, LOCATION_2_X, LOCATION_2_Y, ALLEGRO_ALIGN_CENTER, MESSAGE_TEXT.c_str());	// Convert the text to a c_str to avoid errors.

	// Draw Qumby scaled.
	al_draw_scaled_bitmap(quimbyBitmap, 0, 0, quimbyWidth, quimbyHeight, LOCATION_3_X, LOCATION_3_Y, quimbyWidth * SCALE_FACTOR, quimbyHeight * SCALE_FACTOR, 0);
	
	// Refresh the display.
	al_flip_display();

	// Play the sample on a loop until the display closes.
	al_play_sample(clappingSample, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, NULL);


	// Stop tracking drawing.
	pPerformanceTracker->stopTracking(DRAW_TRACKER_NAME);//leave this alone

	// Start tracking waiting.
	pPerformanceTracker->startTracking(WAIT_TRACKER_NAME);//leave this alone


	/******************
		Wait timer.
	*******************/
	//al_rest(SLEEP_TIME_IN_SECONDS); - leave this alone for now
	Timer* pTimer = new Timer;
	pTimer->start();
	pTimer->sleepUntilElapsed(SLEEP_TIME_IN_SECONDS*1000.0);


	// Stop tracking waiting.
	pPerformanceTracker->stopTracking(WAIT_TRACKER_NAME);//leave this alone


	/****************************
		Destroy all pointers.
	*****************************/
	al_destroy_display(display);
	al_destroy_sample(clappingSample);
	al_destroy_bitmap(quimbyBitmap);
	al_destroy_bitmap(backgroundBitmap);
	al_destroy_font(courierFont);


	/****************************
		Report elapsed times.
	*****************************/
	cout << endl << "Time to Init:" << pPerformanceTracker->getElapsedTime(INIT_TRACKER_NAME) << " ms" << endl;
	cout << endl << "Time to Draw:" << pPerformanceTracker->getElapsedTime(DRAW_TRACKER_NAME) << " ms" << endl;
	cout << endl << "Time spent waiting:" << pPerformanceTracker->getElapsedTime(WAIT_TRACKER_NAME) << " ms" << endl;


	MemoryTracker::getInstance()->reportAllocations(cout);//leave this alone - will report memory leaks - don't worry about this for now

	system("pause");
	return 0;
}