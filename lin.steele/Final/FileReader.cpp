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
	Color * tempColor = new Color(0, 0, 0);

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
	Game::getStaticInstance()->mPlayerAnimation = new Animation(NAME_OF_PLAYER, Game::getStaticInstance()->mBufferManager.getBuffer(NAME_OF_PLAYER), temp.mX, temp.mY, Game::getStaticInstance()->mDisplayDimensions, Game::getStaticInstance()->mPlayerDimensions);


	fin.ignore();


	// Get the Player Jump Spritesheet
	fin >> input;
	fin >> input;
	Game::getStaticInstance()->mBufferManager.addBuffer(ASSET_PATH_TWO + input, NAME_OF_PLAYER_JUMP);

	// Get the Sprites per row and column for the Player Jump Sprites
	fin >> input;
	fin >> input;
	temp.mX = stoi(input);
	fin >> input;
	temp.mY = stoi(input);
	Game::getStaticInstance()->mPlayerJumpAnimation = new Animation(NAME_OF_PLAYER_JUMP, Game::getStaticInstance()->mBufferManager.getBuffer(NAME_OF_PLAYER_JUMP), temp.mX, temp.mY, Game::getStaticInstance()->mDisplayDimensions, Game::getStaticInstance()->mPlayerDimensions);


	fin.ignore();


	// Get the Player Jump Spritesheet
	fin >> input;
	fin >> input;
	Game::getStaticInstance()->mBufferManager.addBuffer(ASSET_PATH_TWO + input, NAME_OF_PLAYER_JUMP_LEFT);

	// Get the Sprites per row and column for the Player Jump Sprites
	fin >> input;
	fin >> input;
	temp.mX = stoi(input);
	fin >> input;
	temp.mY = stoi(input);
	Game::getStaticInstance()->mPlayerJumpLeftAnimation = new Animation(NAME_OF_PLAYER_JUMP_LEFT, Game::getStaticInstance()->mBufferManager.getBuffer(NAME_OF_PLAYER_JUMP_LEFT), temp.mX, temp.mY, Game::getStaticInstance()->mDisplayDimensions, Game::getStaticInstance()->mPlayerDimensions);


	fin.ignore();


	// Get the Player Jump Spritesheet
	fin >> input;
	fin >> input;
	Game::getStaticInstance()->mBufferManager.addBuffer(ASSET_PATH_TWO + input, NAME_OF_PLAYER_WALKING_LEFT);

	// Get the Sprites per row and column for the Player Jump Sprites
	fin >> input;
	fin >> input;
	temp.mX = stoi(input);
	fin >> input;
	temp.mY = stoi(input);
	Game::getStaticInstance()->mPlayerWalkingAnimationLeft = new Animation(NAME_OF_PLAYER_WALKING_LEFT, Game::getStaticInstance()->mBufferManager.getBuffer(NAME_OF_PLAYER_WALKING_LEFT), temp.mX, temp.mY, Game::getStaticInstance()->mDisplayDimensions, Game::getStaticInstance()->mPlayerDimensions);


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
	Game::getStaticInstance()->mDefaultBlockAnimation = new Animation(NAME_OF_DEFAULT_BLOCK, Game::getStaticInstance()->mBufferManager.getBuffer(NAME_OF_DEFAULT_BLOCK), temp.mX, temp.mY, Game::getStaticInstance()->mDisplayDimensions, Game::getStaticInstance()->mDefaultBlockDimensions);


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
	Game::getStaticInstance()->mBrickBlockAnimation = new Animation(NAME_OF_BRICK_BLOCK, Game::getStaticInstance()->mBufferManager.getBuffer(NAME_OF_BRICK_BLOCK), temp.mX, temp.mY, Game::getStaticInstance()->mDisplayDimensions, Game::getStaticInstance()->mBrickBlockDimensions);


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
	Game::getStaticInstance()->mQuestionBlockAnimation = new Animation(NAME_OF_QUESTION_BLOCK, Game::getStaticInstance()->mBufferManager.getBuffer(NAME_OF_QUESTION_BLOCK), temp.mX, temp.mY, Game::getStaticInstance()->mDisplayDimensions, Game::getStaticInstance()->mQuestionBlockDimensions);


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
	Game::getStaticInstance()->mQuestionBlockEmptyAnimation = new Animation(NAME_OF_EMPTY_QUESTION_BLOCK, Game::getStaticInstance()->mBufferManager.getBuffer(NAME_OF_EMPTY_QUESTION_BLOCK), temp.mX, temp.mY, Game::getStaticInstance()->mDisplayDimensions, Game::getStaticInstance()->mQuestionBlockEmptyDimensions);


	fin.ignore();


	// Get the Goomba Spritesheet
	fin >> input;
	fin >> input;
	Game::getStaticInstance()->mBufferManager.addBuffer(ASSET_PATH_TWO + input, NAME_OF_GOOMBA);

	// Get the dimensions of the Goomba Sprite
	fin >> input;
	fin >> input;
	Game::getStaticInstance()->mGoombaDimensions.mX = stoi(input);
	fin >> input;
	Game::getStaticInstance()->mGoombaDimensions.mY = stoi(input);

	// Get the Sprites per row and column for the Goomba Sprites
	fin >> input;
	fin >> input;
	temp.mX = stoi(input);
	fin >> input;
	temp.mY = stoi(input);
	Game::getStaticInstance()->mGoombaAnimation = new Animation(NAME_OF_GOOMBA, Game::getStaticInstance()->mBufferManager.getBuffer(NAME_OF_GOOMBA), temp.mX, temp.mY, Game::getStaticInstance()->mDisplayDimensions, Game::getStaticInstance()->mGoombaDimensions);

	
	fin.ignore();


	// Get the Goomba Spritesheet
	fin >> input;
	fin >> input;
	Game::getStaticInstance()->mBufferManager.addBuffer(ASSET_PATH_TWO + input, NAME_OF_BIG_HILL);

	// Get the Sprites per row and column for the Goomba Sprites
	fin >> input;
	fin >> input;
	temp.mX = stoi(input);
	fin >> input;
	temp.mY = stoi(input);
	Game::getStaticInstance()->mBigHillAnimation = new Animation(NAME_OF_BIG_HILL, Game::getStaticInstance()->mBufferManager.getBuffer(NAME_OF_BIG_HILL), 1, 1, Game::getStaticInstance()->mDisplayDimensions, temp);


	fin.ignore();


	// Get the Goomba Spritesheet
	fin >> input;
	fin >> input;
	Game::getStaticInstance()->mBufferManager.addBuffer(ASSET_PATH_TWO + input, NAME_OF_CLOUD);

	// Get the Sprites per row and column for the Goomba Sprites
	fin >> input;
	fin >> input;
	temp.mX = stoi(input);
	fin >> input;
	temp.mY = stoi(input);
	Game::getStaticInstance()->mCloudAnimation = new Animation(NAME_OF_CLOUD, Game::getStaticInstance()->mBufferManager.getBuffer(NAME_OF_CLOUD), 1, 1, Game::getStaticInstance()->mDisplayDimensions, temp);

	delete tempColor;
}

void FileReader::readUIFile(string fileName)
{
	string input;
	ifstream fin;
	Vector2 temp = Vector2(0, 0);
	string tempStr = "";
	Color * tempColor = new Color(0, 0, 0);

	// Open the text file
	fin.open(fileName);

	fin >> input;//Header

	// Get the File name of the font
	fin >> input;//Name
	fin >> input;//File Path
	Game::getStaticInstance()->mUIFont = new Font(input);

	fin.ignore();// go to next line

	//Get the Font color
	fin >> input;//Name
	fin >> input;//get the r
	tempColor->setR((stof(input.c_str())));//set the r

	fin >> input;//get the g
	tempColor->setG((stof(input.c_str())));//set the g

	fin >> input;//get the b
	tempColor->setB((stof(input.c_str())));//set the b
	
	//Set the member font colors value to the temp ones
	Game::getStaticInstance()->mUIFontColor->setR(tempColor->getR());
	Game::getStaticInstance()->mUIFontColor->setG(tempColor->getG());
	Game::getStaticInstance()->mUIFontColor->setB(tempColor->getB());

	fin.ignore();
	// Delete the temporary color pointer
	delete tempColor;
}
