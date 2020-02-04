#include "GameData.h"
#include <fstream>

void GameData::read(const std::string& configFilepath)
{
	std::ifstream input;
	input.open(configFilepath);

	if(input.good())
	{
		std::string index;
		while(input >> index)
		{
			if(index == "DISPLAY_DIMENSIONS")
			{
				float x; input >> x;
				float y; input >> y;
				mDisplayDimesions = Vector2D(x, y);
			}
			else if(index == "TARGET_FRAME_RATE")
			{
				input >> mTargetFrameRate;
			}
			else if(index == "ASSET_PATH")
			{
				input >> mAssetPath;
			}
			else if(index == "BACKGROUND_COLOR")
			{
				input >> mBackgroundColor.r;
				input >> mBackgroundColor.g;
				input >> mBackgroundColor.b;
				input >> mBackgroundColor.a;
			}
			else if(index == "PLAYER_READY_BUFFER_FILENAME")
			{
				input >> mPlayerReadyBufferFilename;
			}
			else if(index == "PLAYER_RELOAD_BUFFER_FILENAME")
			{
				input >> mPlayerReloadBufferFilename;
			}
			else if(index == "BULLET_BUFFER_FILENAME")
			{
				input >> mBulletBufferFilename;
			}
			else if(index == "MUSHROOM_BUFFER_FILENAME")
			{
				input >> mMushroomBufferFilename;
			}
			else if (index == "CENTIPEDE_BODY_BUFFER_FILENAME")
			{
				input >> mCentipedeBodyBufferFilename;
			}
			else if (index == "CENTIPEDE_HEAD_BUFFER_FILENAME")
			{
				input >> mCentipedeHeadBufferFilename;
			}
			else if (index == "FONT_FILENAME")
			{
				input >> mFontFilename;
			}
		}
	}
}
