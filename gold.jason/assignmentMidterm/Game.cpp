#include<cstdlib>
#include<ctime>
#include<fstream>
#include<string>
#include "Game.h"
#include "GameEvent.h"
#include "EventSystem.h"

Game* Game::mpGameInstance = nullptr;

Game::Game(EventSystem* eventSys):EventListener(eventSys)
{

}

void Game::calledEvent(const Event & event)
{
	int x = mSnakeHolder->getX();
	int y = mSnakeHolder->getY();
	int size = mSnakeHolder->getSize();

	if (event.getType() == (EventType)R_KEY)
	{
		restart();
	}
	else if (event.getType() == (EventType)LEFT_KEY)
	{
		if(mLastDirection == 0 || mLastDirection == 3)
		{
			x -= (size / 1.4);
			if (x < 0)
			{
				x += size;
			}
			mSnakeHolder->setX(x);
			cout << "Pressed Left Arrow!" << endl;
			mLastDirection = 1;
		}
	}
	else if (event.getType() == (EventType)RIGHT_KEY)
	{
		if(mLastDirection == 0 || mLastDirection == 3)
		{
			x += (size / 1.4);
			if (x > 800)
			{
				x -= size;
			}
			mSnakeHolder->setX(x);
			cout << "Pressed Right Arrow!" << endl;
			mLastDirection = 2;
		}
	}
	else if (event.getType() == (EventType)UP_KEY)
	{
		if(mLastDirection == 1 || mLastDirection == 2)
		{
			y -= (size / 1.4);
			if (y < 0)
			{
				y += size;
			}
			mSnakeHolder->setY(y);
			cout << "Pressed Up Arrow!" << endl;
			mLastDirection = 3;
		}
	}
	else if (event.getType() == (EventType)DOWN_KEY)
	{
		if(mLastDirection == 1 || mLastDirection == 2)
		{
			y += (size / 1.4);
			if (y > 600)
			{
				y -= size;
			}
			mSnakeHolder->setY(y);
			cout << "Pressed Down Arrow!" << endl;
			mLastDirection = 0;
		}
	}
	else if(event.getType() == (EventType)SPACE_KEY)
	{
		if(notStarted == true)
		{
			notStarted = false;
			mLastDirection = 0;
		}
	}
	else if (event.getType() == (EventType)N_KEY)
	{
		cout << "NEXT" << endl;
		nextLevel();
	}
	else if (event.getType() == (EventType)EXIT)
	{
		mShutDown = true;
		cout << "End of Line" << endl;
	}
}

Game::~Game()
{
	cleanUpGame();
}

Game * Game::getInstance()
{
	assert(mpGameInstance != nullptr);
	return mpGameInstance;
}

void Game::initInstance(EventSystem* eventSys)
{
	mpGameInstance = new Game(eventSys);
	eventSys->addListener((EventType)LEFT_KEY, mpGameInstance);
	eventSys->addListener((EventType)RIGHT_KEY, mpGameInstance);
	eventSys->addListener((EventType)UP_KEY, mpGameInstance);
	eventSys->addListener((EventType)DOWN_KEY, mpGameInstance);
	eventSys->addListener((EventType)R_KEY, mpGameInstance);
	eventSys->addListener((EventType)SPACE_KEY, mpGameInstance);
	eventSys->addListener((EventType)N_KEY, mpGameInstance);
	eventSys->addListener((EventType)EXIT, mpGameInstance);	
}

void Game::cleanUpInstance()
{
	delete mpGameInstance;
}

void Game::initGame(int dispHeight, int dispWidth)
{
	mSnakeHolder = new SnakeManager();
	mpSystem = new System();
	mpTimer = new Timer;
	mpSystem->InitSystem(dispHeight, dispWidth);
	mpGraphicsBufferHolder = new GraphicsBufferManager();
	mInputTrans = new InputTranslator(getEventSystem());
	f1 = new Font();

	string line;
	ifstream myfile("Data.txt");
	if (myfile.is_open())
	{
		getline(myfile, line);

		//reading in asset paths
		getline(myfile, line);
		snakeHeadFileName = line;
		getline(myfile, line);
		snakeBodyFileName = line;
		getline(myfile, line);
		foodFileName = line;
		getline(myfile, line);
		debuffFileName = line;
		getline(myfile, line);
		buffFileName = line;
		getline(myfile, line);
		backgroundFileName = line;
		getline(myfile, line);
		gameOverFileName = line;
		getline(myfile, line);
		wallFileName = line;
		
		getline(myfile, line);
		getline(myfile, line);

		getline(myfile, line);
		scoreMultiplier = stoi(line);

		getline(myfile, line);
		getline(myfile, line);

		getline(myfile, line);
		INCREMENT = stoi(line);
		getline(myfile, line);
		MOVE = stoi(line);

		getline(myfile, line);
		getline(myfile, line);

		//readin buff and debuff affects
		getline(myfile, line);
		buffEffect = stoi(line);
		getline(myfile, line);
		debuffEffect = stoi(line);

		getline(myfile, line);
		getline(myfile, line);
		if(line == "END OF LINE")
		{
			myfile.close();
		}
		else
		{
			cout << "FAILED TO CLOSE FILE" << endl;
		}
	}
	else
	{
		cout << "FAILED TO OPEN FILE" << endl;
	}


	mpGraphicsBufferHolder->addBuffer(foodFileName, "Food");
	mpGraphicsBufferHolder->addBuffer(snakeHeadFileName, "Snake Head");
	mpGraphicsBufferHolder->addBuffer(snakeBodyFileName, "Snake Body");
	mpGraphicsBufferHolder->addBuffer(buffFileName, "Buff");
	mpGraphicsBufferHolder->addBuffer(debuffFileName, "Debuff");
	mpGraphicsBufferHolder->addBuffer(backgroundFileName, "Background");
	mpGraphicsBufferHolder->addBuffer(gameOverFileName, "Game Over");
	mpGraphicsBufferHolder->addBuffer(wallFileName, "Wall");


	//consts for unit's start location
	const float UNIT_STARTX = DISP_WIDTH / 2.0f;
	const float UNIT_STARTY = DISP_HEIGHT / 2.0f;

	red = Color(255, 0, 0);
	black = Color(0, 0, 0);

	red1;

	f1 = new Font();
	f2 = new Font(32);
}

