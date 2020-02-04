#include "GraphicsBufferManager.h"

GraphicsBufferManager::GraphicsBufferManager()
{
	//stub
}

GraphicsBufferManager::~GraphicsBufferManager()
{
	clearAllBuffers();
}

void GraphicsBufferManager::addBuffer(GraphicsBuffer * passedBuffer)
{
	mpListOfBuffers.push_back(passedBuffer);
}

void GraphicsBufferManager::removeBuffer(int index)
{
	mpListOfBuffers.erase(mpListOfBuffers.begin() + index);
}

GraphicsBuffer* GraphicsBufferManager::getBuffer(int index)
{
	return mpListOfBuffers[index];
}

void GraphicsBufferManager::clearAllBuffers()
{
	for (int i = 0; i < (int) mpListOfBuffers.size(); i++)
	{
		if (mpListOfBuffers[i]->returnBitmap() == NULL)
		{

		}
		else
		{
			delete mpListOfBuffers[i];
		}
		
	}
	mpListOfBuffers.clear();
}
