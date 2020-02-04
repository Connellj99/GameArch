#include "FileReader.h"
#include "Game.h"

// This function is the default constructor of the class
FileReader::FileReader()
{
}





// This function is the destructor of the class
FileReader::~FileReader()
{
}





// This function reads text file with all modifiable in-game values
// and assigns them to their respective variables
void FileReader::readFile(string fileName)
{
	string input;
	ifstream fin;
	Vector2 temp = Vector2(0, 0);
	string tempStr = "";
//	Color * tempColor = new Color(0, 0, 0);

	// Open the text file
	fin.open(fileName);




	// Get the display dimensions of the game
	fin >> input;
	fin >> input;
	Game::getStaticInstance()->mDisplayDimensions.mX = stoi(input);
	fin >> input;
	Game::getStaticInstance()->mDisplayDimensions.mY = stoi(input);


	fin.ignore();


	// Get the background image
	fin >> input;
	fin >> input;
	Game::getStaticInstance()->mBufferManager.addBuffer(ASSET_PATH_TWO + input, NAME_OF_BACKGROUND_BUFFER);

	// Get the value to scale the background image by
	fin >> input;
	fin >> input;
	Game::getStaticInstance()->mBackgroundScalingValue = stod(input);



	fin.ignore();


	// Get the Player Spritesheet
	fin >> input;
	fin >> input;
	Game::getStaticInstance()->mBufferManager.addBuffer(ASSET_PATH_TWO + input, NAME_OF_PLAYER);

	// Get the dimensions of the Player Sprite
	fin >> input;
	fin >> input;
	Game::getStaticInstance()->mPlayerDimensions.mX = stoi(input);
	fin >> input;
	Game::getStaticInstance()->mPlayerDimensions.mY = stoi(input);

	// Get the Sprites per row and column for the Player Sprites
	fin >> input;
	fin >> input;
	temp.mX = stoi(input);
	fin >> input;
	temp.mY = stoi(input);
	Game::getStaticInstance()->mPlayerAnimation = new Animation(Game::getStaticInstance()->mBufferManager.getBuffer(NAME_OF_PLAYER), temp.mX, temp.mY, Game::getStaticInstance()->mDisplayDimensions, Game::getStaticInstance()->mPlayerDimensions);


	fin.ignore();


	// Get the Default Block Spritesheet
	fin >> input;
	fin >> input;
	Game::getStaticInstance()->mBufferManager.addBuffer(ASSET_PATH_TWO + input, NAME_OF_DEFAULT_BLOCK);

	// Get the dimensions of the Default Block Sprite
	fin >> input;
	fin >> input;
	Game::getStaticInstance()->mDefaultBlockDimensions.mX = stoi(input);
	fin >> input;
	Game::getStaticInstance()->mDefaultBlockDimensions.mY = stoi(input);

	// Get the Sprites per row and column for the Default Block Sprites
	fin >> input;
	fin >> input;
	temp.mX = stoi(input);
	fin >> input;
	temp.mY = stoi(input);
	Game::getStaticInstance()->mDefaultBlockAnimation = new Animation(Game::getStaticInstance()->mBufferManager.getBuffer(NAME_OF_DEFAULT_BLOCK), temp.mX, temp.mY, Game::getStaticInstance()->mDisplayDimensions, Game::getStaticInstance()->mDefaultBlockDimensions);


	fin.ignore();

	// Get the Brick Block Spritesheet
	fin >> input;
	fin >> input;
	Game::getStaticInstance()->mBufferManager.addBuffer(ASSET_PATH_TWO + input, NAME_OF_BRICK_BLOCK);

	// Get the dimensions of the Brick Block Sprite
	fin >> input;
	fin >> input;
	Game::getStaticInstance()->mBrickBlockDimensions.mX = stoi(input);
	fin >> input;
	Game::getStaticInstance()->mBrickBlockDimensions.mY = stoi(input);

	// Get the Sprites per row and column for the Brick Block Sprites
	fin >> input;
	fin >> input;
	temp.mX = stoi(input);
	fin >> input;
	temp.mY = stoi(input);
	Game::getStaticInstance()->mBrickBlockAnimation = new Animation(Game::getStaticInstance()->mBufferManager.getBuffer(NAME_OF_BRICK_BLOCK), temp.mX, temp.mY, Game::getStaticInstance()->mDisplayDimensions, Game::getStaticInstance()->mBrickBlockDimensions);


	fin.ignore();


	// Get the Question Block Spritesheet
	fin >> input;
	fin >> input;
	Game::getStaticInstance()->mBufferManager.addBuffer(ASSET_PATH_TWO + input, NAME_OF_QUESTION_BLOCK);

	// Get the dimensions of the Question Block Sprite
	fin >> input;
	fin >> input;
	Game::getStaticInstance()->mQuestionBlockDimensions.mX = stoi(input);
	fin >> input;
	Game::getStaticInstance()->mQuestionBlockDimensions.mY = stoi(input);

	// Get the Sprites per row and column for the Question Block Sprites
	fin >> input;
	fin >> input;
	temp.mX = stoi(input);
	fin >> input;
	temp.mY = stoi(input);
	Game::getStaticInstance()->mQuestionBlockAnimation = new Animation(Game::getStaticInstance()->mBufferManager.getBuffer(NAME_OF_QUESTION_BLOCK), temp.mX, temp.mY, Game::getStaticInstance()->mDisplayDimensions, Game::getStaticInstance()->mQuestionBlockDimensions);


	fin.ignore();


	// Get the Empty Question Block Spritesheet
	fin >> input;
	fin >> input;
	Game::getStaticInstance()->mBufferManager.addBuffer(ASSET_PATH_TWO + input, NAME_OF_EMPTY_QUESTION_BLOCK);

	// Get the dimensions of the Empty Question Block Sprite
	fin >> input;
	fin >> input;
	Game::getStaticInstance()->mQuestionBlockEmptyDimensions.mX = stoi(input);
	fin >> input;
	Game::getStaticInstance()->mQuestionBlockEmptyDimensions.mY = stoi(input);

	// Get the Sprites per row and column for the Empty Question Block Sprites
	fin >> input;
	fin >> input;
	temp.mX = stoi(input);
	fin >> input;
	temp.mY = stoi(input);
	Game::getStaticInstance()->mQuestionBlockEmptyAnimation = new Animation(Game::getStaticInstance()->mBufferManager.getBuffer(NAME_OF_EMPTY_QUESTION_BLOCK), temp.mX, temp.mY, Game::getStaticInstance()->mDisplayDimensions, Game::getStaticInstance()->mQuestionBlockEmptyDimensions);


//	delete tempColor;
}