void Game::cleanUpGame()
{
	mpSystem->CleanUpSystem();
	delete mpSystem;
	delete mpTimer;
	delete mpGraphicsBufferHolder;
	mSnakeHolder->cleanUp();
	delete mSnakeHolder;
	delete mInputTrans;
	delete f1;
	delete f2;
//	delete levelSpawns;
}

void Game::doLoop()
{
	mpTimer->start();
	PerformanceTracker* pTracker = new PerformanceTracker();
	pTracker->startTracking("Draw");
	do
	{
		pTracker->clearTracker("Draw");
		pTracker->startTracking("Draw");
		mpTimer->start();

		mInputChoice = input();
		
		if(fps % 30 == 0)
		{
			if(!updateStop)
			{
				update();
				draw();
			}
		}

		mpTimer->sleepUntilElapsed(16.7);
		fps++;
		fpsOutput = mpTimer->getElapsedTime();
		fpsAverage += mpTimer->getElapsedTime();
		pTracker->stopTracking("Draw");
		std::cout << pTracker->getElapsedTime("Draw") << std::endl;

	} while (mShutDown == false);

	delete pTracker;
	pTracker = nullptr;
}

int Game::input()
{
	mpSystem->getInputSys()->update();
	return 0;
}

void Game::levelLoad()
{
	if (level == 1)
	{
		if(firstRun == true)
		{
			wallSpawnsX[0] = 260.0f;
			wallSpawnsX[1] = 320.0f;
			wallSpawnsX[2] = 590.0f;
			wallSpawnsX[3] = 440.0f;
			wallSpawnsX[4] = 640.0f;

			wallSpawnsY[0] = 440.0f;
			wallSpawnsY[1] = 590.0f;
			wallSpawnsY[2] = 260.0f;
			wallSpawnsY[3] = 640.0f;
			wallSpawnsY[4] = 320.0f;
		}

		mpGameInstance->getSystem()->getGraphicsSystem()->draw(mpGraphicsBufferHolder->getGraphicsBuffer("Wall"), 290.0f, 440.0f, 0.05f);
		mpGameInstance->getSystem()->getGraphicsSystem()->draw(mpGraphicsBufferHolder->getGraphicsBuffer("Wall"), 320.0f, 590.0f, 0.05f);
		mpGameInstance->getSystem()->getGraphicsSystem()->draw(mpGraphicsBufferHolder->getGraphicsBuffer("Wall"), 590.0f, 290.0f, 0.05f);
		mpGameInstance->getSystem()->getGraphicsSystem()->draw(mpGraphicsBufferHolder->getGraphicsBuffer("Wall"), 440.0f, 640.0f, 0.05f);
		mpGameInstance->getSystem()->getGraphicsSystem()->draw(mpGraphicsBufferHolder->getGraphicsBuffer("Wall"), 640.0f, 320.0f, 0.05f);
	}
	else if(level == 2)
	{
		if (firstRun == true)
		{
			wallSpawnsX[0] = 540.0f;
			wallSpawnsX[1] = 253.0f;
			wallSpawnsX[2] = 642.0f;
			wallSpawnsX[3] = 198.0f;
			wallSpawnsX[4] = 388.0f;

			wallSpawnsY[0] = 198.0f;
			wallSpawnsY[1] = 642.0f;
			wallSpawnsY[2] = 388.0f;
			wallSpawnsY[3] = 540.0f;
			wallSpawnsY[4] = 253.0f;
		}

		mpGameInstance->getSystem()->getGraphicsSystem()->draw(mpGraphicsBufferHolder->getGraphicsBuffer("Wall"), 540.0f, 198.0f, 0.05f);
		mpGameInstance->getSystem()->getGraphicsSystem()->draw(mpGraphicsBufferHolder->getGraphicsBuffer("Wall"), 253.0f, 642.0f, 0.05f);
		mpGameInstance->getSystem()->getGraphicsSystem()->draw(mpGraphicsBufferHolder->getGraphicsBuffer("Wall"), 642.0f, 388.0f, 0.05f);
		mpGameInstance->getSystem()->getGraphicsSystem()->draw(mpGraphicsBufferHolder->getGraphicsBuffer("Wall"), 198.0f, 540.0f, 0.05f);
		mpGameInstance->getSystem()->getGraphicsSystem()->draw(mpGraphicsBufferHolder->getGraphicsBuffer("Wall"), 388.0f, 253.0f, 0.05f);
	}
	else if (level == 3)
	{
		if (firstRun == true)
		{
			wallSpawnsX[0] = 602.0f;
			wallSpawnsX[1] = 315.0f;
			wallSpawnsX[2] = 563.0f;
			wallSpawnsX[3] = 264.0f;
			wallSpawnsX[4] = 425.0f;

			wallSpawnsY[0] = 264.0f;
			wallSpawnsY[1] = 425.0f;
			wallSpawnsY[2] = 315.0f;
			wallSpawnsY[3] = 563.0f;
			wallSpawnsY[4] = 602.0f;
		}

		mpGameInstance->getSystem()->getGraphicsSystem()->draw(mpGraphicsBufferHolder->getGraphicsBuffer("Wall"), 602.0f, 264.0f, 0.05f);
		mpGameInstance->getSystem()->getGraphicsSystem()->draw(mpGraphicsBufferHolder->getGraphicsBuffer("Wall"), 315.0f, 425.0f, 0.05f);
		mpGameInstance->getSystem()->getGraphicsSystem()->draw(mpGraphicsBufferHolder->getGraphicsBuffer("Wall"), 563.0f, 315.0f, 0.05f);
		mpGameInstance->getSystem()->getGraphicsSystem()->draw(mpGraphicsBufferHolder->getGraphicsBuffer("Wall"), 264.0f, 563.0f, 0.05f);
		mpGameInstance->getSystem()->getGraphicsSystem()->draw(mpGraphicsBufferHolder->getGraphicsBuffer("Wall"), 425.0f, 602.0f, 0.05f);
	}
	else
	{
		cout << "WALLS ARE ALREADY MADE" << endl;
	}
}

