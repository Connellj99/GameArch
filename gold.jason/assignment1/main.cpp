/*
Author: Jason Gold
Class: EGP-310-01
Date Due: 1/25/19 12:01pm
Assignment: Assignment 1

References:
Chun Tao Lin
Piazza QA
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

	//initialize all the needed allegro stuff
	if (!al_init())
	{
		cout << "error initting Allegro\n";
		system("pause");
		return 1;
	}
	if (!al_init_image_addon())
	{
		cout << "error initting image add-on\n";
		system("pause");
		return 1;
	}
	if (!al_install_audio())
	{
		cout << "error initting audio\n";
		system("pause");
		return 1;
	}
	if (!al_reserve_samples(1))
	{
		cout << "error initting audio\n";
		system("pause");
		return 1;
	}
	if (!al_init_font_addon())
	{
		cout << "error initting font\n";
		system("pause");
		return 1;
	}
	if (!al_init_ttf_addon())
	{
		cout << "error initting font\n";
		system("pause");
		return 1;
	}
	if (!al_init_acodec_addon())
	{
		cout << "error initting acodec\n";
		system("pause");
		return 1;
	}
	if (!al_init_primitives_addon())
	{
		cout << "error initting primitives\n";
		system("pause");
		return 1;
	}

	//various constants that you should use for asset loading and locating things to be drawn
	const int DISP_WIDTH = 800;
	const int DISP_HEIGHT = 600;

	// a backlash is a escape sequence, if you add two backslashes, then it will actually use a backlash
	const string ASSET_PATH = "..\\..\\shared\\assets\\";//may need to change this
	const string BACKGROUND_FILENAME = "axamer-lizum.png";
	const string QUIMBY_FILENAME = "mayor_quimby.png";
	const string FONT_FILENAME = "cour.ttf";
	const int FONT_SIZE = 24;
	const string SAMPLE_FILENAME = "clapping.wav";
	const double SLEEP_TIME_IN_SECONDS = 5.0;

	//create the display
	ALLEGRO_DISPLAY* display = al_create_display(DISP_WIDTH, DISP_HEIGHT);
	assert(display);

	//example of how to construct the path and pass it to allegro
	ALLEGRO_BITMAP* bitmap = al_load_bitmap((ASSET_PATH + BACKGROUND_FILENAME).c_str());
	ALLEGRO_BITMAP* quimby = al_load_bitmap((ASSET_PATH + QUIMBY_FILENAME).c_str());
	ALLEGRO_FONT* font = al_load_font((ASSET_PATH + FONT_FILENAME).c_str(), FONT_SIZE, 0);
	ALLEGRO_SAMPLE* clapaudio = al_load_sample((ASSET_PATH + SAMPLE_FILENAME).c_str());

	//assert and check if the pointers returned valid data
	assert(bitmap);
	assert(quimby);
	assert(font);
	assert(clapaudio);

	//some colors
	const ALLEGRO_COLOR WHITE = al_map_rgb(255, 255, 255);
	const ALLEGRO_COLOR BLACK = al_map_rgb(0, 0, 0);
	const ALLEGRO_COLOR BLACK_TRANSPARENT = al_map_rgba(0, 0, 0, 200);
	const ALLEGRO_COLOR PURPLE = al_map_rgb(128, 64, 212);

	//load all assets and start playing sample (looping)

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
	int widthQuimb = al_get_bitmap_width(quimby);//these two i added so that way I can store the bitmap dimensions of quimbly.
	int heightQuimb = al_get_bitmap_height(quimby);

	//clear display and make it white
	al_clear_to_color(WHITE);

	//draw and display the axamer image
	al_draw_bitmap(bitmap, 0, 0, 0);

	//Nick helped a lot, this for example he helped me with and I was able to get a good idea from there.
	//draw and display first circle
	al_draw_filled_circle(LOC1_X, LOC1_Y, CIRCLE_RADIUS, BLACK);

	al_draw_text(font, WHITE, LOC1_X, LOC1_Y, ALLEGRO_ALIGN_CENTER, MESSAGE_TEXT.c_str());

	//draw and display second circle
	al_draw_filled_circle(LOC2_X, LOC2_Y, CIRCLE_RADIUS, BLACK_TRANSPARENT);

	al_draw_text(font, PURPLE, LOC2_X, LOC2_Y, ALLEGRO_ALIGN_CENTER, MESSAGE_TEXT.c_str());


	//draw and display quimby
	al_draw_scaled_bitmap(quimby, 0, 0, widthQuimb, heightQuimb, LOC3_X, LOC3_Y, widthQuimb * SCALE_FACTOR, heightQuimb * SCALE_FACTOR, 0);

	al_flip_display();

	al_play_sample(clapaudio, 1.0, 0, 1.0, ALLEGRO_PLAYMODE_LOOP, NULL);

	pPerformanceTracker->stopTracking(DRAW_TRACKER_NAME);//leave this alone

	pPerformanceTracker->startTracking(WAIT_TRACKER_NAME);//leave this alone

	//wait 5 seconds then proceed
	al_rest(5.0);

	pPerformanceTracker->stopTracking(WAIT_TRACKER_NAME);//leave this alone


	//destroy and free up the pointers
	al_destroy_display(display);
	al_destroy_bitmap(bitmap);
	al_destroy_bitmap(quimby);
	al_destroy_font(font);
	al_destroy_sample(clapaudio);

	//report elapsed times - leave this alone
	cout << endl << "Time to Init:" << pPerformanceTracker->getElapsedTime(INIT_TRACKER_NAME) << " ms" << endl;
	cout << endl << "Time to Draw:" << pPerformanceTracker->getElapsedTime(DRAW_TRACKER_NAME) << " ms" << endl;
	cout << endl << "Time spent waiting:" << pPerformanceTracker->getElapsedTime(WAIT_TRACKER_NAME) << " ms" << endl;

	MemoryTracker::getInstance()->reportAllocations(cout);//leave this alone - will report memory leaks - don't worry about this for now

	system("pause");
	return 0;
}