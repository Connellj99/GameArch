#pragma once
#include "Trackable.h"
#include "Font.h"
#include "Color.h"
#include <Vector2D.h>
using namespace std;


class OnScreenText : public Trackable
{
public:
	OnScreenText();
	void Init(Font *font, Color);
	void CleanUp();
	~OnScreenText();

	void Print(int level, int score, int fps);
	void Print(string text);

private:
	Font *mFont = nullptr;
	Vector2D mTextLoc;
	Color mColor;
	const string LEVEL = "Level: ";
	const string SCORE = " Score: ";
	const string FPS = " FPS: ";
};