#pragma once
#include "Trackable.h"
#include <iterator>
#include <map>
#include <string>

class GBuffer;

class GBufferManager : public Trackable		//A class to hold all the GraphicsBuffers in the game (except the backbuffer which should still reside in the GraphicsSystem – although having a way of getting to it through the GraphicsBufferManager is not a bad idea) 
{
public:

	GBuffer* getBuffer(std::string key) { return mpBufferMap.at(key); };

	void init(std::string filename);
	void cleanup();

	GBufferManager();
	//GBufferManager();
	~GBufferManager();

	void addBuffer(std::string key, GBuffer* object);
	void removeBuffer(std::string key);

	void clearAllBuffers();

	void createNewBuffer(std::string key, std::string path, std::string filename);

	//int getCount() { return mCount;  };

private:

	//static int mCount;

	std::map<std::string, GBuffer*> mpBufferMap;
};