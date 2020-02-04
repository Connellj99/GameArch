/*
Author: Simon Steele
Class: EGP-310-01
Assignment: Assignment 2
Certification of Authenticity: I certify that this
assignment is entirely my own work.
*/

#include <iostream>
#include <cassert>
#include <string>

#include <PerformanceTracker.h>
#include <MemoryTracker.h>


#include <GraphicsSystem.h>

using namespace std;





int main()
{

	// Display constant variables
	const int DISP_WIDTH = 800;
	const int DISP_HEIGHT = 600;
	const int RED_BUFFER_HEIGHT = 700;

	// Asset-related constant variables
	const string MESSAGE = "Curse You Papa Smurf!";
	const string ASSET_PATH = "..\\..\\shared\\assets\\";
	const string BACKGROUND_FILENAME = "steps.png";
	const string QUIMBY_FILENAME = "mayor_quimby.png";
	const string SMURF_SPRITE_FILENAME = "smurf_sprites.png";
	const string FONT_FILENAME = "cour.ttf";
	const int FONT_SIZE = 24;
	const Vector2 DEFAULT_POSITION = Vector2(0, 0);

	const Vector2 SMURF_DIMENSIONS = Vector2(64, 60);

	// Buffer posiitions
	Vector2 RED_IMAGE_POSITION = Vector2(0, 0);
	Vector2 STEPS_IMAGE_POS = Vector2(125, 150);
	Vector2 TEXT_POSITION = Vector2(0, 0);

	const float WINDOW_COOLDOWN_TIME = 5.0;
	const float DEFAULT_SCALING = 1.0;
	const float STEPS_SCALING_AMOUNT = 0.33;

	// All smurf positions
	const Vector2 SMURF_ONE_DIMENSIONS = Vector2(0, 0);
	const Vector2 SMURF_ONE_POSITION = Vector2(142, 300);

	const Vector2 SMURF_TWO_DIMENSIONS = Vector2(64, 0);
	const Vector2 SMURF_TWO_POSITION = Vector2(268, 400);

	const Vector2 SMURF_THREE_DIMENSIONS = Vector2(128, 0);
	const Vector2 SMURF_THREE_POSITION = Vector2(587, 100);

	const Vector2 SMURF_FOUR_DIMENSIONS = Vector2(192, 0);
	const Vector2 SMURF_FOUR_POSITION = Vector2(724, 60);

	const Vector2 SMURF_FIVE_DIMENSIONS = Vector2(0, 60);
	const Vector2 SMURF_FIVE_POSITION = Vector2(189, 340);

	const Vector2 SMURF_SIX_DIMENSIONS = Vector2(64, 60);
	const Vector2 SMURF_SIX_POSITION = Vector2(340, 133);

	const Vector2 SMURF_SEVEN_DIMENSIONS = Vector2(128, 60);
	const Vector2 SMURF_SEVEN_POSITION = Vector2(512, 345);

	const Vector2 SMURF_EIGHT_DIMENSIONS = Vector2(192, 60);
	const Vector2 SMURF_EIGHT_POSITION = Vector2(702, 100);

	const Vector2 SMURF_NINE_DIMENSIONS = Vector2(0, 120);
	const Vector2 SMURF_NINE_POSITION = Vector2(604, 289);

	const Vector2 SMURF_TEN_DIMENSIONS = Vector2(0, 120);
	const Vector2 SMURF_TEN_POSITION = Vector2(506, 112);

	const Vector2 SMURF_ELEVEN_DIMENSIONS = Vector2(0, 120);
	const Vector2 SMURF_ELEVEN_POSITION = Vector2(369, 120);

	const Vector2 SMURF_TWELVE_DIMENSIONS = Vector2(0, 120);
	const Vector2 SMURF_TWELVE_POSITION = Vector2(600, 100);

	const Vector2 SMURF_THIRTEEN_DIMENSIONS = Vector2(0, 180);
	const Vector2 SMURF_THIRTEEN_POSITION = Vector2(50, 30);

	const Vector2 SMURF_FOURTEEN_DIMENSIONS = Vector2(64, 180);
	const Vector2 SMURF_FOURTEEN_POSITION = Vector2(80, 300);

	const Vector2 SMURF_FIFTEEN_DIMENSIONS = Vector2(128, 180);
	const Vector2 SMURF_FIFTEEN_POSITION = Vector2(90, 500);

	const Vector2 SMURF_SIXTEEN_DIMENSIONS = Vector2(192, 180);
	const Vector2 SMURF_SIXTEEN_POSITION = Vector2(100, 700);



	// Initialize the graphics system
	GraphicsSystem graphics = GraphicsSystem();
	graphics.init( DISP_WIDTH, DISP_HEIGHT );

	// Colors
	const Color RED = Color(255, 0, 0);
	const Color BLACK = Color(0, 0, 0);

	// Fonts
	Font niceFont = Font( ASSET_PATH + FONT_FILENAME, FONT_SIZE );

	// Buffers
	GraphicsBuffer * redImageBuffer = new GraphicsBuffer( DISP_WIDTH, RED_BUFFER_HEIGHT, RED );
	GraphicsBuffer * stepsImageBuffer = new GraphicsBuffer( ASSET_PATH + BACKGROUND_FILENAME );


	// Sprites
	Sprite stepsImage = Sprite( stepsImageBuffer, DEFAULT_POSITION.mX, DEFAULT_POSITION.mY);
	Sprite redImage = Sprite( redImageBuffer, DEFAULT_POSITION.mX, DEFAULT_POSITION.mY);
	Sprite smurfsSpriteSheet = Sprite(ASSET_PATH + SMURF_SPRITE_FILENAME, DEFAULT_POSITION.mX, DEFAULT_POSITION.mY);


	// Draw the red image and corresponding text to the screen
	graphics.drawText(* redImageBuffer, TEXT_POSITION, niceFont, BLACK, MESSAGE);
	graphics.draw( RED_IMAGE_POSITION, redImage, DEFAULT_SCALING);
	

	// Draw the steps image
	graphics.draw( STEPS_IMAGE_POS, stepsImage, STEPS_SCALING_AMOUNT);


	// Draw all of the sprites from the sprite sheet
	graphics.drawFromSpriteSheet( SMURF_ONE_DIMENSIONS, SMURF_ONE_POSITION, smurfsSpriteSheet, SMURF_DIMENSIONS);
	graphics.drawFromSpriteSheet( SMURF_TWO_DIMENSIONS, SMURF_TWO_POSITION, smurfsSpriteSheet, SMURF_DIMENSIONS);
	graphics.drawFromSpriteSheet( SMURF_THREE_DIMENSIONS, SMURF_THREE_POSITION, smurfsSpriteSheet, SMURF_DIMENSIONS);
	graphics.drawFromSpriteSheet( SMURF_FOUR_DIMENSIONS, SMURF_FOUR_POSITION, smurfsSpriteSheet, SMURF_DIMENSIONS);


	graphics.drawFromSpriteSheet( SMURF_FIVE_DIMENSIONS, SMURF_FIVE_POSITION, smurfsSpriteSheet, SMURF_DIMENSIONS);
	graphics.drawFromSpriteSheet( SMURF_SIX_DIMENSIONS, SMURF_SIX_POSITION, smurfsSpriteSheet, SMURF_DIMENSIONS);
	graphics.drawFromSpriteSheet( SMURF_SEVEN_DIMENSIONS, SMURF_SEVEN_POSITION, smurfsSpriteSheet, SMURF_DIMENSIONS);
	graphics.drawFromSpriteSheet( SMURF_EIGHT_DIMENSIONS, SMURF_EIGHT_POSITION, smurfsSpriteSheet, SMURF_DIMENSIONS);


	graphics.drawFromSpriteSheet( SMURF_NINE_DIMENSIONS, SMURF_NINE_POSITION, smurfsSpriteSheet, SMURF_DIMENSIONS);
	graphics.drawFromSpriteSheet( SMURF_TEN_DIMENSIONS, SMURF_TEN_POSITION, smurfsSpriteSheet, SMURF_DIMENSIONS);
	graphics.drawFromSpriteSheet( SMURF_ELEVEN_DIMENSIONS, SMURF_ELEVEN_POSITION, smurfsSpriteSheet, SMURF_DIMENSIONS);
	graphics.drawFromSpriteSheet( SMURF_TWELVE_DIMENSIONS, SMURF_TWELVE_POSITION, smurfsSpriteSheet, SMURF_DIMENSIONS);


	graphics.drawFromSpriteSheet( SMURF_THIRTEEN_DIMENSIONS, SMURF_THIRTEEN_POSITION, smurfsSpriteSheet, SMURF_DIMENSIONS);
	graphics.drawFromSpriteSheet( SMURF_FOURTEEN_DIMENSIONS, SMURF_FOURTEEN_POSITION, smurfsSpriteSheet, SMURF_DIMENSIONS);
	graphics.drawFromSpriteSheet( SMURF_FIFTEEN_DIMENSIONS, SMURF_FIFTEEN_POSITION, smurfsSpriteSheet, SMURF_DIMENSIONS);
	graphics.drawFromSpriteSheet( SMURF_SIXTEEN_DIMENSIONS, SMURF_SIXTEEN_POSITION, smurfsSpriteSheet, SMURF_DIMENSIONS);


	// Save the both the red image and back buffers
	graphics.saveBuffer( * redImageBuffer, "redbuffer.jpg" );
	graphics.saveBuffer( graphics.getBackBuffer(), "backbuffer.jpg" );

	// Flip the display
	graphics.flip();


	// Close the window after 5 seconds
	graphics.closeWindow( WINDOW_COOLDOWN_TIME );

	// Delete dynamic memory
	delete redImageBuffer;
	delete stepsImageBuffer;

	MemoryTracker::getInstance()->reportAllocations( cout );
	system("pause");
	return 0;
}