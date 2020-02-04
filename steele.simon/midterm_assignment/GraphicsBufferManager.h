#ifndef GRAPHICSBUFFERMANAGER_H
#define GRAPHICSBUFFERMANAGER_H

// Graphics Library Includes
#include <GraphicsBuffer.h>

// Standard Library Includes
#include <vector>

typedef string GraphicsBufferKey;

class GraphicsBufferManager: public Trackable
{
public:
	// Constructors
	GraphicsBufferManager();

	// Destructors
	~GraphicsBufferManager();

	// Acessors
	GraphicsBuffer* getBuffer( GraphicsBufferKey name );
	
	// Mutators
	void addBuffer( string bitmapFilePath, GraphicsBufferKey name );
	void deleteBuffer( GraphicsBufferKey name );
	void removeAllBuffers();

private:

	// Vectors
	vector<GraphicsBuffer*> mBuffers;

};

#endif // !GRAPHICSBUFFERMANAGER_H