void Game::update()
{	
	if(start == true)
	{
		start = false;
		mpGameInstance->getSystem()->getGraphicsSystem()->draw(mpGraphicsBufferHolder->getGraphicsBuffer("Snake Head"), mSnakeHolder->getX(), mSnakeHolder->getY(), 0.05f);
	}

	//draw background
	mpGameInstance->getSystem()->getGraphicsSystem()->draw(mpGraphicsBufferHolder->getGraphicsBuffer("Background"), 0, 0, 20.0f);

	if(foodOnScreen == false)
	{
		newFood();
		foodOnScreen = true;
	}

	directionCheck();

	checkCollision();

	levelLoad();

	hud();

	if(buff)
	{
		spawnBuff();
		buffCollision();
	}

	if(debuff)
	{
		spawnDebuff();
		debuffCollision();
	}

	firstRun = false;
}

 void Game::hud()
 {
	 if(firstRun == false)
	 {
		 if(notStarted == true)
		 {
			 mpGameInstance->getSystem()->getGraphicsSystem()->WriteTextF(f2, black, "PRESS SPACE BAR TO START", 200.0f, 300.0f);
		 }

		 //displays the number of lives the player has left
		 mpGameInstance->getSystem()->getGraphicsSystem()->WriteTextF1(f1, red1, "Lives: ", 0.0f, 0.0f);
		 mpGameInstance->getSystem()->getGraphicsSystem()->WriteTextF(f1, red, to_string(lives), 65.0f, 0.0f);

		 //displays the player's score
		 mpGameInstance->getSystem()->getGraphicsSystem()->WriteTextF(f1, red, "Score: ", 100.0f, 0.0f);
		 int outputScore = totalScore * scoreMultiplier;
		 mpGameInstance->getSystem()->getGraphicsSystem()->WriteTextF(f1, red, to_string((outputScore)), 160.0f, 0.0f);

		 //display the current number of frames per second
		 mpGameInstance->getSystem()->getGraphicsSystem()->WriteTextF(f1, red, "FPS: ", 200.0f, 0.0f);
		 double fpsOut = 1000.0 / fpsOutput;
		 mpGameInstance->getSystem()->getGraphicsSystem()->WriteTextF(f1, red, to_string((fpsOut)), 260.0f, 0.0f);

		 //mpGameInstance->getSystem()->getGraphicsSystem()->flip_Display();

		 //displays the average fps
		 //mpGameInstance->getSystem()->getGraphicsSystem()->WriteTextF(f1, black, "Average FPS: ", 300.0f, 0.0f);
		 //mpGameInstance->getSystem()->getGraphicsSystem()->WriteTextF(f1, black, to_string((1000 / fpsAverage)), 420.0f, 0.0f);
	 }
 }

 void Game::buffCollision()
 {
	 if (buff)
	 {
		 for (int i = 0; i < 21; i++)
		 {
			 for (int j = 0; j < 21; j++)
			 {
				 if (level == 1)
				 {
					 if (mSnakeHolder->getX() + i == 200.0f && mSnakeHolder->getY() + j == 250.0f)
					 {
						 buff = false;
						 INCREMENT = INCREMENT * buffEffect;
						 MOVE = MOVE * buffEffect;
					 }
					 else if (mSnakeHolder->getX() - i == 200.0f && mSnakeHolder->getY() + j == 250.0f)
					 {
						 buff = false;
						 INCREMENT = INCREMENT * buffEffect;
						 MOVE = MOVE * buffEffect;
					 }
					 else if (mSnakeHolder->getX() + i == 200.0f && mSnakeHolder->getY() - j == 250.0f)
					 {
						 buff = false;
						 INCREMENT = INCREMENT * buffEffect;
						 MOVE = MOVE * buffEffect;
					 }
					 else if (mSnakeHolder->getX() - i == 200.0f && mSnakeHolder->getY() - j == 250.0f)
					 {
						 buff = false;
						 INCREMENT = INCREMENT * buffEffect;
						 MOVE = MOVE * buffEffect;
					 }
				 }
				 if (level == 2)
				 {
					 if (mSnakeHolder->getX() + i == 600.0f && mSnakeHolder->getY() + j == 550.0f)
					 {
						 buff = false;
						 INCREMENT = INCREMENT * buffEffect;
						 MOVE = MOVE * buffEffect;
					 }
					 else if (mSnakeHolder->getX() - i == 600.0f && mSnakeHolder->getY() + j == 550.0f)
					 {
						 buff = false;
						 INCREMENT = INCREMENT * buffEffect;
						 MOVE = MOVE * buffEffect;
					 }
					 else if (mSnakeHolder->getX() + i == 600.0f && mSnakeHolder->getY() - j == 550.0f)
					 {
						 buff = false;
						 INCREMENT = INCREMENT * buffEffect;
						 MOVE = MOVE * buffEffect;
					 }
					 else if (mSnakeHolder->getX() - i == 600.0f && mSnakeHolder->getY() - j == 550.0f)
					 {
						 buff = false;
						 INCREMENT = INCREMENT * buffEffect;
						 MOVE = MOVE * buffEffect;
					 }
				 }
				 if (level == 3)
				 {
					 if (mSnakeHolder->getX() + i == 400.0f && mSnakeHolder->getY() + j == 500.0f)
					 {
						 buff = false;
						 INCREMENT = INCREMENT * buffEffect;
						 MOVE = MOVE * buffEffect;
					 }
					 else if (mSnakeHolder->getX() - i == 400.0f && mSnakeHolder->getY() + j == 500.0f)
					 {
						 buff = false;
						 INCREMENT = INCREMENT * buffEffect;
						 MOVE = MOVE * buffEffect;
					 }
					 else if (mSnakeHolder->getX() + i == 400.0f && mSnakeHolder->getY() - j == 500.0f)
					 {
						 buff = false;
						 INCREMENT = INCREMENT * buffEffect;
						 MOVE = MOVE * buffEffect;
					 }
					 else if (mSnakeHolder->getX() - i == 400.0f && mSnakeHolder->getY() - j == 500.0f)
					 {
						 buff = false;
						 INCREMENT = INCREMENT * buffEffect;
						 MOVE = MOVE * buffEffect;
					 }
				 }
			 }
		 }
	 }
 }

 void Game::debuffCollision()
 {

	 if (debuff)
	 {
		 for (int i = 0; i < 21; i++)
		 {
			 for (int j = 0; j < 21; j++)
			 {
				 if (level == 1)
				 {
					 if (mSnakeHolder->getX() + i == 400.0f && mSnakeHolder->getY() + j == 500.0f)
					 {
						 debuff = false;
						 INCREMENT = INCREMENT / debuffEffect;
						 MOVE = MOVE / debuffEffect;
					 }
					 else if (mSnakeHolder->getX() - i == 400.0f && mSnakeHolder->getY() + j == 500.0f)
					 {
						 debuff = false;
						 INCREMENT = INCREMENT / debuffEffect;
						 MOVE = MOVE / debuffEffect;
					 }
					 else if (mSnakeHolder->getX() + i == 400.0f && mSnakeHolder->getY() - j == 500.0f)
					 {
						 debuff = false;
						 INCREMENT = INCREMENT / debuffEffect;
						 MOVE = MOVE / debuffEffect;
					 }
					 else if (mSnakeHolder->getX() - i == 400.0f && mSnakeHolder->getY() - j == 500.0f)
					 {
						 debuff = false;
						 INCREMENT = INCREMENT / debuffEffect;
						 MOVE = MOVE / debuffEffect;
					 }
				 }
				 if (level == 2)
				 {
					 if (mSnakeHolder->getX() + i == 200.0f && mSnakeHolder->getY() + j == 250.0f)
					 {
						 debuff = false;
						 INCREMENT = INCREMENT / debuffEffect;
						 MOVE = MOVE / debuffEffect;
					 }
					 else if (mSnakeHolder->getX() - i == 200.0f && mSnakeHolder->getY() + j == 250.0f)
					 {
						 debuff = false;
						 INCREMENT = INCREMENT / debuffEffect;
						 MOVE = MOVE / debuffEffect;
					 }
					 else if (mSnakeHolder->getX() + i == 200.0f && mSnakeHolder->getY() - j == 250.0f)
					 {
						 debuff = false;
						 INCREMENT = INCREMENT / debuffEffect;
						 MOVE = MOVE / debuffEffect;
					 }
					 else if (mSnakeHolder->getX() - i == 200.0f && mSnakeHolder->getY() - j == 250.0f)
					 {
						 debuff = false;
						 INCREMENT = INCREMENT / debuffEffect;
						 MOVE = MOVE / debuffEffect;
					 }
				 }
				 if (level == 3)
				 {
					 if (mSnakeHolder->getX() + i == 600.0f && mSnakeHolder->getY() + j == 550.0f)
					 {
						 debuff = false;
						 INCREMENT = INCREMENT / debuffEffect;
						 MOVE = MOVE / debuffEffect;
					 }
					 else if (mSnakeHolder->getX() - i == 600.0f && mSnakeHolder->getY() + j == 550.0f)
					 {
						 debuff = false;
						 INCREMENT = INCREMENT / debuffEffect;
						 MOVE = MOVE / debuffEffect;
					 }
					 else if (mSnakeHolder->getX() + i == 600.0f && mSnakeHolder->getY() - j == 550.0f)
					 {
						 debuff = false;
						 INCREMENT = INCREMENT / debuffEffect;
						 MOVE = MOVE / debuffEffect;
					 }
					 else if (mSnakeHolder->getX() - i == 600.0f && mSnakeHolder->getY() - j == 550.0f)
					 {
						 debuff = false;
						 INCREMENT = INCREMENT / debuffEffect;
						 MOVE = MOVE / debuffEffect;
					 }
				 }
			 }
		 }
	 }
 }

