/*
Author:Jackson Michaels
Class: EGP-310-01
Assignment: Assignment 2
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/

#pragma once
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

using namespace std;
const ALLEGRO_COLOR RED = al_map_rgba_f(1, 0, 0, 1);
const ALLEGRO_COLOR WHITE = al_map_rgba_f(1, 1, 1, 1);
const ALLEGRO_COLOR BLACK = al_map_rgba_f(0, 0, 0, 1);
const string ASSET_PATH = "..\\..\\shared\\assets\\";


class GraphicsBuffer : public Trackable{
	friend class GraphicsSystem;
	friend class Sprite;
	private:
		ALLEGRO_BITMAP* mBitmap;
		ALLEGRO_BITMAP* getBitMap() { return mBitmap; };
		int mWidth, mHeight;
		bool mOwnsBitmap;
		GraphicsBuffer(ALLEGRO_BITMAP*);
	public:
		GraphicsBuffer(string);
		GraphicsBuffer(int, int);
		~GraphicsBuffer();
		int getWidth() { return mWidth; };
		int getHeight() { return mHeight; };
		void setDementions(int width, int height) { mWidth = width; mHeight = height; };
		void setColor(ALLEGRO_COLOR color);
};

class Sprite : public Trackable {
	private:
		GraphicsBuffer* mBuffer;
		int mLocX, mLocY;
		int mWidth, mHeight;
	public:
		Sprite(GraphicsBuffer*, int x = 0, int y = 0, int width = NULL, int height = NULL);

		GraphicsBuffer* getBuffer() { return mBuffer; };
		void setBuffer(GraphicsBuffer* buff) { mBuffer = buff; };

		int getLocX() { return mLocX; };
		int getLocY() { return mLocY; };
		void setLoc(int x, int y) { mLocX = x; mLocY = y; };


		int getWidth() { return mWidth; };
		int getHeight() { return mHeight; };
		void setDementions(int width, int height) { mWidth = width; mHeight = height; };

};

class Font : public Trackable {
	friend class GraphicsSystem;
	private:
		ALLEGRO_FONT* mFont;
		ALLEGRO_FONT* getFont() { return mFont; };
		int mSize;	
	public:
		Font(string, int = 24);
		~Font();

		int getSize() { return mSize; };
		void setSize(int size) { mSize = size; };
};

class GraphicsSystem : public Trackable {
private:
	int mDispWidth;
	int mDistHeight;
	GraphicsBuffer* mBackBuffer;
	ALLEGRO_DISPLAY* mDisplay;
public:
	GraphicsSystem(int = 100, int = 100);
	~GraphicsSystem();
	int init();
	int cleanUp();
	static void flip();
	int draw(Sprite*, int, int,  float scale = 1.0);
	int draw(GraphicsBuffer*, Sprite*, int, int,  float scale = 1.0);
	int writeText(string, int, int, Font*, ALLEGRO_COLOR);
	int writeText(string, GraphicsBuffer*, int, int, Font*, ALLEGRO_COLOR);
	int saveBuffer(string, GraphicsBuffer* = NULL);

};
