/*********************************************************************
**		Author:	Nick DaCosta										**
**		Class: 310 <Section 01>										**
**		Assignment: pa 4											**
**		Certification of Authenticity:								**
**		I certify that this assignment is entirely my own work.	    **
*********************************************************************/

#include <map>
#include <vector>
#include <iostream>

#include "Trackable.h"

#include "BufferFlags.h"

#include "Color.h"
#include "GraphicsBuffer.h"
#include "GraphicsBufferManager.h"

// Constructor.
GraphicsBufferManager::GraphicsBufferManager()
{
	return;
}

// Destructor.
GraphicsBufferManager::~GraphicsBufferManager()
{
	return;
}

// Clean up all the buffers.
void GraphicsBufferManager::cleanUp()
{
	clear();

	return;
}

// Add a graphics buffer to the buffer map.
void GraphicsBufferManager::addBuffer(std::string _name, GraphicsBuffer * _pBuffer)
{
	mBuffers.insert(std::pair<std::string, GraphicsBuffer*>(_name, _pBuffer));

	return;
}

// Delete a graphics buffer from the buffer map.
void GraphicsBufferManager::deleteBuffer(std::string _name)
{
	mBuffers.erase(_name);

	return;
}

// Get a graphics buffer from the buffer map.
GraphicsBuffer* GraphicsBufferManager::getBuffer(std::string _name)
{
	return mBuffers.find(_name)->second;
}

// Clear all the buffers from the map.
void GraphicsBufferManager::clear()
{
	for (std::map<std::string, GraphicsBuffer*>::iterator iterator = mBuffers.begin(); iterator != mBuffers.end(); ++iterator)
	{
		if (iterator->second != nullptr)
		{
			delete iterator->second;
		}

		iterator->second = nullptr;
	}

	return;
}