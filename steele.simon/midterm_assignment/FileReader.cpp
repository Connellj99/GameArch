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


	// Get the Centipede Sprite Dimensions
	fin >> input;
	fin >> input;
	Game::getStaticInstance()->mCentipedeDimensions.mX = stoi(input);
	fin >> input;
	Game::getStaticInstance()->mCentipedeDimensions.mY = stoi(input);

	// Get the Centipede Segment Spritesheet
	fin >> input;
	fin >> input;
	Game::getStaticInstance()->mBufferManager.addBuffer(ASSET_PATH_TWO + input, NAME_OF_CENTIPEDE_SEGMENT_BUFFER);

	// Get the Centipede Head Spritesheet
	fin >> input;
	fin >> input;
	Game::getStaticInstance()->mBufferManager.addBuffer(ASSET_PATH_TWO + input, NAME_OF_CENTIPEDE_HEAD_BUFFER);

	// Get the Sprites per row and column for the Centipede Sprites
	fin >> input;
	fin >> input;
	temp.mX = stoi(input);
	fin >> input;
	temp.mY = stoi(input);
	Game::getStaticInstance()->mCentipedeHeadAnimation = new Animation(Game::getStaticInstance()->mBufferManager.getBuffer(NAME_OF_CENTIPEDE_HEAD_BUFFER), temp.mX, temp.mY, Game::getStaticInstance()->mDisplayDimensions, Game::getStaticInstance()->mCentipedeDimensions);
	Game::getStaticInstance()->mCentipedeSegmentAnimation = new Animation(Game::getStaticInstance()->mBufferManager.getBuffer(NAME_OF_CENTIPEDE_SEGMENT_BUFFER), temp.mX, temp.mY, Game::getStaticInstance()->mDisplayDimensions, Game::getStaticInstance()->mCentipedeDimensions);


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

	// Get the boundaries for the Player
	fin >> input;
	fin >> input;
	Game::getStaticInstance()->mPlayerBounds.mX = stoi(input);
	fin >> input;
	Game::getStaticInstance()->mPlayerBounds.mY = stoi(input);

	// Get the initial lives for the play per each game iteration
	fin >> input;
	fin >> input;
	Game::getStaticInstance()->mPlayerInitialLives = stoi(input);


	fin.ignore();


	// Get the Bullet Spritesheet
	fin >> input;
	fin >> input;
	Game::getStaticInstance()->mBufferManager.addBuffer(ASSET_PATH_TWO + input, NAME_OF_BULLET);

	// Get the dimensions of the bullet Sprites
	fin >> input;
	fin >> input;
	Game::getStaticInstance()->mBulletDimensions.mX = stoi(input);
	fin >> input;
	Game::getStaticInstance()->mBulletDimensions.mY = stoi(input);

	// Get the Sprites per row and column for the Bullet Sprites
	fin >> input;
	fin >> input;
	temp.mX = stoi(input);
	fin >> input;
	temp.mY = stoi(input);
	Game::getStaticInstance()->mBulletAnimation = new Animation(Game::getStaticInstance()->mBufferManager.getBuffer(NAME_OF_BULLET), temp.mX, temp.mY, Game::getStaticInstance()->mDisplayDimensions, Game::getStaticInstance()->mBulletDimensions);

	// Get the speed of the bullet
	fin >> input;
	fin >> input;
	Game::getStaticInstance()->mBulletSpeed = stoi(input);


	fin.ignore();


	// Get the Dimensions of the Mushroom Sprites
	fin >> input;
	fin >> input;
	Game::getStaticInstance()->mMushroomDimensions.mX = stoi(input);
	fin >> input;
	Game::getStaticInstance()->mMushroomDimensions.mY = stoi(input);

	// Get the First Mushroom Spritesheet
	fin >> input;
	fin >> input;
	Game::getStaticInstance()->mBufferManager.addBuffer(ASSET_PATH_TWO + input, NAME_OF_FIRST_MUSHROOM);

	// Get the Second Mushroom Spritesheet
	fin >> input;
	fin >> input;
	Game::getStaticInstance()->mBufferManager.addBuffer(ASSET_PATH_TWO + input, NAME_OF_SECOND_MUSHROOM);

	// Get the Third Mushroom Spritesheet
	fin >> input;
	fin >> input;
	Game::getStaticInstance()->mBufferManager.addBuffer(ASSET_PATH_TWO + input, NAME_OF_THIRD_MUSHROOM);

	// Get the Fourth Mushroom Spritesheet
	fin >> input;
	fin >> input;
	Game::getStaticInstance()->mBufferManager.addBuffer(ASSET_PATH_TWO + input, NAME_OF_FOURTH_MUSHROOM);

	// Get the Sprites per row and column for the Mushroom Sprites
	fin >> input;
	fin >> input;
	temp.mX = stoi(input);
	fin >> input;
	temp.mY = stoi(input);
	Game::getStaticInstance()->mMushroomOneAnimation = new Animation(Game::getStaticInstance()->mBufferManager.getBuffer(NAME_OF_FIRST_MUSHROOM), temp.mX, temp.mY, Game::getStaticInstance()->mDisplayDimensions, Game::getStaticInstance()->mMushroomDimensions);
	Game::getStaticInstance()->mMushroomTwoAnimation = new Animation(Game::getStaticInstance()->mBufferManager.getBuffer(NAME_OF_SECOND_MUSHROOM), temp.mX, temp.mY, Game::getStaticInstance()->mDisplayDimensions, Game::getStaticInstance()->mMushroomDimensions);
	Game::getStaticInstance()->mMushroomThreeAnimation = new Animation(Game::getStaticInstance()->mBufferManager.getBuffer(NAME_OF_THIRD_MUSHROOM), temp.mX, temp.mY, Game::getStaticInstance()->mDisplayDimensions, Game::getStaticInstance()->mMushroomDimensions);
	Game::getStaticInstance()->mMushroomFourAnimation = new Animation(Game::getStaticInstance()->mBufferManager.getBuffer(NAME_OF_FOURTH_MUSHROOM), temp.mX, temp.mY, Game::getStaticInstance()->mDisplayDimensions, Game::getStaticInstance()->mMushroomDimensions);


	fin.ignore();


	// Get the number of Segments per centipede spawned
	fin >> input;
	fin >> input;
	Game::getStaticInstance()->mNumOfSegments = stoi(input);
	Game::getStaticInstance()->mNumOfSegmentsRemaining = Game::getStaticInstance()->mNumOfSegments;

	// Get the initial speed of the centipede
	fin >> input;
	fin >> input;
	Game::getStaticInstance()->mInitialSpeedOfCentipede = stod(input);

	// Get the initial position of the position of the Centipede
	fin >> input;
	fin >> input;
	Game::getStaticInstance()->mInitialCentipedePosition.mX = stoi(input);
	fin >> input;
	Game::getStaticInstance()->mInitialCentipedePosition.mY = stoi(input);


	fin.ignore();


	// Get the number of Mushrooms spawned per each game
	fin >> input;
	fin >> input;
	Game::getStaticInstance()->mMushroomsPerLevel = stoi(input);

	// Get the initial health the mushrooms should be at
	fin >> input;
	fin >> input;
	Game::getStaticInstance()->mInitialHealthOfAMushroom = stoi(input);


	fin.ignore();


	// Get the Color for the Text Font
	fin >> input;
	fin >> input;
	tempColor->setR(stod(input));
	fin >> input;
	tempColor->setG(stod(input));
	fin >> input;
	tempColor->setB(stod(input));


	// Get the Font file for the In-game font
	fin >> input;
	fin >> input;
	Game::getStaticInstance()->mGameFont = new Font(ASSET_PATH_TWO + input);
	Game::getStaticInstance()->mTextManager->addText(NAME_OF_INTRO_TEXT, ASSET_PATH_TWO + input, 0, *tempColor, "", Vector2(0, 0));
	Game::getStaticInstance()->mTextManager->addText(NAME_OF_INSTRUCT_TEXT, ASSET_PATH_TWO + input, 0, *tempColor, "", Vector2(0, 0));
	Game::getStaticInstance()->mTextManager->addText(NAME_OF_END_TEXT, ASSET_PATH_TWO + input, 0, *tempColor, "", Vector2(0, 0));
	Game::getStaticInstance()->mTextManager->addText(NAME_OF_SCORE_TEXT, ASSET_PATH_TWO + input, 0, *tempColor, to_string(Game::getStaticInstance()->mScore), Vector2(0, 0));
	Game::getStaticInstance()->mTextManager->addText(NAME_OF_FPS_TEXT, ASSET_PATH_TWO + input, 0, *tempColor, to_string(Game::getStaticInstance()->mFramesPerSecond), Vector2(0, 0));
	Game::getStaticInstance()->mTextManager->addText(NAME_OF_LIVES_REMAINING_DISPLAY_TEXT, ASSET_PATH_TWO + input, 0, Color(255, 0, 0), "", Vector2(0, 0));
	Game::getStaticInstance()->mTextManager->addText(NAME_OF_LIVES_REMAINING_TEXT, ASSET_PATH_TWO + input, 0, Color(255, 0, 0), "", Vector2(0, 0));


	fin.ignore();


	// Get the Position of the Introductory Text
	fin >> input;
	fin >> input;
	temp.mX = stoi(input);
	fin >> input;
	temp.mY = stoi(input);
	Game::getStaticInstance()->mTextManager->getText(NAME_OF_INTRO_TEXT)->setTextPosition(temp);

	// Get the Font size of the Introductory Text
	fin >> input;
	fin >> input;
	Game::getStaticInstance()->mTextManager->getText(NAME_OF_INTRO_TEXT)->changeFontSize(stoi(input));

	// Get the Message of the Introductory Text
	tempStr = "";
	fin >> input;
	fin >> input;
	fin >> input;
	while (input != "\"")
	{
		tempStr += input + "  ";
		fin >> input;
	}
	Game::getStaticInstance()->mTextManager->getText(NAME_OF_INTRO_TEXT)->changeMessage(tempStr);


	fin.ignore();


	// Get the Position of the Instructional Text
	fin >> input;
	fin >> input;
	temp.mX = stoi(input);
	fin >> input;
	temp.mY = stoi(input);
	Game::getStaticInstance()->mTextManager->getText(NAME_OF_INSTRUCT_TEXT)->setTextPosition(temp);

	// Get the Font size of the Instructional Text
	fin >> input;
	fin >> input;
	Game::getStaticInstance()->mTextManager->getText(NAME_OF_INSTRUCT_TEXT)->changeFontSize(stoi(input));

	// Get the Message of the Instructional Text
	tempStr = "";
	fin >> input;
	fin >> input;
	fin >> input;
	while (input != "\"")
	{
		tempStr += input + "  ";
		fin >> input;
	}
	Game::getStaticInstance()->mTextManager->getText(NAME_OF_INSTRUCT_TEXT)->changeMessage(tempStr);


	fin.ignore();


	// Get the Position of the End Text
	fin >> input;
	fin >> input;
	temp.mX = stoi(input);
	fin >> input;
	temp.mY = stoi(input);
	Game::getStaticInstance()->mTextManager->getText(NAME_OF_END_TEXT)->setTextPosition(temp);

	// Get the Font size of the End Text
	fin >> input;
	fin >> input;
	Game::getStaticInstance()->mTextManager->getText(NAME_OF_END_TEXT)->changeFontSize(stoi(input));

	// Get the message of the End Text
	tempStr = "";
	fin >> input;
	fin >> input;
	fin >> input;
	while (input != "\"")
	{
		tempStr += input + "  ";
		fin >> input;
	}
	Game::getStaticInstance()->mTextManager->getText(NAME_OF_END_TEXT)->changeMessage(tempStr);


	fin.ignore();


	// Get the position of the Score Text
	fin >> input;
	fin >> input;
	temp.mX = stoi(input);
	fin >> input;
	temp.mY = stoi(input);
	Game::getStaticInstance()->mTextManager->getText(NAME_OF_SCORE_TEXT)->setTextPosition(temp);

	// Get the Font size of the Score Text
	fin >> input;
	fin >> input;
	Game::getStaticInstance()->mTextManager->getText(NAME_OF_SCORE_TEXT)->changeFontSize(stoi(input));

	// Get the message of the Score text
	tempStr = "";
	fin >> input;
	fin >> input;
	fin >> input;
	while (input != "\"")
	{
		tempStr += input + "  ";
		fin >> input;
	}
	Game::getStaticInstance()->mScoreTextMessage = tempStr;


	fin.ignore();


	// Get the position of the lives remaining display text
	fin >> input;
	fin >> input;
	temp.mX = stoi(input);
	fin >> input;
	temp.mY = stoi(input);
	Game::getStaticInstance()->mTextManager->getText(NAME_OF_LIVES_REMAINING_DISPLAY_TEXT)->setTextPosition(temp);

	// Get the Font size of the Lives Remaining display Text
	fin >> input;
	fin >> input;
	Game::getStaticInstance()->mTextManager->getText(NAME_OF_LIVES_REMAINING_DISPLAY_TEXT)->changeFontSize(stoi(input));

	// Get the message for the Lives Remaining display Text
	tempStr = "";
	fin >> input;
	fin >> input;
	fin >> input;
	while (input != "\"")
	{
		tempStr += input + "  ";
		fin >> input;
	}
	Game::getStaticInstance()->mLivesRemainingDisplayTextMessage = tempStr;


	fin.ignore();


	// Get the position of the lives remaining text
	fin >> input;
	fin >> input;
	temp.mX = stoi(input);
	fin >> input;
	temp.mY = stoi(input);
	Game::getStaticInstance()->mTextManager->getText(NAME_OF_LIVES_REMAINING_TEXT)->setTextPosition(temp);

	// Get the Font size of the Lives Remaining Text
	fin >> input;
	fin >> input;
	Game::getStaticInstance()->mTextManager->getText(NAME_OF_LIVES_REMAINING_TEXT)->changeFontSize(stoi(input));

	// Get the message for the Lives Remaining Text
	tempStr = "";
	fin >> input;
	fin >> input;
	fin >> input;
	while (input != "\"")
	{
		tempStr += input + "  ";
		fin >> input;
	}
	Game::getStaticInstance()->mLivesRemainingTextMessage = tempStr;


	fin.ignore();


	// Get the position of the FPS Text
	fin >> input;
	fin >> input;
	temp.mX = stoi(input);
	fin >> input;
	temp.mY = stoi(input);
	Game::getStaticInstance()->mTextManager->getText(NAME_OF_FPS_TEXT)->setTextPosition(temp);

	// Get the Font size of the FPS Text
	fin >> input;
	fin >> input;
	Game::getStaticInstance()->mTextManager->getText(NAME_OF_FPS_TEXT)->changeFontSize(stoi(input));

	// Get the message of the FPS text
	tempStr = "";
	fin >> input;
	fin >> input;
	fin >> input;
	while (input != "\"")
	{
		tempStr += input + "  ";
		fin >> input;
	}
	Game::getStaticInstance()->mFPSTextMessage = tempStr;


	fin.ignore();


	// Get the scoring value for a Centipede Segment
	fin >> input;
	fin >> input;
	Game::getStaticInstance()->mCentipedeScoringValue = stoi(input);

	// Get the minimum scoring value for an extra life
	fin >> input;
	fin >> input;
	Game::getStaticInstance()->mExtraLifeMinimumScore = stoi(input);


	// Close the text file
	fin.close();

	// Delete all dynamic memory
	delete tempColor;
}