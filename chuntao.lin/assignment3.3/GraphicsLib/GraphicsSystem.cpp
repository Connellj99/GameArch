#include "GraphicsSystem.h"

//GraphicsSystem Functions--------------------------------------------------------------------------/
GraphicsSystem::GraphicsSystem(int width,int height)
{
	mWidth = width;
	mHeight = height;
}

GraphicsSystem::~GraphicsSystem()
{
	
}

int GraphicsSystem::initGraphicSys()
{
	//creates a display with the mWidth and mHeight and then sets it to the mDisplay pointer
	mpDisplay = al_create_display(mWidth, mHeight);
	//assert to check if it is valid.
	assert(mpDisplay);
	return 1;
}

void GraphicsSystem::cleanGraphicSys()
{
	//destroy and clear up mDisplay;
	//NOT needed in assignment 3 but was done in assignment 2
	//al_destroy_display(mpDisplay);

}

void GraphicsSystem::waitDisplay()
{
	//wait 5 seconds
	al_rest(5.0);
}

int GraphicsSystem::getGraphicSysHeight()
{
	return mHeight;
}

int GraphicsSystem::getGraphicSysWidth()
{
	return mWidth;
}

void GraphicsSystem::setBackBuffer()
{
	//sets the target bitmap to the backbuffer of display
	al_set_target_bitmap(al_get_backbuffer(mpDisplay));
}

void GraphicsSystem::flipDisplay()
{
	//flip the display to show the image
	al_flip_display();
}

void GraphicsSystem::drawBackBuffer(float xPos, float yPos,GraphicsBuffer& buffer,float scale)
{
	////retargets the bitmap to the backbuffer
	setBackBuffer();
	//then draw onto it with the passed in parameters, including the passed in buffer
	//al_draw_bitmap(buffer.mBuffer, 0, 0, 0);
	al_draw_scaled_bitmap(buffer.mpBuffer, 0, 0, buffer.getBufferWidth(),buffer.getBufferHeight(),0,0,buffer.getBufferWidth()*scale,buffer.getBufferHeight()*scale,0);
	//al_clear_to_color(al_map_rgb(255, 0, 255));
	//al_flip_display();
	//al_draw_bitmap(buffer)
}

void GraphicsSystem::drawToGivenBuffer(GraphicsBuffer& targetBuffer, float xPos, float yPos, float scale)
{
	//sets target to the passed in buffer
	al_set_target_bitmap(targetBuffer.mpBuffer);
	
	//then draw
	al_draw_scaled_bitmap(targetBuffer.mpBufferSprite, xPos, yPos, targetBuffer.getBufferWidth(), targetBuffer.getBufferHeight(), xPos, yPos, targetBuffer.getBufferWidth() *scale, targetBuffer.getBufferHeight() *scale, 0);
	//al_flip_display();
}

void GraphicsSystem::writeTextBackBuffer(float xPos, float yPos, Font& font, Colors& color, std::string theText)
{
	//get and set to the backbuffer
	setBackBuffer();
	//draw the text with the mFont and all the parameters passed
	al_draw_text(font.mFont, color.BLACK, xPos, yPos, 0, (theText).c_str());

}

void GraphicsSystem::writeTextGraphicBuffer(GraphicsBuffer& graphicBuffer, float xPos, float yPos, Font& font, Colors& color, std::string theText)
{
	//call the loadtext to essentially get the mFont to be the right font
	font.loadText();
	
	//set target bitmap ot the passed in buffers mBuffer
	al_set_target_bitmap(graphicBuffer.mpBuffer);

	//draw the text with the mFont and all the parameters passed
	al_draw_text(font.mFont, color.BLACK, xPos, yPos, 0, (theText).c_str());

}

void GraphicsSystem::drawSmurfs(GraphicsBuffer & targetBuffer, float xPos, float yPos, float scale)
{
	//floats to give random numbers
	float locationOnDisplayX = 400;
	
	float locationOnDisplayY = 300;

	//give it random numbers within a range
//	randomXPos = rand() % getGraphicSysWidth()/1.5;
//	randomYPos = rand() % getGraphicSysHeight()/1.5;

	//al_set_target_bitmap(targetBuffer.mBuffer);

	al_draw_scaled_bitmap(targetBuffer.mpBufferSprite, xPos, yPos, targetBuffer.getBufferWidth()/SPRITESX, targetBuffer.getBufferHeight()/ SPRITESX, locationOnDisplayX, locationOnDisplayY, targetBuffer.getBufferWidth() *scale, targetBuffer.getBufferHeight() *scale, 0);

}

void GraphicsSystem::drawSprite(Sprite * passedSprite, float xPos, float yPos)
{
	al_draw_bitmap_region(passedSprite->graphicBuffObject.mpBuffer, passedSprite->getSpriteSourceLocationX(), passedSprite->getSpriteSourceLocationY(), passedSprite->getSpriteWidth(), passedSprite->getSpriteHeight(), xPos, yPos,0);
}

void GraphicsSystem::saveBuffer(GraphicsBuffer&  graphicBuffer, std::string outputFile)
{
	//open the file
	std::ofstream outFile;

	outFile.open(outputFile);

	//then save bitmap with the output file name
	al_save_bitmap(outputFile.c_str(), graphicBuffer.mpBuffer);

	//close the file
	outFile.close();
}
