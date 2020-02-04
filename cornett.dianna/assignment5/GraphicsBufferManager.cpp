/*
Author: Amelia Payne
Class: EGP-310 <2>
Assignment: pa 4
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/


#include "GraphicsBufferManager.h"

/*
Set up the graphicsBuffer
*/
GraphicsBufferManager::GraphicsBufferManager() 
{
	mIsInit = true;
}

/*
Call clear to deallocate all data before destroying
*/
GraphicsBufferManager::~GraphicsBufferManager() 
{
	clear();
}

/*
Remove all the items from mGraphicsBuffer and deallocate the memory
*/
void GraphicsBufferManager::clear() 
{
	if (mIsInit) 
	{
		mIsInit = false;

		//Loop through and delete the buffers
		for (auto const& x : mGraphicsBuffers)
		{
			delete x.second;
		}
	}
}

/*
Add a new key, value pair to the map of graphicsBuffers
*/
void GraphicsBufferManager::addBuffer(std::string name, GraphicsBuffer* buffer)
{
	mGraphicsBuffers.insert(std::pair<std::string, GraphicsBuffer *>(name, buffer));
}

/*
Get a buffer pointer with a given name (key)
*/
GraphicsBuffer * GraphicsBufferManager::getBuffer(std::string name) 
{
	return mGraphicsBuffers[name];
}


/*
Delete a buffer with a given key
*/
void GraphicsBufferManager::deleteBufferWithKey(std::string name)
{
	GraphicsBuffer * temp = mGraphicsBuffers[name];
	mGraphicsBuffers.erase(name);
	delete temp;
}