#ifndef GraphicsBufferManager_h
#define GraphicsBufferManager_h

#include "Trackable.h"
#include <vector>
#include "System.h"
#include <map>

enum key : int 
{
	WOODS_BUFFER,
	SMURF_BUFFER,
	DEAN_SMURF_BUFFER
};
typedef std::string Key;

class GraphicsBufferManager : public Trackable
{
public:
	GraphicsBufferManager();
	~GraphicsBufferManager();
	GraphicsBuffer* addBuffer(std::string filename, const Key& ID);
	void removeBuffer(Key key);
	void graphicsBufferManagerCleanUp();
	GraphicsBuffer* getGraphicsBuffer(Key key);
private:
	std::map<Key, GraphicsBuffer*> mGraphicsBufferMap;
};
#endif // !GraphicsBufferManager_h
