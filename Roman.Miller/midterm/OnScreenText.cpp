#include "OnScreenText.h"
#include "GraphicsSystem.h"
#include "Game.h"
#include <string>

OnScreenText::OnScreenText()
{
}

void OnScreenText::Init(Font * font, Color color)
{
	mFont = font;
	mColor = color;
	mTextLoc = (0, 400);
}

void OnScreenText::CleanUp()
{
	delete mFont;
	mFont = nullptr;
}

OnScreenText::~OnScreenText()
{
}

void OnScreenText::Print(int level, int score, int fps)
{
	string sLevel, sScore, sFps, output;
	output = LEVEL + to_string(level) + SCORE + to_string(score) + FPS + to_string(fps);
	Game::getInstance()->getSystem()->getGraphicsSystem()->writeText(mTextLoc.getX(), mTextLoc.getY(),*mFont, mColor, output);
}

void OnScreenText::Print(string text)
{
	Game::getInstance()->getSystem()->getGraphicsSystem()->writeText(mTextLoc.getX(), mTextLoc.getY(), *mFont, mColor, text);
}
