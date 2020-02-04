#include "GBufferManager.h"
#include "GraphicsBuffer.h"
//#include <string>

//int GBufferManager::mCount = 0;

GBufferManager::GBufferManager()
{
	//mpBufferMap = new map<std::string, GBuffer*>();
}

GBufferManager::~GBufferManager()
{
	cleanup();
}

void GBufferManager::init(std::string filename)
{
	

}

void GBufferManager::cleanup()
{
	clearAllBuffers();
}

void GBufferManager::addBuffer(std::string key, GBuffer* object)
{
	mpBufferMap.insert(pair<std::string, GBuffer*>(key, object));
}

void GBufferManager::removeBuffer(std::string key)
{
	mpBufferMap.erase(key);
	delete mpBufferMap.at(key);
}

void GBufferManager::clearAllBuffers()
{
	for (map<std::string, GBuffer*>::iterator itr = mpBufferMap.begin(); itr != mpBufferMap.end(); itr++)
	{
		delete itr->second;
		
	}
	mpBufferMap.clear();
}

void GBufferManager::createNewBuffer(std::string key, std::string path, std::string filename)
{
	GBuffer* newBuffer = new GBuffer(path, filename);
	
	addBuffer(key, newBuffer);
}