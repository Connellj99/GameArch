/*
Author:Jackson Michaels
Class: EGP-310-01
Assignment: Midterm
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/
#ifndef GAME_H
#define GAME_H

#include "System.h"
#include "UnitManager.h"
#include "InputTranslator.h"
#include "Snake.h"
#include "PowerUp.h"
#include <fstream>
#include <sstream>

struct Wall
{
	Wall(int size = 0, Point loc = Point(0, 0));
	~Wall() { delete sprite; }
	void draw();
	Point loc;
	Sprite* sprite;
}; 

class Level :public Trackable {
public:
	Level(int num, string fileName) { number = num; file = fileName; }

	~Level();

	void loadLevel();

	void drawWalls();

	int setValues(vector<int>);

	int number;
	string file;
	int width;
	int height;
	int blockSize;
	int startLen;
	int targetLen;
	int pointsPerPower;
	int powerFreq;
	vector<Wall*> walls;
	Point start;
};

static class Game : public EventListener
{
public:
	static Game* getInstance() { assert(mpGame != nullptr); return mpGame; };
	static void initInstance(EventSystem* pEventSystem, int fps) { mpGame = new Game(pEventSystem, fps); };
	static void cleanupInstance() { delete mpGame; };

	void init(int = 600, int = 600);
	void cleanUp();

	void handleEvent(const Event& theEvent);

	EventSystem* getEventSystem() { return EventListener::getEventSystem(); }
	void runGame();

	System* getSystem() { return mSystem; };

	void nextLevel(int level = 0);

	void reset();

	bool mPaused = false;

	int mScore;

private:
	Game(EventSystem* pEventSystem, int fps);
	~Game();
	UnitManager* mUnitMan;
	Snake* mSnake;
	GraphicsBufferManager* mGBMan;
	System* mSystem;
	bool mInit = false;
	bool mExit = false;
	double msPerFrame;

	int mLevel = 0;
	int mMaxLevel = 4;
	Level * mpLevelObj;
	string mLevels[5] = {"menu.txt", "level1.txt", "level2.txt", "level3.txt", "menu.txt"};

	void spawnPowerUp();
	void readGraphicsData(string);
	vector<PowerUpObj*> mPowerUps;

	static Game* mpGame;
};

#endif // !GAME_H