void Game::checkCollision()
{
	bool isOnScreen = true;

	if ((0 < mSnakeHolder->getX() && (mSnakeHolder->getX() + (mSnakeHolder->getSize() / 2)) <= (800 - (mSnakeHolder->getSize() / 2))) && (0 < mSnakeHolder->getY() && (mSnakeHolder->getY() + (mSnakeHolder->getSize() / 2)) <= (600 - (mSnakeHolder->getSize() / 2))))
	{
		isOnScreen = true;
	}
	else
	{
		isOnScreen = false;
		cout << "Hit The Wall!" << endl;
	}
	
	if (!isOnScreen)
	{
		lives--;
		if (lives > 0)
		{
			restart();
		}
		else if (lives <= 0)
		{
			gameOver();
		}
	}

	for(int i = 0; i < 21; i++)
	{
		for(int j = 0; j < 21; j++)
		{
			if (mSnakeHolder->getX() + i == foodX && mSnakeHolder->getY() + j == foodY)
			{
				//mpGameInstance->getSystem()->getGraphicsSystem()->draw(mpGraphicsBufferHolder->getGraphicsBuffer("Black Space"), foodX, foodY, 0.10f);
				newFood();
				score++;
				body++;
			}
			else if(mSnakeHolder->getX() - i == foodX && mSnakeHolder->getY() - j == foodY)
			{
				//mpGameInstance->getSystem()->getGraphicsSystem()->draw(mpGraphicsBufferHolder->getGraphicsBuffer("Black Space"), foodX, foodY, 0.10f);
				newFood();
				score++;
				body++;
			}
			else if(mSnakeHolder->getX() - i == foodX && mSnakeHolder->getY() + j == foodY)
			{
				//mpGameInstance->getSystem()->getGraphicsSystem()->draw(mpGraphicsBufferHolder->getGraphicsBuffer("Black Space"), foodX, foodY, 0.10f);
				newFood();
				score++;
				body++;
			}
			else if(mSnakeHolder->getX() + i == foodX && mSnakeHolder->getX() - j == foodY)
			{
				//mpGameInstance->getSystem()->getGraphicsSystem()->draw(mpGraphicsBufferHolder->getGraphicsBuffer("Black Space"), foodX, foodY, 0.10f);
				newFood();
				score++;
				body++;
			}
		}
	}

	for (int i = 0; i < 21; i++)
	{
		for (int j = 0; j < 21; j++)
		{
			for(int h = 0; h < 5; h++)
			{
				if (mSnakeHolder->getX() + i == wallSpawnsX[h] && mSnakeHolder->getY() + j == wallSpawnsY[h])
				{
					wallCollision = true;
				}
				else if (mSnakeHolder->getX() - i == wallSpawnsX[h] && mSnakeHolder->getY() + j == wallSpawnsY[h])
				{
					wallCollision = true;
				}
				else if (mSnakeHolder->getX() + i == wallSpawnsX[h] && mSnakeHolder->getY() - j == wallSpawnsY[h])
				{
					wallCollision = true;
				}
				else if (mSnakeHolder->getX() - i == wallSpawnsX[h] && mSnakeHolder->getY() - j == wallSpawnsY[h])
				{
					wallCollision = true;
				}
			}
		}
	}

	if(wallCollision)
	{
		lives--;
		if (lives > 0) 
		{
			restart();
		}
		else
		{
			gameOver();
		}
	}
}

