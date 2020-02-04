/*
 * Adam Clarke
 * EGP-310-01
 * Assignment 1
 * I certify that this assignment is entirely my own work.
*/
#include <PerformanceTracker.h>
#include <MemoryTracker.h>

#include "GraphicsSystem.h"

int main()
{
	const Vector2D DISP_DIMENSIONS(800, 600);
	const float REST_TIME = 5.0;

	const std::string ASSET_PATH = "..\\..\\shared\\assets\\";
	const std::string FONT_FILENAME = "cour.ttf";
	const std::string STEPS_FILENAME = "steps.png";
	const std::string SMURF_FILENAME = "smurf_sprites.png";
	const std::string BUFFER_SAVE_PATH = "..\\..\\clarke.adam\\assignment2\\";
	const std::string BACK_BUFFER_SAVE_FILENAME = "backbuffer.jpg";
	const std::string RED_BUFFER_SAVE_FILENAME = "redbuffer.jpg";
	const int FONT_SIZE = 30;
	const Vector2D TEXT_LOC(0, 0);
	const Color BLACK(0, 0, 0, 255);
	const Color RED(255, 0, 0, 255);
	const float STEPS_SCALE = 2 / 3.0f;
	const Vector2D NUM_SMURFS(4, 4);
	const Vector2D SMURF_SPRITE_DIMENSIONS(60, 60);

	auto graphicsSystem = new GraphicsSystem(DISP_DIMENSIONS);

	// red buffer, cleared to red
	const auto redBuffer = new GraphicsBuffer(DISP_DIMENSIONS, RED);

	// create courrier font
	const auto courFont = new Font(ASSET_PATH + FONT_FILENAME, FONT_SIZE);
	// write text in courFont to redBuffer
	graphicsSystem->writeText(*redBuffer, TEXT_LOC, *courFont, BLACK, "Curse you Papa Smurf!!!");

	// create sprite of all of redBuffer
	const auto redSprite = new Sprite(redBuffer, Vector2D(0, 0), DISP_DIMENSIONS);
	// draw all of redBuffer to BackBuffer
	graphicsSystem->draw(Vector2D(0, 0), *redSprite);

	// steps buffer, bitmap of steps image
	const auto stepsBuffer = new GraphicsBuffer(ASSET_PATH + STEPS_FILENAME);
	// create sprite of all of stepsBuffer
	const auto stepsSprite = new Sprite(stepsBuffer, Vector2D(0, 0), DISP_DIMENSIONS);
	// draw all of stepsBuffer, scaled and positioned in center of BackBuffer
	graphicsSystem->draw(DISP_DIMENSIONS * 0.5 - DISP_DIMENSIONS * STEPS_SCALE * 0.5, *stepsSprite, STEPS_SCALE);

	// smurf buffer, bitmap of spritesheet
	const auto smurfBuffer = new GraphicsBuffer(ASSET_PATH + SMURF_FILENAME);
	// visit each sprite in spritesheet
	for (auto x = 0; x < NUM_SMURFS.getX(); x++)
	{
		for (auto y = 0; y < NUM_SMURFS.getY(); y++)
		{
			// create sprite of smurf at current position in spritesheet
			const auto smurf = new Sprite(smurfBuffer,
				Vector2D(x * SMURF_SPRITE_DIMENSIONS.getX(), y * SMURF_SPRITE_DIMENSIONS.getY()),
				SMURF_SPRITE_DIMENSIONS);
			// random location on display between 0 and display dimensions minus half smurf sprite size
			const Vector2D randLoc(rand() % int(DISP_DIMENSIONS.getX() - SMURF_SPRITE_DIMENSIONS.getX() * 0.5f),
				rand() % int(DISP_DIMENSIONS.getX() - SMURF_SPRITE_DIMENSIONS.getY() * 0.5f));
			// draw smurf to BackBuffer
			graphicsSystem->draw(randLoc, *smurf, 1);
			delete smurf;
		}
	}

	// save redBuffer to file in assignment2 folder
	graphicsSystem->saveBuffer(BUFFER_SAVE_PATH + BACK_BUFFER_SAVE_FILENAME);
	// save BackBuffer to file in assignment2 folder
	graphicsSystem->saveBuffer(*redBuffer, BUFFER_SAVE_PATH + RED_BUFFER_SAVE_FILENAME);

	// flip BackBuffer to display bitmap
	graphicsSystem->flip();
	graphicsSystem->rest(REST_TIME);

	// clear allocated memory
	delete smurfBuffer;

	delete redBuffer;
	delete courFont;
	delete redSprite;

	delete stepsBuffer;
	delete stepsSprite;

	delete graphicsSystem;

	MemoryTracker::getInstance()->reportAllocations(std::cout);
	system("pause");

	return 0;

}
