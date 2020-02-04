#include "GraphicsBufferManager.h"

GraphicsBufferManager::GraphicsBufferManager() 
{
}

void GraphicsBufferManager::addBuffer(GraphicsBuffer* buffer)
{
	mBuffers.push_back(buffer);
}

void GraphicsBufferManager::removeBuffer(int bufferName) 
{
	mBuffers.erase(mBuffers.begin() + bufferName);
}

GraphicsBuffer* GraphicsBufferManager::getBuffer(int bufferName)
{
	return mBuffers[bufferName];
}

void GraphicsBufferManager::clear() 
{
	if (!mIsClear) {
		
		for (auto i : mBuffers)
		{
			delete i;
		}

		mIsClear = true;
	}
}

GraphicsBufferManager::~GraphicsBufferManager() 
{
	if (!mIsClear) 
	{
		clear();
	}
}