void Game::restart()
{
	cout << "Restart!" << endl;
	mSnakeHolder->setX(400.0f);
	mSnakeHolder->setY(300.0f);
	level = 1;
	mLastDirection = 4;
	body = 0;
	foodOnScreen;
	start = true;
	firstRun = true;
	death = false;
	notStarted = true;
	wallCollision = false;
	updateStop = false;
	buff = true;
	debuff = true;
	INCREMENT = 30;
	MOVE = 10.0f;
}

void Game::nextLevel()
{
	level++;
	if(level > 3)
	{
		gameOver();
	}
	cout << "Next Level!" << endl;
	mSnakeHolder->setX(400.0f);
	mSnakeHolder->setY(300.0f);
	mLastDirection = 4;
	body = 0;
	score = 0;
	foodOnScreen;
	start = true;
	firstRun = true;
	death = false;
	notStarted = true;
	wallCollision = false;
	updateStop = false;
	buff = true;
	debuff = true;
}


void Game::spawnDebuff()
{
	if (level == 1)
	{
		mpGameInstance->getSystem()->getGraphicsSystem()->draw(mpGraphicsBufferHolder->getGraphicsBuffer("Debuff"), 400.0f, 500.0f, 0.05f);
	}
	else if (level == 2)
	{
		mpGameInstance->getSystem()->getGraphicsSystem()->draw(mpGraphicsBufferHolder->getGraphicsBuffer("Debuff"), 200.0f, 250.0f, 0.05f);
	}
	else if (level == 3)
	{
		mpGameInstance->getSystem()->getGraphicsSystem()->draw(mpGraphicsBufferHolder->getGraphicsBuffer("Debuff"), 600.0f, 550.0f, 0.05f);
	}
}

