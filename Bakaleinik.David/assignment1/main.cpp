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


/*
Author: David Bakaleinik
Class: EGP-310
Assignment: PA 01
Date Assigned: 01/16/2019 - 12:30pm
Due Date: 01/25/2019 - 11:59pm
Description:
An introduction to Allegro5, linking and how this all works.
Note: This assignment allowed for cooperation between students. I did not directly copy anybodys help, but a student had helped me fix some of the issues I was having.

Certification of Authenticity:
I certify that this is entirely my own work, except where I have given
fully-documented references to the work of others. I understand the
definition and consequences of plagiarism and acknowledge that the assessor
of this assignment may, for the purpose of assessing this assignment:
- Reproduce this assignment and provide a copy to another member of
academic staff; and/or
- Communicate a copy of this assignment to a plagiarism checking
service (which may then retain a copy of this assignment on its
database for the purpose of future plagiarism checking)
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

	//init the various add-ons - you will need image, font, ttf, primitives, audio, and acodec
	//al_init();
	
	if (!al_init_image_addon())		//This was done after looking at piazza		Form here:
	{
		cout << "error initting image add-on\n";
		system("pause");
		return 1;
	}
	if (!al_init_font_addon())
	{
		cout << "error initting font add-on\n";
		system("pause");
		return 1;
	}
	
	if (!al_init_ttf_addon())
	{
		cout << "error initting ttf add-on\n";
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
		fprintf(stderr, "Failed to initialise audio!\n");
		return -1;
	}

	if (!al_init_acodec_addon())
	{
		fprintf(stderr, "Failed to initialize audio codecs!\n");
		return -1;
	}

	if (!al_reserve_samples(1)) {
		fprintf(stderr, "Failed to reserve samples!\n");
		return -1;
	}																		//To here


	

	//various constants that you should use for asset loading and locating things to be drawn
	const int DISP_WIDTH = 800;
	const int DISP_HEIGHT = 600;

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
	assert(bitmap);
	


	//some colors
	const ALLEGRO_COLOR WHITE = al_map_rgb(255, 255, 255);
	const ALLEGRO_COLOR BLACK = al_map_rgb(0, 0, 0);
	const ALLEGRO_COLOR BLACK_TRANSPARENT = al_map_rgba(0, 0, 0, 200);
	const ALLEGRO_COLOR PURPLE = al_map_rgb(128, 64, 212);

	//load all assets and start playing sample (looping)

	//Asset loading
	ALLEGRO_BITMAP* quimby = al_load_bitmap((ASSET_PATH + QUIMBY_FILENAME).c_str());
	assert(quimby);

	ALLEGRO_FONT* font = al_load_font((ASSET_PATH + FONT_FILENAME).c_str(), FONT_SIZE, 0);
	assert(font);

	//Audio stuff
	ALLEGRO_SAMPLE *clapingSound = al_load_sample((ASSET_PATH + SAMPLE_FILENAME).c_str());
	assert(clapingSound);
	

	al_play_sample(clapingSound, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, NULL);

	if (!clapingSound) {
		printf("Audio clip sample not loaded!\n");
		return -1;
	}

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

	
	//I hap a sclassmate help me with some of these functions

	al_clear_to_color(WHITE);
	al_draw_bitmap(bitmap, 0.0, 0.0, 0);

	al_draw_filled_circle(LOC1_X, LOC1_Y, CIRCLE_RADIUS, BLACK);
	al_draw_text(font, WHITE, LOC1_X, LOC1_Y, 1, MESSAGE_TEXT.c_str());

	al_draw_filled_circle(LOC2_X, LOC2_Y, CIRCLE_RADIUS, BLACK_TRANSPARENT);
	al_draw_text(font, PURPLE, LOC2_X, LOC2_Y, 1, MESSAGE_TEXT.c_str());
	
	float dw = al_get_bitmap_width(quimby) * SCALE_FACTOR;
	float dh = al_get_bitmap_height(quimby) * SCALE_FACTOR;
	
	al_draw_scaled_bitmap(quimby, 0.0, 0.0, al_get_bitmap_width(quimby), al_get_bitmap_height(quimby), LOC3_X, LOC3_Y, dw, dh, 0);
	al_flip_display();

	

	pPerformanceTracker->stopTracking(DRAW_TRACKER_NAME);//leave this alone

	pPerformanceTracker->startTracking(WAIT_TRACKER_NAME);//leave this alone

	//al_rest(SLEEP_TIME_IN_SECONDS); - leave this alone for now
	Timer* pTimer = new Timer;
	pTimer->start();
	pTimer->sleepUntilElapsed(SLEEP_TIME_IN_SECONDS*1000.0);

	pPerformanceTracker->stopTracking(WAIT_TRACKER_NAME);//leave this alone

	al_destroy_display(display);

	al_destroy_sample(clapingSound);
	al_destroy_bitmap(bitmap);
	al_destroy_bitmap(quimby);

	//report elapsed times - leave this alone
	cout << endl << "Time to Init:" << pPerformanceTracker->getElapsedTime(INIT_TRACKER_NAME) << " ms" << endl;
	cout << endl << "Time to Draw:" << pPerformanceTracker->getElapsedTime(DRAW_TRACKER_NAME) << " ms" << endl;
	cout << endl << "Time spent waiting:" << pPerformanceTracker->getElapsedTime(WAIT_TRACKER_NAME) << " ms" << endl;

	MemoryTracker::getInstance()->reportAllocations(cout);//leave this alone - will report memory leaks - don't worry about this for now

	system("pause");
	return 0;
}