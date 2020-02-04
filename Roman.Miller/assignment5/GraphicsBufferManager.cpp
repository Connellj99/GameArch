#include "GraphicsBufferManager.h"
using namespace std;
GraphicsBufferManager::GraphicsBufferManager()
{
}

GraphicsBufferManager::GraphicsBufferManager(GraphicsBuffer * backBuffer)
{
	mpBackBuffer = backBuffer;
}

GraphicsBufferManager::~GraphicsBufferManager()
{
	for (auto x : mpMap)
	{
		delete x.second;
		x.second = nullptr;
	}
	mpBackBuffer = nullptr;
}

void GraphicsBufferManager::addBuffer(string name, GraphicsBuffer * buffer)
{
	mpMap.insert({ name, buffer });
}

void GraphicsBufferManager::deleteBuffer(string name)
{
	mpMap.erase(name);
}

GraphicsBuffer * GraphicsBufferManager::getBuffer(string name)
{
	return mpMap[name];
}

GraphicsBuffer * GraphicsBufferManager::getBuffer()
{
	return mpBackBuffer;
}