void Game::spawnBuff()
{
	if (level == 1)
	{
		mpGameInstance->getSystem()->getGraphicsSystem()->draw(mpGraphicsBufferHolder->getGraphicsBuffer("Buff"), 200.0f, 250.0f, 0.05f);
	}
	else if (level == 2)
	{
		mpGameInstance->getSystem()->getGraphicsSystem()->draw(mpGraphicsBufferHolder->getGraphicsBuffer("Buff"), 600.0f, 550.0f, 0.05f);
	}
	else if (level == 3)
	{
		mpGameInstance->getSystem()->getGraphicsSystem()->draw(mpGraphicsBufferHolder->getGraphicsBuffer("Buff"), 400.0f, 500.0f, 0.05f);
	}
}


void Game::newFood()
{
	srand(time(0));

	foodX = rand() % 700 + 100;
	foodY = rand() % 500 + 100;

	mpGameInstance->getSystem()->getGraphicsSystem()->draw(mpGraphicsBufferHolder->getGraphicsBuffer("Food"), foodX, foodY, 0.05f);
}

void Game::directionCheck()
{
	oldX = mSnakeHolder->getX();
	oldY = mSnakeHolder->getY();

	if(oldSpace % 2 == 0)
	{
		oldX2 = oldX;
		oldY2 = oldY;
	}

	if (mLastDirection == 0)
	{
		mSnakeHolder->setY(mSnakeHolder->getY() + INCREMENT);

		//mpGameInstance->getSystem()->getGraphicsSystem()->draw(mpGraphicsBufferHolder->getGraphicsBuffer("Black Space"), oldX - 20.0, oldY - 30.0, 0.10f);

		bodyMove();

		mpGameInstance->getSystem()->getGraphicsSystem()->draw(mpGraphicsBufferHolder->getGraphicsBuffer("Snake Head"), mSnakeHolder->getX(), mSnakeHolder->getY(), 0.05f);

		mpGameInstance->getSystem()->getGraphicsSystem()->draw(mpGraphicsBufferHolder->getGraphicsBuffer("Food"), foodX, foodY, 0.05f);
	}
	else if(mLastDirection == 1)
	{
		mSnakeHolder->setX(mSnakeHolder->getX() - INCREMENT);

		bodyMove();

		mpGameInstance->getSystem()->getGraphicsSystem()->draw(mpGraphicsBufferHolder->getGraphicsBuffer("Snake Head"), mSnakeHolder->getX(), mSnakeHolder->getY(), 0.05f);

		mpGameInstance->getSystem()->getGraphicsSystem()->draw(mpGraphicsBufferHolder->getGraphicsBuffer("Food"), foodX, foodY, 0.05f);
	}
	else if(mLastDirection == 2)
	{
		mSnakeHolder->setX(mSnakeHolder->getX() + INCREMENT);

		bodyMove();

		mpGameInstance->getSystem()->getGraphicsSystem()->draw(mpGraphicsBufferHolder->getGraphicsBuffer("Snake Head"), mSnakeHolder->getX(), mSnakeHolder->getY(), 0.05f);

		mpGameInstance->getSystem()->getGraphicsSystem()->draw(mpGraphicsBufferHolder->getGraphicsBuffer("Food"), foodX, foodY, 0.05f);
	}
	else if(mLastDirection == 3)
	{
		mSnakeHolder->setY(mSnakeHolder->getY() - INCREMENT);

		bodyMove();

		mpGameInstance->getSystem()->getGraphicsSystem()->draw(mpGraphicsBufferHolder->getGraphicsBuffer("Snake Head"), mSnakeHolder->getX(), mSnakeHolder->getY(), 0.05f);

		mpGameInstance->getSystem()->getGraphicsSystem()->draw(mpGraphicsBufferHolder->getGraphicsBuffer("Food"), foodX, foodY, 0.05f);
	}


	oldSpace++;
}

