/*********************************************************************
**		Author:	Nick DaCosta										**
**		Class: 310 <Section 01>										**
**		Assignment: pa 4											**
**		Certification of Authenticity:								**
**		I certify that this assignment is entirely my own work.	    **
*********************************************************************/

#pragma once

typedef std::string bufferKey;

/// <summary>
///		Manages all the graphics buffers.
/// </summary>
/// <seealso cref="Trackable" />
class GraphicsBufferManager :
	public Trackable
{
public:
	// Constructor.
	GraphicsBufferManager();

	// Destructor.
	~GraphicsBufferManager();

	// Clean up all the buffers.
	void cleanUp();

	// Add a graphics buffer to the buffer map.
	void addBuffer(std::string _name, GraphicsBuffer* _pBuffer);

	// Delete a graphics buffer from the buffer map.
	void deleteBuffer(std::string _name);

	// Get a graphics buffer from the buffer map.
	GraphicsBuffer* getBuffer(std::string _name);

	// Clear all the buffers from the map.
	void clear();

private:
	// Map of all the buffers.
	std::map<std::string, GraphicsBuffer*> mBuffers;
};