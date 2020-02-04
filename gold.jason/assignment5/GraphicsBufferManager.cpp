#include "GraphicsBufferManager.h"

GraphicsBufferManager::GraphicsBufferManager()
{

}

GraphicsBufferManager::~GraphicsBufferManager()
{
	graphicsBufferManagerCleanUp();
}

GraphicsBuffer* GraphicsBufferManager::addBuffer(std::string filename, const Key& ID)
{
	GraphicsBuffer* pBuffer = NULL;
	std::map<Key, GraphicsBuffer*>::iterator finder = mGraphicsBufferMap.find(ID);
	if (finder == mGraphicsBufferMap.end())
	{
		pBuffer = new GraphicsBuffer(filename, true);
		mGraphicsBufferMap[ID] = pBuffer;
	}
	return pBuffer;
}

void GraphicsBufferManager::graphicsBufferManagerCleanUp()
{
	std::map<Key, GraphicsBuffer*>::iterator finder;
	for (finder = mGraphicsBufferMap.begin(); finder != mGraphicsBufferMap.end(); ++finder)
	{
		GraphicsBuffer* pBuffer = finder->second;
		delete pBuffer;
	}
	mGraphicsBufferMap.clear();
}

void GraphicsBufferManager::removeBuffer(Key key)
{
	std::map<Key, GraphicsBuffer*>::iterator finder = mGraphicsBufferMap.find(key);
	if (finder != mGraphicsBufferMap.end())
	{
		delete finder->second;
		mGraphicsBufferMap.erase(finder);
	}
}

GraphicsBuffer* GraphicsBufferManager::getGraphicsBuffer(Key key)
{
	std::map<Key, GraphicsBuffer*>::const_iterator finder = mGraphicsBufferMap.find(key);
	if (finder != mGraphicsBufferMap.end())
	{
		return finder->second;
	}
	else
	{
		return NULL;
	}
}
