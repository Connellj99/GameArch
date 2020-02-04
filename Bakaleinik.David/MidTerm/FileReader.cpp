#include "FileReader.h"
#include <string>
#include <iostream>
#include <fstream>

FileReader* FileReader::msInstance = nullptr;

FileReader::FileReader(std::string filename, std::string filePath)
{
	mFilename = filename;
	mAsset_path = filePath;

	readFileData();
}

void FileReader::readFileData()
{
	std::ifstream input;
	std::string data;
	input.open(mAsset_path+mFilename);

	bool fileCheck = input.is_open();
	while (fileCheck)
	{
		input >> data;

		if (data == "Data_Start")
		{
			//Read the centipede data block
			/*input >> data;
			if (data == "Asset_Path")
			{
				input >> mAsset_path;
			}*/

			input >> data;
			if (data == "Mushroom_Count")
			{
				input >> mMushroomCount;
			}
			
			input >> data;
			if (data == "Centipede_Speed")
			{
				input >> mCentipedeSpeed;
			}
			
			input >> data;
			if (data == "Mushroom_Images")
			{
				for (int i = 0; i < 4; i++)
				{
					input >> data;
					mMushroomImages.push_back(data);
				}
			}
			
			input >> data;
			if (data == "Centipede_Images")
			{
				for (int i = 0; i < 2; i++)
				{
					input >> data;
					mCentipedeImages.push_back(data);
				}

			}

			input >> data;
			if (data == "Target_FPS")
			{
				input >> mFPS;
			}

			input >> data;
			if (data == "Text_Font")
			{
				input >> mText_Font;
				input >> mText_Size;
			}

		}
		else
		{
			std::cout << "Data block not found!" << std::endl;
			fileCheck = false;
		}

		fileCheck = false;
	}
}