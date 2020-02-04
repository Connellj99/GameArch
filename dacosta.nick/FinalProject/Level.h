#pragma once

class Level :
	public Trackable
{
public:
	Level();

	// Constructor.
	Level(std::vector<int> _layout, int _rows, int _columns, int _cellWidth, int _cellHeight, int _playerStartLength, int _playerX, int _playerY, double _playerSpeed, int _playerEndLength, int _foodPoints, int _powerUpFrequency);

	// Destructor.
	~Level();

	void getLayout(int* _layout);

	std::multimap<int, int> getWallLocations();

	std::multimap<int, int> getCollectableLocations();

	std::multimap<int, int> getPowerUpLocations();

	// Check for wall collisions at the given grid coordinates.
	bool checkCollision(int _coordinateX, int _coordinateY);

	// Add a segment location of the player.
	void addPlayerLocation(int _coordinateX, int _coordinateY);

	// Remove a segment location of the player.
	void removePlayerLocation(int _coordinateX, int _coordinateY);

	// Get an empty level location.
	void getEmptyLocation(int& _coordinateX, int& _coordinateY);

	void draw(GraphicsSystem* _pGraphicsSystem);

	int getPlayerStartX();

	int getPlayerStartY();

	int getPlayerStartLength();

	double getPlayerSpeed();

	int getPlayerEndLength();

	int getFoodPoints();

	int getPowerUpFrequency();

	void getCellDimensions(int& _width, int& _height);

	void getGridDimensions(int& _width, int& _height);


private:
	std::multimap<int, int> mmWallLocations;
	std::multimap<int, int> mmEmptyLocations;
	std::multimap<int, int> mmPlayerLocations;
	std::multimap<int, int> mmCollectableLocations;
	std::multimap<int, int> mmPowerUpLocations;

	int mCellWidth = 0;

	int mCellHeight = 0;

	int mRows = 0;

	int mColumns = 0;

	int mPlayerStartLength = 3;

	int mPlayerStartX = 10;

	int mPlayerStartY = 10;

	double mPlayerSpeed = 0.2;

	int mPlayerEndLength = 10;

	int mFoodPoints = 10;

	int mPowerUpFrequency = 60;

};

