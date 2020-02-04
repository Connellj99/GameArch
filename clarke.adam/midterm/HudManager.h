#ifndef HUD_MANAGER_H
#define HUD_MANAGER_H

#include "Font.h"
#include "GameData.h"
class GraphicsSystem;

class HudManager : public Trackable
{
public:
	HudManager();
	~HudManager();

	void init();
	void cleanup();
	void draw() const;

	void setScore(int newScore) { mScore = newScore; }
	void setLevel(int newLevel) { mLevel = newLevel; }
	void setFps(float newFps) { mFps = newFps; }
	void setLives(int numLives) { mLives = numLives; }
private:
	GraphicsSystem* pGraphicsSystem = nullptr;
	GameData* pGameData = nullptr;

	Font* mpFont = nullptr;
	int mScore = 0;
	int mLevel = 0;
	float mFps = 0;
	int mLives = 0;
};
#endif