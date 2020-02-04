#ifndef GRAPHICS_BUFFER_MANAGER_H
#define GRAPHICS_BUFFER_MANAGER_H

#include "Trackable.h"
#include <map>
#include "GraphicsBuffer.h"

typedef std::string BufferKey;

// holds all the GraphicsBuffers in the game
class GraphicsBufferManager : public Trackable
{
public:
	GraphicsBufferManager();
	GraphicsBufferManager(std::map<BufferKey, GraphicsBuffer*>& graphicsBuffers);
	~GraphicsBufferManager();

	void createGraphicsBuffer(const BufferKey& key, const std::string& filename);
	void createGraphicsBuffer(const BufferKey& key, const Vector2D& dimensions, const Color& color);
	void addGraphicsBuffer(const BufferKey& key, GraphicsBuffer* graphicsBuffer);
	GraphicsBuffer* getGraphicsBuffer(const BufferKey& key);
	// frees memory taken by graphics buffer and erases key position in map
	void deleteGraphicsBuffer(const BufferKey& key);

	// remove and delete all GraphicsBuffers 
	void clear();
private:
	std::map<BufferKey, GraphicsBuffer*> mGraphicsBuffers;
};
#endif