#include <iostream>
#include <cassert>
#include <string>

#include <PerformanceTracker.h>
#include <MemoryTracker.h>

#include <GraphicsSystem.h>
#include <GraphicsBuffer.h>
#include <Sprite.h>
#include <Font.h>

using namespace std;

int main()
{

	PerformanceTracker* pPerformanceTracker = new PerformanceTracker;
	
	const string INIT_TRACKER_NAME = "init";
	const string DRAW_TRACKER_NAME = "draw";
	const string WAIT_TRACKER_NAME = "wait";

	pPerformanceTracker->startTracking(INIT_TRACKER_NAME);
	
	const double STEP_SCALE = 0.66;
	const int STEP_LOCATION = 130;
	const int RED_LOCATION = 0;
	const int WIDTH = 800;
	const int HEIGHT = 600;

	GraphicsSystem* gSystem = new GraphicsSystem(WIDTH, HEIGHT);

	GraphicsBuffer* gBufferOne = new GraphicsBuffer("steps.png");
	Sprite* stepsBG = new Sprite(gBufferOne, 0, 0, WIDTH, HEIGHT);

	GraphicsBuffer* gBufferTwo = new GraphicsBuffer("smurf_sprites.png");
	Sprite* smurfBG = new Sprite(gBufferTwo, 0, 0, WIDTH, HEIGHT);

	GraphicsBuffer* gBufferThree = new GraphicsBuffer(255, 0, 0);
	Sprite* redBG = new Sprite(gBufferThree, 0, 0, WIDTH, HEIGHT);
	
	Font* font = new Font(32);
	string badSmurf = "Curse you Papa Smurf!";

	const string BACKBUFFER_FILENAME = "backbuffer.jpg";
	const string RED_SCREEN_FILENAME = "redbuffer.jpg";

	pPerformanceTracker->stopTracking(INIT_TRACKER_NAME); // end of init
	pPerformanceTracker->startTracking(DRAW_TRACKER_NAME);

	gSystem->WriteText(redBG->getBuffer(), 0, 0, font, 0, 0, 0, badSmurf);

	gSystem->Draw(RED_LOCATION, RED_LOCATION, redBG);
	gSystem->Draw(STEP_LOCATION, STEP_LOCATION, stepsBG, STEP_SCALE);
	gSystem->DrawSmurfs(smurfBG);

	gSystem->SaveBuffer(BACKBUFFER_FILENAME);
	gSystem->SaveBuffer(redBG->getBuffer(), RED_SCREEN_FILENAME);

	gSystem->Flip();

	pPerformanceTracker->stopTracking(DRAW_TRACKER_NAME); // end of draw
	pPerformanceTracker->startTracking(WAIT_TRACKER_NAME); // start wait
	gSystem->ExitApplication();
	pPerformanceTracker->stopTracking(WAIT_TRACKER_NAME); // end wait

	// begin destructors

	delete font;
	delete stepsBG;
	delete smurfBG;
	delete redBG;
	delete gSystem;

	cout << endl << "Time to Init:" << pPerformanceTracker->getElapsedTime(INIT_TRACKER_NAME) << " ms" << endl;
	cout << endl << "Time to Draw:" << pPerformanceTracker->getElapsedTime(DRAW_TRACKER_NAME) << " ms" << endl;
	cout << endl << "Time spent waiting:" << pPerformanceTracker->getElapsedTime(WAIT_TRACKER_NAME) << " ms" << endl;

	delete pPerformanceTracker;

	MemoryTracker::getInstance()->reportAllocations(cout);


	system("pause");

	return 0;

}