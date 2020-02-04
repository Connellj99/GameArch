/*
Author: Grady Mayo
Class: EGP-310 <Section 01>
Assignment: Midterm
Certification of Authenticity: I certify that this assignment is entirely my own work.
*/

#include "Level.h"

Level::Level(string filename)
{
	mFilename = filename;
	readFromFile();
}

Level::~Level()
{
	int size = mvWallList.size();
	for (int i = 0; i < size; i++)
	{
		delete mvWallList[i];
	}

	mvWallList.clear();
}

void Level::readFromFile()
{
	ifstream input;
	string info;

	input.open(mFilename);

	while (!input.eof())
	{
		input >> info;

		if (info == "ASSET_PATH")
		{
			input >> info;
			mAssetPath = info;
		}
		if (info == "FONT_FILENAME")
		{
			input >> info;
			mFontFilename = info;
		}
		if (info == "FONT_SIZE")
		{
			input >> info;
			mFontSize = stoi(info);
		}
		if (info == "WALL_FILENAME")
		{
			input >> info;
			mWallFilename = info;
		}
		if (info == "HEAD_FILENAME")
		{
			input >> info;
			mHeadFilename = info;
		}
		if (info == "BODY_FILENAME")
		{
			input >> info;
			mBodyFilename = info;
		}
		if (info == "BACKGROUND_FILENAME")
		{
			input >> info;
			mBackgroundFilename = info;
		}
		if (info == "FOOD_FILENAME")
		{
			input >> info;
			mFoodFilename = info;
		}
		if (info == "FOOD_ROW")
		{
			input >> info;
			mFoodRow = stoi(info);
		}
		if (info == "FOOD_COL")
		{
			input >> info;
			mFoodCol = stoi(info);
		}
		if (info == "BONUS_FILENAME")
		{
			input >> info;
			mBonusFilename = info;
		}
		if (info == "BONUS_ROW")
		{
			input >> info;
			mBonusRow = stoi(info);
		}
		if (info == "BONUS_COL")
		{
			input >> info;
			mBonusCol = stoi(info);
		}
		if (info == "FAST_FILENAME")
		{
			input >> info;
			mFastFilename = info;
		}
		if (info == "FAST_ROW")
		{
			input >> info;
			mFastRow = stoi(info);
		}
		if (info == "FAST_COL")
		{
			input >> info;
			mFastCol = stoi(info);
		}
		if (info == "SLOW_FILENAME")
		{
			input >> info;
			mSlowFilename = info;
		}
		if (info == "SLOW_ROW")
		{
			input >> info;
			mSlowRow = stoi(info);
		}
		if (info == "SLOW_COL")
		{
			input >> info;
			mSlowCol = stoi(info);
		}
		if (info == "DISPLAY_WIDTH")
		{
			input >> info;
			mDispWidth = stoi(info);
		}
		if (info == "DISPLAY_HEIGHT")
		{
			input >> info;
			mDispHeight = stoi(info);
		}
		if (info == "DESIRED_FPS")
		{
			input >> info;
			mDesiredFPS = MILLI_SEC/stoi(info);
		}
		if (info == "SPRITE_SIZE")
		{
			input >> info;
			mSpriteSize = stoi(info);
		}
		if (info == "NUM_WALLS")
		{
			input >> info;
			int size = stoi(info);
			for (int i = 0; i < size; i++)
			{
				mvWallList.push_back(new Vector2D);
			}
			mNumWalls = stoi(info);
		}
		if (info == "W1_X")
		{
			input >> info;
			mvWallList[0]->setX(stoi(info));
		}
		if (info == "W1_Y")
		{
			input >> info;
			mvWallList[0]->setY(stoi(info));
		}
		if (info == "W2_X")
		{
			input >> info;
			mvWallList[1]->setX(stoi(info));
		}
		if (info == "W2_Y")
		{
			input >> info;
			mvWallList[1]->setY(stoi(info));
		}
		if (info == "W3_X")
		{
			input >> info;
			mvWallList[2]->setX(stoi(info));
		}
		if (info == "W3_Y")
		{
			input >> info;
			mvWallList[2]->setY(stoi(info));
		}
		if (info == "W4_X")
		{
			input >> info;
			mvWallList[3]->setX(stoi(info));
		}
		if (info == "W4_Y")
		{
			input >> info;
			mvWallList[3]->setY(stoi(info));
		}
		if (info == "W5_X")
		{
			input >> info;
			mvWallList[4]->setX(stoi(info));
		}
		if (info == "W5_Y")
		{
			input >> info;
			mvWallList[4]->setY(stoi(info));
		}
		if (info == "SPEED")
		{
			input >> info;
			mSpeed = stoi(info);
		}
		if (info == "SEGMENTS")
		{
			input >> info;
			mSegments = stoi(info);
		}
		if (info == "TARGET")
		{
			input >> info;
			mTarget = stoi(info);
		}
		if (info == "FOOD_SCORE")
		{
			input >> info;
			mFoodScore = stoi(info);
		}
		if (info == "POWER_FREQ")
		{
			input >> info;
			mPowerFreq = stoi(info);
		}
		if (info == "FAST_VALUE")
		{
			input >> info;
			mFastValue = stoi(info);
		}
		if (info == "SLOW_VALUE")
		{
			input >> info;
			mSlowValue = stoi(info);
		}
		if (info == "BONUS_VALUE")
		{
			input >> info;
			mBonusValue = stoi(info);
		}
	}
}