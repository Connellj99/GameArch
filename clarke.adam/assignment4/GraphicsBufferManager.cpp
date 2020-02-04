#include "GraphicsBufferManager.h"

GraphicsBufferManager::GraphicsBufferManager()
{
}

GraphicsBufferManager::GraphicsBufferManager(std::map<BufferKey, GraphicsBuffer*>& graphicsBuffers)
	:mGraphicsBuffers(graphicsBuffers)
{
}

GraphicsBufferManager::~GraphicsBufferManager()
{
	clear();
}

void GraphicsBufferManager::createGraphicsBuffer(const BufferKey& key, const std::string& filename)
{
	mGraphicsBuffers[key] = new GraphicsBuffer(filename);
}

void GraphicsBufferManager::createGraphicsBuffer(const BufferKey& key, const Vector2D& dimensions, const Color& color)
{
	mGraphicsBuffers[key] = new GraphicsBuffer(dimensions, color);
}

void GraphicsBufferManager::addGraphicsBuffer(const BufferKey& key, GraphicsBuffer* graphicsBuffer, bool isMine)
{
	if(isMine)
	{
		mGraphicsBuffers[key] = graphicsBuffer;
	}
	else
	{
		mUnownedGraphicsBuffers[key] = graphicsBuffer;
	}
}

GraphicsBuffer* GraphicsBufferManager::getGraphicsBuffer(const BufferKey& key)
{
	GraphicsBuffer* graphicsBuffer = nullptr;
	graphicsBuffer = mGraphicsBuffers[key];
	if(graphicsBuffer)
	{
		return graphicsBuffer;
	}
	graphicsBuffer = mUnownedGraphicsBuffers[key];
	if(graphicsBuffer)
	{
		return graphicsBuffer;
	}
	return graphicsBuffer;
}

void GraphicsBufferManager::deleteGraphicsBuffer(const BufferKey& key)
{
	delete mGraphicsBuffers[key];
	mGraphicsBuffers.erase(key);
}

void GraphicsBufferManager::clear()
{
	for (const auto& pair : mGraphicsBuffers)
	{
		delete pair.second;
	}
	mGraphicsBuffers.clear();
	mUnownedGraphicsBuffers.clear();
}
