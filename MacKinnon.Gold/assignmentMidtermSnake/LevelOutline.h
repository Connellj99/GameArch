#pragma once
#include <string>
#include <vector>
#include "System.h"
#include "UnitManager.h"
#include "EventListener.h"
#include "GraphicsBufferManager.h"
#include "Font.h"
#include "GameEvents.h"
//#include "LevelManager.h"
#include "Vector2D.h"

const std::string ASSET_PATH = "..\\..\\MacKinnon.Gold\\assets\\";
const std::string GAME_FONT = "cour.ttf";
const std::string BACKGROUND_IMAGE = "background_texture.jpg";
const std::string SNAKE_IMAGE = "snake.png";
const std::string WALL_IMAGE = "wallAnimated.png";
const std::string FOOD_IMAGE = "foodAnimated.png";
const std::string SPEED_DOWN_IMAGE = "speedDown.png";
const std::string SPEED_UP_IMAGE = "speedUp.png";
const std::string EXTRA_POINTS_IMAGE = "extraPoints.png";
const std::string BACKGROUND_BUFFER_KEY = "BACKGROUND";
const std::string START_BUFFER_KEY = "START";
const std::string END_BUFFER_KEY = "END";
const std::string SNAKE_BUFFER_KEY = "SNAKE";
const std::string FOOD_BUFFER_KEY = "FOOD";
const std::string SPEED_DOWN_BUFFER_KEY = "DOWN";
const std::string SPEED_UP_BUFFER_KEY = "UP";
const std::string WALL_BUFFER_KEY = "WALL";
const std::string EXTRA_POINTS_BUFFER_KEY = "EXTRA";
const std::string GAME_BUFFER_KEY = "GAME";
const float SCALE_FACTOR = 1.0;
const int DISP_WIDTH = 800;
const int DISP_HEIGHT = 600;

class LevelOutline : public EventListener
{
public:
	LevelOutline();
	~LevelOutline();

	virtual void init(System* system, std::string level);
	void cleanup();
	virtual void update(double time);//probably need to modify
	virtual void reset();
	virtual void drawFrameRate(double frameRate);

	UnitManager* getUnitManager() { return mpUnitManager; };
	GraphicsBufferManager* getGraphicsBufferManager() { return mpGraphicsBufferManager; };
	System* getSystem() { return mpSystem; };

	virtual void handleEvent(const Event& theEvent) = 0;

protected:
	UnitManager* mpUnitManager;
	GraphicsBufferManager* mpGraphicsBufferManager;
	System* mpSystem;

	std::string mLevel;

	bool mIsInit;
};

