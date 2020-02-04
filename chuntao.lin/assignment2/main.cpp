/*
Author: Chun Tao Lin
Class: EGP-310-01
Assignment: Assignment 2

Certification of Authenticity: I certify that this assignment is entirely my own work.
All this code was written by myself.

Notes:
I have been slaving away since very early in the week before the assignment. I did not procrastinate and pushed through long
periods of work. I finally managed to believe finish all of this assignment. Thanks for pushing us to finish even if it was couple days late.
*/
#ifndef main_h

#define main_h
#include "Colors.h"
#include "GraphicsSystem.h"
#include "GraphicsBuffer.h"
#include "Font.h"
#include "Sprites.h"

#endif
int main()
{
	//create the class objects of graphic system and font
	GraphicsSystem graphicSys(800,600);
	Font font;

	//how big you want the graphic buffers bitmap to be
	float xSize = 800;
	float ySize = 600;

	//placement for Woods/steps
	float xSteps = 130;
	float ySteps = 100;
	
	//will create display
	graphicSys.getGraphicSysHeight();
	graphicSys.getGraphicSysWidth();

	graphicSys.initGraphicSys();

	//create the class object with filler rgb
	Colors color(0.0, 0.0, 0.0);

	//create the class object of graphic buffer that passes in the colors object and the xSize and ySize floats from above
	// will also create the red background in this
	GraphicsBuffer graphicBuff(color,xSize,ySize);

	//draw to the backbuffer the red.
	graphicSys.drawBackBuffer(xSize, ySize, graphicBuff, 1.0);

	//create  a sprite classobject
	Sprite spriteObj;

	//write the text to the passed in graphicbuffer, with the position, and the text
	graphicSys.writeTextGraphicBuffer(graphicBuff,0,0,font.loadText(),color,"CURSE YOU DEAN SMURFF");

	//then save the buffer to an output file.
	graphicSys.saveBuffer(graphicBuff, "redbuffer.jpg");

	//draw the red with text to the backbuffer 
	graphicSys.drawBackBuffer(0, 0, graphicBuff, 1.0);

	//Should change and set a new sprite with new bitmap data(Steps)
	spriteObj.setSpriteSteps(graphicBuff);
	
	//Should then pass in the same buffer and draw the sprite.
	graphicSys.drawToGivenBuffer(graphicBuff,xSteps, ySteps, 0.33);

	//then take that and draw to backbuffer
	graphicSys.drawBackBuffer(0, 0, graphicBuff, 1.0);

	//set sprites to the smurf dean and pass in the graphicsbuffer
	spriteObj.setSpriteSmurfDean(graphicBuff);

	//find the source location
	spriteObj.setSpriteSourceLocation(graphicBuff);

	//Loop that essentially draws the 16 individual dean smurfs
	for (spriteObj.getNumOfSmurfsY(); spriteObj.getNumOfSmurfsY() < 4; spriteObj.addNumOfSmurfsY())
	{
		//draw smurfs
		graphicSys.drawSmurfs(graphicBuff, (spriteObj.getNumOfSmurfsX() * spriteObj.getSpriteSourceLocationX()),  (spriteObj.getNumOfSmurfsY() *spriteObj.getSpriteSourceLocationY()), 1.0 / 4);

		//add to the number of smurfs that have been drawn
		spriteObj.addNumOfSmurfs();
			
		//draw to backbuffer
		graphicSys.drawBackBuffer(0, 0, graphicBuff, 1.0);

		//add to the number of x smurfs, which essentially shifts the x source position
		spriteObj.addNumOfSmurfsX();

			//draws smurf in the row of 
		for (spriteObj.getNumOfSmurfsX(); spriteObj.getNumOfSmurfsX() < 4; spriteObj.addNumOfSmurfsX())
		{	
			graphicSys.drawSmurfs(graphicBuff, (spriteObj.getNumOfSmurfsX() *  spriteObj.getSpriteSourceLocationX()), (spriteObj.getNumOfSmurfsY() *spriteObj.getSpriteSourceLocationY()), 1.0 / 4);

			graphicSys.drawBackBuffer(0, 0, graphicBuff, 1.0);

			spriteObj.addNumOfSmurfs();

		}
		//reset before going to top
		spriteObj.resetNumOfSmurfsX();
	}

	graphicSys.saveBuffer(graphicBuff, "backbuffer.jpg");

	//then should flip display to reveal the images
	graphicSys.flipDisplay();

	MemoryTracker::getInstance()->reportAllocations(std::cout);
 	
	//wait 5 seconds before quiting app.
	graphicSys.waitDisplay();

	return 0;
}