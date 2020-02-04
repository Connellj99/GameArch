#include "GraphicsBufferManager.h"



// This function is the default constructor for the class
GraphicsBufferManager::GraphicsBufferManager()
{
}





// This function is the destructor for the class
GraphicsBufferManager::~GraphicsBufferManager()
{
	removeAllBuffers();
}





// This function creates and adds a graphics buffer to the manager vector based on the
// given bitmap file path and given name for said graphics buffer
void GraphicsBufferManager::addBuffer( string bitmapFilePath, GraphicsBufferKey name ) 
{
	mBuffers.push_back( new GraphicsBuffer(bitmapFilePath, name) );
}





// This function gets and returns a graphics buffer based
// on a given name of the graphics buffer
GraphicsBuffer* GraphicsBufferManager::getBuffer( GraphicsBufferKey name ) 
{
	for ( int i = 0, max = mBuffers.size(); i < max; i++ ) 
	{
		// Does the buffer name equal the name to be searched
		if ( mBuffers[i]->mName == name ) 
		{
			// If yes, return said graphics buffer
			return mBuffers[i];
		}
	}

	// If nothing has been found, return a null value
	return nullptr;
}





// This function deletes a buffer based on a given name
void GraphicsBufferManager::deleteBuffer( GraphicsBufferKey name ) 
{
	for ( int i = 0, max = mBuffers.size(); i < max; i++ )
	{
		// Is the current buffer name the same
		// as the given name?
		if ( mBuffers[i]->mName == name )
		{
			// If yes, then delete said buffer
			delete mBuffers[i];
		}
	}
}





// This function removes all of the Graphics buffers
// from the Graphics buffer list
void GraphicsBufferManager::removeAllBuffers() 
{
	for ( int i = 0, max = mBuffers.size(); i < max; i++ )
	{
		delete mBuffers[i];
	}
}