void Game::bodyMove()
{
	if(score > 0)
	{
		if(body == 1)
		{
			mpGameInstance->getSystem()->getGraphicsSystem()->draw(mpGraphicsBufferHolder->getGraphicsBuffer("Snake Body"), oldX, oldY, 0.05f);
		}
		else if(body == 2)
		{
			mpGameInstance->getSystem()->getGraphicsSystem()->draw(mpGraphicsBufferHolder->getGraphicsBuffer("Snake Body"), oldX, oldY, 0.05f);
			mpGameInstance->getSystem()->getGraphicsSystem()->draw(mpGraphicsBufferHolder->getGraphicsBuffer("Snake Body"), oldX2, oldY2, 0.05f);
		}
		else if(score >=3)
		{
			totalScore += score;
			nextLevel();
		}
	}
}

void Game::draw()
{
	mSnakeHolder->drawAll();
	mpSystem->getGraphicsSystem()->flip_Display();
}

System * Game::getSystem()
{
	return mpSystem;
}

void Game::gameOver()
{
	//write text to the screen and pause everything
	string gameOver = "GAME OVER!!!";
	mpGameInstance->getSystem()->getGraphicsSystem()->draw(mpGraphicsBufferHolder->getGraphicsBuffer("Game Over"), -212.0f, -50.0f, 0.3f);
	cout << gameOver << endl;
	death = true;

	if(death == true)
	{
		mpGameInstance->getSystem()->getGraphicsSystem()->flip_Display();
		updateStop = true;
	}
	
	//if lives are 0, R is pressed reset the game otherwise auto reset
}


//old bodyMove function, holding onto it just in case

