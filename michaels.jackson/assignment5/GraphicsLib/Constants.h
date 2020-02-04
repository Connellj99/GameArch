/*
Author:Jackson Michaels
Class: EGP-310-01
Assignment: Assignment 2
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/
#pragma once
#include <string>
#include <allegro5/allegro.h>

const std::string ASSET_PATH = "..\\..\\shared\\assets\\";

struct Point
{
	float x, y;
};
struct MouseState
{
	bool left, right;
	Point loc;
};

enum KeyConvert
{
	KEY_F = ALLEGRO_KEY_F,
	KEY_S = ALLEGRO_KEY_S,
	KEY_ENTER = ALLEGRO_KEY_ENTER,
	KEY_ESCAPE = ALLEGRO_KEY_ESCAPE,
	KEY_SPACE = ALLEGRO_KEY_SPACE
};
