/*
Author: Grady Mayo
Class: EGP-310 <Section 01>
Assignment: Assignment 2
Certification of Authenticity: I certify that this assignment is entirely my own work.
*/

#include "GraphicsBuffer.h"

//Constructor for back buffer
GraphicsBuffer::GraphicsBuffer( ALLEGRO_BITMAP* bitmap )
{
	this->mOwnsBitmap = true;
	this->mpBitmap = bitmap;
}

//constructor with filename
GraphicsBuffer::GraphicsBuffer( string filename )
{
	mpBitmap = al_load_bitmap( filename.c_str() );
}

//constructor with size
GraphicsBuffer::GraphicsBuffer( int width, int height, Color& color )
{
	ALLEGRO_BITMAP* backBuffer = al_get_target_bitmap();//save back buffer target
	mpBitmap = al_create_bitmap(width, height);//create bitmap to color
	al_set_target_bitmap(mpBitmap);//set target to bitmap to color
	mColor = al_map_rgb(color.getRValue(), color.getGValue(), color.getBValue());
	al_clear_to_color(mColor);
	al_set_target_bitmap(backBuffer);//reset target
}

//Destructor
GraphicsBuffer::~GraphicsBuffer()
{
	if (!mOwnsBitmap == true)
	{
		al_destroy_bitmap(mpBitmap);
	}
}