/*void Game::bodyMove()
{
	if(score > 0)
	{
		if(mLastDirection == 0 || mLastDirection == 3)
		{
			if(mLastDirection == 0)
			{
				if (score == 1)
				{
					//mpGameInstance->getSystem()->getGraphicsSystem()->draw(mpGraphicsBufferHolder->getGraphicsBuffer("Black Space"), mSnakeHolder->getX() - 30.0f, mSnakeHolder->getY() - 60.0f, 0.5f);

					//-30.0f
					mpGameInstance->getSystem()->getGraphicsSystem()->draw(mpGraphicsBufferHolder->getGraphicsBuffer("Snake Body"), oldX, oldY, 0.05f);
				}
				if(score == 2)
				{
					//mpGameInstance->getSystem()->getGraphicsSystem()->draw(mpGraphicsBufferHolder->getGraphicsBuffer("Black Space"), mSnakeHolder->getX()- 30.0f, mSnakeHolder->getY() - 90.0f, 0.25f);

					//mpGameInstance->getSystem()->getGraphicsSystem()->draw(mpGraphicsBufferHolder->getGraphicsBuffer("Snake Body"), mSnakeHolder->getX(), mSnakeHolder->getY() - 30.0f, 0.05f);

					mpGameInstance->getSystem()->getGraphicsSystem()->draw(mpGraphicsBufferHolder->getGraphicsBuffer("Snake Body"), oldX, oldY, 0.05f);

					mpGameInstance->getSystem()->getGraphicsSystem()->draw(mpGraphicsBufferHolder->getGraphicsBuffer("Snake Body"), mSnakeHolder->getX(), mSnakeHolder->getY() - 60.0f, 0.05f);
				}
				if(score >= 3)
				{
					level++;

					if(level > 3)
					{
						gameOver();
					}
				}
			}
			else if(mLastDirection == 3)
			{
				if (score == 1)
				{
					//mpGameInstance->getSystem()->getGraphicsSystem()->draw(mpGraphicsBufferHolder->getGraphicsBuffer("Black Space"), mSnakeHolder->getX() - 30.0f, mSnakeHolder->getY() - 60.0f, 0.5f);

					mpGameInstance->getSystem()->getGraphicsSystem()->draw(mpGraphicsBufferHolder->getGraphicsBuffer("Snake Body"), oldX, oldY, 0.05f);

					//mpGameInstance->getSystem()->getGraphicsSystem()->draw(mpGraphicsBufferHolder->getGraphicsBuffer("Snake Body"), mSnakeHolder->getX(), mSnakeHolder->getY() + 30.0f, 0.05f);
				}
				if (score == 2)
				{
					//mpGameInstance->getSystem()->getGraphicsSystem()->draw(mpGraphicsBufferHolder->getGraphicsBuffer("Black Space"), mSnakeHolder->getX() - 30.0f, mSnakeHolder->getY() - 90.0f, 0.25f);

					//mpGameInstance->getSystem()->getGraphicsSystem()->draw(mpGraphicsBufferHolder->getGraphicsBuffer("Snake Body"), mSnakeHolder->getX() + 30.0f, mSnakeHolder->getY(), 0.05f);

					mpGameInstance->getSystem()->getGraphicsSystem()->draw(mpGraphicsBufferHolder->getGraphicsBuffer("Snake Body"), oldX, oldY, 0.05f);

					mpGameInstance->getSystem()->getGraphicsSystem()->draw(mpGraphicsBufferHolder->getGraphicsBuffer("Snake Body"), mSnakeHolder->getX(), mSnakeHolder->getY() + 60.0f, 0.05f);
				}
				if (score == 3)
				{
					level++;

					if (level > 3)
					{
						gameOver();
					}
				}
			}
		}
		else if(mLastDirection == 1 || mLastDirection == 2)
		{
			if(mLastDirection == 1)
			{
				if (score == 1)
				{
					//mpGameInstance->getSystem()->getGraphicsSystem()->draw(mpGraphicsBufferHolder->getGraphicsBuffer("Black Space"), mSnakeHolder->getX() + 60.0f, mSnakeHolder->getY(), 0.5f);


					mpGameInstance->getSystem()->getGraphicsSystem()->draw(mpGraphicsBufferHolder->getGraphicsBuffer("Snake Body"), oldX, oldY, 0.05f);

					//mpGameInstance->getSystem()->getGraphicsSystem()->draw(mpGraphicsBufferHolder->getGraphicsBuffer("Snake Body"), mSnakeHolder->getX() + 30.0f, mSnakeHolder->getY(), 0.05f);
				}
				if (score == 2)
				{
					//mpGameInstance->getSystem()->getGraphicsSystem()->draw(mpGraphicsBufferHolder->getGraphicsBuffer("Black Space"), mSnakeHolder->getX() + 90.0f, mSnakeHolder->getY(), 0.5f);

					//mpGameInstance->getSystem()->getGraphicsSystem()->draw(mpGraphicsBufferHolder->getGraphicsBuffer("Snake Body"), mSnakeHolder->getX() + 30.0f, mSnakeHolder->getY(), 0.05f);

					mpGameInstance->getSystem()->getGraphicsSystem()->draw(mpGraphicsBufferHolder->getGraphicsBuffer("Snake Body"), oldX, oldY, 0.05f);

					mpGameInstance->getSystem()->getGraphicsSystem()->draw(mpGraphicsBufferHolder->getGraphicsBuffer("Snake Body"), mSnakeHolder->getX() + 60.0f, mSnakeHolder->getY(), 0.05f);
				}
				if (score == 3)
				{
					level++;

					if (level > 3)
					{
						gameOver();
					}
				}
			}
			else if(mLastDirection == 2)
			{
				if (score == 1)
				{
					//mpGameInstance->getSystem()->getGraphicsSystem()->draw(mpGraphicsBufferHolder->getGraphicsBuffer("Black Space"), mSnakeHolder->getX() - 60.0f, mSnakeHolder->getY(), 0.5f);

					mpGameInstance->getSystem()->getGraphicsSystem()->draw(mpGraphicsBufferHolder->getGraphicsBuffer("Snake Body"), oldX, oldY, 0.05f);

					//mpGameInstance->getSystem()->getGraphicsSystem()->draw(mpGraphicsBufferHolder->getGraphicsBuffer("Snake Body"), mSnakeHolder->getX() - 30.0f, mSnakeHolder->getY(), 0.05f);
				}
				if (score == 2)
				{
					//mpGameInstance->getSystem()->getGraphicsSystem()->draw(mpGraphicsBufferHolder->getGraphicsBuffer("Black Space"), mSnakeHolder->getX() - 90.0f, mSnakeHolder->getY(), 0.25f);

					//mpGameInstance->getSystem()->getGraphicsSystem()->draw(mpGraphicsBufferHolder->getGraphicsBuffer("Snake Body"), mSnakeHolder->getX() - 30.0f, mSnakeHolder->getY(), 0.05f);

					mpGameInstance->getSystem()->getGraphicsSystem()->draw(mpGraphicsBufferHolder->getGraphicsBuffer("Snake Body"), oldX, oldY, 0.05f);

					mpGameInstance->getSystem()->getGraphicsSystem()->draw(mpGraphicsBufferHolder->getGraphicsBuffer("Snake Body"), mSnakeHolder->getX() - 60.0f, mSnakeHolder->getY(), 0.05f);
				}
				if (score == 3)
				{
					level++;

					if (level > 3)
					{
						gameOver();
					}
				}
			}
		}
	}
}*/
