#ifndef Game_h
#define Game_h

#include <vector>
#include "PerformanceTracker.h"
#include "Trackable.h"
#include "System.h"
#include "SnakeManager.h"
#include "Snake.h"
#include "GraphicsBufferManager.h"
#include "InputTranslator.h"
#include "Font.h"

//Consts for allegro's keyboard inputs
const int RIGHTCLICKED_KEYCODE = 2;
const int ESCAPE_KEYCODE = 59;
const int F_KEYCODE = 6;
const int S_KEYCODE = 19;
const int ENTER_KEYCODE = 67;
const int LEFTCLICK_KEYCODE = 1;
const int SPACE_BAR_KEYCODE = 75;

//Display dimensions
const int DISP_WIDTH = 900;
const int DISP_HEIGHT = 600;

//Asset paths
//moved to data text file

//sleep time
const double SLEEP_TIME = 5.0;

const double FRAME_RATE = 16.7;

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
	void directionCheck();

	void newFood();
	void hud();
	void buffCollision();
	void debuffCollision();
	void restart();
	void nextLevel();

	void spawnDebuff();

	void spawnBuff();

	void bodyMove();

	System* getSystem();

	void checkCollision();
	void levelLoad();

	virtual void calledEvent(const Event& event);
private:
	Game(EventSystem* eventSys);
	~Game();
	static Game* mpGameInstance;
	System* mpSystem;
	Timer* mpTimer;
	bool mShutDown;
	bool foodOnScreen;
	bool start = true;
	bool firstRun = true;
	bool death = false;
	bool notStarted = true;
	bool wallCollision = false;
	bool updateStop = false;
	bool buff = true;
	bool debuff = true;

	int mInputChoice;
	InputTranslator* mInputTrans;
	void gameOver();
	int mLastDirection = 4;
	int level = 1;

	int INCREMENT;
	float MOVE;

	int fpsOutput;
	int fpsAverage;

	string foodFileName;
	string snakeHeadFileName;
	string snakeBodyFileName;
	string buffFileName;
	string debuffFileName;
	string backgroundFileName;
	string gameOverFileName;
	string wallFileName;

	int buffEffect;
	int debuffEffect;
	float wallSpawnsX[5];
	float wallSpawnsY[5];

	int scoreMultiplier;
	int totalScore;


	Font* f1;
	Font* f2;

	int oldX;
	int oldY;
	int oldX2;
	int oldY2;
	int oldSpace;

	int foodX;
	int foodY;

	int body = 0;
	int score;
	int lives = 3;

	int fps;

	Color black;
	Color red;

	ALLEGRO_COLOR red1;

	SnakeManager* mSnakeHolder;
	GraphicsBufferManager* mpGraphicsBufferHolder;
};
#endif // !Game_h
