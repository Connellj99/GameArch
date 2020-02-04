#ifndef GraphicsBufferManager_h
#define GraphicsBufferManager_h

#include "Trackable.h"
#include "System.h"
#include <map>
#include <string>

enum key : int 
{
	WOODS,
	SMURF,
	DEAN
};

typedef std::string Key;
class GraphicsBufferManager : public Trackable
{
public:
	GraphicsBufferManager();
	~GraphicsBufferManager();

	GraphicsBuffer* addGraphicsBuffer(std::string filePath, const Key& key);
	GraphicsBuffer* getGraphicsBuffer(Key key);

	void clear();
	void removeGraphicsBuffer(const Key& key);

private:
	std::map<Key, GraphicsBuffer*> mGraphicsBuffersMap;
};
#endif // !GraphicsBufferManager_h
