#include "GraphicsBufferManager.h"

GraphicsBufferManager::GraphicsBufferManager()
{
	initGraphicsBufferManager();
}

GraphicsBufferManager::~GraphicsBufferManager()
{
	cleanup();
}

void GraphicsBufferManager::initGraphicsBufferManager()
{
	//mMap = { {NULL, nullptr} };
	return;
}

void GraphicsBufferManager::addBuffToManager(GraphicsBuffer* buffAdd, string key)
{
	mMap[key] = buffAdd;
}

void GraphicsBufferManager::deleteBuffFromManager(GraphicsBuffer* buffDelete)
{
	map<buffKey, GraphicsBuffer*>::iterator iter;

	//go through all entries in map searching for the specified buffer
	for (iter = mMap.begin(); iter != mMap.end(); ++iter)
	{
		//if found delete
		if (buffDelete == iter->second)
		{
			delete buffDelete;
			mMap.erase(iter);
			return;
		}
	}
}

void GraphicsBufferManager::deleteBuffFromManager(const buffKey & key)
{
	//find out if the key exists
	map<buffKey, GraphicsBuffer*>::iterator iter = mMap.find(key);

	//if found delete
	if (iter != mMap.end())
	{
		delete iter->second;
		mMap.erase(iter);
	}
}

GraphicsBuffer* GraphicsBufferManager::getBuffer(const buffKey& key)
{
	map<buffKey, GraphicsBuffer*>::const_iterator iter = mMap.find(key);

	if (iter != mMap.end())
	{
		return iter->second;
	}
	else
	{
		return NULL;
	}
}

void GraphicsBufferManager::cleanup()
{
	map<buffKey, GraphicsBuffer*>::iterator iter;

	//go through all entries in map and delete
	for (iter = mMap.begin(); iter != mMap.end(); ++iter)
	{
		GraphicsBuffer* pBuff = iter->second;
		delete pBuff;
		pBuff = nullptr;
	}

	mMap.clear();
}
