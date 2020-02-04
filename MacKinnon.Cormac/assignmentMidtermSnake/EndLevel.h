#pragma once
#include "LevelOutline.h"
#include "LevelManager.h"

class LevelOutline;

 
class EndLevel : public LevelOutline
{
public:
	EndLevel();
	~EndLevel();

	void init(System* system, std::string level);
	void cleanup();
	void update(double time);

	void drawText();
	void drawFrameRate(double frameRate);

	void handleEvent(const Event& theEvent);

private:
	std::string mMessageText = "Press R to Reset or Escape to Quit";
	std::string mTitleText = "Game Over!";
	Font* mpFont;
	Font* mpMessageFont;

	bool mIsInit;
};

