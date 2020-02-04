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
	Point(float xIn = 0, float yIn = 0) { x = xIn; y = yIn; }
	float x, y;
	bool isEqual(const Point& right) { return (x == right.x && y == right.y); }
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
	KEY_SPACE = ALLEGRO_KEY_SPACE,
	KEY_UP = ALLEGRO_KEY_UP,
	KEY_RIGHT = ALLEGRO_KEY_RIGHT,
	KEY_DOWN = ALLEGRO_KEY_DOWN,
	KEY_LEFT = ALLEGRO_KEY_LEFT
};
