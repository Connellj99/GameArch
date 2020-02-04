#ifndef SnakeManager_h
#define SnakeManager_h

#include "Trackable.h"
#include <vector>
#include "Snake.h"

using namespace std;

class SnakeManager : public Trackable
{
public:
	SnakeManager();
	~SnakeManager();
	void cleanUp();
	void drawAll();
	void setX(int x);
	void setY(int y);
	int getX();
	int getY();
	int getSize();
private:
	Snake* mSnake;
};
#endif // !SnakeManager_h
