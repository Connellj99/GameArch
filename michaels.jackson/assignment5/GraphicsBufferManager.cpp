/*
Author:Jackson Michaels
Class: EGP-310-01
Assignment: Assignment 4
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/
#include "GraphicsBufferManager.h"

GraphicsBufferManager::GraphicsBufferManager()
{

}

GraphicsBufferManager::~GraphicsBufferManager()
{
	this->clear();
}

void GraphicsBufferManager::addBuffer(GraphicsBuffer* buffer, BufferKey name)
{
	if (this->getBuffer(name) == NULL)
	{
		mBuffers.insert(pair<BufferKey, GraphicsBuffer*>(name, buffer));
	}
}

GraphicsBuffer* GraphicsBufferManager::createBuffer(string file, BufferKey name)
{
	GraphicsBuffer* pBuff = NULL;

	//figure out if it exists already
	map<BufferKey, GraphicsBuffer*>::iterator iter = mBuffers.find(name);

	//already in map?
	if (iter == mBuffers.end())
	{
		//not already there - just create and add it
		pBuff = new GraphicsBuffer(file);
		mBuffers[name] = pBuff;
	}

	return pBuff;
}

GraphicsBuffer* GraphicsBufferManager::createBuffer(int wide, int tall, BufferKey name)
{
	GraphicsBuffer* pBuff = NULL;

	//figure out if it exists already
	map<BufferKey, GraphicsBuffer*>::iterator iter = mBuffers.find(name);

	//already in map?
	if (iter == mBuffers.end())
	{
		//not already there - just create and add it
		pBuff = new GraphicsBuffer(wide, tall);
		mBuffers[name] = pBuff;
	}

	return pBuff;
}

GraphicsBuffer* GraphicsBufferManager::addBuffer(BufferKey fileName, BufferKey name)
{
	GraphicsBuffer* newBuff = new GraphicsBuffer(fileName);
	if (this->getBuffer(name) == NULL)
	{
		mBuffers.insert(pair<BufferKey, GraphicsBuffer*>(name, newBuff));
	}
	else
	{
		delete newBuff;
	}
	
	return newBuff;
}

void GraphicsBufferManager::removeBuffer(BufferKey bufferName)
{
	mBuffers.erase(bufferName);
}

GraphicsBuffer* GraphicsBufferManager::getBuffer(BufferKey buffName)
{
	std::map<BufferKey, GraphicsBuffer*>::iterator it;
	it = mBuffers.find(buffName);
	if (it == mBuffers.end())
	{
		return NULL;
	}
	else
	{
		return it->second;
	}
}

void GraphicsBufferManager::clear()
{
	std::map<BufferKey, GraphicsBuffer*>::iterator it;

	for (it = mBuffers.begin(); it != mBuffers.end(); it++)
	{
		delete it->second;
	}
	mBuffers.clear();

}