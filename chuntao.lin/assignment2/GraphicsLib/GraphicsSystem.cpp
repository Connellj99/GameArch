#include "GraphicsSystem.h"

//GraphicsSystem Functions--------------------------------------------------------------------------/
GraphicsSystem::GraphicsSystem(int width,int height)
{
	mWidth = width;
	mHeight = height;
}

GraphicsSystem::~GraphicsSystem()
{
	//calls the clean graphic system function
	cleanGraphicSys();
}

int GraphicsSystem::initGraphicSys()
{
	//initialize allegro
	if (!al_init())
	{
		std::cout << "error initting Allegro\n";
		return 1;
	}

	//creates a display with the mWidth and mHeight and then sets it to the mDisplay pointer
	mDisplay = al_create_display(mWidth, mHeight);
	//assert to check if it is valid.
	assert(mDisplay);
	return 1;
}

void GraphicsSystem::cleanGraphicSys()
{
	//destroy and clear up mDisplay;
	al_destroy_display(mDisplay);

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

void GraphicsSystem::getBackBuffer()
{
	//sets the target bitmap to the backbuffer of display
	al_set_target_bitmap(al_get_backbuffer(mDisplay));
}

void GraphicsSystem::flipDisplay()
{
	//flip the display to show the image
	al_flip_display();
}

void GraphicsSystem::drawBackBuffer(float xPos, float yPos,GraphicsBuffer& buffer,float scale)
{
	////retargets the bitmap to the backbuffer
	getBackBuffer();
	//then draw onto it with the passed in parameters, including the passed in buffer
	al_draw_bitmap(buffer.mBuffer, xPos, yPos, 0);

}

void GraphicsSystem::drawToGivenBuffer(GraphicsBuffer& targetBuffer, float xPos, float yPos, float scale)
{
	//sets target to the passed in buffer
	al_set_target_bitmap(targetBuffer.mBuffer);
	
	//then draw
	al_draw_scaled_bitmap(targetBuffer.mBufferSprite, xPos, yPos, targetBuffer.getBufferWidth(), targetBuffer.getBufferHeight(), xPos, yPos, targetBuffer.getBufferWidth() *scale, targetBuffer.getBufferHeight() *scale, 0);
}

void GraphicsSystem::writeTextBackBuffer(float xPos, float yPos, Font& font, Colors& color, std::string theText)
{
	//get and set to the backbuffer
	getBackBuffer();
	//draw the text with the mFont and all the parameters passed
	al_draw_text(font.mFont, color.BLACK, xPos, yPos, 0, (theText).c_str());

}

void GraphicsSystem::writeTextGraphicBuffer(GraphicsBuffer& graphicBuffer, float xPos, float yPos, Font& font, Colors& color, std::string theText)
{
	//call the loadtext to essentially get the mFont to be the right font
	font.loadText();
	
	//set target bitmap ot the passed in buffers mBuffer
	al_set_target_bitmap(graphicBuffer.mBuffer);

	//draw the text with the mFont and all the parameters passed
	al_draw_text(font.mFont, color.BLACK, xPos, yPos, 0, (theText).c_str());

}

void GraphicsSystem::drawSmurfs(GraphicsBuffer & targetBuffer, float xPos, float yPos, float scale)
{
	//floats to give random numbers
	float randomXPos = 0;
	
	float randomYPos = 0;

	//give it random numbers within a range
	randomXPos = rand() % getGraphicSysWidth()/1.5;
	randomYPos = rand() % getGraphicSysHeight()/1.5;

	al_set_target_bitmap(targetBuffer.mBuffer);

	al_draw_scaled_bitmap(targetBuffer.mBufferSprite, xPos, yPos, targetBuffer.getBufferWidth()/SPRITESX, targetBuffer.getBufferHeight()/ SPRITESX, randomXPos, randomYPos, targetBuffer.getBufferWidth() *scale, targetBuffer.getBufferHeight() *scale, 0);

}

void GraphicsSystem::saveBuffer(GraphicsBuffer&  graphicBuffer, std::string outputFile)
{
	//open the file
	std::ofstream outFile;

	outFile.open(outputFile);

	//then save bitmap with the output file name
	al_save_bitmap(outputFile.c_str(), graphicBuffer.mBuffer);

	//close the file
	outFile.close();
}
