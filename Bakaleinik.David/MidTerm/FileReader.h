#pragma once
#include "Trackable.h"
#include <cassert>
#include <vector>

class FileReader : public Trackable
{
public:

	static FileReader* getInstance() { assert(msInstance != nullptr); return msInstance; };
	static void initReader(std::string filename, std::string filePath) { msInstance = new FileReader(filename, filePath); };
	static void deleteReader() { delete msInstance; };
	
	std::string getPath() { return mAsset_path; };
	std::string getFont() { return mText_Font; };
	int getTextSize() { return mText_Size; };
	int getMushroomCount() { return mMushroomCount; };
	int getCentipedeSpeed() { return mCentipedeSpeed; };
	int getFPS() { return mFPS; };
	std::vector<std::string>* getMushroomVector() { return &mMushroomImages; };
	std::vector<std::string>* getCentipedeVector() { return &mCentipedeImages; };


private:

	static FileReader* msInstance;
	std::string mFilename;

	std::string mAsset_path;
	
	std::string mText_Font;
	int mText_Size;

	int mMushroomCount;

	int mCentipedeSpeed;
	
	int mFPS;

	std::vector<std::string> mMushroomImages;

	std::vector<std::string> mCentipedeImages;
	

	FileReader(std::string filename, std::string filePath);
	~FileReader() {};

	void readFileData();
	//ifstream - goes until a whitespace


};