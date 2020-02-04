#pragma once
#include "LevelOutline.h"
#include "LevelManager.h"

class LevelOutline;


class StartLevel : public LevelOutline
{
public:
	StartLevel();
	~StartLevel();

	void init(System* system, std::string level);
	void cleanup();
	void update(double time);
	void drawText();
	void drawFrameRate(double frameTime);
	
	void handleEvent(const Event& theEvent);

private:
	Font* mpFont;
	Font* mpMessageFont;
	std::string mTitleText = "Welcome To Snake!";
	std::string mMessageText = "Press Space to Start";
	bool mIsInit;
};

