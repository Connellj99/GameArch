
/*
Author:Jackson Michaels
Class: EGP-310-01
Assignment: Assignment 4
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/
#pragma once
#include "GraphicsBuffer.h"
#include <iterator> 
#include <string>
#include <map> 

using namespace std;

typedef std::string BufferKey;

class GraphicsBufferManager : public Trackable
{
public:
	GraphicsBufferManager();
	~GraphicsBufferManager();

	void addBuffer(GraphicsBuffer* buffer, BufferKey name);
	GraphicsBuffer* createBuffer(string file, BufferKey name);
	GraphicsBuffer* createBuffer(int, int, BufferKey name);


	GraphicsBuffer* addBuffer(BufferKey bufferFile, BufferKey name);

	void removeBuffer(BufferKey bufferName);
	GraphicsBuffer* getBuffer(BufferKey buffName);
	void clear();

private:
	map<BufferKey, GraphicsBuffer*> mBuffers;
};