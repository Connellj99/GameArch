/*
Conner Root
EGP 310 - 01
*/

#pragma once

#include <PerformanceTracker.h>

#include "GraphicsBufferManager.h"

// Constructor
GraphicsBufferManager::GraphicsBufferManager()
{

}

// Add units
void GraphicsBufferManager::addBuffer(string filename)
{
	GraphicsBuffer* pTempBuffer = new GraphicsBuffer(filename);
	mpBufferList.push_back(pTempBuffer);
}

// Accessor
int GraphicsBufferManager::findBuffer(string filename)
{
	for (int i = 0; i < (int)mpBufferList.size(); i++)
	{
		if (mpBufferList[i]->getFileName() == filename)
			return i;
	}

	cout << "Error finding buffer";
	return -1;
}

GraphicsBuffer* GraphicsBufferManager::getBuffer(string filename)
{
	return mpBufferList[findBuffer(filename)];
}

// Delete buffer(s)
void GraphicsBufferManager::deleteBuffer(string filename)
{
	delete mpBufferList[findBuffer(filename)];
	mpBufferList.erase(mpBufferList.begin() + findBuffer(filename));
}

void GraphicsBufferManager::deleteAllBuffers()
{
	for each (GraphicsBuffer* g in mpBufferList)
	{
		delete g;
	}
}

// Constructor
GraphicsBufferManager::~GraphicsBufferManager()
{
	deleteAllBuffers();
}