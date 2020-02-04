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

GraphicsBuffer* GraphicsBufferManager::getGraphicsBuffer(const BufferKey& key)
{
	GraphicsBuffer* graphicsBuffer = nullptr;
	return mGraphicsBuffers[key];
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
}
