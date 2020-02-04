#ifndef HUD_UI_MANAGER_H
#define HUD_UI_MANAGER_H

#include "Trackable.h"
#include "Game.h"

class HudUIManager : public Trackable
{
public:

	//Constructor/Destructor
	HudUIManager();
	~HudUIManager();

	void flipDisplay();//flip the display
	void render();//renders the game
	void renderHUD();//renders the current level counter and the score
	void renderTitleScreen();//render just the beginning "scene"
	void renderNextLevelScreen();//render just the next level "scene"
	void renderEndScreen();//render just the end "scene"
};
#endif