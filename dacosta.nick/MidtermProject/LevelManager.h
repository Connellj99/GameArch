#pragma once

typedef std::string LevelKey;

class LevelManager :
	public Trackable
{
public:
	// Constructor.
	LevelManager();

	// Destructor.
	~LevelManager();

	// Clean up the manager.
	void cleanUp();

	// Update the level.
	void update(double _deltaTime);

	// Add a new unit to the list.
	void addLevel(LevelKey _key, Level* _pLevel);

	// Get the current level.
	Level* getLevel();

	// Get the specified level.
	bool getLevel(LevelKey _key, Level* _level);

	// Check if the level exists.
	bool getLevel(LevelKey _key);

	void setLevel(LevelKey _key);

	void draw(GraphicsSystem* _pGraphicsSystem);

	void swapLevel();

	// Draw each wall to the screen.
	//void draw(GraphicsSystem* _pGraphicsSystem);

	// Update each unit's animation.
	//virtual void update(double _deltaTime);

	// Clear the map.
	void clear();

	bool checkPLayerSize(int _currentSize);

	void drawHUD(GraphicsSystem* _pGraphicsSystem, int _score, Font& _font, Color& _color);

private:
	// List of created levels.
	std::map<LevelKey, Level*> mmLevels;

	LevelKey mCurrentLevel = "Main Menu";

	void changeLevel();

	void changeLevel(LevelKey _level);
};

