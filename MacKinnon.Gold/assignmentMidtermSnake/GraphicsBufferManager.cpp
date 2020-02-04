#include "GraphicsBufferManager.h"


//constructor
GraphicsBufferManager::GraphicsBufferManager()
{

}

//destructor
GraphicsBufferManager::~GraphicsBufferManager()
{
	clear();
}

//adds a graphics buffer to the map and returns the graphics buffer pointer
GraphicsBuffer* GraphicsBufferManager::addGraphicsBuffer(std::string filePath, const Key& key)
{
	GraphicsBuffer* pGraphicsBuffer = NULL;
	std::map<Key, GraphicsBuffer*>::iterator itr = mGraphicsBuffersMap.find(key);
	if (itr == mGraphicsBuffersMap.end()) 
	{
		pGraphicsBuffer = new GraphicsBuffer(filePath, true); 
		mGraphicsBuffersMap[key] = pGraphicsBuffer;
	}
	return pGraphicsBuffer;
}

//gets a specifc graphics buffer by iterating through a map using the key
GraphicsBuffer * GraphicsBufferManager::getGraphicsBuffer(Key key)
{
	std::map<Key, GraphicsBuffer*>::const_iterator itr = mGraphicsBuffersMap.find(key);
	if (itr != mGraphicsBuffersMap.end()) 
	{
		return itr->second;
	}
	else 
	{
		return NULL;
	}
}

//deletes all remaining graphics buffers during cleanup
void GraphicsBufferManager::clear()
{
	std::map<Key, GraphicsBuffer*>::iterator itr;
	for (itr = mGraphicsBuffersMap.begin(); itr != mGraphicsBuffersMap.end(); itr++) 
	{
		GraphicsBuffer* pGraphicsBuffer = itr->second;
		delete pGraphicsBuffer;
	}
	mGraphicsBuffersMap.clear();
}

//deletes a specifc graphics buffer based on its key in the map
void GraphicsBufferManager::removeGraphicsBuffer(const Key& key)
{
	delete mGraphicsBuffersMap[key];
	mGraphicsBuffersMap.erase(key);
}
