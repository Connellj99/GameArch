#ifndef Game_h
#define Game_h

#include "PerformanceTracker.h"
#include "Trackable.h"
#include "System.h"
#include "UnitManager.h"
#include "Unit.h"
#include "GraphicsBufferManager.h"
#include "InputTranslator.h"

//Consts for allegro's keyboard inputs
const int RIGHTCLICKED_KEYCODE = 2;
const int ESCAPE_KEYCODE = 59;
const int F_KEYCODE = 6;
const int S_KEYCODE = 19;
const int ENTER_KEYCODE = 67;
const int LEFTCLICK_KEYCODE = 1;
const int SPACE_BAR_KEYCODE = 75;
//Display dimensions
const int DISP_WIDTH = 800;
const int DISP_HEIGHT = 600;
//Asset paths
const std::string ASSET_PATH = "..\\..\\shared\\assets\\";
const std::string SMURFS_FILENAME = "smurf_sprites.png";
const std::string WOODS_FILENAME = "Woods.png";
const std::string DEAN_SMURFS_FILENAME = "dean_sprites.png";
//sleep time
const double SLEEP_TIME = 5.0;

const double ANIMATION_TIME_ADJUSTMENT = 1.0;
const double FRAME_RATE = 16.7;
const float SMURF_ROWS = 4.0f;
const float SMURF_COLS = 4.0f;


class Game : public EventListener
{
public:
	static Game* getInstance();
	static void initInstance(EventSystem* eventSys);
	static void cleanUpInstance();
	
	void initGame(int dispHeight, int dispWidth);
	void cleanUpGame();
	void doLoop();

	int input();
	void update();
	void draw();

	System* getSystem();
	
	virtual void calledEvent(const Event& event);
private:
	Game(EventSystem* eventSys);
	~Game();
	static Game* mpGameInstance;
	System* mpSystem;
	Timer* mpTimer;
	bool mShutDown;
	int mInputChoice;
	InputTranslator* mInputTrans;

	UnitManager* mpUnitHolder;
	GraphicsBufferManager* mpGraphicsBufferHolder;
	std::vector<Sprites*> mSmurfVector;
	std::vector<Sprites*> mDeanSmurfVector;
};
#endif // !Game_h
